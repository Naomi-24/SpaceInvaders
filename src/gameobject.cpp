#include "include/gameobject.h"

GameObject::GameObject()
{
    //assigning mesh from file to m_mesh
    m_mesh.reset(new ngl::Obj("mesh/Player.obj"));
    m_mesh->createVAO(); // creatin array of vertex thingies from the mesh loaded in
}

GameObject::~GameObject()
{

}


void GameObject::setPos(ngl::Vec3 _pos)
{
    m_pos = _pos;
}

void GameObject::draw()
{
    m_mesh->draw(); //this draw() is the ngl draw function, not a repeat of GameObject::draw()
}

void GameObject::update()
{

}

void GameObject::move(ngl::Vec3 _pos)
{

}


