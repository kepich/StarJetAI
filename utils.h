#pragma once
#include <dvec.h>

float _mm256_reduce_add_ps(__m256 v1) {
	__m128 vec4 = _mm_hadd_ps(_mm256_extractf128_ps(v1, 0), _mm256_extractf128_ps(v1, 1));
	vec4 = _mm_hadd_ps(vec4, vec4);
	return _mm_cvtss_f32(_mm_hadd_ps(vec4, vec4));
}

float _mm256_reduce_add_ps(__m256 v1, __m256 v2) {
	return _mm256_reduce_add_ps(v1) + _mm256_reduce_add_ps(v2);
}
