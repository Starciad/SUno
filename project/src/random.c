#include "random.h"
#include <stdlib.h>

// Returns a random integer in the given range.
extern int16_t random_int(int16_t min, int16_t max)
{
    return min + rand() % (max - min + 1);
}
