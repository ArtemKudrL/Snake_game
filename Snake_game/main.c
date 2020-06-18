#include "snake.h"

int main(int argc, char* argv[])
{
	GAME game;
	if (Initialisation(&game))
		return 1;
	DrawField(&game);
	return 0;
}