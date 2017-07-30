#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>
#include "enemyship.h"

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Blank NGL");

  //Gonna make the timer call our update function every 20 ms.
  startTimer( 20 );
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

void NGLScene::createEnemy()
{
    m_enemy.reset(new EnemyShip(ngl::Vec3(0.0f,0.0f,0.0f), "models/obs.obj"));
}


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



}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      //Pretty sure ngl::Vec3 defaul constructs to be zeroed. My version of ngl is not new enough
      //to have ngl::zero //Ben
      m_modelPos.set(ngl::Vec3());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}

void NGLScene::timerEvent(QTimerEvent * t)
{
    //This is a built in qt function which gets called regularly. The interval is set by making a qt timer,
    //which fires off every x milliseconds. I set this up in the NGLScene constructor.
    //Do your updating and stuff in here. It's a good idea to split drawing and updating into two functions,
    //because it can get confusing if you try to do both at once.
    //Maybe make a draw() and an update() function and call them in here? It's up to you how you wanna set it up.
    //Ben
    std::cout << "Ben's update function!\n";
}
