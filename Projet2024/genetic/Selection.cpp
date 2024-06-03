#include "Selection.h"

vector<int> Selection::getParent1() const
{
    return d_parent_1;
}

vector<int> Selection::getParent2() const
{
    return d_parent_2;
}

void Selection::clearParentsList()
{
    d_parents.clear();
}

vector<vector<int>> Selection::getParents() const
{
    return d_parents;
}
