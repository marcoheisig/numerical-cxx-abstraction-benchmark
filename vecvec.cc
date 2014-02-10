#include "config.hh"
#include "fixalloc.hh"

#define FIXVECTOR std::vector<Real, fixalloc<Real> >

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

    FIXVECTOR  src[rows];
    FIXVECTOR dest[rows];
    for(size_t i = 0; i < rows; ++i) {
        src[i]  = FIXVECTOR(columns, Real(), & src_ptr[i * columns]);
        dest[i] = FIXVECTOR(columns, Real(), &dest_ptr[i * columns]);
    }

    for(size_t iy = 1; iy < rows - 1; ++iy) {
        for(size_t ix = 1; ix < columns - 1; ++ix) {
            dest[iy][ix] = w * (src[iy - 1][ix] +
                                src[iy + 1][ix] +
                                src[iy][ix - 1] +
                                src[iy][ix + 1]);
        }
    }
}
