#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>
#include "playership.h"
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/NGLStream.h>
#include <QDebug>

/// enum for different player ship models
enum Model
{
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
	GameObject::destroyMeshes();
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

//-----------------------------------------------------------------------------------------------------------
void NGLScene::createEnemy(ngl::Vec3 _spawnPos)
{
   /// Add a new instance of an enemy to the storage vector
	 m_enemies.push_back(std::unique_ptr<PlayerShip>(new PlayerShip(_spawnPos, BASIC, "Invader.obj" )));
   ///print out vector size to see how many enemies have been spawned
   std::cout<< "spawning " << m_enemies.size() << '\n';
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

  ///Create new instance of the player
	m_player = new PlayerShip(ngl::Vec3(0.0f,0.0f,0.0f), BASIC, "Player.obj");
  ///Load in the mesh for the Player ship
  m_playerMesh.reset(new ngl::Obj("meshes/Player.obj"));
  m_playerMesh->createVAO();


  /// Checking co-ordinates of Player bounding box
  std::cout << "Max x of player BBox is " << m_playerMesh->getBBox().maxX() << std::endl;
  std::cout << "Min x of player BBox is " << m_playerMesh->getBBox().minX() << std::endl;
  std::cout << "Max y of player BBox is " << m_playerMesh->getBBox().maxY() << std::endl;
  std::cout << "Max y of player BBox is " << m_playerMesh->getBBox().minY() << std::endl;
  std::cout << "Max z of player BBox is " << m_playerMesh->getBBox().maxZ() << std::endl;
  std::cout << "Min z of player BBox is " << m_playerMesh->getBBox().minZ() << std::endl;


//---------------------------------------------------------------------------------------------------------

  ///Let's setup the shaders to get something onscreen
  std::string name = "blinn";
  std::string vert = "PhongVertex";
  std::string frag = "PhongFragment";


  ///Load in shaders
  ///
  ///grabbin a ptr to a shader manage
  ngl::ShaderLib * slib = ngl::ShaderLib::instance();
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

  /// Create Enemies
  //ngl::Vec3 spawn = ngl::Vec3(0,5,5);
  for(int i = 0; i < 5; ++i){
    createEnemy(ngl::Vec3(0.0f, 10.0f, 10.0f + i * 2.5f));

  }

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
              ///calc the aspect ratio in float so it doesn't fuck up ints
              m_win.width / (float)m_win.height,
              ///clipping plane sortof near
              0.1f,
              ///clipping far plane
              512.0f
              );

  ///Create the MVP
  m_VP = V*P;

  ///this transformation matrix make sit easier to move the model around in the future
  ngl::Transformation T;

  ///grab the manager again bc we gonna use the shader
  ngl::ShaderLib * slib = ngl::ShaderLib::instance();

  ///tellin gl which shader to use
  slib->use("blinn");


  ///Draw the Meshes
  /// Player
  T.setPosition(m_player->getPos());
  slib->setRegisteredUniform("MVP", T.getMatrix() * m_VP);
  m_playerMesh->draw();
  for(int i = 0; i < 5; ++i){
    ///Enemy
    T.setPosition(m_enemies[i]->getPos()); ///in future this will use spawn position
    slib->setRegisteredUniform("MVP", T.getMatrix() * m_VP);
    ///Load in the mesh for the Enemy ship
		m_enemies[i]->draw();
  }

  m_enemies[2]->setVelocity(m_enemies[2]->getVelocity()+ ngl::Vec3(0.0, 0.05, 0.0));

  //qDebug() << "TESTTSTTST" << m_playerMesh->getBBox().maxX();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quit
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS);
  break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
  break;

  //---------------------------my code below
  /// WASD Controls

  /// W key to accelerate player up vertically
  case Qt::Key_W :
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, 0.05, 0.0));
  break;

  /// S key to deccelerate
  case Qt::Key_S :
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, -0.05, 0.0));
  break;

  /// A to strafe left
  case Qt::Key_A :
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, 0.0, 0.05));
  break;

  /// D to strafe right
  case Qt::Key_D :
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, 0.0, -0.05));
  break;

  /// ARROW Controls for filthy casuals,scrubs & n00bs

  /// UP key to accelerate player up vertically
  case Qt::Key_Up:
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, 0.05, 0.0));
  break;

  /// S key to deccelerate
  case Qt::Key_Down :
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, -0.05, 0.0));
  break;

  /// A to strafe left
  case Qt::Key_Left :
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, 0.0, 0.05));
  break;

  /// D to strafe right
  case Qt::Key_Right:
        m_player->setVelocity(m_player->getVelocity()+ ngl::Vec3(0.0, 0.0, -0.05));
  break;

  default : break;
  }
  /// finally update the GLWindow and re-draw

    update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent( QMouseEvent* _event )
{

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent( QMouseEvent* _event )
{
  // that method is called when the mouse button is pressed in this case we

 // if ( _event->button() == Qt::LeftButton )

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent( QMouseEvent* _event )
{

}

//-----------------------------------------------------------------------------------------------------------------------
void NGLScene::timerEvent(QTimerEvent *event)
{

    ///update player position
    m_player->setPos(m_player->getPos() + m_player->getVelocity());
    ///update player velocity
    m_player->setVelocity(m_player->getVelocity()* 0.95f);

    ///update enemies position
    for(int i = 0; i < 5; ++i)
    {
      m_enemies[i]->setPos(m_enemies[i]->getPos() + m_enemies[i]->getVelocity());
    }

    ///-----------------Player/Screen Border Detection
    if (m_player->getPos().m_z > 40.0)
    {
        m_player->setVelocity(ngl::Vec3(0.0,0.0,-1.0));
        std::cout << "Player has gone offscreen.\n";
    }

    if (m_player->getPos().m_z < -40.0)
    {
        m_player->setVelocity(ngl::Vec3(0.0,0.0,1.0));
        std::cout << "Player has gone offscreen.\n";
    }

    if (m_player->getPos().m_y > 30.0)
    {
        m_player->setVelocity(ngl::Vec3(0.0,-1.0,0.0));
        std::cout << "Player has gone offscreen.\n";
    }

    if (m_player->getPos().m_y < -30.0)
    {
        m_player->setVelocity(ngl::Vec3(0.0,1.0,0.0));
        std::cout << "Player has gone offscreen.\n";
    }
    ///--------------------------------------------------
    paintGL();
    update();
    //std::cout << m_player->getPos();
}

bool NGLScene::isTouching(const GameObject &_lhs, const GameObject &_rhs)
{
	ngl::Vec3 diff = _lhs.getCollisionCenter() - _rhs.getCollisionCenter();
	float dist = diff.lengthSquared();

	//float dist = diff.length();
	//if( dist < _lhs.getCollisionRadius() + _rhs.getCollisionRadius() )

	if( dist < (_lhs.getCollisionRadius() * _lhs.getCollisionRadius()) + (_rhs.getCollisionRadius() * _rhs.getCollisionRadius()) )
		return true;
	return false;
}
