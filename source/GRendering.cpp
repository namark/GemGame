#include "GRendering.h"
#include "GRenderable.h"



using namespace GRendering;

Sprite Renderer::Sprites[Renderer::SPRITE_COUNT];

void Renderer::Render(const Renderable& r) const
{
    RenderInfo* rinfo = r.getInfo();
    if(rinfo)
    {
        SpriteName n = rinfo->getCurSprName();
        if(n == SPRITE_COUNT) return;
        Sprite& curspr = Sprites[n];
        on->blit(curspr[rinfo->curentFrame()%curspr.size()],r);
        rinfo->preIncrFrame();
    }
}
