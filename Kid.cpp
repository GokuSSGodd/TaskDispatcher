#include "Kid.hpp"
#include "Printer.hpp"

/** Kid constructor<br>
 * Creates an empty signal set and adds SIGUSR1 and SIGQUIT.<br>
 * Applies a thread-level signal mask to block signals until needed.
 * @param name Kid's name
 * @param table Pointer to shared JobTable
 */
Kid::Kid(const string& name, JobTable* table):name(name), table(table), inProgress(nullptr){
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGQUIT);
    pthread_sigmask(SIG_BLOCK, &set, nullptr);
}

/** Randomly selects a mood for the kid */
void Kid::selectMood() {
    mood = static_cast<Mood>(rand()%5);
}

/** Checks if job is suitable based on Kid's mood
 * @param job Reference to the Job object
 * @return true if job passes the mood filter, else false
 */
bool Kid::moodChecker(Job& job) {
    return (job.heavy < 3 && mood == Mood::LAZY) ||
           (job.dirty < 3 && mood == Mood::PRISSY) ||
           (job.slow < 3 && mood == Mood::OVERTIRED) ||
           (job.value > 40 && mood == Mood::GREEDY);
}

/** Selects task for non-cooperative kids<br>
 * Iterates through the JobTable linearly.<br>
 * Picks the first available job matching the mood filter.<br>
 * Locks mutex during selection to prevent race conditions.
 */
void Kid::non_Coop_Task_Select() {
    int counter=-1;
    for (Job* job: table->jobs) {
        counter++;
        pthread_mutex_lock(&table->lock);
        if (job->status != JobStatus::NOT_STARTED ) {
            pthread_mutex_unlock(&table->lock);
            continue;
        }
        if (moodChecker(*job)) {
            job->chooseJob(name, counter);
            inProgress = job;
            pthread_mutex_unlock(&table->lock);
            break;
        }
        pthread_mutex_unlock(&table->lock);
    }
}

/** Selects task for cooperative kids<br>
 * Chooses the last available job in reverse order.<br>
 * Locks mutex during access for thread safety.
 */
void Kid::coop_Task_Select() {
    for (int j = 9; j >= 0; j--) {
        pthread_mutex_lock(&table->lock);
        Job* job = table->jobs[j];
        if (job->status != JobStatus::NOT_STARTED ) {
            pthread_mutex_unlock(&table->lock);
            continue;
        }
        job->chooseJob(name, j);
        inProgress = job;
        pthread_mutex_unlock(&table->lock);
        break;
    }
}

/** Job Selection wrapper based on mood<br>
 * Cooperative kids use reverse selection strategy<br>
 * Non-cooperative kids race to grab jobs
 */
void Kid::selectJob() {
    if (mood != Mood::COOPERATIVE) non_Coop_Task_Select();
    else coop_Task_Select();
}

/** Signal handler to react to SIGUSR1 and SIGQUIT<br>
 * SIGUSR1 starts job selection loop<br>
 * SIGQUIT cleanly exits the thread
 * @param sig Signal received
 */
void Kid::work(int sig) {
    if (sig == SIGUSR1) {
        ss << "\nStart work Signal " << sig << " received by consumer\n";
        Printer::write(ss, cout);
    } else if (sig == SIGQUIT) {
        ss << "\nEnd work Signal: " << sig << " received by consumer\n";
        Printer::write(ss, cout);
        pthread_exit(nullptr);
    }
}

/** Main job execution loop
 * - Waits for SIGUSR1 to begin working
 * - Selects mood and prints it
 * - Repeatedly attempts to grab jobs while `quitFlag` is true
 * - Sleeps for duration of job
 * - Announces job completion
 * - Stores completed job in finishedJobs
 */
void Kid::run() {
    struct sigaction startAct{};
    sigset_t emptySet;
    sigemptyset(&emptySet);
    startAct.sa_handler = work;
    startAct.sa_mask = emptySet;
    startAct.sa_flags = 0;

    sigaction(SIGUSR1, &startAct, nullptr);
    sigaction(SIGQUIT, &startAct, nullptr);
    int signo;
    while (true) {
        int ret = sigwait(&set, &signo);
        if (ret) perror("sigwait");
        if (signo == SIGUSR1) break;
    }

    pthread_sigmask(SIG_UNBLOCK, &set, nullptr);
    ss<<"Start working: "<<name<<endl;
    Printer::write(ss, cout);
    selectMood();
    ss<<name<<" mood is: "<<moodName[static_cast<int>(mood)] <<endl;
    Printer::write(ss, cout);

    while (table->quitFlag) {
        selectJob();
        if (inProgress != nullptr && inProgress->status == JobStatus::WORKING) {
            sleep(inProgress->slow);
            inProgress->announceDone();
            finishedJobs.push_back(inProgress);
            ss<<"Job Completed status: "<< jobStatusName[static_cast<int>(inProgress->status)]<<endl;
            Printer::write(ss, cout);
        }
    }
}

/** Prints Kid's name to output stream */
void Kid::print() {
    Printer::writeln("This is Kid: " + name, cout);
}

/** Prints all completed jobs by the Kid */
void Kid::printCompletedJob() {
    for (Job* job: finishedJobs) {
        ss << *job << " was completed by " << job->kidName << endl;
        Printer::write(ss, cout);
    }
}
