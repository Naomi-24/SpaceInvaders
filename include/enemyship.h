#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "enemymodel.h"
#include "gameobject.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file EnemyShip.h
/// @brief this class inherits from GameEntity
/// @author Naomi Morgan
/// @version 1.0
/// @date 11/05/17
/// @class EnemyShip
/// @brief enemy ships
//----------------------------------------------------------------------------------------------------------------------
class EnemyShip : GameObject
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief cstr for EnemyShip class.
    /// @param ngl::vec3 stores position data
    /// @param const char* is the filename of the model used.
    //----------------------------------------------------------------------------------------------------------------------
    EnemyShip(ngl::Vec3, const char*);
    ~EnemyShip();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns position for enemyship object in scene.
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 GetPos();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief
    /// @param
    /// @param
    //----------------------------------------------------------------------------------------------------------------------
    void SetPos();


private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pointer to EnemyModel class, which contains the mesh.  Flyweight pattern.
    //----------------------------------------------------------------------------------------------------------------------
    EnemyModel* m_model;


} ;

#endif // ENEMYSHIP_H
