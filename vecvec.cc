#include <array>
#include "config.hh"
#include "fixalloc.hh"

namespace {
struct Real {
    real value;
    Real() {} // necessary to avoid vector initializing mem to zero
    Real(const real& x) : value(x) {}
    operator real() { return value; }
};
}

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    Real *src_ptr  = (Real*) src_vec.data();
    Real *dest_ptr = (Real*)dest_vec.data();
    using fixvector = std::vector<Real, fixalloc<Real>>;

    fixvector src[3] = {
        {columns, Real(), &src_ptr[0 * columns]},
        {columns, Real(), &src_ptr[1 * columns]},
        {columns, Real(), &src_ptr[2 * columns]}
        };

    fixvector dest[3] = {
        {columns, Real(), &dest_ptr[0 * columns]},
        {columns, Real(), &dest_ptr[1 * columns]},
        {columns, Real(), &dest_ptr[2 * columns]}
        };

    for(size_t iy = 1; iy < rows - 1; ++iy) {
        for(size_t ix = 1; ix < columns - 1; ++ix) {
            dest[iy][ix] = w0 * w1 * (src[iy - 1][ix] +
                                      src[iy + 1][ix] +
                                      src[iy][ix - 1] +
                                      src[iy][ix + 1]);
        }
    }
}
