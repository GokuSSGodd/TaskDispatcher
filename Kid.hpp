#pragma once
#include "tools.hpp"
#include "Enums.hpp"
#include "Job.hpp"
#include "JobTable.hpp"

/**
 * @class Kid <br>
 * Represents a child thread that performs jobs assigned by Mom.<br>
 * Each Kid has a name, mood, pointer to the shared JobTable, and tracks completed jobs.
 */
class Kid {
private:
    string name;                     ///< Name of the Kid <br>
    Mood mood;                       ///< Mood of the Kid (e.g., LAZY, PRISSY) <br>
    vector<Job*> finishedJobs;       ///< List of completed jobs <br>
    Job* inProgress;                 ///< Pointer to job currently in progress <br>
    JobTable* table;                 ///< Pointer to shared JobTable <br>
    sigset_t set{};                  ///< Signal set for thread control <br>

    /** Selects a job using non-cooperative strategy */
    void non_Coop_Task_Select();

    /** Selects a job using cooperative strategy */
    void coop_Task_Select();

    /** Checks if the Kid is willing to do the job based on mood */
    bool moodChecker(Job&);

    /** Static signal handler to trigger job selection and execution */
    static void work(int sig);

public:
    /** Default constructor */
    Kid() = default;

    /** Default destructor */
    ~Kid() = default;

    /**
     * Parameterized constructor <br>
     * @param name Name of the Kid <br>
     * @param table Pointer to the shared JobTable <br>
     */
    Kid(const string& name, JobTable* table);

    /** Randomly assigns a mood to the Kid */
    void selectMood();

    /** Determines job selection strategy based on mood */
    void selectJob();

    /** Main execution loop for the Kid */
    void run();

    /** Prints Kid's name */
    void print();

    /** Prints all completed jobs by the Kid */
    void printCompletedJob();
};
