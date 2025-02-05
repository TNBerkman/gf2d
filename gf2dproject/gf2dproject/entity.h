#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"

#include "gf2d_sprite.h"

typedef struct Entity Entity;
struct Entity
{
	Bool _inuse;
	Sprite* sprite;
	float frame;
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	Entity* holder;
	int controlled;

	void(*think)(struct Entity* self);
};

/**
* @brief initialize the internal manager for the entity system
* @note this will automatically queue up the close function for program exit
* @param max this is the maximum number of supported entities at a given time
*/
void entity_manager_init(Uint32 max);

/**
* @brief allocate and initialize a new entity
* @return NULL if there are no entities left, an empty entity otherwise
*/
Entity* entity_new();

/**
* @brief free a previously allocated entity
* @param ent the entity to free
*/
void entity_free(Entity* ent);

/**
* 
*/
void entity_free_all();

/**
*/
void entity_draw_all();

/**
*/
void entity_update_all();

/**
*/
void entity_think_all();

#endif