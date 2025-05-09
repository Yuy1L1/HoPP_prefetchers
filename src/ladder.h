#ifndef LADDER_H
#define LADDER_H

#include "hopp_prefetcher.h"

struct prefetcher _ladder(int vpn_a, int stride_a, int pid_a, int *access_history, int *stride_history);

#endif
