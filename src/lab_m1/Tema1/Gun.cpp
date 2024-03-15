#include "Gun.h"

Gun::Gun() {
	this->color = "";
	this->position = glm::vec3(0, 0, 0);
	this->time_to_shoot = 0;
	this->first_shoot = true;
	this->hit = 0;
	this->time = 0;

}

Gun::~Gun() {
	this->color = "";
	this->position = glm::vec3(0, 0, 0);
	this->time_to_shoot = 0;
	this->first_shoot = true;
	this->hit = 0;
	this->time = 0;
}

std::string Gun::getColor() {
	return this->color;
}

void Gun::setColor(std::string color) {
	this->color = color;
}

glm::vec3 Gun::getPosition() {
	return this->position;
}

void Gun::setPosition(glm::vec3 position) {
	this->position = position;
}

std::vector<Star>& Gun::getShootingStars() {
	return this->shooting_stars;
}

void Gun::setShootingStars(std::vector<Star> shooting_stars) {
	this->shooting_stars = shooting_stars;
}

float Gun::getTimeToShoot() {
	return this->time_to_shoot;
}

void Gun::setTimeToShoot(float time_to_shoot) {
	this->time_to_shoot = time_to_shoot;
}

bool Gun::getFirstShoot() {
	return this->first_shoot;
}

void Gun::setFirstShoot(bool first_shoot) {
	this->first_shoot = first_shoot;
}

int Gun::getHit() {
	return this->hit;
}

void Gun::setHit(int hit) {
	this->hit = hit;
}

float Gun::getTime() {
	return this->time;
}

void Gun::setTime(float time) {
	this->time = time;
}