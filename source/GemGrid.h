#ifndef GEMGRID_H_INCLUDED
#define GEMGRID_H_INCLUDED
#include "GemFactory.h"

namespace Gems
{
using std::vector;
using namespace Generic;
using namespace Geometry2D;

class Grid : public Rect
{
    uint timer;
    uint game_time;

    uint cur_score;

    uint min_group_size;

    uint spwn_dist, spwn_spac;
    Point grid_size;
    Point cell_size;
    vector< vector< vector<Gem> > > grid;

    Point cur_row_col;

    vector<Point> trigger_group;

    uint8 gem_rarity[TYPE_COUNT];

public:


    Grid(): Rect(0,0,0,0),
            grid_size(0,0), cell_size(0,0),
            cur_row_col(0,0),
            min_group_size(0),
            spwn_dist(0), spwn_spac(0),
            cur_score(0),
            timer(0), game_time(0) {}
    //Grid(uint x, uint y, uint width, uint height, uint rows, uint cols);
    //Grid(const Point& position, const Point& width_height, const Point& rows_cols );
    Grid(const Rect& rect, const Point& rows_cols, uint min_group_size = 3, uint game_time = 60 );

    Point gridSize(){return grid_size;}
    Point cellSize(){return cell_size;}
    Point getCoordinates(const Point& row_col = Point(-1,-1)); // by default(negative values) uses cur_row_col

    vector<Gem>& operator[](const Point& coord);

    void update(const GRendering::Renderer& renderer);

    void findGroup(Point p, GemType type);
    void handleMouse(const Point& mc);

    Gem& currentGem(uint i=0){return (*this)[cur_row_col][i];}
    Point currentIndex(){return cur_row_col;}
    void currentIndex(const Point& p){cur_row_col = p;}

    void gravitate();
    void createNew();
    void update();
    void render(const GRendering::Renderer& renderer);

    void score();
    uint score(const Gem& gem);

    bool time();

    void draw(Drawing32::Canvas32& canvas);


};

}
#endif // GEMGRID_H_INCLUDED
