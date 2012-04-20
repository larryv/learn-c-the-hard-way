#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "game.h"

extern Object MapProto;
extern Object MonsterProto;
extern Object RoomProto;

int process_input(Map *game);

int Map_init(void *self)
{
    assert(self);

    Map *map = self;

    /* make some rooms for a small map */
    Room *hall = NEW(Room, "The great Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

    /* extra credit: add more rooms */
    Room *dungeon = NEW(Room, "The dungeon, with the chimera");
    Room *keep = NEW(Room, "The keep, with the hydra");
    Room *pantry = NEW(Room, "The overflowing pantry");
    Room *courtyard = NEW(Room, "The beautiful courtyard, with the troll");
    Room *garden = NEW(Room, "The fertile garden");

    /* put the bad guy in the arena */
    arena->bad_guy = NEW(Monster, "The evil minotaur");

    /* extra credit: add more bad guys */
    dungeon->bad_guy = NEW(Monster, "the vicious chimera");
    keep->bad_guy = NEW(Monster, "the deadly hydra");
    courtyard->bad_guy = NEW(Monster, "the ruthless troll");

    /* set up the map rooms */
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    arena->north = dungeon;
    dungeon->south = arena;

    throne->north = keep;
    keep->south = throne;

    kitchen->south = pantry;
    pantry->north = kitchen;

    hall->south = courtyard;
    courtyard->north = hall;

    kitchen->east = garden;
    garden->west = kitchen;

    /* start the map and the character off in the hall */
    map->start = hall;
    map->location = hall;

    return 1;
}

int main(int argc, const char **argv)
{
    /* simple way to set up the randomness */
    srand(time(NULL));

    /* make our map to work with */
    Map *game = NEW(Map, "The Hall of the Minotaur.");

    printf("You enter the ");
    game->location->_(describe)(game->location);

    while (process_input(game))
        ;

    return 0;
}
