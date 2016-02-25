#ifndef GEMFACTORY_H_INCLUDED
#define GEMFACTORY_H_INCLUDED
#include "Gems.h"



namespace Gems
{
    typedef GRendering::Renderer::SpriteName SpriteName;
    class GenericGem : public GemInfo
    {
    public:
        enum RndrState
        {
            IDLE_ANIM,
            TRIGGERING_ANIM,

            ANIM_STATE_COUNT
        };

        enum
        {
            IDLE,
            FALLING,
            TRIGGERING,
            DEAD
        };

        GenericGem();

        bool is_dead() const { return gem_state == DEAD; }
        void update(Grid* g);
        bool trigger(Grid* g);

        virtual void triggering(Grid* g);

        virtual SpriteName getCurSprName() const=0;
    };


    class BlueGem : public GenericGem
    {
        static SpriteName sprites[ANIM_STATE_COUNT];
    public:
        GemType type() const {return BLUE_GEM;}


        virtual SpriteName getCurSprName() const {return sprites[spr_state];}
        static void setSprite(RndrState state, SpriteName name) { sprites[state]= name; }

    };

    class RedGem : public GenericGem
    {
        static SpriteName sprites[ANIM_STATE_COUNT];
    public:
        GemType type() const {return RED_GEM;}


        virtual SpriteName getCurSprName() const {return sprites[spr_state];}
        static void setSprite(RndrState state, SpriteName name) { sprites[state]= name; }

    };


    class GreenGem : public GenericGem
    {
        static SpriteName sprites[ANIM_STATE_COUNT];
    public:
        GemType type() const {return GREEN_GEM;}


        virtual SpriteName getCurSprName() const {return sprites[spr_state];}
        static void setSprite(RndrState state, SpriteName name) { sprites[state]= name; }
    };

    class YellowGem : public GenericGem
    {
        static SpriteName sprites[ANIM_STATE_COUNT];
    public:
        GemType type() const {return YELLOW_GEM;}


        virtual SpriteName getCurSprName() const {return sprites[spr_state];}
        static void setSprite(RndrState state, SpriteName name) { sprites[state]= name; }
    };

    class PurpleGem : public GenericGem
    {
        static SpriteName sprites[ANIM_STATE_COUNT];
    public:
        GemType type() const {return PURPLE_GEM;}

        // make these functions friends
        virtual SpriteName getCurSprName() const {return sprites[spr_state];}
        static void setSprite(RndrState state, SpriteName name) { sprites[state]= name; }
    };



/////////////////////////////LINER/////////////////////////////////////
    class LinerGem : public GenericGem
    {
        bool blown;
        static SpriteName sprites[ANIM_STATE_COUNT];
    public:
        GemType type() const {return BLUE_GEM;}

        // make these functions friends?
        virtual SpriteName getCurSprName() const {return sprites[spr_state];}
        static void setSprite(RndrState state, SpriteName name) { sprites[state]= name; }

        bool trigger(Grid* g);
    };


//////////////////////////////BOMB//////////////////////////////////
class BombGem : public GenericGem
    {
        static Generic::uint8 radius;
        static SpriteName sprites[ANIM_STATE_COUNT];
    public:
        GemType type() const {return RED_GEM;}

        // make these functions friends?
        virtual SpriteName getCurSprName() const {return sprites[spr_state];}
        static void setSprite(RndrState state, SpriteName name) { sprites[state]= name; }

        bool trigger(Grid* g);
    };



    GemInfo* createGem(GemType type);

}
#endif // GEMFACTORY_H_INCLUDED
