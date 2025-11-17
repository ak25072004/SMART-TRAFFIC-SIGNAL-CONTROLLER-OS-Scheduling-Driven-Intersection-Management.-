import time
import random

# --- Constants ---
GREEN_DURATION = 30  
YELLOW_DURATION = 5  
RED_DURATION = 35    

# --- Classes ---

class TrafficPhase:
    """
    Represents one traffic flow group (e.g., North-South or East-West).
    Manages the current state (color) and its duration.
    """
    def __init__(self, name, opposing_phase=None):
        self.name = name 
        self.state = "RED"
        self.time_in_state = 0
        self.opposing_phase = opposing_phase

    def set_opposing(self, opposing_phase):
        """Link this phase to its opposing phase for coordinated control."""
        self.opposing_phase = opposing_phase

    def transition_state(self):
        """Handles the state sequence: RED -> GREEN -> YELLOW -> RED."""
        
        current_time = self.time_in_state

        if self.state == "RED" and self.opposing_phase.state in ["RED", "YELLOW"]:
             
            if self.opposing_phase.state == "RED" and self.opposing_phase.time_in_state >= RED_DURATION:
                self.state = "GREEN"
                self.time_in_state = 0
                print(f"[{self.name}] -> GREEN. Starting {GREEN_DURATION}s cycle.")

        elif self.state == "GREEN" and current_time >= GREEN_DURATION:
            self.state = "YELLOW"
            self.time_in_state = 0
            print(f"[{self.name}] -> YELLOW. Starting {YELLOW_DURATION}s transition.")

        elif self.state == "YELLOW" and current_time >= YELLOW_DURATION:
            self.state = "RED"
            self.time_in_state = 0
            print(f"[{self.name}] -> RED. Waiting for opposing traffic to clear.")

    def tick(self, delta_time=1):
        """Increments time in the current state."""
        self.time_in_state += delta_time
        
        
        self.transition_state()

        print(f"  {self.name} is {self.state.ljust(6)} (Time: {self.time_in_state:02}s)")


class TrafficController:
    """
    Manages and coordinates the two primary traffic phases.
    This acts as the Finite State Machine (FSM) manager.
    """
    def __init__(self):
        # 1. Initialize the two phases
        self.ns_phase = TrafficPhase("North-South")
        self.ew_phase = TrafficPhase("East-West")
        
        # 2. Link them to their opposing counterparts
        self.ns_phase.set_opposing(self.ew_phase)
        self.ew_phase.set_opposing(self.ns_phase)
        
        # 3. Set the initial state for a safe startup
        self.ns_phase.state = "GREEN"
        self.ew_phase.state = "RED"
        self.ew_phase.time_in_state = RED_DURATION 

        print(f"Controller Initialized. NS: {self.ns_phase.state}, EW: {self.ew_phase.state}")
        print("-" * 40)

    def run_simulation(self, total_duration_seconds):
        """Runs the simulation for a specified total duration."""
        print("Starting Traffic Signal Simulation...")
        
        for t in range(total_duration_seconds):
            print(f"\n[SIMULATION TIME: {t:03}s]")
            
           
            self.ns_phase.tick()
            self.ew_phase.tick()

            time.sleep(1) 

        print("\nSimulation Finished.")

# --- Execution ---

if __name__ == "__main__":
    try:
        controller = TrafficController()
        controller.run_simulation(total_duration_seconds=180)
    except KeyboardInterrupt:
        print("\nSimulation interrupted by user.")
    except Exception as e:
        print(f"\nAn error occurred: {e}")