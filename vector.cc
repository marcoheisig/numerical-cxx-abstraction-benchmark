#include "config.hh"
using namespace std;

void run(std::vector<real> &src, std::vector<real> &dest) {
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
