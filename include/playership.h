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
    //---PUBLIC FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief cstr for PlayerShip class.
    /// @param [in] ngl::vec3 stores position data
    /// @param [in] int is the filename of the model used.
    /// @param [in] const std::string &_id
    //----------------------------------------------------------------------------------------------------------------------
    PlayerShip(ngl::Vec3, int, const std::string &_id);

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dstr for PlayerShip class
    /// @param none
    //----------------------------------------------------------------------------------------------------------------------
    ~PlayerShip();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief getter function for health of player
    /// @param none
    //----------------------------------------------------------------------------------------------------------------------
    inline size_t getHealth() const {return m_health;}

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief getter function for enemy spawn position, returns spawn position as vec3
    /// @param none
    //----------------------------------------------------------------------------------------------------------------------
    ///please move to enemyShip class///
    inline ngl::Vec3 getSpawnPos() const {return m_spawnPos;}

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief setter function for object health
    /// @param [in] const size_t& health
    //----------------------------------------------------------------------------------------------------------------------    
    void setHealth(const size_t& health) {m_health = health;}

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief setter function for enemy spawn position
    /// @param [in] const ngl::Vec3 spawnPosIn
    //----------------------------------------------------------------------------------------------------------------------
    ///please move to enemyShip class///
    inline void setSpawnPos(const ngl::Vec3 spawnPosIn) {m_spawnPos = spawnPosIn;}



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---PRIVATE ATTRIBUTES
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///object health
    size_t          m_health;

    ///please move to enemyShip class///
    ///object start position, when its first instantiated
    ngl::Vec3       m_spawnPos;




};

#endif // PlayerShip_H
