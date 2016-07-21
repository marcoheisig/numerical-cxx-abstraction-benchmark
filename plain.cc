#include "config.hh"
#include "runb.hh"

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    real *src  = & src_vec[0];
    real *dest = &dest_vec[0];

    for(size_t iy = 1; iy < rows - 1; ++iy) {
//#pragma vector aligned
//#pragma unroll(16)
#pragma ivdep
        for(size_t ix = 1; ix < columns - 1; ++ix) {
            size_t index = iy * columns + ix;
            dest[index] = w * (src[index - 1      ] +
                               src[index + 1      ] +
                               src[index - columns] +
                               src[index + columns]);
        }
    }
}
