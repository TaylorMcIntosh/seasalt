// NAME :  taylormci
// DATE :  2026-10-14
// PURP :  object.h -> object struct

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static char input[100];
static bool is_playing = true;

typedef struct adj {
	const char *name;
	const int value;
} adj;

extern adj opinions[];
extern adj sizes[];
extern adj qualities[];
extern adj ages[];
extern adj materials[];

typedef struct object {
	const char *name;

	struct adj *opinion;
	struct adj *size;
	struct adj *qualitie;
	struct adj *age;
	struct adj *material;

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
