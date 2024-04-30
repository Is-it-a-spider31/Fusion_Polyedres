#include "Vertex.h"


Vertex::Vertex(int id, double x, double y, double z) : d_id(id), d_x(x), d_y(y), d_z(z) {}

Vertex::~Vertex() {}


int Vertex::getId() const { return d_id; }

double Vertex::getX() const { return d_x; }

double Vertex::getY() const { return d_y; }

double Vertex::getZ() const { return d_z; }


void Vertex::setId(int id){ d_id = id; }

void Vertex::setX(double x){ d_x = x; }

void Vertex::setY(double y){ d_y = y; }

void Vertex::setZ(double z){ d_z = z; }

void Vertex::setVertex(const Vertex& v){
	d_id = v.d_id;
	d_x = v.d_x;
	d_y = v.d_y;
	d_z = v.d_z;
}


bool Vertex::operator==(const Vertex& v) const {
	return(d_x == v.d_x && d_y == v.d_y && d_z == v.d_z);
}

bool Vertex::operator!=(const Vertex& v) const {
	return !(*this == v);
}

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	os << "v " << v.getX() << " " << v.getY() << " " << v.getZ() << std::endl;

	return os;
}
