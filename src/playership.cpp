#include "playership.h"

PlayerShip::PlayerShip(ngl::Vec3 _pos, int model, const std::string &_id) : GameObject( _id )
{
    setPos(_pos);

}

PlayerShip::~PlayerShip()
{

}
