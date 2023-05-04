
#ifndef INCLUDE_UNIX_TIMESTAMP_H
#define INCLUDE_UNIX_TIMESTAMP_H

#include <cstdint>

struct unix_timestamp {
  int64_t sec;
  int64_t usec;
};

void set_unix_timestamp(unix_timestamp *ut);

#endif