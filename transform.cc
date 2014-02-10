#include <algorithm>
#include <functional>
#include "config.hh"

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    size_t len = columns - 2;
    std::vector<real>::iterator       C = dest_vec.begin() +   columns + 1;
    std::vector<real>::const_iterator N =  src_vec.begin()             + 1;
    std::vector<real>::const_iterator W =  src_vec.begin() +   columns    ;
    std::vector<real>::const_iterator E =  src_vec.begin() +   columns + 2;
    std::vector<real>::const_iterator S =  src_vec.begin() + 2*columns + 1;

    transform(N, N+len, W, C, std::plus<real>());
    transform(E, E+len, C, C, std::plus<real>());
    transform(S, S+len, C, C, std::plus<real>());
    transform(C, C+len, C,    std::bind2nd(std::multiplies<real>(),w));
}
