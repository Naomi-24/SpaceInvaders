#include "include/gameobject.h"

std::unordered_map< std::string, ngl::Obj * > GameObject::s_meshes;

GameObject::GameObject(const std::string _meshID)
{
    //assigning mesh from file to m_mesh
    //m_mesh.reset(new ngl::Obj("meshes/Player.obj"));
    //m_mesh->createVAO(); // creatin array of vertex thingies from the mesh loaded in

	//Is our mesh already loaded? If not, load it.
	m_meshID = _meshID;
	if(s_meshes.find( m_meshID ) == s_meshes.end())
		loadMesh( m_meshID, "meshes/" + m_meshID );

	//Get the center and radius for collisions.
	m_collisionCenter = s_meshes[ m_meshID ]->getSphereCenter();
	m_collisionRadius = s_meshes[ m_meshID ]->getSphereRadius();
}

GameObject::~GameObject()
{

}

void GameObject::loadMesh(const std::string &_id, const std::string &_path)
{
	 ngl::Obj * o = new ngl::Obj( _path );
	 o->createVAO();
	 o->calcBoundingSphere();
	 s_meshes.insert(
				 std::make_pair( _id, o )
				 );
}

void GameObject::setPos(ngl::Vec3 _pos)
{
    m_pos = _pos;
}

void GameObject::draw()
{
		s_meshes[m_meshID]->draw(); //this draw() is the ngl draw function, not a repeat of GameObject::draw()
}

void GameObject::update()
{

}

void GameObject::move(ngl::Vec3 _pos)
{

}


