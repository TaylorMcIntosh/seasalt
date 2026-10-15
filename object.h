// NAME :  taylormci
// DATE :  2026-10-14
// PURP :  object.h -> object struct

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// TODO : Add Order of Adjectives as psuedo rarity sytem for items, rolled when first grabbed
// Opinion, Size, Physical Quality, Shape, Age, Color, Material, Type, Purpose

static char input[100];
static bool is_playing = true;

typedef struct object {
	const char *name;

	struct object *loc;
	struct object *north;
	struct object *south;
	struct object *east;
	struct object *west;
} object;

extern object objects[];

#define cave    (objects + 0)
#define field   (objects + 1)
#define beach   (objects + 2)
#define player  (objects + 3)
#define coin    (objects + 4)

#define obj_end (objects + 5)
