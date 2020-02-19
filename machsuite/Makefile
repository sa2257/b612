BENCHMARKS=\
	machsuite-bfs-bulk \
	machsuite-bfs-queue \
	machsuite-fft-strided \
	machsuite-gemm-blocked \
	machsuite-gemm-ncubed \
	machsuite-gemm-ncubed-int \
	machsuite-md-grid \
	machsuite-md-knn \
	machsuite-nw \
	machsuite-spmv-crs \
	machsuite-spmv-ellpack \
	machsuite-stencil-stencil2d \
	machsuite-stencil-stencil3d \
	machsuite-viterbi
	#machsuite-aes \
	machsuite-backprop \
	machsuite-fft-transpose \
	machsuite-kmp \
	machsuite-sort-merge \
	machsuite-sort-radix \

.PHONY: run clean

run:
	@( for b in $(BENCHMARKS); do $(MAKE) -C $$b run; done )

clean:
	@( for b in $(BENCHMARKS); do $(MAKE) -C $$b clean || exit ; done )
