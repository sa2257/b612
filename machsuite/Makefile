BENCHMARKS=\
	machsuite-aes \
	machsuite-backprop \
	machsuite-bfs-bulk \
	machsuite-bfs-queue \
	machsuite-fft-strided \
	machsuite-fft-transpose \
	machsuite-gemm-blocked \
	machsuite-gemm-ncubed \
	machsuite-gemm-ncubed-int \
	machsuite-kmp \
	machsuite-md-grid \
	machsuite-md-knn \
	machsuite-nw \
	machsuite-sort-merge \
	machsuite-sort-radix \
	machsuite-spmv-crs \
	machsuite-spmv-ellpack \
	machsuite-stencil-stencil2d \
	machsuite-stencil-stencil3d \
	machsuite-viterbi

.PHONY: profile allocate clean

profile:
	@( for b in $(BENCHMARKS); do $(MAKE) -C $$b profile; done )

allocate:
	@( for b in $(BENCHMARKS); do $(MAKE) -C $$b allocate; done )

clean:
	@( for b in $(BENCHMARKS); do $(MAKE) -C $$b clean || exit ; done )
