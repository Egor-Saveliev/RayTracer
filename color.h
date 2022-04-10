#pragma once

#include "vec3.h"

void write_color(std::ofstream& out, color pixel_color, int samples_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide the color by the number of samples and gamma-correct for gamma=2.0
	auto scale = 1.0f / samples_per_pixel;
	//std::cout << "Scale: [" << scale << "]\n";

	r = sqrt(scale * r);
	//std::cout << "R: [" << r << "]\n";

	g = sqrt(scale * g);
	//std::cout << "G: [" << g << "]\n";

	b = sqrt(scale * b);
	//std::cout << "B: [" << b << "]\n";

	// Write the translated [0, 255] value for each color component
	out << static_cast<int>(256 * clamp(r, 0.0f, 0.999f)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0f, 0.999f))<< ' '
		<< static_cast<int>(256 * clamp(b, 0.0f, 0.999f)) << '\n';
}