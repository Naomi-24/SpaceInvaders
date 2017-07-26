#include "enemyship.h"

EnemyShip::EnemyShip(ngl::Vec3 _pos, const char* _fname)
{
    m_pos = _pos;

}

EnemyShip::~EnemyShip()
{

}
/*
EnemyShip::Draw()
{

}

EnemyShip::Update()
{

}
*/
ngl::Vec3 EnemyShip::GetPos()
{
    return m_pos;
}

void EnemyShip::SetPos()
{

}

/*EnemyShip::MoveShip()
{

}

int EnemyShip::getLife()
{
    return m_health;
}

void EnemyShip::setLife()
{

}

*/
