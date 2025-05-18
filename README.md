🧹 TaskDispatcher

TaskDispatcher is a multithreaded, concurrent task scheduler developed in C++ for simulating dynamic job delegation and execution in a shared-memory environment. Inspired by real-world workload management, this tool showcases synchronization, randomized decision-making, and POSIX signal handling within a multithreaded architecture.

This utility is ideal for environments exploring concurrent system behaviors, such as simulations, training systems, or operating systems coursework.

📘 Introduction

TaskDispatcher models a parent-child concurrency pattern where a controller thread (Mom) delegates tasks to multiple worker threads (Kids) based on randomized behavioral profiles (moods). Each worker selects tasks from a shared job board using mood-driven logic and executes the assigned task, reporting completion back to the dispatcher.

This simulation emphasizes:

    ✅ Safe thread coordination using mutexes

    🧠 Job selection based on context-aware heuristics

    📡 Controlled signaling for execution flow (start and stop)

✨ Features

    🧠 Mood-Based Job Selection
    Worker threads select jobs based on one of five moods: lazy, prissy, overtired, greedy, or cooperative.

    🔒 Thread-Safe Shared Memory
    All access to the shared JobTable is mutex-protected, ensuring data consistency during concurrent operations.

    🚨 Signal-Driven Execution
    Uses SIGUSR1 to initiate work and SIGQUIT to terminate, ensuring clean coordination.

    🏆 Real-Time Scoring System
    Each job has a reward score calculated from time, unpleasantness, and effort. Final tallies are computed, and the highest earner is awarded a bonus.

    🧪 Randomized Output
    Simulated moods and job properties vary between executions, ensuring unique results with each run.

💻 Usage
🔧 Compilation

git clone https://github.com/yourusername/taskdispatcher.git
cd taskdispatcher
mkdir build && cd build
cmake ..
make

▶️ Running the Simulation

./TaskDispatcher

This command launches the simulation for 21 time units (~3.5 simulated hours). Logs are printed to the console showing each thread’s decisions, job completions, and the final earnings report.
🛠️ Project Structure

.
├── main.cpp            # Entry point
├── Mom.[cpp|hpp]       # Controller logic and task scheduler
├── Kid.[cpp|hpp]       # Worker thread behavior and mood logic
├── Job.[cpp|hpp]       # Chore model with scoring logic
├── JobTable.hpp        # Shared job list and mutex
├── Enums.hpp           # Enum definitions for moods and status
├── Printer.[cpp|hpp]   # Thread-safe output utility
├── tools.[cpp|hpp]     # Utility functions
├── CMakeLists.txt      # CMake build file
└── output.txt          # Example output

📄 Example Command

./TaskDispatcher

The simulation will display each worker’s mood, selected tasks, processing times, and a final report summarizing total earnings and the top performer.
📈 Sample Output

See output.txt for a logged simulation that showcases:

    Worker mood assignments

    Real-time job tracking

    Final earnings and leaderboard

🤝 Contributing

Contributions are welcome! If you'd like to improve TaskDispatcher, please fork the repo and open a pull request. For large changes, open an issue first to discuss proposed features or design modifications.
📜 License

TaskDispatcher is released under the MIT License. See the LICENSE file for details.  
