#! /usr/bin/make -f

KERNEL           = gemm
MAIN             = bench
HW_SRCS          = $(KERNEL).c
HOST_SRCS        = $(MAIN).c

SOURCES   := $(HW_SRCS) $(HOST_SRCS)
LLVMS     := $(SOURCES:%.c=%.ll)
PASSES    := $(SOURCES:%.c=%-prof.ll)
TARGET    := a.out

# Ordinary Clang options.
CXX+      := /usr/local/opt/llvm/bin/clang
CXX      := clang
OPT      := /usr/local/opt/llvm/bin/opt
ASMFLAG  := -S
LLVMFLAG := -emit-llvm
OPTFLAGS := -load ../../build/skeleton/libShackletonPass.so --shackleton
PASSFLAGS:= -select

# Create assembly.
%.ll: %.c
	$(CXX) $(ASMFLAG) $(LLVMFLAG) $^ > $@

# Run pass on kernel.
$(KERNEL)-prof.ll: $(KERNEL).ll
	$(OPT) $(OPTFLAGS) $(PASSFLAGS) $(ASMFLAG) $^ > $@

# Run pass on main.
$(MAIN)-prof.ll: $(MAIN).ll
	$(OPT) $(OPTFLAGS) $(ASMFLAG) $^ > $@

# Link the program.
$(TARGET): $(PASSES)
	$(CXX+) $^ --output $@

# Run profiler.
.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm $(LLVMS) $(PASSES) $(TARGET)

