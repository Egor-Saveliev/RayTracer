#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.141592f;

// Utility Functions

inline float degrees_to_radians(float degrees)
{
	return degrees * pi / 180.0f;
}

inline float random_float()
{
	static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	static std::mt19937 generator;
	return distribution(generator);
}

inline float random_float(float min, float max)
{
	static std::uniform_real_distribution<float> distribution(min, max);
	static std::mt19937 generator;
	return distribution(generator);
}

inline float clamp(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline void render_progress_print(const int j, const int height)
{
	float r_progress = 100 - (100 * (j / static_cast<float>(height)));
	
	if (fmod(r_progress, 1) != 0) {
		system("CLS");

		std::cout << "Render progress: "
			<< static_cast<int>(r_progress) << '%'
			<< std::flush;
	}
}

// Common Headers

#include "ray.h"
#include "vec3.h"