#include "Mom.hpp"
#include "Printer.hpp"

/**
 * Thread entry function for Kid threads. <br>
 * Casts the argument to a Kid pointer and calls its run method.
 */
void* kidMain(void* k) {
    Kid* kid = static_cast<Kid*>(k);
    kid->run();
    return nullptr;
}

/**
 * Mom Destructor <br>
 * --------------------------------------------------<br>
 * Cleans up by deallocating all dynamically allocated completed jobs.
 */
Mom::~Mom() {
    for (Job* job : completedJobs) delete job;
}

/**
 * Initializes the shared JobTable with 10 random jobs. <br>
 * Each job is dynamically allocated and stored in the table. <br>
 * Job information is printed to both the terminal and output file.
 */
void Mom::initializeJobTable() {
    pthread_mutex_lock(&table.lock);
    for (int i = 0; i < 10; i++) {
        Job* newJob = new Job;
        table.jobs[i] = newJob;
        ss << "Job" << i << endl;
        Printer::write(ss, cout);
        ss << *newJob << endl;
        Printer::write(ss, cout);
    }
    pthread_mutex_unlock(&table.lock);
}

/**
 * Scans the JobTable for completed jobs. <br>
 * If a job is marked COMPLETE, it's saved in the completed list and replaced with a new job.
 */
void Mom::scanJobTable() {
    for (int i = 0; i < 10; i++) {
        if (table.jobs[i]->status == JobStatus::COMPLETE) {
            completedJobs.push_back(table.jobs[i]);
            table.jobs[i] = new Job();
            ss << "Adding new job at index: " << i << endl;
            Printer::write(ss, cout);
        }
    }
}

/**
 * Simple helper function to print an introductory message.
 */
void Mom::print() {
    ss << "Hey kids, This is Mama" << endl;
    Printer::write(ss, cout);
}

/**
 * Main control logic for the Mom thread. <br>
 * --------------------------------------------------
 * - Prints welcome message
 * - Initializes jobs and spawns kid threads
 * - Signals all kids to begin work
 * - Waits for 21 seconds, polling for completed jobs
 * - Sends termination signal to each kid
 * - Joins all threads and prints summary results
 */
void Mom::run() {
    print();
    initializeJobTable();
    ss << "Job Table Initialized" << endl;
    Printer::write(ss, cout);

    // Create Kid threads
    for (int i = 0; i < NUM_THREADS; i++) {
        kids[i] = Kid(kidNames[i], &table);
        int rc = pthread_create(&kidThreadTids[i], nullptr, kidMain, &kids[i]);
        ss << "Kid created: " << kidNames[i] << endl;
        Printer::write(ss, cout);
        if (rc) cerr << "ERROR; failed to create kid thread";
    }

    // Signal each kid to start
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_kill(kidThreadTids[i], SIGUSR1);
        ss << "Signal sent to start work: " << kidNames[i] << endl;
        Printer::write(ss, cout);
    }

    table.quitFlag = true;
    time(&startTime);

    // Run simulation for 21 seconds
    while (difftime(time(&currentTime), startTime) < 21) {
        sleep(1);
        scanJobTable();
    }

    // Signal each kid to stop and print their results
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_kill(kidThreadTids[i], SIGQUIT);
        ss << "------------------Kids--------------------------------" << endl;
        Printer::write(ss, cout);
        kids[i].printCompletedJob();
        ss << "Signal sent to stop work: " << kidNames[i] << endl;
        Printer::write(ss, cout);
        ss << "------------------Kids- End--------------------------------" << endl;
        Printer::write(ss, cout);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        void* retVal;
        pthread_join(kidThreadTids[i], &retVal);
        ss << "Kid " << kidNames[i] << " joined" << endl;
        Printer::write(ss, cout);
    }

    table.quitFlag = false;
    scanJobTable();

    // Tally results
    unordered_map<string, int> totalEarnings;
    for (Job* job : completedJobs) {
        totalEarnings[job->kidName] += job->value;
    }

    string winner;
    int maxEarnings = -1;
    for (auto& [name, value] : totalEarnings) {
        if (value > maxEarnings) {
            maxEarnings = value;
            winner = name;
        }
    }
    totalEarnings[winner] += 5;

    ss << "--------------------Mama-----------------------------" << endl;
    Printer::write(ss, cout);

    for (Job* job : completedJobs) {
        ss << "Child " << job->kidName << " has earned a total value of " << job->value << " on this job " << job->jobNumber << endl;
        Printer::write(ss, cout);
    }

    ss << "The winner for today is " << winner << ", who had a total of " << totalEarnings[winner] << endl;
    Printer::write(ss, cout);
}
