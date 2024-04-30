#include "Face.h"

Face::Face(const vector<Point> lesPoints, int id) {

	points = lesPoints;
	d_id = id;
}


Point Face::getPoint(int i)  { return points[i]; }


int Face::getId() const
{
    return d_id;
}



bool Face::operator==(Face f)
{
	if (points.size() == f.points.size()) {
		int pointsEnCommun = 0;

		for (int i = 0; i < points.size(); ++i) {
			for (int j = 0; j < points.size(); ++j)
            {
				if (points[i] == f.points[j])
				{

					pointsEnCommun++;
				}
			}
		}

		return pointsEnCommun == points.size();
	}
	return false;
}
