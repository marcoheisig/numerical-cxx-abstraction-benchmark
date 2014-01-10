#include "config.hh"
#include "fixalloc.hh"

namespace {
struct Real {
    Real() {}
    Real(const real& x) : value(x) {}
    operator real() { return value; }
    real value;
};
}

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    using fixvector = std::vector<Real, fixalloc<Real>>;
    auto  src = fixvector(cells, Real(), (Real*)src_vec.data());
    auto dest = fixvector(cells, Real(), (Real*)dest_vec.data());

    for(size_t iy = 1; iy < rows - 1; ++iy) {
        for(size_t ix = 1; ix < columns - 1; ++ix) {
            size_t index = iy * columns + ix;
            dest[index] = w0 * w1 * (src[index - 1      ] +
                                     src[index + 1      ] +
                                     src[index - columns] +
                                     src[index + columns]);
        }
    }
}
