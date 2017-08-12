#ifndef PlayerShip_H
#define PlayerShip_H

#include "gameobject.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file PlayerShip.h
/// @brief this class inherits from GameObject
/// @author Naomi Morgan
/// @version 1.0
/// @date 11/05/17
/// @class PlayerShip
/// @brief Player ships
//----------------------------------------------------------------------------------------------------------------------
class PlayerShip : public GameObject
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief cstr for PlayerShip class.
    /// @param ngl::vec3 stores position data
    /// @param int is the filename of the model used.
    //----------------------------------------------------------------------------------------------------------------------
    PlayerShip(ngl::Vec3, int);
    ~PlayerShip();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief setter function for object health
    /// @param const uint& health
    //----------------------------------------------------------------------------------------------------------------------
    inline void setHealth(const uint& health) {m_health = health;}


private:
    ///object health
    uint m_health;


};

#endif // PlayerShip_H
