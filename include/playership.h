#ifndef PlayerShip_H
#define PlayerShip_H

#include "enemymodel.h"
#include "gameobject.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file PlayerShip.h
/// @brief this class inherits from GameEntity
/// @author Naomi Morgan
/// @version 1.0
/// @date 11/05/17
/// @class PlayerShip
/// @brief enemy ships
//----------------------------------------------------------------------------------------------------------------------
class PlayerShip : public GameObject
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief cstr for PlayerShip class.
    /// @param ngl::vec3 stores position data
    /// @param const char* is the filename of the model used.
    //----------------------------------------------------------------------------------------------------------------------
    PlayerShip(ngl::Vec3, int);
    ~PlayerShip();
    inline void setHealth(const uint& health) {m_health = health;}


private:
    uint m_health;

};

#endif // PlayerShip_H
