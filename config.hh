#pragma once
#include <cstddef>
#include <vector>

/*
  The benchmark performs a specified number of Jacobi sweeps on a rectangular
  domain. The domain is defined here by a size in bytes. Note, that the border
  points of the domain act as ghost layer and are not updated.

  It is advisable to keep the size small enough to fit into the target CPU's
  L1 cache, otherwise compiler optimisations will be shadowed by memory
  transfer times.
 */
typedef double real;

/* usable cache size (in bytes). Adapt this to your CPU */
const size_t usable_cache_size           = 22 * 1000;

/* the following parameters should not be changed */
const size_t domain_size       = usable_cache_size / 2;
const size_t rows              = 3;
const size_t flops_per_stencil = 4;
const real w                   = 0.25; // 1 / (4 * h^2)
const size_t columns           = 386; //(domain_size / sizeof(real) / rows);
const size_t cells             = rows * columns;
const size_t stencils_per_iter = (rows - 2) * (columns - 2);
const size_t flops_per_iter    = stencils_per_iter * flops_per_stencil;

void run(std::vector<real> &src, std::vector<real> &dest);
void runb(std::vector<real> &src, std::vector<real> &dest);
