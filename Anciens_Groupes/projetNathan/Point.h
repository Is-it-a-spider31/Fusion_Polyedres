#ifndef POINT_H
#define POINT_H


class Point
{
   public:
	Point(int id, double x, double y, double z);
	~Point();

	int getId() const;
	double getX() const;
	double getY() const;
	double getZ() const;

	void setId(int id);
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setPoint(const Point& v);

	bool operator==(Point v);
	bool operator!=(Point v);

private:
	int d_id;
	double d_x, d_y, d_z;
};

#endif // POINT_H
