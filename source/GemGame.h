#ifndef GEMGAME_H
#define GEMGAME_H
#include <SDL_drawing/SDL_class.h>
#include "GemGrid.h"

namespace GemGame
{
using namespace SDL;




const uint WIN_WIDTH = 520, WIN_HEIGHT = 480;
// the rect dimensions must be divisible by the grid size
const Rect gem_grid_rect(50,25,420,420);
const Point gem_grid_size(14,14);



class Window : public SDL_class
{
    GRendering::Renderer renderer;
    Gems::Grid gg;
    // Gems::Grid gg2;

    Point mousePoint;
    bool LMB;

public:
    Window();

    virtual ~Window(){}

    void mainLoop();

    void mousePressed(SDL_MouseButtonEvent& mouse);
};

}

#endif // GEMGAME_H
