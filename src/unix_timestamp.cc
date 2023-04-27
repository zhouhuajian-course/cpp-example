#include "unix_timestamp.h"
#include <time.h>
#include <iostream>

using namespace std;

void set_unix_timestamp(unix_timestamp *ut)
{
    time_t t = time(NULL);
    // cout<<"sizeof(time_t) is: "<<sizeof(time_t)<<endl;
    // cout<<"myt is :"<<myt<<endl;
    // time_t t;
    // time(&t);
    // cout<<"t is:"<<t<<endl;
    ut->sec = t;
}

