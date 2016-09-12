#pragma once
#include <string>
using std::string;

class Paddle
{
public:
	int xPos, yPos, yVel, width, height, speed;
	unsigned int color, texture;

	void moveUp(int ceilingValue);
	void moveDown(int floorValue);
};

void Paddle::moveUp(int ceilingValue)
{
	if (yPos >= ceilingValue)
	{
		yPos = ceilingValue;
		yVel = 0;
	}
	else
	{
		yPos += speed;
		yVel = speed;
	}
}

void Paddle::moveDown(int floorValue)
{
	if (yPos - height <= floorValue)
	{
		yPos = height + floorValue;
		yVel = 0;
	}
	else
	{
		yPos -= speed;
		yVel = -speed;
	}
}