#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray& r, const hittable& world, int depth)
{
	hit_record rec;

	if (depth <= 0) return color(0, 0, 0);

	if (world.hit(r, 0.001f, infinity, rec))
	{
		//point3 target = rec.p + rec.normal + random_in_unit_sphere(); // Random Ray Direction
		point3 target = rec.p + rec.normal + random_unit_vector(); // Lambertian Reflection
		//point3 target = rec.p + random_in_hemisphere(rec.normal); // Hemispherical scattering

		return 0.5f * ray_color( ray( rec.p, target - rec.p ), world, depth-1);
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5f * (unit_direction.y() + 1.0f);

	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

int main()
{
	// Image

	const auto aspect_ratio = 16.0f / 9.0f;
	const int image_width = 1920;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World

	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5f));
	world.add(make_shared<sphere>(point3(0, -100.5f, -1), 100));

	// Camera

	camera cam;

	// Render

	std::ofstream file;
	file.open("image1.ppm", std::ios::trunc);
	if (file.is_open()) {std::cout << "file opened\n"; }

	file << "P3\n" << image_width << ' ' << image_height << "\n255\n";


	for (int j = image_height - 1; j >= 0; --j)
	{
		render_progress_print(j, image_height);

		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto u = (i + random_float()) / (image_width - 1);
				auto v = (j + random_float()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}

			write_color(file, pixel_color, samples_per_pixel);
		}
	}

	std::cout << "Render done" << std::endl;
	file.close();

	std::system("image1.ppm");

	return 0;
}