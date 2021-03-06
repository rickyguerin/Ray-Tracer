#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

#include "shape.h"

class Triangle : public Shape {
private:
	// Vertices of Triangle in clockwise order
	std::vector<glm::vec3> vertices;

public:
	// Constructor
	Triangle(IlluminationModel* illumination, const std::vector<glm::vec3>& vertices);

	// Override from Shape
	virtual void transformToCameraSpace(const glm::mat4& cameraMatrix);
	virtual Intersection collision(const Ray& ray) const;
};

#endif