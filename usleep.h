/* Cross platform sleeping code by Bernardo Ramos on Stack Overflow: https://stackoverflow.com/a/28827188 
/* Modified by Aftersol */
#ifndef SLEEP_FUNC_H
#define SLEEP_FUNC_H

#if __cplusplus
extern "C"
{
#endif

#ifdef _WIN32
#include <synchapi.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) { // cross-platform sleep function
#ifdef _WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

#if __cplusplus
extern "C"
}
#endif

#endif