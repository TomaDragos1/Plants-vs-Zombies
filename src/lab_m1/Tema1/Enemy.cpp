#include "Enemy.h"



Enemy::Enemy()
{
	this->time = 0;
	this->color = "";
	this->position = glm::vec3(0, 0, 0);
	this->centre_x = 0;
	this->centre_y = 0;
	this->lives = 3;
	this->radius = 60;
}

Enemy::~Enemy()
{
	this->time = 0;
	this->color = "";
	this->position = glm::vec3(0, 0, 0);
	this->centre_x = 0;
	this->centre_y = 0;
	this->lives = 3;
	this->radius = 60;
}

float Enemy::getTime() {
	return this->time;
}

void Enemy::setTime(float time) {
	this->time = time;
}

std::string Enemy::getColor() {
	return this->color;
}

void Enemy::setColor(std::string color) {
	this->color = color;
}

glm::vec3 Enemy::getPosition() {
	return this->position;
}

void Enemy::setPosition(glm::vec3 position) {
	this->position = position;
}

float Enemy::getXCenter() {
	return this->centre_x;
}

void Enemy::setXCenter(float x_center) {
	this->centre_x = x_center;
}

float Enemy::getYCenter() {
	return this->centre_y;
}

void Enemy::setYCenter(float y_center) {
	this->centre_y = y_center;
}

int Enemy::getLives() {
	return this->lives;
}

void Enemy::setLives(int lives) {
	this->lives = lives;
}

bool Enemy::getFinished() {
	return this->finished;
}

void Enemy::setFinished(bool finished) {
	this->finished = finished;
}

float Enemy::getRadius() {
	return this->radius;
}

void Enemy::setRadius(float radius) {
	this->radius = radius;
}