#include "mediane.h"

/**
 * @brief Computes the median of three integers.
 *
 * This function takes three integer arguments and returns the median value.
 * The median is the middle value when the integers are sorted in ascending order.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @param c The third integer.
 * @return The median of the three integers.
 */
int mediane(int a, int b, int c) {
    if ((a >= b && a <= c) || (a <= b && a >= c)) {
        return a;
    } else if ((b >= a && b <= c) || (b <= a && b >= c)) {
        return b;
    } else {
        return c;
    }
}
