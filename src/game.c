#include <SDL.h>
#include "simple_logger.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

#include "entity.h"

void bug_think(Entity* self);
void init_player(Entity* self);
void ball_think(Entity* self);

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *background;
    Entity* first_base;
    Entity* second_base;
    Entity* third_base;
    Entity* home_plate;
    Entity* pitcher;
    Entity* catcher;
    Entity* first;
    Entity* second;
    Entity* third;
    Entity* shortstop;
    Entity* left;
    Entity* center;
    Entity* right;
    Entity* batter;
    Entity* bat;
    Entity* ball;
    Entity* runner1;
    Entity* runner2;
    Entity* runner3;
    /*
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Color mouseColor = gfc_color8(255,100,255,200);
    */
    
    /*program initializtion*/
    init_logger("gf2d.log", 1);
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        700,
        700,
        700,
        700,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    entity_manager_init(1024);
    //SDL_ShowCursor(SDL_DISABLE);
    
    background = gf2d_sprite_load_image("images/backgrounds/field.png");

    home_plate = entity_new();
    if (home_plate)
    {
        home_plate->sprite = gf2d_sprite_load_image("images/base.png");
        home_plate->position.x = 345;
        home_plate->position.y = 582;
    }
    first_base = entity_new();
    if (first_base)
    {
        first_base->sprite = gf2d_sprite_load_image("images/base.png");
        first_base->position.x = 450;
        first_base->position.y = 475;
    }
    second_base = entity_new();
    if (second_base)
    {
        second_base->sprite = gf2d_sprite_load_image("images/base.png");
        second_base->position.x = 345;
        second_base->position.y = 368;
    }
    third_base = entity_new();
    if (third_base)
    {
        third_base->sprite = gf2d_sprite_load_image("images/base.png");
        third_base->position.x = 240;
        third_base->position.y = 475;
    }

    pitcher = entity_new();
    init_player(pitcher, 1, 346, 471);
    catcher = entity_new();
    init_player(catcher, 2, 346, 602);
    first = entity_new();
    init_player(first, 3, 450, 440);
    second = entity_new();
    init_player(second, 4, 400, 368);
    third = entity_new();
    init_player(third, 5, 240, 440);
    shortstop = entity_new();
    init_player(shortstop, 6, 290, 368);
    left = entity_new();
    init_player(left, 7, 195, 275);
    center = entity_new();
    init_player(center, 8, 345, 230);
    right = entity_new();
    init_player(right, 9, 505, 275);
    batter = entity_new();
    init_player(batter, 0, 335, 583);
    runner1 = entity_new();
    //init_player(runner1, 10);
    runner2 = entity_new();
    //init_player(runner2, 11);
    runner3 = entity_new();
    //init_player(runner3, 12);

    bat = entity_new();
    if (bat)
    {
        bat->sprite = gf2d_sprite_load_image("images/baseball_bat.png");
        bat->position.x = batter->position.x + 5;
        bat->position.y = batter->position.y + 5;
    }
    ball = entity_new();
    if (ball)
    {
        ball->sprite = gf2d_sprite_load_image("images/baseball.png");
        ball->holder = pitcher;
        ball->position.x = ball->holder->position.x;
        ball->position.y = ball->holder->position.y;
        ball->think = ball_think;
    }

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        //make all entities follow their think functions
        entity_think_all();
        //show all entity updates
        entity_update_all();
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        
        // all drawing should happen betweem clear_screen and next_frame
        gf2d_sprite_draw_image(background,vector2d(0,0)); //backgrounds drawn first 
        entity_draw_all(); //draw all entities
        
        gf2d_graphics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}

void bug_think(Entity* self)
{
    int mx, my;
    if (!self)return;
    SDL_GetMouseState(&mx, &my);
    if (mx < self->position.x)self->velocity.x = -0.1;
    if (mx > self->position.x)self->velocity.x = 0.1;
    if (my < self->position.y)self->velocity.y = -0.1;
    if (my > self->position.y)self->velocity.y = 0.1;
}

void pitcher_think(Entity* self)
{
    int mx, my;
    if (!self)return;
    SDL_GetMouseState(&mx, &my);
    if (mx < self->position.x)self->velocity.x = -0.1;
    if (mx > self->position.x)self->velocity.x = 0.1;
    if (my < self->position.y)self->velocity.y = -0.1;
    if (my > self->position.y)self->velocity.y = 0.1;
}

void ball_think(Entity* self)
{
    if (!self)return;
    self->position = self->holder->position;
}

void init_player(Entity* self, int id, int posX, int posY)
{
    if (!self) return;
    if (id != 0 && id < 10)
        self->sprite = gf2d_sprite_load_image("images/player_blue.png");
    else
        self->sprite = gf2d_sprite_load_image("images/player_red.png");

    self->position.x = posX;
    self->position.y = posY;
    
    //self->think = think_function;
    switch (id)
    {
        case 1:
            self->think = pitcher_think;

    }
}

/*eol@eof*/
