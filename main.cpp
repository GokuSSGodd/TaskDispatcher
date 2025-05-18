#include "tools.hpp"
#include "Mom.hpp"

/**
 * Main Function <br>
 * ------------------------------------------------------- <br>
 * - Initializes random seed using current time <br>
 * - Creates a `Mom` object <br>
 * - Runs the simulation using `Mom::run()` <br>
 * - Exits program with return code 0 <br>
 */
int main() {
    srand(time(nullptr));
    // banner();  // Optional banner display
    Mom mom;
    mom.run();
    // bye();     // Optional closing message
    return 0;
}
