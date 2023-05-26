# Processes' Scheduling Simulation
This is an algorithm that simulates process scheduling in a multiprocessor system. It allocates processes to the appropriate processor according to certain calculated parameters and schedules each process according to its processor's scheduling algorithm. It also calculates statistical data to help improve the system. 
# Input
The program takes an input file containing number of processors, their respective scheduling algorithms (First Come First Serve, Round Robin or Shortest Job First), the number of processes, the data of each process (its computaion time, arrival time, time(s) at and duration for which it needs to utilise IO resources), timeslice of Round Robin Scheduling, times at which process should be killed, a fork probability for processes and process migration parameters.
# Logic
The program schedules all processes according to the input parameters in the most efficient way possible. The processes are first enqueued in NEW Queue. Then throughout the program, processes are transferred across different lists (RDY lists, RUN states, BLK lists and TRM lists) according to their appropriate state and respective scheduling properties. After all processes are transferred to TRM list, the program terminates and an output file is produced. An integer value, incremented at appropriate times throughout the program operation, is used to simulate the concept of a timestep.
# Operation Modes
The program interface operates in three modes:
### 1. Interactive Mode:
All lists' data is printed every timestep. Moving from one timestep to another is done manually by clicking on the screen when indicated. An output file is produced at the end.
### 2. Step-By-Step Mode:
All lists' data is printed every timestep. Moving from one timestep to another is done automatically every second. An output file is produced at the end.
### 3. Silent Mode:
No output is produced on screen while scheduling takes place. An output file is produced at the end.
# Output File
The output file produced contains number of processes, the statsictical data of each process and some general efficiency-related statsictics. It also includes information about processor's migration, utilization and load. 
# Langauge and Software
The program was implemented entirely in C++ using Visual Studio (2022).






