#include "GemGrid.h"
#include <ctime>


using namespace Gems;

Grid::Grid(const Rect& rect, const Point& rows_cols,
           uint min_group_size, uint game_time) :   Rect(rect), grid_size(rows_cols), min_group_size(min_group_size),
                                                    spwn_dist(400), spwn_spac(30),
                                                    cur_score(0),
                                                    timer(::time(0)), game_time(game_time)
{
    Generic::uint seed = ::time(0);
    printf("%u", seed);
    Generic::stiny_rand(seed);
    cell_size = Point(w()/grid_size.x,h()/grid_size.y);
    grid.resize(grid_size.y);
    for(int i=0; i<grid_size.y; ++i)
    {
        grid[i].resize(grid_size.x);
        for(int j=0; j<grid_size.x; ++j)
        {
            grid[i][j].push_back(Gem(this));
        }
    }

    memset(gem_rarity,1,TYPE_COUNT);
    gem_rarity[LINER_GEM] = 5;
    gem_rarity[BOMB_GEM] = 5;

}

Point Grid::getCoordinates(const Point& row_col) // by default(negative values) uses cur_row_col
{
    if(row_col.x<0 || row_col.y<0) return Point(x+cur_row_col.x*cell_size.x, y+cur_row_col.y*cell_size.y);
    return Point(x+row_col.x*cell_size.x, y+row_col.y*cell_size.y);
}

vector<Gem>& Grid::operator[](const Point& coord)
{
    return grid[coord.y][coord.x];
}

void Grid::findGroup(Point p, GemType type)
{
    if(p.x < 0 || p.x >= grid_size.x || p.y < 0 || p.y >= grid_size.y ) return;
    Gem& current = (*this)[p][0];
    if(
       (current.mark() == false) &&
       (current.state() == GenericGem::IDLE) &&
       (current.type() == type)
      )
    {
        trigger_group.push_back(p);
        current.mark(true);
        ++p.x;
        findGroup(p,current.type());
        --p.x;
        --p.x;
        findGroup(p,current.type());
        ++p.x;
        ++p.y;
        findGroup(p,current.type());
        --p.y;
        --p.y;
        findGroup(p,current.type());
    }

}

void Grid::handleMouse(const Point& mc)
{
    if(!mc.is_in(*this)) return;
    cur_row_col = mc - topLeft();
    //if(cur_row_col.x < 0 ||
    //  cur_row_col.y < 0 ||
     //  cur_row_col.x >= w() ||
     //  cur_row_col.y >= h()) return;

    cur_row_col.x /= cell_size.x;
    cur_row_col.y /= cell_size.y;
    findGroup(cur_row_col,currentGem().type());
    if(trigger_group.size()>=min_group_size)
    {
        for(int i = 0; i < trigger_group.size(); ++i)
        {
            cur_row_col = trigger_group[i];
            Gem& current = currentGem();
            current.mark(false);
            current.trigger();
        }
        trigger_group.resize(0);
    }
    else
    {
        for(int i = 0; i < trigger_group.size(); ++i)
        {
            cur_row_col = trigger_group[i];
            Gem& current = currentGem();
            current.mark(false);
        }
    }
    trigger_group.resize(0);

}

void Grid::gravitate()
{
    for(cur_row_col.x = 0; cur_row_col.x < grid_size.x; ++cur_row_col.x)
    {
        int empty_slot = -1;
        for(cur_row_col.y = grid_size.y - 1; cur_row_col.y >=0 ; --cur_row_col.y)
        {
            Gem& current = currentGem();
            if(empty_slot==-1)
            {
                if(current.is_dead()) empty_slot = cur_row_col.y;
            }
            else
            {
                if(!current.is_dead())
                {
                    if(!current.moveTo(Point(cur_row_col.x,empty_slot))) empty_slot = -1;
                    else --empty_slot;
                }
            }
        }
    }
}

void Grid::createNew()
{
    for(cur_row_col.y = 0; cur_row_col.y < grid_size.y; ++cur_row_col.y)
        for(cur_row_col.x = 0; cur_row_col.x < grid_size.x; ++cur_row_col.x)
        {
            Gem& current = currentGem();
            if(current.is_dead())
            {
                GemType type;
                do
                {
                    type = static_cast<GemType>(Generic::tiny_rand()%TYPE_COUNT);
                }
                while(Generic::tiny_rand()%gem_rarity[type]);
                current = createGem(type);
                current.accelerate(PointF(0,0.3));
                current.setVelocity(PointF(0,0));
                Point pos = getCoordinates();
                pos.y -= (spwn_dist+(grid_size.y - cur_row_col.y)*spwn_spac);
                current.setPosition(pos);
            }
        }
}

void Grid::render(const GRendering::Renderer& renderer)
{
    for(cur_row_col.y = 0; cur_row_col.y < grid_size.y; ++cur_row_col.y)
        for(cur_row_col.x = 0; cur_row_col.x < grid_size.x; ++cur_row_col.x)
        {
            vector<Gem>& current = (*this)[cur_row_col];
            for(int i=0; i<current.size(); ++i )
                {renderer.Render(current[i]);}
        }
}

void Grid::update()
{
    for(cur_row_col.y = 0; cur_row_col.y < grid_size.y; ++cur_row_col.y)
        for(cur_row_col.x = 0; cur_row_col.x < grid_size.x; ++cur_row_col.x)
        {
            vector<Gem>& current = (*this)[cur_row_col];
            for(int i=0; i<current.size(); ++i )
                current[i].update();
        }
}

void Grid::score()
{
    for(cur_row_col.y = 0; cur_row_col.y < grid_size.y; ++cur_row_col.y)
        for(cur_row_col.x = 0; cur_row_col.x < grid_size.x; ++cur_row_col.x)
            if(currentGem().is_dead())
            {
                Gem& current_gem = currentGem();
                cur_score+=score(current_gem);
                current_gem = 0;
            }
}
uint Grid::score(const Gem& gem)
{
    switch(gem.type())
    {
    case BLUE_GEM:
        return 1;
    break;
    case RED_GEM:
        return 1;
    break;
    case GREEN_GEM:
        return 1;
    break;
    case YELLOW_GEM:
        return 1;
    break;
    case PURPLE_GEM:
        return 1;
    break;
    default:
        return 0;
    }
}

bool Grid::time()
{
    return (::time(0)-timer) < game_time;
}

void Grid::update(const GRendering::Renderer& renderer)
{
    gravitate();
    if(time()) createNew();
    render(renderer);
    update();
    score();
}

void Grid::draw(Drawing32::Canvas32& canvas)
{
	const int bar_width = 6;
	const int bar_margin = 25;
    Rect left(x-bar_margin-bar_width,y,bar_width,h()), right(x+w()+bar_margin,y,bar_width,h());
    Drawing32::Painter32 painter(canvas,0xFFFFFFFF);
    painter.drawRect(*this);
    painter.drawRect(left);
    painter.drawRect(right);
    painter.setBrushColor(0xFFFF0000);
    painter.setPenColor(0);
    RectF t(left);
    Rect s(right);
    double mt = (t.s.y/game_time)*(::time(0)-timer);
    t.y+= mt;
    t.s.y-= mt;
    if(t.s.y>1)painter.drawRect(t);
    painter.setBrushColor(0xFFFFFF00);
    s.y = s.y+s.h() - cur_score;
    s.s.y = cur_score;
    painter.drawRect(s);
}
