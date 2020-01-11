#include "../header/world.h"
#include <iostream>
#include <fstream>

glm::ivec4 World::trace(Ray ray, double time) {

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].collision(ray, time)) {
			return glm::ivec4(255, 0, 0, 255);
		}
	}

	if (double(rand()) / (double(RAND_MAX) + 1.0) < 0.0005) {
		return glm::ivec4(255, 255, 255, 255);
	}
	else {
		return glm::ivec4(0, 0, 0, 255);
	}
}

void World::add(std::string filename) {
	std::ifstream inf(filename);

	std::string token;

	Sphere sphere;

	inf >> token;
	if (token.compare("SPHERE") == 0) {
		while (inf) {
			inf >> token;
			if (token.compare("FRAME") == 0) {
				inf >> token;
				double timestamp = std::stod(token);

				inf >> token;
				double x = std::stod(token);

				inf >> token;
				double y = std::stod(token);
				
				inf >> token;
				double z = std::stod(token);
				
				inf >> token;
				double radius = std::stod(token);

				SphereFrame sf {
					timestamp,
					glm::vec3(x, y, z),
					radius
				};

				sphere.addFrame(sf);
			}
		}

		objects.push_back(sphere);
	}
}