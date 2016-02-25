#include "GemGame.h"


using namespace GemGame;

void drawGem(SDL::SDL_Canvas32& c, Drawing32::Color32 col, Color32 addit = 0)
{
    Color32 brtnr = addit;
    //brtnr.alpha(brightness);


    Color32 bcol = 0;
    c.fill(bcol);
    Rect dr = Rect(0,0,c.width(), c.height());
    uint8 step =  255/(std::min(c.width(), c.height())/2);
    uint8 a = step;
    col.alpha(a);
    Painter32 p(c, col);
    while(dr.valid())
    {
        bcol = 0xFF000000;
        col.alpha(a);
        bcol.blend(col);
        bcol.blend(brtnr);
        p.setPenColor(bcol);
        p.drawRect(dr);
        ++dr.x;
        ++dr.y;
        dr.s.x-=2;
        dr.s.y-=2;
        a+=step;
    }
    col.alpha(255);
    col.blend(brtnr);
    p.setPenColor(col);
    --dr.x;
    --dr.y;
    dr.s.x+=2;
        dr.s.y+=2;
    p.drawRect(dr);

    Rect dr2 = Rect(1,1,c.width()-2, c.height()-2);
    p.drawRect(dr2);

}

Window::Window() :  SDL_class(WIN_WIDTH,WIN_HEIGHT, 32, "Gem-Game", 0 , 60),
                    gg(gem_grid_rect,gem_grid_size),
                    // gg2(gem_grid_rect,gem_grid_size),
                    renderer(&screenCanvas()),
                    mousePoint(-1,-1), LMB(false)
{
    // gg2 += Point(415,0);

    //initialize renderer
    using namespace GRendering;
    SDL_Canvas32 canv(gg.cellSize().x,gg.cellSize().y);
    Sprite spr;
    spr.push_back(canv);
    drawGem(spr[0],0xFF0000FF);
    Renderer::setSprite(Renderer::BLUE_GEM_IDLE, spr);
    drawGem(spr[0],0xFFFF0000);
    Renderer::setSprite(Renderer::RED_GEM_IDLE, spr);
    drawGem(spr[0],0xFF00FF00);
    Renderer::setSprite(Renderer::GREEN_GEM_IDLE, spr);
    drawGem(spr[0],0xFFFFFF00);
    Renderer::setSprite(Renderer::YELLOW_GEM_IDLE, spr);
    drawGem(spr[0],0xFFFF00FF);
    Renderer::setSprite(Renderer::PURPLE_GEM_IDLE, spr);

    drawGem(spr[0],0xFF0000FF);
    spr.resize(32,spr[0]);
    Color32 LGA = 0x550000FF;
    for(int i = 0; i<spr.size()/2; ++i) drawGem(spr[i],0xFF0000FF, LGA);
    Renderer::setSprite(Renderer::LINER_GEM_IDLE, spr);

    spr.resize(1);
    drawGem(spr[0],0xFFFF0000);
    spr.resize(32,spr[0]);
    LGA = 0x55FF0000;
    for(int i = 0; i<spr.size()/2; ++i) drawGem(spr[i],0xFFFF0000, LGA);
    Renderer::setSprite(Renderer::BOMB_GEM_IDLE, spr);

    spr.resize(1);
    drawGem(spr[0],0xFFFFFFFF);
    spr.resize(10,spr[0]);
    Renderer::setSprite(Renderer::GEM_TRIGGERED, spr);

    //initialise gem types
    using namespace Gems;
    BlueGem::setSprite(GenericGem::IDLE_ANIM, Renderer::BLUE_GEM_IDLE);
    BlueGem::setSprite(GenericGem::TRIGGERING_ANIM, Renderer::GEM_TRIGGERED);
    RedGem::setSprite(GenericGem::IDLE_ANIM, Renderer::RED_GEM_IDLE);
    RedGem::setSprite(GenericGem::TRIGGERING_ANIM, Renderer::GEM_TRIGGERED);
    GreenGem::setSprite(GenericGem::IDLE_ANIM, Renderer::GREEN_GEM_IDLE);
    GreenGem::setSprite(GenericGem::TRIGGERING_ANIM, Renderer::GEM_TRIGGERED);
    YellowGem::setSprite(GenericGem::IDLE_ANIM, Renderer::YELLOW_GEM_IDLE);
    YellowGem::setSprite(GenericGem::TRIGGERING_ANIM, Renderer::GEM_TRIGGERED);
    PurpleGem::setSprite(GenericGem::IDLE_ANIM, Renderer::PURPLE_GEM_IDLE);
    PurpleGem::setSprite(GenericGem::TRIGGERING_ANIM, Renderer::GEM_TRIGGERED);

    LinerGem::setSprite(GenericGem::IDLE_ANIM, Renderer::LINER_GEM_IDLE);
    LinerGem::setSprite(GenericGem::TRIGGERING_ANIM, Renderer::GEM_TRIGGERED);
    BombGem::setSprite(GenericGem::IDLE_ANIM, Renderer::BOMB_GEM_IDLE);
    BombGem::setSprite(GenericGem::TRIGGERING_ANIM, Renderer::GEM_TRIGGERED);


}

void Window::mainLoop()
{
    SDL_Canvas32 canv(WIN_WIDTH,WIN_HEIGHT);
    canv.fill(0x22000000);
    //Drawing32::Painter32 p(screenCanvas(),0,1,0x44000000);
    //p.drawRect(Rect(0,0,WIN_WIDTH,WIN_HEIGHT));
    //screenCanvas().fill();
    screenCanvas().blit(canv);
    gg.draw(screenCanvas());
    gg.update(renderer);
    // gg2.draw(screenCanvas());
    // gg2.update(renderer);
    if(LMB)
    {
        gg.handleMouse(mousePoint);
        // gg2.handleMouse(mousePoint);
        LMB = false;
    }
}

void Window::mousePressed(SDL_MouseButtonEvent& mouse)
{
    if(mouse.button == SDL_BUTTON_LEFT)
    {
        LMB = true;
        mousePoint.x = mouse.x;
        mousePoint.y = mouse.y;
    }
}
