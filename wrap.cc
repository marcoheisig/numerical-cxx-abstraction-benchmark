#include "config.hh"
#include "fixalloc.hh"

#define FIXVECTOR std::vector<Real, fixalloc<Real> >

namespace {
struct Real {
    Real() {}
    Real(const real& x) : value(x) {}
    operator real() { return value; }
    real value;
};
}

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    FIXVECTOR  src = FIXVECTOR(cells, Real(), (Real*) &src_vec[0]);
    FIXVECTOR dest = FIXVECTOR(cells, Real(), (Real*)&dest_vec[0]);

    for(size_t iy = 1; iy < rows - 1; ++iy) {
        for(size_t ix = 1; ix < columns - 1; ++ix) {
            size_t index = iy * columns + ix;
            dest[index] = w * (src[index - 1      ] +
                               src[index + 1      ] +
                               src[index - columns] +
                               src[index + columns]);
        }
    }
}
