#ifndef GRENDERABLE_H_INCLUDED
#define GRENDERABLE_H_INCLUDED
#include "GRendering.h"

namespace Gems
{
    class Grid;
}


namespace GRendering
{

class RenderInfo;

class Renderable: public PointF
{
protected:
    RenderInfo* info;
    //Uint32 render_state;
    void cleanup();
public:
    Renderable(RenderInfo* ri = 0): info(ri) {}
    RenderInfo* getInfo() const {return info;}
    virtual ~Renderable(){cleanup();}
};


class RenderInfo // make this pure virtual?
{

protected:
    // add pause/play functionality
    uint spr_state;
    uint cur_frame;
    //static std::vector<Renderer::SpriteName> sprites; // define this in derived classes

public:

    //virtual static void setSprite(Renderer::SpriteName sprite, uint state){}

    virtual Renderer::SpriteName getCurSprName() const=0;

    void setSprState(uint state, uint frame = 0) { spr_state = state; cur_frame = frame; }
    uint currentSprState() const {return spr_state; }
    uint curentFrame() const { return cur_frame; }
    uint /*operator++*/ preIncrFrame() { return ++cur_frame;}
    uint /*operator++(int)*/postIncrFrame() { return cur_frame++;}

    virtual ~RenderInfo(){}

    virtual Generic::uint Action(uint action, Gems::Grid* g = 0) =0; // TODO: separate RenderInfo from GemInfo, or just get rid of Grid* here
};



}
#endif // GRENDERABLE_H_INCLUDED
