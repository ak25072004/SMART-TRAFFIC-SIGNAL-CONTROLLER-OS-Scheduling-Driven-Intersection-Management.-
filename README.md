# SMART-TRAFFIC-SIGNAL-CONTROLLER-OS-Scheduling-Driven-Intersection-Management.-
The Smart Traffic Signal Controller is a Python-based project that uses Operating System scheduling algorithms to manage traffic at road intersections. Each road is treated like a process, and algorithms such as Round Robin, Priority Scheduling, and a Hybrid approach are used to decide which signal turns green next.
B.tech CSE PROJECT PROPOSAL
 Page 1
Project Title
(Try to choose a catchy title. Max 20 words).
SMART TRAFFIC SIGNAL CONTROLLER: OS Scheduling–Driven Intersection Management.
Student/Team Information
Team Name: CODECREW
Team member 1 (Team Lead)
AKARSHAN KUMAR,
UNIROLL NO.-2111502
STUDENT ID.- 211111010,
EMAIL ID.- akarshank12@gmail.com

Team member 2
PRAJJWAL SINGH NEGI,
UNI ROLL NO.- 2361403
STUDENT ID.- 230112758
EMAIL ID.- prajjwalnegi73@gmail.com

PROJECT AND TEAM INFORMATION
B.tech CSE PROJECT PROPOSAL
 Page 2
Team member 3
SHUBHANGI KUMARI
UNI ROLL NO.- 2319629
STUDENT ID.- 230122632
EMAIL ID.-shubhangiii.74@gmail.com

Team member 4
SHREYA DHYANI
UNI ROLL NO.- 2319595
STUDENT ID.- 23152275
EMAIL ID.-shreyadhyani01@gmail.com

B.tech CSE PROJECT PROPOSAL
 Page 3
Project Abstract
(Brief restatement of your project’s main goal. Max 300 words).
The Smart Traffic Signal Controller is a Python-based project that uses Operating System scheduling algorithms to manage
traffic at road intersections. Each road is treated like a process, and algorithms such as Round Robin, Priority Scheduling,
and a Hybrid approach are used to decide which signal turns green next.
The main goal is to reduce traffic congestion and waiting time by giving green light time based on real-time traffic density.
The project includes a simulation core, a scheduling module, and a GUI visualization built using Tkinter or Pygame. It helps
demonstrate OS concepts like process scheduling, fairness, and context switching in a real-world scenario while improving
traffic flow and efficiency.
Updated Project Approach and Architecture
(Describe your current approach, including system design, communication protocols, libraries used, etc. Max 300 words).
The Smart Traffic Signal Controller project follows a modular Python-based approach inspired by Operating System
scheduling. The system is divided into three main layers:
1. Simulation Core:
This layer models each road as a process with properties such as arrival rate, queue length, and priority. It
handles vehicle arrivals, signal timing, and process switching (similar to context switching in OS).
2. Scheduling Module:
This part implements different OS scheduling algorithms — Round Robin, Priority Scheduling, and a Hybrid
Scheduler with aging — to allocate green signal time dynamically. Each algorithm can be tested separately to
compare performance in terms of fairness and average waiting time.
3. Visualization Layer (GUI):
The GUI, built using Tkinter or Pygame, visually displays the intersection layout, active signals, traffic queues, and
ongoing scheduler activity. It helps users observe how scheduling decisions affect traffic flow in real time.
Libraries Used:
Python’s standard libraries (like queue and time) are used for core logic, while Tkinter/Pygame are used for visualization
and matplotlib for plotting results.
PROJECT PROGRESS DESCRIPTION
B.tech CSE PROJECT PROPOSAL
 Page 4
Tasks Completed
(Describe the main tasks that have been assigned and already completed. Max 250 words).
Task Completed Team Member
Designed and implemented the backend simulation core
including process model and scheduling algorithms
(Round Robin, Priority, Hybrid)
Created a basic prototype of the frontend interface using
Pygame.
Akarshan Kumar, Shubhangi Kumari
Prajjwal Singh Negi, Shreya Dhyani
Challenges/Roadblocks
(Describe the challenges that you have faced or are facing so far and how you plan to solve them. Max 300 words).
During the development of the Smart Traffic Signal Controller project, the team faced challenges in both technical
implementation and system integration. Synchronizing the backend scheduling logic with the frontend visualization
proved difficult, as real-time traffic updates were not always accurately reflected in the GUI. Frontend development is still
in early stages, and designing a clear, dynamic, and user-friendly interface requires additional work. Minor issues also
arose when testing different scheduling algorithms, such as handling idle lanes and maintaining fairness under heavy load.
To address these, the team plans to use event-driven programming and threading for real-time synchronization, enhance
the frontend using Tkinter or Pygame, and perform iterative testing to ensure smooth integration. These improvements
will result in a functional and visually interactive traffic simulation based on OS scheduling algorithms.
Tasks Pending
(Describe the main tasks that you still need to complete. Max 250 words).
Task Pending Team Member (to complete the task)
Frontend development & enhancement
Frontend-backend integration
Real-time sync of scheduling & GUI
Prajjwal, Shreya
Prajjwal, Shreya, Akarshan, Shubhangi
Shubhangi, Akarshan
B.tech CSE PROJECT PROPOSAL
 Page 5
Project Outcome/Deliverables
(Describe what are the key outcomes / deliverables of the project. Max 200 words).
The Smart Traffic Signal Controller project aims to simulate and manage traffic flow efficiently using OS scheduling
algorithms. The key deliverables include:
1. Backend Implementation: Fully functional traffic scheduling algorithms (FCFS, Round Robin, Priority, etc.)
managing lane queues and signal timing.
2. Interactive Frontend: A dynamic and user-friendly GUI that visually represents real-time traffic flow and signal
changes.
3. Integration: Seamless communication between backend algorithms and frontend visualization for accurate, realtime updates.
4. Testing & Validation: Thorough testing under different traffic scenarios to ensure fairness, handle idle lanes, and
maintain stability under heavy load.
Progress Overview
(Summarize how much of the project is done, what's behind schedule, what's ahead of schedule. Max 200 words.)
The backend of the Smart Traffic Signal Controller project is fully implemented, including all traffic scheduling algorithms
and queue management. The core logic is tested and functioning correctly. However, the frontend development is still in
the early stages and remains behind schedule. Integration of the frontend with the backend is pending, which is crucial for
real-time visualization and interaction. Testing of combined scheduling algorithms under different traffic scenarios is
partially done, with some edge cases like idle lanes and heavy load conditions still needing attention.
Tasks ahead include completing the frontend, implementing real-time synchronization between the backend and GUI,
enhancing visualization for user-friendly interaction, and performing iterative testing to ensure system stability. With
focused effort on frontend development and integration, the project is expected to achieve a functional, interactive, and
visually accurate traffic simulation as planned.
B.tech CSE PROJECT PROPOSAL
 Page 6
Codebase Information
(Repository link, branch, and information about important commits.)
Your answer here
Testing and Validation Status
(Provide information about any tests conducted)
Test Type Status (Pass/Fail) Notes
Backend Scheduling
Algorithms
GUI Visualization
Integration Testing
(Backend + Frontend)
Edge Case Testing (Idle
lanes, Heavy traffic)
Overall System Stability
Pass
Partial
In Progress
In Progress
Partial
All algorithms produce correct lane scheduling and signal timing
Basic layout works; real-time traffic updates not fully synced yet
Synchronization issues between backend updates and GUI rendering
Some scenarios still require fine-tuning to maintain fairness
Stable for small simulations; needs more testing for heavy load
B.tech CSE PROJECT PROPOSAL
 Page 7
Deliverables Progress
(Summarize the current status of all key project deliverables mentioned earlier. Indicate whether each deliverable is
completed, in progress, or pending.)
The backend implementation of traffic scheduling algorithms is completed.
The frontend development and its integration with the backend are in progress, as real-time synchronization and
interactive visualization are still being enhanced.
Testing and validation of the full system are in progress.
