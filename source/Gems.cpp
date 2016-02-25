#include "Gems.h"
#include "GemGrid.h"

using namespace Gems;

uint GemInfo::Action(uint action, Grid* g)
{
    // swich to the state of falling if not in place
    switch(action)
    {
    case IS_DEAD:
        return is_dead();
    break;
    case UPDATE:
        if(g)update(g);
    break;
    case TRIGGER:
        if(g) return trigger(g);
    break;
    case TYPE:
        return type();
    break;
    case STATE:
        return state();
    break;
    case COMPATIBLE:
        return compatible(g);
    }
    return 0;
}



void Gem::update(){if(info) info->Action(GemInfo::UPDATE, cur_grid);}
bool Gem::trigger(){ !info || info->Action(GemInfo::TRIGGER, cur_grid);}
bool Gem::is_dead() const { return !info || info->Action(GemInfo::IS_DEAD);}
GemType Gem::type() const { if(info) return static_cast<GemType>(info->Action(GemInfo::TYPE)); else return TYPE_COUNT;}
Generic::uint Gem::state() const { if(info) return info->Action(GemInfo::STATE); else return -1;}
bool Gem::compatible(){ return !info || info->Action(GemInfo::COMPATIBLE, cur_grid);}

bool Gem::moveTo(const Point& position)
{
    std::vector<Gem>& target = (*cur_grid)[position];
    int i;
    for(i=0; i<target.size(); ++i)
        if(target[i].is_dead()) break;
    if(i==target.size()) target.push_back(Gem(cur_grid));

    Gem& target_gem = target[i];

    // this could be an operator=, maybe
    target_gem = reinterpret_cast<GemInfo*>(info);
    target_gem.cur_grid = cur_grid;
    target_gem.marked = marked;
    target_gem.accelerate(acceleration());
    target_gem.setVelocity(velocity());
    target_gem.setPosition(*this);


    info = 0;

    return true;
}

Gem& Gem::operator=(GemInfo* gi)
{
    cleanup();
    info=gi;
    if(gi)gi->setProj(this);
}

