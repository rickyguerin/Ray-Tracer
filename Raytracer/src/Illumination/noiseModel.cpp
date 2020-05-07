#include <algorithm>
#include <glm/common.hpp>
#include "../../header/Illumination/noiseModel.h"

NoiseModel::NoiseModel(const glm::vec3& diffuseColor, const glm::vec3& specularColor,
	const float ambientConst, const float diffuseConst, const float specularConst, const float specularExp) {

	this->noiseGenerator = FastNoise();
	this->noiseGenerator.SetFrequency(10.0);

	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;

	this->ambientConst = ambientConst;
	this->diffuseConst = diffuseConst;
	this->specularConst = specularConst;
	this->specularExp = specularExp;
}

glm::vec3 NoiseModel::illuminate(Intersection intersection, const std::vector<Light>& lights, const bool shadow) const {
	float noise = noiseGenerator.GetPerlinFractal(intersection.point.x, intersection.point.y, intersection.point.z);

	noise = (noise + 1.0) / 2.0;
	noise = noise < 0.0 ? 0.0 : noise;
	noise = noise > 1.0 ? 1.0 : noise;

	glm::vec3 moddedColor = diffuseColor * glm::vec3(noise, noise, noise);

	glm::vec3 ambientPart = moddedColor * glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 diffusePart = glm::vec3();
	glm::vec3 specularPart = glm::vec3();

	glm::vec3 src, r;

	if (!shadow) {
		for (int i = 0; i < lights.size(); i++) {
			src = glm::normalize(lights[i].position - intersection.point);
			r = glm::reflect(src, intersection.normal);

			diffusePart += lights[i].color * moddedColor * std::max(0.0f, glm::dot(src, intersection.normal));
			specularPart += lights[i].color * specularColor * std::pow(std::max(0.0f, glm::dot(r, intersection.ray)), specularExp);
		}
	}

	return ambientConst * ambientPart + diffuseConst * diffusePart + specularConst * specularPart;
}

IlluminationModel* NoiseModel::interpolate(IlluminationModel* other, const float t) const {
	return new NoiseModel(
		glm::mix(this->diffuseColor, ((NoiseModel*)other)->diffuseColor, t),
		glm::mix(this->specularColor, ((NoiseModel*)other)->specularColor, t),

		glm::mix(this->ambientConst, ((NoiseModel*)other)->ambientConst, t),
		glm::mix(this->diffuseConst, ((NoiseModel*)other)->diffuseConst, t),
		glm::mix(this->specularConst, ((NoiseModel*)other)->specularConst, t),
		glm::mix(this->specularExp, ((NoiseModel*)other)->specularExp, t)
	);
}