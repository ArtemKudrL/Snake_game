#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <malloc.h>
#include <wtypes.h>
#include <wincon.h>
#include <conio.h>

struct _LIST
{
	struct _COORD pos;
	struct _LIST* next;
};

struct _SNAKE
{
	struct _LIST* head;
	struct _COORD velocity;
	int size;
};

struct _GAME
{
	HANDLE hStdOut;

	char* field;
	struct _SNAKE snake;

	char vertical_border_sym;
	char horizontal_border_sym;
	char apple_sym;
	char snake_head_sym;
	char snake_body_sym;

	int border;
	int speed;
	int delay;

	COORD size;
};

typedef struct _LIST LIST;
typedef struct _SNAKE SNAKE;
typedef struct _GAME GAME;

int Initialisation(GAME* game);
int AddBody(SNAKE* snake);
int CheckCollision(GAME* game);
int MoveSnake(SNAKE* snake);
int Events(GAME* game);
void ClearField(GAME* game);
void DrawField(GAME* game);