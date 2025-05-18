#pragma once
#include "tools.hpp"
#include "Job.hpp"

/**
 * JobTable class<br>
 * ------------------------------------------------------<br>
 * - Holds an array of pointers to 10 Job objects.<br>
 * - Includes a pthread mutex for safe concurrent access.<br>
 * - Contains a quitFlag used to signal when job selection should stop.<br>
 * - The constructor initializes the mutex.<br>
 * - The destructor destroys the mutex to prevent leaks.<br>
 * - Used and accessed by Mom and Kid classes.<br>
 */
class JobTable {
private:
  Job* jobs[10]{};                 ///< Array of pointers to Job objects
  pthread_mutex_t lock{};         ///< Mutex for synchronizing access to the table
  bool quitFlag;                  ///< Flag to indicate whether kids should continue working

public:
  /** Constructor<br>
   * Initializes the mutex and sets quitFlag to false.
   */
  JobTable(): quitFlag(false) {
    pthread_mutex_init(&lock, nullptr);
  }

  /** Destructor<br>
   * Destroys the mutex to clean up resources.
   */
  ~JobTable() {
    pthread_mutex_destroy(&lock);
  }

  /** Print function placeholder<br>
   * Currently unused but reserved for future printing logic.<br>
   * @param out Output stream to print to
   */
  void print(ostream& out) {}

  friend class Kid;  ///< Grants access to Kid class
  friend class Mom;  ///< Grants access to Mom class
};

