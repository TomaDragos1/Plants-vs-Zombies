#pragma once

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "components/simple_scene.h"
#include "lab_m1/Tema1/Star.h"


using namespace std;

class Gun
{
public:
	Gun();
	~Gun();
	std::string getColor();
	void setColor(std::string color);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	std::vector<Star>& getShootingStars();
	void setShootingStars(std::vector<Star> shooting_stars);
	float getTimeToShoot();
	void setTimeToShoot(float time_to_shoot);
	std::vector<Star> shooting_stars;
	bool getFirstShoot();
	void setFirstShoot(bool first_shoot);
	int getHit();
	void setHit(int hit);
	float getTime();
	void setTime(float time);

	

private:
	float time_to_shoot;
	std::string color;
	glm::vec3 position;
	bool first_shoot;
	int hit;
	float time;

};