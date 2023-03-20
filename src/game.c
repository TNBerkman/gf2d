#include <SDL.h>
#include "simple_logger.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

#include "entity.h"

void init_player(Entity* self, int id, int posX, int posY);
void ball_think(Entity* self);
void pitcher_think(Entity* self);


Entity* ball;
int inPlay;
int pitched;
Entity* first_base;
Entity* second_base;
Entity* third_base;
Entity* home_plate;
const Uint8* keys;

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;

    Sprite *background;

    // Declare entities
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

    // create new entities for the field
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

    // create players
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

    // create bat and ball, attatch them where needed initially
    bat = entity_new();
    if (bat)
    {
        bat->sprite = gf2d_sprite_load_image("images/baseball_bat.png");
        bat->holder = batter;
        bat->position.x = bat->holder->position.x + 5;
        bat->position.y = bat->holder->position.y + 5;
        
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
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());

    }
    slog("---==== END ====---");
    return 0;
}

/* BUGTHINK CODE
    int mx, my;
    if (!self)return;
    SDL_GetMouseState(&mx, &my);
    if (mx < self->position.x)self->velocity.x = -0.1;
    if (mx > self->position.x)self->velocity.x = 0.1;
    if (my < self->position.y)self->velocity.y = -0.1;
    if (my > self->position.y)self->velocity.y = 0.1;
*/

void pitcher_think(Entity* self)
{
    if (!self)return;

    if (ball->holder == self)//if the pitcher has the ball
    {
        if (inPlay) // you are holding the ball in play
        {
            
        }
        else // you are pitching
        {
            // movement
            if (keys[SDL_SCANCODE_A]) self->velocity.x = -.1;
            else if (keys[SDL_SCANCODE_D]) self->velocity.x = .1;
            else self->velocity.x = 0;
            
            //pitches
            if (keys[SDL_SCANCODE_1])
            { 
                ball->velocity.y = 1;
                pitched = 1;
            }
        }
    }
    else //the pitcher doesnt have the ball
    {
        //do nothing for now, will work fine
    }
}

void catcher_think(Entity* self)
{
    if (inPlay)
    {
        if (ball->holder == self)//if the player has the ball
        {

        }
        else //the player does not have the ball
        {
            //dumb C brain just cover home
        }
    }
    else
    {
        self->position.x = 346;
        self->position.y = 602;
    }
}

void first_think(Entity* self)
{
    if (inPlay)
    {
        if (ball->holder == self)//if the player has the ball
        {

        }
        else //the player does not have the ball
        {
            //dumb 1B brain just cover first
        }
    }
    else
    {
        self->position.x = 450;
        self->position.y = 440;
    }
}

void second_think(Entity* self)
{
    if (inPlay)
    {
        if (ball->holder == self)//if the player has the ball
        {

        }
        else //the player does not have the ball
        {
            if (ball->position.x > second_base->position.x) //the ball is to the right side of the field
            {
                //field it
            }
            else // the ball is to the left
            {
                //cover second base
            }
        }
    }
    else
    {
        self->position.x = 400;
        self->position.y = 368;
    }
}

void third_think(Entity* self)
{
    if (inPlay)
    {
        if (ball->holder == self)//if the player has the ball
        {

        }
        else //the player does not have the ball
        {
            //dumb 3B brain just cover third
        }
    }
    else
    {
        self->position.x = 240;
        self->position.y = 440;
    }
}

void shortstop_think(Entity* self)
{
    if (inPlay)
    {
        if (ball->holder == self)//if the player has the ball
        {

        }
        else //the player does not have the ball
        {
            if (ball->position.x > second_base->position.x) //the ball is to the right side of the field
            {
                //cover second base
            }
            else // the ball is to the left
            {
                //field it
            }
        }
    }
    else
    {
        self->position.x = 290;
        self->position.y = 368;
    }
}

void left_think(Entity* self)
{
    if (inPlay)
    {
        if (ball->holder == self)//if the player has the ball
        {

        }
        else //the player does not have the ball
        {
            if (ball->position.x > second_base->position.x) //the ball is to the right side of the field
            {
                //do nothing
            }
            else // the ball is to the left
            {
                //field it
            }
        }
    }
    else
    {
        self->position.x = 195;
        self->position.y = 275;
    }
}

void center_think(Entity* self)
{
    if (inPlay)
    {
        if (ball->holder == self)//if the player has the ball
        {

        }
        else //the player does not have the ball
        {
            //field it
        }
    }
    else
    {
        self->position.x = 345;
        self->position.y = 230;
    }
}

void right_think(Entity* self)
{
    if (inPlay)
    {
        if (ball->holder == self)//if the player has the ball
        {

        }
        else //the player does not have the ball
        {
            if (ball->position.x > second_base->position.x) //the ball is to the right side of the field
            {
                //field it
            }
            else // the ball is to the left
            {
                //do nothing
            }
        }
    }
    else
    {
        self->position.x = 505;
        self->position.y = 275;
    }
}

void ball_think(Entity* self)
{
    if (!self)return;
    if (inPlay) // ball is in play
    {

    }
    else if (pitched) // ball is not in play but must move towards home
    {
        if (self->position.y > 602)
        {
            pitched = 0;
        }
    }
    else // between plays
    {
        self->position = self->holder->position; // ball is back in pitcher's hand
    }
    
    
}

void bat_think(Entity* self)
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
            break;
        case 2:
            self->think = catcher_think;
            break;
        case 3:
            self->think = first_think;
            break;
        case 4:
            self->think = second_think;
            break;
        case 5:
            self->think = third_think;
            break;
        case 6:
            self->think = shortstop_think;
            break;
        case 7:
            self->think = left_think;
            break;
        case 8:
            self->think = center_think;
            break;
        case 9:
            self->think = right_think;
            break;
    }
}

/*eol@eof*/
