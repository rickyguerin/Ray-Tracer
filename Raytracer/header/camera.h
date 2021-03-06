#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "world.h"

class Camera {
private:
	// Orientation in world space
	glm::vec3 eye;
	glm::vec3 lookat;
	glm::vec3 up;

	// Film plane parameters
	float focalLength;
	float canvasWidth;
	float canvasHeight;
	float ldmax;
	unsigned sampleLevel;

	// World -> Camera transformation matrix
	glm::mat4 matrix;

public:
	// Constructor
	Camera(const glm::vec3& eye, const glm::vec3& lookat, const glm::vec3& up, const float focalLength, const float canvasWidth, const float canvasHeight, const float ldmax, const unsigned sampleLevel);

	// Use this camera to render an image of the World
	void render(World& world, const std::string& filename, const unsigned imageWidth, const unsigned imageHeight, const float time) const;
};

#endif