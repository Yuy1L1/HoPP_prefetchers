#include "dominator.h"
#include "ladder.h"
#include "hopp_support.h"


int main() {
    // I need a duration to run!

    // verbose
    bool verbose = true;

    // when the simulation starts, addr holds the current address. assume that
    // his is virtual.
    int addr;

    // I am keeping a count of each window. A window is defined as the duration
    // until the history length is filled up.
    int window = 0;

    // generating traffic until some length
    for (int i = 0 ; i < 100 ; i++) {
        // generate is a yield function.
        addr = generate_traffic(i, "ladder", verbose);

        // fill up the access history until the window is completed.
        access_history[i % LENGTH] = addr;

        // if the index is > 0, record the difference between this address and
        // the previous address. This fills up the access stride history table
        // until a window is complete.
        if ((i % LENGTH ) > 0) {
            stride_history[(i % LENGTH) - 1] =
                                       addr - access_history[(i % LENGTH) - 1];
        }
        // process this window. bring in the prefetcher!
        if ((i % LENGTH == 0) && (i != 0)) {

            // TODO add verbose options to not print everything everytime!
            if (verbose == true)
                printf("\t == stats for window %d\n", window++);

            if (verbose == true) {
                printf(" stride_history: ");
                for (int i = 0 ; i < LENGTH - 1; i++) {
                    printf("%d\t", stride_history[i]);
                }
                printf("\n access_history: ");
                for (int i = 0 ; i < LENGTH ; i++) {
                    printf("%d\t", access_history[i]);
                }
            printf("\n");
            }

            // start of a new window!
            // the prefetcher kicks. first use the SSP

            // i think we need to separate out hot pages here! from the window?
            // struct hot_pages = get_hot_pages(int window);
            struct prefetcher results = _dominator();

            if (results.stride_target != -1) {
                // There is a dominating stride!
                // TODO What do I do with it?
                printf("dom stride is %d\n", results.stride_target);
            }
            else {
                printf("no dom stride found!\n");
                // there was no dominating pattern found! try the ladder
                // prefetcher now!
                // need to calculate the current stride.
                // TODO: Remove this line when we all understand this!
                int stride_a = addr - access_history[LENGTH - 1];

                results = _ladder(
                        addr, stride_a, 0, access_history, stride_history);

                // now make sure to prefetch the addresses
                // as per the paper, this is given by:
                // addr = vpn_a + stride_target + i * pattern_stride

                printf("ladder: %d %d next_addr: %d\n", results.stride_target,
                        results.pattern_target, addr + results.stride_target +
                        results.pattern_target);

            }
        }
    }

    return 0;
}
