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


bool test_x_collision(vector<float>* first_rect, vector<float>* second_rect) {
	if (((*first_rect)[0] > (*second_rect)[0]) && ((*first_rect)[0] < ((*second_rect)[0] + (*second_rect)[1])))
		return true;
	else if ((((*first_rect)[0] + (*first_rect)[1]) > (*second_rect)[0]) && (((*first_rect)[0] + (*first_rect)[1]) < ((*second_rect)[0] + (*second_rect)[1])))
		return true;
	else
		return false;
};

bool test_y_collision(vector<float>* first_rect, vector<float>* second_rect) {
	if (((*first_rect)[2] > (*second_rect)[2]) && ((*first_rect)[2] < ((*second_rect)[2] + (*second_rect)[3])))
		return true;
	else if ((((*first_rect)[2] + (*first_rect)[2]) > (*second_rect)[2]) && (((*first_rect)[2] + (*first_rect)[3]) < ((*second_rect)[2] + (*second_rect)[3])))
		return true;
	else
		return false;
};

bool test_collision(GameObject* first, GameObject* second) {
	vector<float>* first_rect = first->get_obj_rect();
	vector<float>* second_rect = second->get_obj_rect();

	return ((test_x_collision(first_rect, second_rect) ||
		test_x_collision(second_rect, first_rect)) &&
		(test_y_collision(first_rect, second_rect) ||
			test_y_collision(second_rect, first_rect)));
}
