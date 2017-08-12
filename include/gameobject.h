#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ngl/Vec3.h"
#include <ngl/Obj.h>
#include <memory>
//----------------------------------------------------------------------------------------------------------------------
/// @file gameobject.h
/// @brief the basic game entity class used for the game
/// @author Naomi Morgan
/// @version 1.0
/// @date 09/05/17
/// @class gameobject
/// @brief this class encapsulates the core state of all objects within the game, including drawing.
//----------------------------------------------------------------------------------------------------------------------
class GameObject
{
public:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PUBLIC FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    GameObject();
    ~GameObject();

    void draw();
    void update();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief getter function for object position, retrieves value(s) of object position (m_pos)
    /// @param returns position
    //----------------------------------------------------------------------------------------------------------------------
    inline ngl::Vec3 getPos() const { return m_pos; }

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief getter function for object velocity, retrieves value(s) of object velocity (m_velocity)
    /// @param
    //----------------------------------------------------------------------------------------------------------------------
    inline ngl::Vec3 getVelocity() const {return m_velocity;}

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief setter function for object position, sets the value of the objects position value(s) (m_pos)
    /// @param [in] ngl::Vec3 containing position data to write
    //----------------------------------------------------------------------------------------------------------------------
    void setPos(ngl::Vec3);

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief setter function for object velocity, sets the value of the objects velocity value(s) (m_velocity)
    /// @param [in] & velocity
    //----------------------------------------------------------------------------------------------------------------------
    void setVelocity(const ngl::Vec3& velocity) {m_velocity = velocity;}

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for our NGL drawing class
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    void move(ngl::Vec3);

protected:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PROTECTED ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///position of object
    ngl::Vec3                   m_pos;

    ///velocity of object
    ngl::Vec3                   m_velocity;

    ///pointer of type ngl::obj thats pointing the address of m_mesh, which will have an obj file assigned to it in .cpp
    /// at the moment this is the BASIC model
    std::unique_ptr<ngl::Obj>   m_mesh;

};

#endif // GAMEOBJECT_H
