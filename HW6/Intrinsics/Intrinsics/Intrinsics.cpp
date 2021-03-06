// Intrinsics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// 3.3 Building AVX Applications
void hello_avx() {
	__m256 odds = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);
	__m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);

	__m256 result = _mm256_sub_ps(evens, odds);
	float* f = (float*)&result;
	printf("%f %f %f %f %f %f %f %f\n",
		f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
}

// 4.1 Initialization with Scalar Values

void init_avx() {
	__m256i int_vector = _mm256_set_epi32(1, 2, 3, 4, 5, 6, 7, 8);
	int* ptr = (int*)&int_vector;
	printf("%d %d %d %d %d %d %d %d\n",
		ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7]);
}

void initr_avx() {
	__m256i int_vector = _mm256_setr_epi32(1, 2, 3, 4, 5, 6, 7, 8);
	int* ptr = (int*)&int_vector;
	printf("%d %d %d %d %d %d %d %d\n",
		ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7]);
}

// 4.2 Loading Data from Memory

//void load_avx() {
//	float* aligned_floats = (float*)std::aligned_alloc(32, 64 * sizeof(float));
//	__m256 vec = _mm256_load_ps(aligned_floats);
//
//	float* unaligned_floats = (float*)malloc(64 * sizeof(float));
//	__m256 vec = _mm256_loadu_ps(unaligned_floats);
//}

void mask_load() {
	int i;
	int int_array[8] = { 100, 200, 300, 400, 500, 600, 700, 800 };
	
	__m256i mask = _mm256_setr_epi32(-20, -72, -48, -9, -100, 3, 5, 8);
	__m256i result = _mm256_maskload_epi32(int_array, mask);

	int* res = (int*)&result;
	printf("%d %d %d %d %d %d %d %d\n",
		res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7]);
}

// 5.3 Fused Multiply And Add

void fmatest() {
	__m256d vecA = _mm256_setr_pd(6.0, 6.0, 6.0, 6.0);
	__m256d vecB = _mm256_setr_pd(2.0, 2.0, 2.0, 2.0);
	__m256d vecC = _mm256_setr_pd(7.0, 7.0, 7.0, 7.0);

	__m256d result = _mm256_fmaddsub_pd(vecA, vecB, vecC);
	double* res = (double*)&result;
	printf("%lf %lf %lf %lf\n", res[0], res[1], res[2], res[3]);
}

// 7 Complex Multiplication

void complex_mult() {
	__m256d vec1 = _mm256_setr_pd(4.0, 5.0, 13.0, 6.0);
	__m256d vec2 = _mm256_setr_pd(9.0, 3.0, 6.0, 7.0);
	__m256d neg = _mm256_setr_pd(1.0, -1.0, 1.0, -1.0);

	__m256d vec3 = _mm256_mul_pd(vec1, vec2);
	vec2 = _mm256_permute_pd(vec2, 0x5);
	vec2 = _mm256_mul_pd(vec2, neg);
	__m256d vec4 = _mm256_mul_pd(vec1, vec2);
	vec1 = _mm256_hsub_pd(vec3, vec4);

	double* res = (double*)&vec1;
	printf("%lf %lf %lf %lf\n", res[0], res[1], res[2], res[3]);
}

int main()
{
	hello_avx();
	init_avx();
	initr_avx();
	mask_load();
	fmatest();
	complex_mult();
	std::getchar();
    return 0;
}

