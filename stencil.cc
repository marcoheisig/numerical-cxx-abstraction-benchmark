#include "config.hh"
#include "runb.hh"

namespace {
template<size_t W, size_t H>
struct Stencil {
    inline real apply_to(real* data, size_t index, size_t stride) const {
        real acc = 0.0;
        size_t i = index - 1 - stride; // upper left corner of the stencil
        for(size_t iy = 0; iy < H; ++iy) {
            for(size_t ix = 0; ix < W; ++ix) {
                acc += weights[iy][ix] * data[i + ix + iy * stride];
            }
        }
        return acc;
    }

    double weights[W][H];
};
}

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    real *src  =  src_vec.data();
    real *dest = dest_vec.data();

    // C++11 - embrace the future (finally more braces than Lisp...)
    Stencil<3, 3> stencil;

    for(size_t iy = 1; iy < rows - 1; ++iy) {
        for(size_t ix = 1; ix < columns - 1; ++ix) {
            size_t index = iy * columns + ix;
            dest[index] = stencil.apply_to(src, index, columns);
        }
    }
}
