#include "GRenderable.h"

using namespace GRendering;


void Renderable::cleanup()
{
    delete info;
    info = 0;
}
