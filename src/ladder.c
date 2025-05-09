

#include "ladder.h"

struct prefetcher _ladder(int vpn_a, int stride_a, int pid_a, int *access_history, int *stride_history) {
    /* Implementation based on the HoPP paper. The algo written in the paper
     * was fed into an AI to generate a python version of the algorithm. It was
     * then translated to C.
     *
     * :param vpn_a: Virtual Page Number of the current access must be the one
     *              at the end of the window?? super confusing.
     * :param stride_a: Stride of the current access i.e. vpn_a - last_vpn_a.
     * :param pid_a: The process ID of the current process (ignored).
     * :param *vpn_history: The array of prior vpn history
     * :param *stride_history: The array of prior strides
     *
     * @returns :struct prefetcher output:
     */
    struct prefetcher output;

    // calculate stride_A
    int pattern_target[2];
    pattern_target[0] = stride_history[LENGTH - 2];
    pattern_target[1] = stride_a;

    // to store the next candidates
    int next_stride[LENGTH];
    int stride_sum[LENGTH];

    // These structures are dynamically filled up!
    int next_stride_index = 0;
    int stride_sum_index = 0;

    // ¯\_(ツ)_/¯
    int last_index = LENGTH - 2;

    for (int i = LENGTH - 3 ; i >= 0 ; i--) {
        if (stride_history[i] == pattern_target[0] && stride_history[i + 1] == pattern_target[1]) {
            next_stride[next_stride_index++] = stride_history[i + 2];
            stride_sum[stride_sum_index++] = access_history[last_index] - access_history[i];
            last_index = i;
        }
    }

    if (next_stride_index > 0) {
        // There is some element in the next_stride array
        output.stride_target = find_most_common_element(next_stride, next_stride_index);
        output.pattern_target = find_most_common_element(stride_sum, stride_sum_index);
    }
    else {
        // return zeros pretty much!
        output.stride_target = 0;
        output.pattern_target = 0;
    }

    return output;

}
