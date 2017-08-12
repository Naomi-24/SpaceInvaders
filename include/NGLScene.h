#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <ngl/Vec3.h>

#include <QOpenGLWindow>
#include "WindowParams.h"
#include "playership.h"
#include <ngl/Mat4.h>
#include <QMap>

//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
/// edited for SpaceInvaders by Naomi Morgan
/// contains main game loop
//----------------------------------------------------------------------------------------------------------------------

class NGLScene : public QOpenGLWindow
{
  public:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PUBLIC FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for our NGL drawing class
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    NGLScene();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor must close down ngl and release OpenGL resources
    //----------------------------------------------------------------------------------------------------------------------
    ~NGLScene();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief
    /// @param position of enemy spawn
    //----------------------------------------------------------------------------------------------------------------------
    void createEnemy(ngl::Vec3 _spawnPos);

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the initialize class is called once when the window is created and we have a valid GL context
    /// use this to setup any default GL stuff
    //----------------------------------------------------------------------------------------------------------------------
    void initializeGL() override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL() override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we resize the window
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(int _w, int _h) override;

private:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PRIVATE FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *_event) override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseMoveEvent (QMouseEvent * _event ) override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is pressed
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mousePressEvent ( QMouseEvent *_event) override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseReleaseEvent ( QMouseEvent *_event ) override;

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief
    /// my code
    /// @param
    //----------------------------------------------------------------------------------------------------------------------
    void timerEvent(QTimerEvent *event) override;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///---PRIVATE ATTRIBUTES
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @brief windows parameters for mouse control etc.
    WinParams m_win;

    /// position for our model
    ngl::Vec3 m_modelPos;

    /// model view preojection matrix
    ngl::Mat4 m_VP;

    /// velocity
   // ngl::Vec3 m_modelVel;

    /// variable for the player ship
    PlayerShip *m_player;

    ///vector of enemy ships (stores enemies)
    std::vector <PlayerShip> m_enemies;

 /*   QMap<int, EnemyShip> m_enemies;

    for(int i=0, i<10, i++)
    {
        m_enemies[i] = new EnemyShip();
        m_enemies[i]->setID(i);  //
    };
*/

    /// Player Mesh pointer
    std::unique_ptr<ngl::Obj> m_playerMesh;

    /// Enemy Mesh pointer
    std::unique_ptr<ngl::Obj> m_enemyMesh;

};



#endif
