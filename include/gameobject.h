#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ngl/Vec3.h"
#include "ngl/Obj.h"
#include <string>
#include <unordered_map>
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
    ///---PUBLIC ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PUBLIC FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctr for GameObject class.
    /// @param none
    //----------------------------------------------------------------------------------------------------------------------
	GameObject() = default;
		GameObject( const std::string _meshID );
    ~GameObject();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief
    /// @param
    //----------------------------------------------------------------------------------------------------------------------
    void draw();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief
    /// @param
    //----------------------------------------------------------------------------------------------------------------------
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

		ngl::Vec3 getCollisionCenter() const {return m_collisionCenter + getPos();}
		float getCollisionRadius() const {return m_collisionRadius;}

		//Destroys all the meshes. Call this at the end of the game.
		static void destroyMeshes();

protected:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PROTECTED ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///position of object
    ngl::Vec3                   m_pos;

    ///velocity of object
    ngl::Vec3                   m_velocity;

        ///Rather than storing its own mesh, each instance of game object stored an ID.
        ///We use this id to grab the ngl::obj inside s_meshes that we want to use.
		std::string m_meshID;

private:
        ///All the meshes are going to be stored in this 'map'. It's a bit like an array, but we can access entries with strings rather than ints.
		static std::unordered_map< std::string, ngl::Obj * > s_meshes;
        ///This function loads a
		static void loadMesh(const std::string &_id, const std::string &_path );

		ngl::Vec3 m_collisionCenter;
		float m_collisionRadius;
};

#endif // GAMEOBJECT_H
