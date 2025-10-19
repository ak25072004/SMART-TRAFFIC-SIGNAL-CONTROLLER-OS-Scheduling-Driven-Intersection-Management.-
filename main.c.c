#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <direct.h>

#define NUM_APPROACH 4
#define DEFAULT_TICK_MS 500
#define JSON_PATH "../data/traffic_data.json"  // Relative to frontend
#define GANTT_LEN 2000

typedef enum { S_RR=0, S_STATIC=1, S_DYNAMIC=2, S_HYBRID=3 } SchedulerType;

typedef struct {
    int id;
    int queue_len;
    double arrival_rate;
    int static_prio;
    double dynamic_prio;
    int served;
    double total_wait;
    int age_ticks;
    int starvation_count;
} Approach;

/* Global state */
Approach approaches[NUM_APPROACH];
CRITICAL_SECTION state_mutex;
long long sim_tick = 0;
SchedulerType scheduler = S_DYNAMIC;
int time_quantum_ticks = 4;
int current_green = -1;
int green_remaining = 0;
int rr_index = 0;
int gantt[GANTT_LEN];
int gantt_pos = 0;
int tick_ms = DEFAULT_TICK_MS;

/* Sleep in ms */
void sleep_ms(int ms) { Sleep(ms); }

/* Poisson arrivals per tick */
int poisson_tick(double rate_per_sec) {
    double mean = rate_per_sec * (tick_ms / 1000.0);
    if (mean <= 0.0) return 0;

    double L = exp(-mean);
    double p = 1.0;
    int k = 0;
    do {
        p *= (double)rand() / RAND_MAX;
        k++;
    } while (p > L && k < 50);

    return k - 1;
}

/* Scheduler functions */
int pick_rr_locked(void) {
    for (int i = 0; i < NUM_APPROACH; ++i) {
        int idx = (rr_index + i) % NUM_APPROACH;
        if (approaches[idx].queue_len > 0) {
            rr_index = (idx + 1) % NUM_APPROACH;
            return idx;
        }
    }
    rr_index = (rr_index + 1) % NUM_APPROACH;
    return rr_index;
}

int pick_static_locked(void) {
    int best = -1, best_p = -999;
    for (int i = 0; i < NUM_APPROACH; ++i) {
        if (approaches[i].queue_len <= 0) continue;
        if (approaches[i].static_prio > best_p) { best_p = approaches[i].static_prio; best = i; }
    }
    return (best==-1)?0:best;
}

int pick_dynamic_locked(void) {
    int best = -1; double best_val = -1e9;
    for (int i=0;i<NUM_APPROACH;i++){
        approaches[i].dynamic_prio = approaches[i].static_prio + approaches[i].age_ticks*0.2;
        if (approaches[i].queue_len<=0) continue;
        if (approaches[i].dynamic_prio>best_val){ best_val=approaches[i].dynamic_prio; best=i;}
    }
    if(best==-1) best=0;
    return best;
}

int pick_hybrid_locked(void) {
    for(int i=0;i<NUM_APPROACH;i++){
        if (approaches[i].age_ticks>50){
            approaches[i].dynamic_prio+=3.0;
            approaches[i].starvation_count++;
        }
    }
    return pick_dynamic_locked();
}

void serve_one_locked(int id){
    if(id<0||id>=NUM_APPROACH) return;
    if(approaches[id].queue_len<=0) return;
    approaches[id].queue_len--;
    approaches[id].served++;
    approaches[id].total_wait += (double)approaches[id].age_ticks;
    approaches[id].age_ticks=0;
}

/* JSON writer thread */
DWORD WINAPI json_writer_thread(LPVOID lpParam){
    (void)lpParam;
    while(1){
        sleep_ms(200);
        EnterCriticalSection(&state_mutex);
        FILE *f=fopen(JSON_PATH,"w");
        if(f){
            fprintf(f,"{\n  \"tick\":%lld,\n  \"current_green\":%d,\n  \"gantt\":[",sim_tick,current_green);
            for(int i=0;i<gantt_pos && i<GANTT_LEN;i++){
                fprintf(f,"%d%s",gantt[i], (i==gantt_pos-1)?"":",");
            }
            fprintf(f,"],\n  \"approaches\":[\n");
            for(int i=0;i<NUM_APPROACH;i++){
                fprintf(f,"    {\"id\":%d,\"queue_len\":%d,\"arrival_rate\":%.2f,\"static_prio\":%d,\"dynamic_prio\":%.2f,\"served\":%d,\"age\":%d,\"starvation\":%d}%s\n",
                    approaches[i].id, approaches[i].queue_len, approaches[i].arrival_rate, approaches[i].static_prio,
                    approaches[i].dynamic_prio, approaches[i].served, approaches[i].age_ticks, approaches[i].starvation_count,
                    (i==NUM_APPROACH-1)?"":",");
            }
            fprintf(f,"  ]\n}\n");
            fflush(f);
            fclose(f);
        }
        LeaveCriticalSection(&state_mutex);
    }
    return 0;
}

/* Simulation thread */
DWORD WINAPI simulation_thread(LPVOID lpParam){
    (void)lpParam;
    while(1){
        sleep_ms(tick_ms);
        EnterCriticalSection(&state_mutex);
        sim_tick++;
        for(int i=0;i<NUM_APPROACH;i++){
            int a=poisson_tick(approaches[i].arrival_rate);
            approaches[i].queue_len+=a;
            if(approaches[i].queue_len>50) approaches[i].queue_len=50;
            if(approaches[i].queue_len>0) approaches[i].age_ticks++;
        }
        if(current_green==-1||green_remaining<=0){
            int next=0;
            switch(scheduler){
                case S_RR: next=pick_rr_locked(); break;
                case S_STATIC: next=pick_static_locked(); break;
                case S_DYNAMIC: next=pick_dynamic_locked(); break;
                case S_HYBRID: next=pick_hybrid_locked(); break;
            }
            if(next!=current_green && current_green>=0 && approaches[current_green].queue_len>0)
                approaches[current_green].starvation_count++;
            current_green=next;
            green_remaining=time_quantum_ticks;
        }
        serve_one_locked(current_green);
        green_remaining--;
        gantt[gantt_pos++%GANTT_LEN]=current_green;
        LeaveCriticalSection(&state_mutex);
    }
    return 0;
}

/* Metrics print */
void compute_and_print_metrics_locked(void){
    double total_wait=0.0; int total_served=0,total_queue=0;
    for(int i=0;i<NUM_APPROACH;i++){
        total_wait+=approaches[i].total_wait;
        total_served+=approaches[i].served;
        total_queue+=approaches[i].queue_len;
    }
    double avg_wait = total_served?total_wait/total_served:0.0;
    printf("Tick:%lld  Green:%d  Q-total:%d  Served:%d  AvgWait:%.2f  Scheduler:%d\n",
        sim_tick,current_green,total_queue,total_served,avg_wait,scheduler);
    fflush(stdout);
}

int main(int argc,char **argv){
    srand((unsigned)time(NULL));
    InitializeCriticalSection(&state_mutex);

    /* parse args */
    if(argc>=2){
        if(!strcmp(argv[1],"rr")) scheduler=S_RR;
        else if(!strcmp(argv[1],"static")) scheduler=S_STATIC;
        else if(!strcmp(argv[1],"dynamic")) scheduler=S_DYNAMIC;
        else if(!strcmp(argv[1],"hybrid")) scheduler=S_HYBRID;
    }
    if(argc>=3){
        int t=atoi(argv[2]);
        if(t>50) tick_ms=t;
    }

    /* create data folder */
    _mkdir("../data");

    /* init approaches */
    for(int i=0;i<NUM_APPROACH;i++){
        approaches[i].id=i;
        approaches[i].queue_len=2+i;
        approaches[i].arrival_rate=0.4+i*0.15;
        approaches[i].static_prio=4-i;
        approaches[i].dynamic_prio=approaches[i].static_prio;
        approaches[i].served=0;
        approaches[i].total_wait=0.0;
        approaches[i].age_ticks=0;
        approaches[i].starvation_count=0;
    }

    /* start threads */
    DWORD sim_thread_id, writer_thread_id;
    HANDLE sim_thr=CreateThread(NULL,0,simulation_thread,NULL,0,&sim_thread_id);
    HANDLE writer_thr=CreateThread(NULL,0,json_writer_thread,NULL,0,&writer_thread_id);

    /* main loop: print metrics */
    while(1){
        sleep_ms(1000);
        EnterCriticalSection(&state_mutex);
        compute_and_print_metrics_locked();
        LeaveCriticalSection(&state_mutex);
    }

    DeleteCriticalSection(&state_mutex);
    return 0;
}