#pragma once
#pragma once

#include <string>
using std::string;

class Paddle
{
public:
	int xPos, yPos, width, height, speed;
	unsigned int color, texture;

	bool BoundaryDetection(int ceilingValue, int floorValue);
};

bool Paddle::BoundaryDetection(int ceilingValue, int floorValue)
{
	return true;
}