#pragma once

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "components/simple_scene.h"
#include "lab_m1/Tema1/Star.h"


using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();
	std::string getColor();
	void setColor(std::string color);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	float getTime();
	void setTime(float time);
	float getXCenter();
	void setXCenter(float x_center);
	float getYCenter();
	void setYCenter(float y_center);
	int getLives();
	void setLives(int lives);
	bool getFinished();
	void setFinished(bool finished);
	float getRadius();
	void setRadius(float radius);

private:
	float time;
	std::string color;
	glm::vec3 position;
	float centre_x;
	float centre_y;
	int lives;
	bool finished;
	float radius;

};