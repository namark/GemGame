#ifndef GPHYSICS_H_INCLUDED
#define GPHYSICS_H_INCLUDED
#include "GRenderable.h"

namespace GPhysics
{
using namespace Geometry2D;

class Projectile: public GRendering::Renderable
{
    PointF veloc, accel;
    double speed, abs_accel; // currently not used
public:
    Projectile(double x=0,double y=0) { setPosition(PointF(x,y));}

    bool move(const Point& destination);

    void setPosition(const PointF& pos);
    void accelerate(const PointF& acc);
    void setVelocity(const PointF& vel);

    //void setPosition(const PointF& pos);
    PointF acceleration(){return accel;}
    PointF velocity(){return veloc;}
    //getAccel
    //getVeloc
};

}
#endif // GPHYSICS_H_INCLUDED
