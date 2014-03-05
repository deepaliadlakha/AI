
#include "timeTracker.h"

timeval beginTime;
void startTimer(void){
        gettimeofday(&beginTime, NULL);
    }

double stopTimer(){
        timeval endTime;
        long seconds, microSeconds;
        double duration;

        gettimeofday(&endTime, NULL);

        seconds  = endTime.tv_sec  - beginTime.tv_sec;
        microSeconds = endTime.tv_usec - beginTime.tv_usec;

        duration = seconds + microSeconds / 1000000.0;

        return duration;
}
