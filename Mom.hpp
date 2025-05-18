#pragma once
#include "tools.hpp"
#include "JobTable.hpp"
#include "Kid.hpp"
#define NUM_THREADS 4

/**
 * Mom Class <br>
 * --------------------------------------------------------------<br>
 * - Manages the job table and interacts with child threads (Kids). <br>
 * - Spawns a fixed number of threads (4 kids) for chore execution. <br>
 * - Tracks completed jobs and manages the lifecycle of the simulation. <br>
 * --------------------------------------------------------------<br>
 */
class Mom {
private:
    JobTable table;                         ///< Shared job table <br>
    const string kidNames[4] = {"Ali", "Cory", "Lee", "Pat"}; ///< Array of kid names <br>
    Kid kids[NUM_THREADS];                  ///< Array of Kid objects <br>
    pthread_t kidThreadTids[NUM_THREADS];   ///< Thread IDs for each Kid <br>
    vector<Job*> completedJobs;             ///< Stores completed jobs <br>
    time_t startTime;                       ///< Start time of the chore session <br>
    time_t currentTime;                     ///< Current time for duration tracking <br>

public:
    Mom() = default;
    ~Mom(); ///< Destructor closes threads and handles cleanup <br>

    /**
     * Initializes the JobTable with random jobs. <br>
     * Called before threads are started. <br>
     */
    void initializeJobTable();

    /**
     * Scans the job table to collect completed jobs. <br>
     * Replaces completed jobs with new ones. <br>
     */
    void scanJobTable();

    /**
     * Prints summary of jobs and performance stats to terminal and file. <br>
     */
    void print();

    /**
     * Main function that: <br>
     * - Initializes jobs <br>
     * - Launches 4 Kid threads <br>
     * - Runs for a fixed duration (e.g., 20 seconds) <br>
     * - Terminates kids and summarizes job completion <br>
     */
    void run();
};
