#ifndef FACE_H
#define FACE_H

#include "Point.h"
#include <vector>

using namespace std;

class Face
{
public:
	Face(const vector<Point> lesPoints, int id);

	Point getPoint(int i) ;
	vector<Point> points;

	int getId() const;

	bool operator==(Face f);


private:
	int d_id;
};

#endif

