#ifndef POLYEDRE_H
#define POLYEDRE_H

#include "Face.h"


class Polyedre
{
public:

	Polyedre(int id);

	int getId() const;

	vector<Face> faces;

private:
	int d_id;

};

#endif
