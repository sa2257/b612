SOURCES   := $(HW_SRCS) $(HOST_SRCS)
LLVMS     := $(SOURCES:%.c=%.ll)
PASSES    := $(SOURCES:%.c=%-alloc.ll)
TARGET    := $(KERNEL)

# Ordinary Clang options.
CXX+      := /usr/local/opt/llvm/bin/clang
CXX       := clang
OPT       := /usr/local/opt/llvm/bin/opt
ASMFLAG   := -S
LLVMFLAG  := -emit-llvm
CXXFLAGS  := -o3 
OPTFLAGS  := -load ../../build/skeleton/libStiltonPass.so --stilton
PASSFLAGS := -select

# Create assembly.
%.ll: %.c
	$(CXX) $(ASMFLAG) $(LLVMFLAG) $(CXXFLAGS) $^ -o $@

# Run pass on kernel.
$(KERNEL)-alloc.ll: $(KERNEL).ll
	$(OPT) $(OPTFLAGS) $(PASSFLAGS) $(ASMFLAG) $^ -o $@

# Run allocator.
.PHONY: run
alloc: $(KERNEL)-alloc.ll
	continue

.PHONY: clean
clean:
	rm -f $(LLVMS) $(PASSES) $(TARGET)

