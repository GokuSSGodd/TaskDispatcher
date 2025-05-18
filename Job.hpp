#pragma once
#include "tools.hpp"
#include "Enums.hpp"

/**
 * Job class<br>
 * ------------------------------------------------------<br>
 * - Represents a single job that a kid can take on.<br>
 * - Contains attributes like job number, difficulty (slow, dirty, heavy), and value.<br>
 * - Tracks the job status and which kid is working on it.<br>
 * - Used by both Mom and Kid classes.<br>
 */
class Job {
private:
    int jobNumber;         ///< Unique identifier for the job
    short int slow;        ///< Time to complete the job (1 to 5)
    short int dirty;       ///< Dirtiness level (1 to 5)
    short int heavy;       ///< Weight/effort required (1 to 5)
    int value;             ///< Calculated value based on job properties
    string kidName;        ///< Name of the kid assigned to this job

public:
    JobStatus status;      ///< Current status of the job (NOT_STARTED, WORKING, COMPLETE)

    /** Default constructor<br>
     * Initializes job with random slow, dirty, heavy values.<br>
     * Calculates value = slow × (dirty + heavy)<br>
     * Sets status to NOT_STARTED.
     */
    Job();

    /** Destructor (default) */
    ~Job() = default;

    /** Assigns job to a kid<br>
     * Sets jobNumber, kidName, and status to WORKING.<br>
     * @param kidname Name of the kid taking the job<br>
     * @param jobNumber ID of the job being assigned<br>
     */
    void chooseJob(const string& kidname, int jobNumber);

    /** Announces job completion<br>
     * Sets status to COMPLETE and prints message.
     */
    void announceDone();

    /** Print function<br>
     * Outputs the job’s attributes (value, slow, dirty, heavy).<br>
     * @param os Output stream<br>
     * @return Output stream reference
     */
    ostream& print(ostream& os) const;

    friend class Kid;  ///< Grants access to Kid class
    friend class Mom;  ///< Grants access to Mom class
};

/** Overloaded << operator for printing jobs */
inline ostream& operator << (ostream& out, Job& job){
    return job.print(out);
}
