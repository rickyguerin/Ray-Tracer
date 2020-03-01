#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

static const double EPSILON = 0.001;

// One keyframe from a Sphere input file
struct SphereFrame {
	// Time when this frame begins
	float timestamp;

	// Location of Sphere center at this time
	glm::vec3 position;

	// Color of Sphere at this time
	glm::ivec4 color;

	// Radius of Sphere at this time
	float radius;
};

class Sphere {
private:
	// All keyframes from input file
	std::vector<SphereFrame> frames;

public:
	// Add a frame to frames
	void addFrame(SphereFrame frame);

	// Get the index of the active frame at the given time
	unsigned getCurrentFrame(float time);

	// Accessors
	glm::vec3 getPos(unsigned frame, float time);
	glm::ivec4 getColor(unsigned frame, float time);
	float getRadius(unsigned frame, float time);

	// Determine if a ray collides with this Sphere
	bool collision(glm::vec3 ray, float time);

	// Determine what color to return if a ray collision occurs
	glm::ivec4 illuminate(float time);

	// Edit frames to move this Sphere into camera space
	void transformToCameraSpace(glm::mat4 cameraMatrix);
};

#endif