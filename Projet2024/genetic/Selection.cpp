#include "Selection.h"

/**
 * @brief R�cup�re le premier parent individuel
 * @return Le premier parent
 */
vector<int> Selection::getParent1() const
{
    return d_parent_1;
}

/**
     * @brief R�cup�re le deuxi�me parent individuel
     * @return Le premier parent
     */
vector<int> Selection::getParent2() const
{
    return d_parent_2;
}

/**
     * @brief Vide la liste des parents
     */
void Selection::clearParentsList()
{
    d_parents.clear();
}


/**
 * @brief Vide la liste des parents
 */
vector<vector<int>> Selection::getParents() const
{
    return d_parents;
}
