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
} object;

// objects array -> Everything in the game
object objects[] = {
	{"cave"     , "a small cave"  , NULL},
	{"field"    , "an empty field", NULL},
	{"coin"     , "a golden coin" , &objects[0]},
	{"yourself" , "yourself"      , &objects[0]},
};

#define cave    (objects + 0)
#define field   (objects + 1)
#define coin    (objects + 2)
#define player  (objects + 3)

#define obj_end (objects + 4)
// }}}

// COMMANDS && ACTIONS {{{
void exec_look(const char *noun) {
	if (strcmp(noun, "around") == 0)
		printf("you are in %s.\n", player->loc->desc);
	else
		printf("I do not know what you wish to see.");
}

void exec_move(const char *noun) {
	object *obj;
	for (obj = objects; obj < obj_end; obj++) {
		if (strcmp(noun, obj->name) == 0 && obj->loc == NULL)
			player->loc = obj;
	}
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
