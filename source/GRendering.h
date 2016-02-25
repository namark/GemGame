#ifndef GRENDERING_H_INCLUDED
#define GRENDERING_H_INCLUDED
#include <SDL_drawing/SDL_draw.h>
#include <vector>



namespace GRendering
{
using namespace SDL;

typedef std::vector<SDL_Canvas32> Sprite;

//class Sprite;
//{
//    SDL_Canvas32 * frames;
//    Uint fram_count;
//public:
//
//};


class Renderable;

class Renderer //dont think i need this
{
public:
    enum SpriteName
    {
        BLUE_GEM_IDLE,
        RED_GEM_IDLE,
        GREEN_GEM_IDLE,
        YELLOW_GEM_IDLE,
        PURPLE_GEM_IDLE,

        GEM_TRIGGERED,

        LINER_GEM_IDLE,
        BOMB_GEM_IDLE,

        SPRITE_COUNT // keep at the end... also used as "nosprite"
    };
private:
    static Sprite Sprites[SPRITE_COUNT];
    /*SDL_*/Canvas32* on;

public:
    Renderer(Canvas32* canv = 0): on(canv) {}
    static void setSprite(SpriteName name,const Sprite& ri) { Sprites[name] = ri;}
    static Sprite& getSprite(SpriteName name) { return Sprites[name];}
    void Render(const Renderable& r) const;
};

}

#endif // GRENDERING_H_INCLUDED
