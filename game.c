#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"


int Monster_attack(void *self, int damage)
{
    assert(self);
    assert(damage >= 0);

    Monster *monster = self;

    printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if (monster->hit_points > 0) {
        printf("It is still alive.\n");
        return 0;
    } else {
        printf("It is dead!\n");
        return 1;
    }
}

int Monster_init(void *self)
{
    assert(self);

    Monster *monster = self;
    monster->hit_points = 10;
    return 1;
}

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};


void *Room_move(void *self, Direction direction)
{
    assert(self);

    Room *room = self;
    Room *next = NULL;

    if (direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north;
    } else if (direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    } else if (direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    } else if (direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
    } else {
        printf("You can't go that direction.\n");
        next = NULL;
    }

    if (next) {
        next->_(describe)(next);
    }

    return next;
}


int Room_attack(void *self, int damage)
{
    assert(self);
    assert(damage >= 0);

    Room *room = self;
    Monster *monster = room->bad_guy;

    if (monster) {
        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}


Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};


void *Map_move(void *self, Direction direction)
{
    assert(self);

    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;

    next = location->_(move)(location, direction);

    if (next) {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    assert(self);
    assert(damage >= 0);

    Map *map = self;
    Room *location = map->location;

    return location->_(attack)(location, damage);
}


Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};


int process_input(Map *game)
{
    assert(game);

    printf("\n> ");

    char ch = getchar();
    getchar(); /* eat ENTER */

    int damage = rand() % 4;

    switch (ch) {
    case -1:
        printf("Giving up? You suck.\n");
        return 0;
        break;

    case 'n':
        game->_(move)(game, NORTH);
        break;

    case 's':
        game->_(move)(game, SOUTH);
        break;

    case 'e':
        game->_(move)(game, EAST);
        break;

    case 'w':
        game->_(move)(game, WEST);
        break;

    case 'a':
        game->_(attack)(game, damage);
        break;

    case 'l':
        printf("You can go:\n");
        if (game->location->north) printf("NORTH\n");
        if (game->location->south) printf("SOUTH\n");
        if (game->location->east) printf("EAST\n");
        if (game->location->west) printf("WEST\n");
        break;

    default:
        printf("What?: %d\n", ch);
    }

    return 1;
}
