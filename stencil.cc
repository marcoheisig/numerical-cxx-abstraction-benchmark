#include <array>
#include "config.hh"

#include <iostream>
using namespace std;
namespace {

template<size_t H, size_t W>
struct Stencil {
    Stencil(std::array<std::array<real, W>, H> weights)
        : weights(weights) { }

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
    const std::array<std::array<real, W>, H> weights;
};
}

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    real *src  =  src_vec.data();
    real *dest = dest_vec.data();

    // C++11 - embrace the future (finally more braces than Lisp...)
    Stencil<3, 3> stencil = {{{
                {{0, w, 0}},
                {{w, 0, w}},
                {{0, w, 0}}
            }}};

    for(size_t iy = 1; iy < rows - 1; ++iy) {
        for(size_t ix = 1; ix < columns - 1; ++ix) {
            size_t index = iy * columns + ix;
            dest[index] = stencil.apply_to(src, index, columns);
        }
    }
}
