#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "image.cpp"
#include "ray.cpp"

class Camera {
private:
	// Position
	glm::vec3 pos;
	glm::vec3 lookat;
	glm::vec3 up;

	// Film Plane
	unsigned width{ 16 };
	unsigned height{ 9 };
	float focalLength{ 1 };

public:
	Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, unsigned width, unsigned height, float focalLength) {
		this->pos = pos;
		this->lookat = lookat;
		this->up = up;

		this->width = width;
		this->height = height;
		this->focalLength = focalLength;
	}

	void render(const char* filename, const unsigned imageWidth, const unsigned imageHeight) {

		Image output(imageWidth, imageHeight);

		const float pixelWidth = width / imageWidth;
		const float pixelHeight = height / imageHeight;

		const float minX = (pixelWidth - width) / 2;
		const float minY = (pixelHeight - height) / 2;

		Ray ray(pos);
		int px, py;

		for (unsigned y = 0; y < output.getHeight(); y++) {
			for (unsigned x = 0; x < output.getWidth(); x++) {

				px = minX + pixelWidth * x;
				py = minY + pixelWidth * y;

				glm::vec3 destination(px, py, focalLength);
				ray.setDirection(glm::normalize(destination));

				output.setPixel(x, y, 255 * !(x & y), x | y, x | y, 255);
			}
		}

		output.write(filename);
	}
};