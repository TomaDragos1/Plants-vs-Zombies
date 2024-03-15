#pragma once

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "components/simple_scene.h"


using namespace std;

class Star
{
public:
	Star();
	~Star();
	std::string getColor();
	void setColor(std::string color);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	float getTimePassed();
	void setTimePassed(float time_passed);
	int getXCenter();
	void setXCenter(int x_center);
	int getYCenter();
	void setYCenter(int y_center);
	float getRadius();
	void setRadius(float radius);

private:
	std::string color;
	float time_passed;
	glm::vec3 position;
	int x_center;
	int y_center;
	float radius;
};	