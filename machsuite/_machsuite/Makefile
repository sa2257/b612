SOURCES   := $(HW_SRCS) $(HOST_SRCS)
LLVMS     := $(SOURCES:%.c=%.ll)
PASSES    := $(SOURCES:%.c=%-prof.ll)
TARGET    := $(KERNEL)

# Ordinary Clang options.
CXX+      := /usr/local/opt/llvm/bin/clang
CXX       := clang
OPT       := /usr/local/opt/llvm/bin/opt
ASMFLAG   := -S
LLVMFLAG  := -emit-llvm
CXXFLAGS  := -o3 
OPTFLAGS  := -load ../../build/skeleton/libShackletonPass.so --shackleton
PASSFLAGS := -select

# Create assembly.
%.ll: %.c
	$(CXX) $(ASMFLAG) $(LLVMFLAG) $(CXXFLAGS) $^ -o $@

# Run pass on kernel.
$(KERNEL)-prof.ll: $(KERNEL).ll
	$(OPT) $(OPTFLAGS) $(PASSFLAGS) $(ASMFLAG) $^ -o $@

# Run pass on main.
%-prof.ll: %.ll
	$(OPT) $(OPTFLAGS) $(ASMFLAG) $^ -o $@

# Link the program.
$(TARGET): $(PASSES)
	$(CXX+) $^ --output $@

# Run profiler.
.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(LLVMS) $(PASSES) $(TARGET)

