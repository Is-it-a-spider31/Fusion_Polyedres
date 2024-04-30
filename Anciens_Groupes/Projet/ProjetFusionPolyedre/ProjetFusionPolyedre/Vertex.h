#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <vector>

//Point 3D
class Vertex
{
public:
	Vertex(int id, double x, double y, double z);
	~Vertex();

	//Getters
	int getId() const;
	double getX() const;
	double getY() const;
	double getZ() const;

	//Setters
	void setId(int id);
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setVertex(const Vertex& v);

	//Surcharges
	bool operator==(const Vertex& v) const;
	bool operator!=(const Vertex& v) const;

	//Entrées - Sorties
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);

private:
	int d_id; //identifiant du point 3D
	double d_x, d_y, d_z; //coordonnées 3D
};

#endif

