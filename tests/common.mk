SOURCES   := $(HW_SRCS) $(HOST_SRCS)
LLVMS     := $(SOURCES:%.c=%.ll)
PROFPASS  := $(SOURCES:%.c=%-prof.ll)
ALLCPASS  := $(SOURCES:%.c=%-alloc.ll)
DEPGPASS  := $(SOURCES:%.c=%-depg.ll)
PASSES    := $(PROFPASS) $(ALLCPASS) $(DEPGPASS)
TARGET    := $(KERNEL)

# Ordinary Clang options.
CXX+      := /usr/local/opt/llvm/bin/clang
CXX       := clang
OPT       := /usr/local/opt/llvm/bin/opt
ASMFLAG   := -S
LLVMFLAG  := -emit-llvm
CXXFLAGS  := -o3 
PROFFLAGS  := -load ../../build/skeleton/libShackletonPass.so --shackleton
ALLCFLAGS  := -load ../../build/skeleton/libStiltonPass.so --stilton
DEPGFLAGS  := -load ../../build/skeleton/libSheltonPass.so --shelton
PASSFLAGS := -select

# Create assembly.
%.ll: %.c
	$(CXX) $(ASMFLAG) $(LLVMFLAG) $(CXXFLAGS) $^ -o $@

# Run profile pass on kernel.
$(KERNEL)-prof.ll: $(KERNEL).ll
	$(OPT) $(PROFFLAGS) $(PASSFLAGS) $(ASMFLAG) $^ -o $@

# Run profile pass on main.
%-prof.ll: %.ll
	$(OPT) $(PROFFLAGS) $(ASMFLAG) $^ -o $@

# Run allocate pass on kernel.
$(KERNEL)-alloc.ll: $(KERNEL).ll
	$(OPT) $(ALLCFLAGS) $(PASSFLAGS) $(ASMFLAG) $^ -o $@

# Run depggen pass on kernel.
$(KERNEL)-depg.ll: $(KERNEL).ll
	$(OPT) $(DEPGFLAGS) $(ASMFLAG) $^ -o $@

# Link the program.
$(TARGET): $(PROFPASS)
	$(CXX+) $^ --output $@

# Run profiler.
.PHONY: profile
profile: $(TARGET)
	./$(TARGET)

# Run allocator.
.PHONY: allocate
allocate: $(KERNEL)-alloc.ll
	continue

# Run dependence graph generator.
.PHONY: depggen
depggen: $(KERNEL)-depg.ll
	continue

.PHONY: clean
clean:
	rm -f $(LLVMS) $(PASSES) $(TARGET)

