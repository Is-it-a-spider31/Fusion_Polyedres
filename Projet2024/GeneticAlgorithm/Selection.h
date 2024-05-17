#pragma once
class Selection
{
public:

	virtual void select();

protected:

	vector<int> d_parent_1;
	vector<int> d_parent_2;

};

