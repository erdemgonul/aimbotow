#include "Point.h"


	Point :: Point(double a,double s) {
		x = a;
		y = s;
	}
	string Point::PrintPoints() {


		std::ostringstream oss;
		oss << x << " " << y << "\n";
		
		return  oss.str();
	}

