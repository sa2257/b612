#include <stdio.h>
#include <stdlib.h>

#define FFT_SIZE 1024
#define twoPI 6.28318530717959

#pragma SDS data zero_copy(real[0:FFT_SIZE], img[0:FFT_SIZE])
void fft(double real[FFT_SIZE], double img[FFT_SIZE], double real_twid[FFT_SIZE/2], double img_twid[FFT_SIZE/2]);


////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
        double real[FFT_SIZE];
        double img[FFT_SIZE];
        double real_twid[FFT_SIZE/2];
        double img_twid[FFT_SIZE/2];
};
