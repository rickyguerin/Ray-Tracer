#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <glm/vec4.hpp>
#include "sphere.h"
#include "ray.h"

class World {
private:
	std::vector<Sphere> objects;

public:
	World(std::vector<Sphere> objects);

	glm::ivec4 trace(Ray ray);
};

#endif
