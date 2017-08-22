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

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PUBLIC FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief setter function for enemy spawn position
    /// @param const ngl::Vec3 spawnPosIn
    //----------------------------------------------------------------------------------------------------------------------
    ///please move to enemyShip class///
    inline void setSpawnPos(const ngl::Vec3 spawnPosIn) {m_spawnPos = spawnPosIn;}

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief getter function for enemy spawn position, returns spawn position as vec3
    /// @param none
    //----------------------------------------------------------------------------------------------------------------------
    ///please move to enemyShip class///
    inline ngl::Vec3 getSpawnPos() const {return m_spawnPos;}

private:

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PRIVATE ATTRIBUTES
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///object health
    uint m_health;

    ///please move to enemyShip class///
    ///object start position, when its first instantiated
    ngl::Vec3 m_spawnPos;




};

#endif // PlayerShip_H
