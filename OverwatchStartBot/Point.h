#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;
class Point {
public:
	double x, y,time;
	Point(double x, double y);
	string PrintPoints();
	double setTime();
};