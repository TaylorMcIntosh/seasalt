// NAME :  taylormci
// DATE :  2026-10-14
// PURP :  main.c -> entry point

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static char input[100];
static bool is_playing = true;

// OBJECTS {{{

// object struct -> this will include anything interactable
typedef struct object {
	const char *name;
	const char *desc;
	struct object *loc;

	struct object *north;
	struct object *south;
	struct object *east;
	struct object *west;
} object;

// objects array -> Everything in the game
object objects[] = {
	{"cave"     , "a small cave"  , NULL, NULL, &objects[1], NULL, NULL},
	{"field"    , "an empty field", NULL, &objects[0], NULL, NULL, &objects[2]},
	{"beach"    , "a calm beach"  , NULL, NULL, NULL, &objects[1], NULL},

	{"coin"     , "a golden coin" , &objects[0], NULL, NULL, NULL, NULL},
	{"yourself" , "yourself"      , &objects[0], NULL, NULL, NULL, NULL},
};

#define cave    (objects + 0)
#define field   (objects + 1)
#define beach   (objects + 2)
#define coin    (objects + 3)
#define player  (objects + 4)

#define obj_end (objects + 5)
// }}}

void look_around(const char *noun) {
	object *obj;
	printf("You are in %s.\n", player->loc->desc);
		for (obj = objects; obj < obj_end; obj++) {
			if (obj->loc == player->loc && obj != player)
				printf("You see: %s\n", obj->desc);
		}
}

// COMMANDS && ACTIONS {{{
void exec_look(const char *noun) {
	if (strcmp(noun, "around") == 0) {
		look_around(noun);	
	}
	else
		printf("I do not know what you wish to see.");
}

void exec_move(const char *noun) {
	object *obj;
	
	if (strcmp(noun, "north") == 0 && player->loc->north != NULL)
		player->loc = player->loc->north;
	else if (strcmp(noun, "south") == 0 && player->loc->south != NULL)
		player->loc = player->loc->south;
	else if (strcmp(noun, "east") == 0 && player->loc->east != NULL)
		player->loc = player->loc->east;
	else if (strcmp(noun, "west") == 0 && player->loc->west != NULL)
		player->loc = player->loc->west;
	else {
		printf("There is nothing of note %s of here.\n", noun);
		return;
	}
	exec_look("around");
}
// }}}

// INPUT OUTPUT {{{
static void input_parse(char *input) {
	char *verb = strtok(input, " \n");  	// get first word  (verb)
	char *noun = strtok(NULL, " \n");   	// get second word (noun)
	if (verb == NULL) { return; }		// return if null
	else if (strcmp(verb, "quit") == 0)	// quit -> quits game
		is_playing = false; 
	else if (strcmp(verb, "look") == 0)	// look -> writes description of current map
		exec_look(noun);
	else if (strcmp(verb, "move") == 0)	// move -> moves player to desired map
		exec_move(noun);
}

static void input_handle() {
	printf("\n--> ");
	fgets(input, sizeof input, stdin);
	input_parse(input);
}
// }}}

// MAIN {{{
int main(int argc, char *argv[]) {
	while (is_playing) { input_handle(); }
	return 0;
}
// }}}
