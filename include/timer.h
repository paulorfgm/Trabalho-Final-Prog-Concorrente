/* File:     timer.h
 *
 * Purpose:  Define a macro that returns the number of seconds that 
 *           have elapsed since some point in the past.  The timer
 *           should return times with microsecond accuracy.
 *
 * Note:     The argument passed to the GET_TIME macro should be
 *           a double, *not* a pointer to a double.
 *
 * Example:  
 *    #include "timer.h"
 *    . . .
 *    double start, finish, elapsed;
 *    . . .
 *    GET_TIME(start);
 *    . . .
 *    Code to be timed
 *    . . .
 *    GET_TIME(finish);
 *    elapsed = finish - start;
 *    printf("The code to be timed took %e seconds\n", elapsed);
 *
 * IPP:  Section 3.6.1 (pp. 121 and ff.) and Section 6.1.2 (pp. 273 and ff.)
 * Author:  Peter Pacheco
 */
#ifndef _TIMER_H_
#define _TIMER_H_

#define __USE_POSIX199309 //para usar CLOCK_MONOTONIC
#include <time.h>

/* The argument now should be a double (not a pointer to a double) */
#define GET_TIME(now) { \
   struct timespec t; \
   clock_gettime(CLOCK_MONOTONIC, &t); \
   now = t.tv_sec + t.tv_nsec/1000000000.0; \
}

#endif
