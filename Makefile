ITERATIONS         := 1000000
COMPILERS          :=

COMPILERS          += g++-4.1.2
g++-4.1.2_CXXFLAGS := -O3 -march=nocona -ffast-math

COMPILERS          += g++-4.3.6
g++-4.3.6_CXXFLAGS := -O3 -ffast-math -march=native

COMPILERS          += g++-4.4.7
g++-4.4.7_CXXFLAGS := -O3 -ffast-math -march=native

COMPILERS          += g++-4.5.4
g++-4.5.4_CXXFLAGS := -O3 -ffast-math -march=native

COMPILERS          += g++-4.6.3
g++-4.6.3_CXXFLAGS := -Ofast -march=native

COMPILERS          += g++-4.7.3
g++-4.7.3_CXXFLAGS := -Ofast -march=native

COMPILERS          += g++-4.8.2
g++-4.8.2_CXXFLAGS := -Ofast -march=native

COMPILERS          += icpc
icpc_CXXFLAGS      := -Ofast -march=native -fno-alias -inline-level=2 -no-inline-max-size

COMPILERS          += clang++
clang++_CXXFLAGS   := -Ofast -march=native

COMPILERS          += pgc++
pgc++_CXXFLAGS     := -fastsse -tp=sandybridge -Mvect=simd:256 -Msafeptr

#COMPILERS          += xlC
xlC_CXXFLAGS       := –O5 –q64 -qhot -qarch=pwr7 -qtune=pwr7 -qalias=noallptrs -qsimd=auto

HEADERS     := config.hh fixalloc.hh
BENCHMARKS  :=
BENCHMARKS  += plain
BENCHMARKS  += vector
#BENCHMARKS  += stencil  # does not work yet
#BENCHMARKS  += wrap     # not different enough from opwrap
BENCHMARKS  += opwrap
#BENCHMARKS  += vecvec
#BENCHMARKS  += template
BENCHMARKS   += 3ptrs
BENCHMARKS   += 4ptrs
BENCHMARKS  += iter
BENCHMARKS  += transform

TARGETS     := $(foreach COMPILER,$(COMPILERS), \
               $(foreach BENCHMARK,$(BENCHMARKS), \
               $(BENCHMARK)_$(COMPILER)))

.PHONY: all asm benchmarks run.sh clean

all:        $(TARGETS) run.sh clean.sh

$(TARGETS):  BASE = $(subst _, ,$@)
$(TARGETS):  CXX = $(word 2,$(BASE))
$(TARGETS):  CXXFLAGS = $($(CXX)_CXXFLAGS)
$(TARGETS):  SRC = $(word 1,$(BASE)).cc
$(TARGETS):  benchmark.cc $(HEADERS) $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) benchmark.cc -o $@
	$(CXX) $(CXXFLAGS) -S $(SRC) -o $@.s


run.sh: $(TARGETS)
	@echo "creating run.sh"
	@echo '#!/bin/sh' > run.sh
	@echo 'echo "== C++ abstraction compiler benchmark by Marco Heisig =="' >> run.sh
	@echo -e $(foreach BENCHMARK, $(BENCHMARKS), '\necho' \
                 $(foreach COMPILER,  $(COMPILERS), \
                 "\n./$(BENCHMARK)_$(COMPILER) $(ITERATIONS)")) >> run.sh
	@chmod a+x ./run.sh

clean.sh: $(TARGETS)
	@echo "creating clean.sh"
	@echo '#!/bin/sh' >> clean.sh
	@echo -e $(foreach BENCHMARK, $(BENCHMARKS), \
                 $(foreach COMPILER,  $(COMPILERS), \
                 "\nrm -f $(BENCHMARK)_$(COMPILER) $(BENCHMARK)_$(COMPILER).s")) >> clean.sh
	@chmod a+x ./clean.sh

clean:
	-./clean.sh
	-rm -f run.sh *.o clean.sh
