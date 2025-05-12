#ifndef HOPP_PREFETCHER_H
#define HOPP_PREFETCHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// Implementation in C 

// The paper defines a length of the window. By default, we use 64
#define LENGTH 16
// We need to define a packet size. For DRAM systems, it has be the same as a
// cache line size. This is in BYTES!
#define PKT_SIZE 8

// For ladder traffic, there is a stride for a couple of addresses before going
// back to an random-like pattern. The stride pattern continues until
// LADDER_LENGTH - 1 packets and then it drops before rising.
#define LADDER_LENGTH 4
// The ladder can have different lengths too!

// The pattern drops. See the graph from the paper. this is in bytes
#define LADDER_DROP_SIZE 8
// The pattern resumes after a certain interval.
#define LADDER_INTERVAL 1
// Ladder also needs to have the rise. After 10 packets, the 11th packet will
// see this jump. this is in bytes.
#define LADDER_RISE 13

// To generate traffic, we need a base address to start with. When these
// addresses are fed into a memory simulator, the address decoding can be seen
// in details.
#define BASE_ADDR 0x0

// We need a global structure that maintains the ladder traffic index
// generators
extern int processed_ladder;

// Here is maintain the stride related parameters
int access_history[LENGTH];
int stride_history[LENGTH];

// A prefetcher algorithm returns a stride pattern
struct prefetcher {
    int stride_target;
    int pattern_target;
};



void fatal(char *reason);
int create_linear(int index);
int create_ladder(int index);
int generate_traffic(int index, char *traffic_type, bool verbose);
int most_dominating_stride();
int find_most_common_element(int *array, int size);
void hopp_prefetcher();

#endif
