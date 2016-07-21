#include "config.hh"
#include "runb.hh"

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    std::vector<real>::iterator       C = dest_vec.begin() +   columns + 1;
    std::vector<real>::const_iterator N =  src_vec.begin()             + 1;
    std::vector<real>::const_iterator W =  src_vec.begin() +   columns    ;
    std::vector<real>::const_iterator E =  src_vec.begin() +   columns + 2;
    std::vector<real>::const_iterator S =  src_vec.begin() + 2*columns + 1;

    for(size_t iy = 0; iy < rows - 2; ++iy) {
        for(size_t ix = 0; ix < columns - 2; ++ix) {
            size_t idx = iy * columns + ix;
            C[idx] = w * (N[idx] + S[idx] + W[idx] + E[idx]);
        }
    }
}
