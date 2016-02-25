#ifndef GEMS_H_INCLUDED
#define GEMS_H_INCLUDED
#include "GPhysics.h"

namespace Gems
{


enum GemType
{
    BLUE_GEM,
    RED_GEM,
    GREEN_GEM,
    YELLOW_GEM,
    PURPLE_GEM,
    OBSTICLE_GEM,

    LINER_GEM,
    BOMB_GEM,

    TYPE_COUNT // also used as invalid type
};

class GemInfo : public GRendering::RenderInfo
{

    //static GemType type;
    //static std::vector<GemType> compatible_with;  // use global map instead
protected:
    GPhysics::Projectile* cur_proj;

    Generic::uint gem_state;
public:
    GemInfo(){}
    virtual ~GemInfo(){}
    enum ActionType
    {
        TRIGGER,
        UPDATE,
        IS_DEAD,
        TYPE,
        STATE,
        RARITY,
        COMPATIBLE
    };

    virtual Generic::uint Action(Generic::uint action, Grid* g = 0);
    virtual void update(Grid* g) =0;
    virtual bool trigger(Grid* g) =0;
    virtual bool is_dead() const=0;
    virtual GemType type() const=0;
    virtual Generic::uint state() const { return gem_state;}
    virtual bool compatible(Grid* g) const {return false;}
    //void scanForNeighbours(Grid* g);
    void setProj(GPhysics::Projectile* proj) {cur_proj = proj;}


    virtual GRendering::Renderer::SpriteName getCurSprName() const=0;

};

class Gem: public GPhysics::Projectile
{
    Grid* cur_grid;
    bool marked;
public:
    Gem(Grid* grid) : cur_grid(grid), marked(false) { info=0;}

    void mark(bool m) {marked = m;}
    bool mark() {return marked;}

    void update();
    bool trigger();
    bool is_dead() const;
    GemType type() const;
    Generic::uint state() const;
    bool compatible();

    bool moveTo(const Geometry2D::Point& position);

    Gem& operator=(GemInfo* gi);


};



}
#endif // GEMS_H_INCLUDED
