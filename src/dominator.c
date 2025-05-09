
#include "dominator.h"

// begin writing the prefetchers here
struct prefetcher _dominator() {
    /* Calculates the dominant stride in the given access history */
    int dom_stride = most_dominating_stride();
    struct prefetcher output;
    output.stride_target = dom_stride;
    return output;
}
