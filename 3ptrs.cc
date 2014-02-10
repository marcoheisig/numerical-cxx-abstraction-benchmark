#include "config.hh"

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    real *src  = & src_vec[0];
    real *dest = &dest_vec[0];
    real *C = dest +   columns + 1;
    real *N =  src             + 1;
    real *W =  src +   columns    ;
    real *S =  src + 2*columns + 1;

    for(size_t iy = 0; iy < rows - 2; ++iy) {
        for(size_t ix = 0; ix < columns - 2; ++ix) {
            size_t idx = iy * columns + ix;
            C[idx] = w * (N[idx] + S[idx] + W[idx] + W[idx + 2]);
        }
    }
}
