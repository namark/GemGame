#include "GPhysics.h"


using namespace GPhysics;

bool Projectile::move(const Point& destination)
{
    //determine acceleration vector(currently set manually), based on absolute acceleration
    veloc+=accel;
    PointF prev = (*this);
    (*this) += veloc;
    // round the doubles ?... Point prev = (*this), next = ((*this)+=veloc);
    return is_between(destination.x, (int)x, (int)prev.x) && is_between(destination.y, (int)y, (int)prev.y);
}

void Projectile::setPosition(const PointF& pos) {(*this).PointF::operator= (pos);}
void Projectile::accelerate(const PointF& acc) {accel = acc;}
void Projectile::setVelocity(const PointF& vel){veloc = vel;}
