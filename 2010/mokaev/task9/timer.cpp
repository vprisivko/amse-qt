#include "timer.h"

Timer :: Timer( int* countValue, int delayValue, QMutex* mutex) : QThread(),
    myCountValue( countValue ), myDelayValue( delayValue ),myMutex( mutex ){
}

void Timer :: run(){
    while( true ){
        usleep( 1000 * myDelayValue );
        myMutex->lock();
        ++( *myCountValue );
        myMutex->unlock();
    }
}
