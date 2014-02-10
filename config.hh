#pragma once
#include <cstddef>
#include <vector>

/*
  The benchmark performs a specified number of Jacobi sweeps on a
  rectangular domain. The domain is defined here by a size in bytes and the
  number of rows. Note, that the border points of the domain act as ghost
  layer and are not updated.

  It is advisable to keep the domain size small enough to fit into the target
  CPU's L1 cache, otherwise compiler optimisations will be shadowed by memory
  transfer times.
 */
typedef double real;

/* adapt this value to cache size */
const size_t cache_size           = 28 * 1000;
const size_t domain_size       = cache_size / 2;

const size_t rows              = 3;
const size_t flops_per_stencil = 4;
const real w                   = 0.25; // 1 / (4 * h^2)
const size_t columns           = (domain_size / sizeof(real) / rows);
const size_t cells             = rows * columns;
const size_t stencils_per_iter = (rows - 2) * (columns - 2);
const size_t flops_per_iter    = stencils_per_iter * flops_per_stencil;

void run(std::vector<real> &src, std::vector<real> &dest);
