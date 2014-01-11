ITERATIONS         := 1000000
COMPILERS          := icpc clang++ g++-4.8.2 g++
icpc_CXXFLAGS      := -Ofast -Wall -Werror -std=c++11 -march=native -mtune=native \
-fno-alias -inline-level=2 -no-inline-max-size
g++-4.8.2_CXXFLAGS := -Ofast -Wall -Werror -std=c++11 -march=native -mtune=native
g++_CXXFLAGS := -Ofast -Wall -Werror -std=c++11 -march=native -mtune=native
clang++_CXXFLAGS   := -Ofast -Wall -Werror -std=c++11 -march=native -mtune=native

HEADERS     := config.hh fixalloc.hh
BENCHMARKS  := plain wrapped vector vecvec stencil #lambda
TARGETS     := $(foreach COMPILER,$(COMPILERS), \
               $(foreach BENCHMARK,$(BENCHMARKS), \
               $(BENCHMARK)_$(COMPILER)))
ASMFILES    := $(patsubst %, %.s, $(TARGETS))

.PHONY: all asm benchmarks run.sh clean

all:        benchmarks asm run.sh
benchmarks: $(TARGETS)
asm:        $(ASMFILES)

define BUILD_TEMPLATE =
$(1)_$(2): $(1).cc benchmark.cc $$(HEADERS)
	$(2) $$($(2)_CXXFLAGS) $$< benchmark.cc -o $$@
endef

define ASM_TEMPLATE =
$(1)_$(2).s: $(1).cc benchmark.cc $$(HEADERS)
	$(2) $$($(2)_CXXFLAGS) -c -S $$< -o $$@
endef

$(foreach COMPILER,  $(COMPILERS),  \
    $(foreach BENCHMARK, $(BENCHMARKS), \
    $(eval $(call BUILD_TEMPLATE,$(BENCHMARK),$(COMPILER))) \
    $(eval $(call ASM_TEMPLATE,$(BENCHMARK),$(COMPILER)))))


run.sh: $(TARGETS)
	@echo "creating run.sh"
	@echo '#!/bin/sh' > run.sh
	@echo 'echo "== C++ abstraction compiler benchmark by Marco Heisig =="' >> run.sh
	@echo -e $(foreach BENCHMARK, $(BENCHMARKS), '\necho "= $(BENCHMARK) ="' \
             $(foreach COMPILER,  $(COMPILERS), \
             "\n./$(BENCHMARK)_$(COMPILER) $(ITERATIONS)")) >> run.sh
	@chmod a+x ./run.sh

clean:
	-rm -f $(ASMFILES) $(TARGETS) *.o
