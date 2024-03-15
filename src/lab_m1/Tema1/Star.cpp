#include "Star.h"

Star::Star() {
	this->color = "";
	this->position = glm::vec3(0, 0, 0);
	this->time_passed = 0;
	this->x_center = 0;
	this->y_center = 0;
	this->radius = 20;
}

Star::~Star() {
	this->color = "";
	this->position = glm::vec3(0, 0, 0);
	this->time_passed = 0;
	this->x_center = 0;
	this->y_center = 0;
	this->radius = 20;

}	



std::string Star::getColor() {
	return this->color;
}

void Star::setColor(std::string color) {
	this->color = color;
}

glm::vec3 Star::getPosition() {
	return this->position;
}

void Star::setPosition(glm::vec3 position) {
	this->position = position;
}

float Star::getTimePassed() {
	return this->time_passed;
}
	
void Star::setTimePassed(float time_passed) {
	this->time_passed = time_passed;
}

int Star::getXCenter() {
	return this->x_center;
}

void Star::setXCenter(int x_center) {
	this->x_center = x_center;
}

int Star::getYCenter() {
	return this->y_center;
}

void Star::setYCenter(int y_center) {
	this->y_center = y_center;
}

float Star::getRadius() {
	return this->radius;
}

void Star::setRadius(float radius) {
	this->radius = radius;
}