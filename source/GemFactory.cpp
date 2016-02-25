#include "GemFactory.h"
#include "GemGrid.h"

using namespace Gems;
using Geometry2D::Point;

// Generic Gem
GenericGem::GenericGem()
{
    gem_state = FALLING;
    setSprState(IDLE_ANIM);
}
void GenericGem::update(Grid* g)
{
    Point dest = g->getCoordinates();

        //cur_proj->setVelocity(Point(0,0));
    switch(gem_state)
    {
    case FALLING:
        if(cur_proj->move(dest))
        {
            cur_proj->setPosition(dest);
            if(gem_state!=TRIGGERING)gem_state = IDLE;
        }
    //break;
    case IDLE:
    if(*cur_proj!=dest) // need to find a better way to organize this
    {
        gem_state = FALLING;
    }
    break;
    case TRIGGERING:
        triggering(g);
    break;
    case DEAD:
    break;
    }
}
bool GenericGem::trigger(Grid* g)
{
    if(gem_state == IDLE)
    {
        gem_state = TRIGGERING;
        setSprState(TRIGGERING_ANIM);
        return true;
    }
    return false;
}
void GenericGem::triggering(Grid* g)
{
    if(cur_frame == GRendering::Renderer::getSprite(getCurSprName()).size()) //  renderable can tell me this...
    {
        gem_state = DEAD;
    }
}


SpriteName BlueGem::sprites[ANIM_STATE_COUNT];
SpriteName RedGem::sprites[ANIM_STATE_COUNT];
SpriteName GreenGem::sprites[ANIM_STATE_COUNT];
SpriteName YellowGem::sprites[ANIM_STATE_COUNT];
SpriteName PurpleGem::sprites[ANIM_STATE_COUNT];


//////////////////////////////////////////LINER////////////////////////////////////
SpriteName LinerGem::sprites[ANIM_STATE_COUNT];

bool LinerGem::trigger(Grid* g)
{
    if(GenericGem::trigger(g))
    {
        Point cur = g->currentIndex();
        Point trig(0,cur.y);
        for(; trig.x<g->gridSize().x; ++trig.x)
        {
            g->currentIndex(trig);
            g->currentGem().trigger();
        }
        g->currentIndex(cur);
        return true;
    }
    return false;
}



//////////////////////////////////////////BOMB////////////////////////////////////
SpriteName BombGem::sprites[ANIM_STATE_COUNT];

Generic::uint8 BombGem::radius = 1;

bool BombGem::trigger(Grid* g)
{
    if(GenericGem::trigger(g))
    {
        Point cur = g->currentIndex();
        Point from(cur.x-radius,cur.y-radius),
              to(cur.x+radius+1,cur.y+radius+1);
        for(int i=from.y;i<to.y; ++i)
            for(int j=from.x; j<to.x; ++j)
            {
                Point p(j,i);
                if(p.is_in(Rect(Point(0,0),g->gridSize())))
                {
                    g->currentIndex(p);
                    g->currentGem().trigger();
                }

            }
        g->currentIndex(cur);
        return true;
    }
    return false;

}





///////////////////////////////////////FACTORY/////////////////////////////////
GemInfo* Gems::createGem(GemType type)
{
    switch(type)
    {
    case BLUE_GEM:
        return new BlueGem;
    break;
    case RED_GEM:
        return new RedGem;
    break;
    case GREEN_GEM:
        return new GreenGem;
    break;
    case YELLOW_GEM:
        return new YellowGem;
    break;
    case PURPLE_GEM:
        return new PurpleGem;
    break;
    case LINER_GEM:
        return new LinerGem;
    break;
    case BOMB_GEM:
        return new BombGem;
    break;
    default:
        return 0;
    }
}
