#include "hopp_support.h"
#include "dominator.h"
#include "ladder.h"
#include "ripple.h"  // Not yet implemented


// Utility function
void fatal(char *reason) {
    printf("%s\n", reason);
    exit(-1);
}

// We need to implement a STT. This
//
// Now we need to define a linear address stream.
int create_linear(int index) {
    /* this function generates linear traffic by adding index * packet_size
     *
     * :param index: nth number of the packet to generate an address for
     */
    return BASE_ADDR + (index * PKT_SIZE);
}

int create_ladder(int index) {
    // increment the ladder
    // current_ladder_traffic++;
    // find the ladder index for the current iteration
    int this_ladder_index = index % LADDER_LENGTH;
    // find the amount of data processed by the traffic generator.
    static int processed_ladder = BASE_ADDR;
    // until LADDER_LENGTH - 1, there will be a const stride. Not necessarily!
    if (this_ladder_index == 0) {
        // this is a rise
        processed_ladder += LADDER_RISE;
    }
    else if ((this_ladder_index > 0) && (this_ladder_index < (LADDER_LENGTH - 1))) {
        processed_ladder += (PKT_SIZE + this_ladder_index);
    }
    // If this is drop
    else if (this_ladder_index == (LADDER_LENGTH - 1)) {
        processed_ladder -= LADDER_DROP_SIZE;
    }
    else {
        // this should not happen
        fatal("error! unhandled exception at create_ladder(..)");
    }

    return processed_ladder;
}

// Can't even use string in C! This is a nightmare.
int generate_traffic(int index, char *traffic_type, bool verbose) {
    /* this function generates a given traffic (linear, dom, ladder, ripple,
     * random). It requires an id for a given traffic packet, i.e.,
     *
     * :param index: index of the current packet to generate
     * :param traffic_type: must be linear, dom, ladder, ripple, random
     */

    int current_traffic;
    if (strcmp(traffic_type, "linear") == 0)
        current_traffic = create_linear(index);
    else if (strcmp(traffic_type, "ladder") == 0)
        current_traffic = create_ladder(index);
    else
        fatal("NotImplementedError! In generate_traffic(..)");

    if (verbose == true && false)
        printf("gen: index = %d; addr = %d\n", index, current_traffic);

    return current_traffic;
}

// get the most dominant stride
int most_dominating_stride() {
    // This is incorrect!
    /* AI generated utility function. Was to lazy to write this */
    int maxCount = 0;
    int mostFrequent = stride_history[0];

    for (int i = 0; i < LENGTH - 1; i++) {
        int count = 0;
        for (int j = 0; j < LENGTH; j++) {
            if (stride_history[j] == stride_history[i]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mostFrequent = stride_history[i];
        }
    }
    // Stride history is counted in LENGTH - 1 size
    if (maxCount > ((LENGTH - 1) / 2))
        return mostFrequent;
    else
        // There is no domaning stride!
        return -1;
}

int find_most_common_element(int *array, int size) {
    // make sure that the size is not 0;.
    assert(size != 0);

    int max_element = array[0];
    //int index = 0;

    for (int i = 0 ; i < size ; i++) {
        if (max_element < array[i]) {
            max_element = array[i];
            //index = i;
        }
    }

    return max_element;
}



// Aggregator function for HoPP Prefetcher
void hopp_prefetcher() {
//    struct prefetcher result;

//   // Layer 1: Dominator Prefetcher
//    result = _dominator();
//    if (result.stride_target != 0) {
//        printf("HoPP: Using Dominator Prefetcher\n");
//      return;
//    }

//    // Layer 2: Ladder Prefetcher
//    result = _ladder(page->vpn, page->stride, page->pid, page->access_history, page->stride_history);
//    if (result.stride_target != 0) {
//        printf("HoPP: Using Ladder Prefetcher\n");
//        return;
//    }

//    // Layer 3: Ripple Prefetcher (Currently not implemented)
//    printf("HoPP: Using Ripple Prefetcher (Not Implemented)\n");
}

