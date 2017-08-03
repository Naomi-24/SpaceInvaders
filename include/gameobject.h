#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ngl/Vec3.h"
#include <ngl/Obj.h>
#include <memory>

    /// @file gameobject.h
    /// @brief the basic game entity class used for the game
    /// @author Naomi Morgan
    /// @version 1.0
    /// @date 09/05/17
    /// @class gameobject
    /// @brief this class encapsulates the core state of all objects within the game, including drawing.
class GameObject
{
public:
    GameObject();
    ~GameObject();

    void draw();
    void update();

    inline ngl::Vec3 getPos() { return m_pos; }
    void setPos(ngl::Vec3);
    void move(ngl::Vec3);

protected:
    ngl::Vec3                   m_pos;
    ngl::Vec3                   m_velocity;
    int                         m_health;
    std::unique_ptr<ngl::Obj>   m_mesh; //pointer of type ngl::obj thats pointing the address of m_mesh, which will have an obj file assigned to it in .cpp

};

#endif // GAMEOBJECT_H