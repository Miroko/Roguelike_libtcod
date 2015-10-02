#pragma once
#include "Point2D.h"
#include <memory>
#include <vector>

class AiFov
{
private:
	int size;
	Point2D centerLocation;
	int luminosityDropDistance;
	double luminosityDropPerDistance;
	std::vector<std::vector<double>> luminosities;

	void setLuminosity(double value, Point2D &location);
	void castRay(Point2D &fromAreaLocation, Point2D &toLuminositiesArrayLocation);

public:
	// 0.0 <-> 1.0 // 0.0 <= invisible
	double getLuminosity(Point2D &fromLocation, Point2D &toLocation);
	void compute(Point2D &fromLocation);

	AiFov(int distance, int luminosityDropDistance) :
		size(distance * 2 + 1),
		centerLocation(Point2D(distance, distance)),
		luminosityDropDistance(luminosityDropDistance),
		luminosityDropPerDistance(-1.0 / (distance - luminosityDropDistance)){
		luminosities.resize(size);
		for (auto &arrayX : luminosities){
			arrayX.resize(size);
		}
	}
};

