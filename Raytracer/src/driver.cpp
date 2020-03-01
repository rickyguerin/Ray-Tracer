#include <vector>
#include <string>

#include "../header/world.h"
#include "../header/camera.h"
#include "../header/sphere.h"

int main() {
	// Create the World
	World world(glm::ivec4(50, 150, 250, 255));
	world.addProgram(SphereProgram("world/prog.txt"));
	world.addProgram(SphereProgram("world/vertSphere.txt"));

	// Create the Camera
	glm::vec3 pos{ 0, 0, 2 };
	glm::vec3 lookat{ 0, 0, 0 };
	glm::vec3 up{ 0, 1, 0 };

	Camera camera(pos, lookat, up, 45, 2.0f);

	// Animation frame information
	const float fps = 1;
	const float duration = 4.0;
	const unsigned frames = fps * duration;

	// Animation timer
	float time = 0.0;
	const float spf = duration / frames;

	// Render frames
	for (int i = 0; i < frames; i++) {
		camera.render(world, "../images/temp/output_" + std::to_string(i) + ".png", 600, 400, time);
		time += spf;
	}

	return 0;
}