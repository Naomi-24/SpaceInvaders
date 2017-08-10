#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>
#include "playership.h"
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>

enum Model {
    BASIC,
    EXTENDED,
    LUXURIOUS
};

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Blank NGL");

}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}
//-----------------------------------------------------------------------------------------------------------
void NGLScene::createEnemy()
{
   // m_enemy.reset(new EnemyShip(ngl::Vec3(0.0f,0.0f,0.0f), "models/obs.obj"));
}
//-----------------------------------------------------------------------------------------------------------

void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

//---------------------------------------------------------------------------------------------------------

  m_player = new PlayerShip(ngl::Vec3(0.0f,0.0f,0.0f), BASIC);
  ///Load in the mesh for the enemy ship
  m_playerMesh.reset(new ngl::Obj("meshes/SpaceShip.obj"));
  m_playerMesh->createVAO();

  std::string name = "blinn";
  std::string vert = "PhongVertex";
  std::string frag = "PhongFragment";


  ///Load in shaders
  ngl::ShaderLib * slib = ngl::ShaderLib::instance(); ///grabbin a ptr to a shader manage
  slib->createShaderProgram(name);
  slib->attachShader(vert, ngl::ShaderType::VERTEX);
  slib->attachShader(frag, ngl::ShaderType::FRAGMENT);

  slib->loadShaderSource(vert, "shaders/" + vert + ".glsl");
  slib->loadShaderSource(frag, "shaders/" + frag + ".glsl");

  slib->compileShader(vert);
  slib->compileShader(frag);

  slib->attachShaderToProgram(name, vert);
  slib->attachShaderToProgram(name, frag);

  slib->linkProgramObject(name);
  (*slib)[name]->use();

  /// Start the timer that runs throughout the game.
  startTimer(25);

//--------------------------------------------------------------------------------------------------------

}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

//-----------------------------------------------------------------------------------------------------------------
  ///tell opengl where the camera is
  ngl::Mat4 V = ngl::lookAt(
              ngl::Vec3(50, 0, 0),
              ngl::Vec3(0, 0, 0),
              ngl::Vec3(0, 1, 0)
              );
  ///takes object and turns into screenspace
  ngl::Mat4 P = ngl::perspective(
              60.0f,
              m_win.width / (float)m_win.height,  ///calc the aspect ratio in float so it doesn't fuck up ints
              0.1f, ///clipping plane sortof near
              512.0f  ///clipping far plane
              );
  ///Create the MVP
  m_VP = V*P;
  ///this transformation matrix make sit easier to move the model around in the future
  ngl::Transformation T;
  T.setPosition(m_modelPos);
  ngl::Mat4 M = T.getMatrix();

  ngl::ShaderLib * slib = ngl::ShaderLib::instance(); ///grab the manager again bc we gonna use the shader
  slib->use("blinn"); ///tellin gl which shader to use
  slib->setRegisteredUniform("MVP", M * m_VP);
  m_playerMesh->draw();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quit
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
      ///---------------------------my code below
  /// W key to accelerate player up vertically
  case Qt::Key_W :
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, 0.05, 0.0));
  break;
  /// S key to accerler
  case Qt::Key_S :
       m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, -0.05, 0.0));
  break;

  //case Qt::Key_S :
 //             m_modelVel += ngl::Vec3(0.0, -0.05, 0.0);
 // break;
  default : break;
  }
  /// finally update the GLWindow and re-draw

    update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent( QMouseEvent* _event )
{
  // note the method buttons() is the button state when event was called
  // that is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if ( m_win.rotate && _event->buttons() == Qt::LeftButton )
  {
    int diffx = _event->x() - m_win.origX;
    int diffy = _event->y() - m_win.origY;
    m_win.spinXFace += static_cast<int>( 0.5f * diffy );
    m_win.spinYFace += static_cast<int>( 0.5f * diffx );
    m_win.origX = _event->x();
    m_win.origY = _event->y();
    update();
  }
  // right mouse translate code
  else if ( m_win.translate && _event->buttons() == Qt::RightButton )
  {
    int diffX      = static_cast<int>( _event->x() - m_win.origXPos );
    int diffY      = static_cast<int>( _event->y() - m_win.origYPos );
    m_win.origXPos = _event->x();
    m_win.origYPos = _event->y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    update();
  }
}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent( QMouseEvent* _event )
{
  // that method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if ( _event->button() == Qt::LeftButton )
  {
    m_win.origX  = _event->x();
    m_win.origY  = _event->y();
    m_win.rotate = true;
  }
  // right mouse translate mode
  else if ( _event->button() == Qt::RightButton )
  {
    m_win.origXPos  = _event->x();
    m_win.origYPos  = _event->y();
    m_win.translate = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent( QMouseEvent* _event )
{
  // that event is called when the mouse button is released
  // we then set Rotate to false
  if ( _event->button() == Qt::LeftButton )
  {
    m_win.rotate = false;
  }
  // right mouse translate mode
  if ( _event->button() == Qt::RightButton )
  {
    m_win.translate = false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent( QWheelEvent* _event )
{

  // check the diff of the wheel position (0 means no change)
  if ( _event->delta() > 0 )
  {
    m_modelPos.m_z += ZOOM;
  }
  else if ( _event->delta() < 0 )
  {
    m_modelPos.m_z -= ZOOM;
  }
  update();
}

//-----------------------------------------------------------------------------------------------------------------------
void NGLScene::timerEvent(QTimerEvent *event)
{

    std::cout << "Timer\n";
    m_modelPos += m_player->getVelocity();
    m_player->setVelocity(m_player->getVelocity()* 0.95f);
    paintGL();
    update();
}
