#include "Job.hpp"
#include "Printer.hpp"

/**
 * Default constructor<br>
 * --------------------------------------------------<br>
 * Randomly initializes job attributes:<br>
 * - slow: how long it takes (1–5)
 * - dirty: how messy it is (1–5)
 * - heavy: how difficult it is (1–5)
 * - value = slow × (dirty + heavy)
 * Sets job status to NOT_STARTED.
 */
Job::Job(){
    slow = rand() % 5 + 1;      // 1 is quick, 5 is long
    dirty = rand() % 5 + 1;     // 1 is pleasant, 5 is messy
    heavy = rand() % 5 + 1;     // 1 is easy, 5 is hard
    value = slow * (dirty + heavy);
    status = JobStatus::NOT_STARTED;
};

/**
 * Assigns job to a kid<br>
 * --------------------------------------------------
 * - Stores the kid's name and job number
 * - Updates job status to WORKING
 * @param kidName Name of the kid accepting the job
 * @param jobNumber ID number of the job
 */
void Job::chooseJob(const string &kidName, int jobNumber){
    this->jobNumber = jobNumber;
    this->kidName = kidName;
    status = JobStatus::WORKING;
};

/**
 * Announces job completion<br>
 * --------------------------------------------------
 * - Updates status to COMPLETE
 * - Logs message to file and terminal via Printer
 */
void Job::announceDone(){
    status = JobStatus::COMPLETE;
    ss << "Job ID:" << jobNumber << " is completed" << endl;
    Printer::write(ss, cout);
};

/**
 * Prints job details<br>
 * --------------------------------------------------
 * - Outputs the job’s value, slow, dirty, and heavy ratings.
 * @param os Output stream
 * @return Output stream reference
 */
ostream& Job::print(ostream& os) const{
    ss << "The job value is : " << value
       << " it has " << slow << " slow"
       << " it has " << dirty << " dirty"
       << " it has " << heavy << " heavy" << endl;
    return ss;
}
