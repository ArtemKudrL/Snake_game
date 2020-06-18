#include "snake.h"

void ClearField(GAME* game)
{
	COORD BufferCoord = { 0, 0 };
	SMALL_RECT srWriteRegion = { 0, 0, game->size.X, game->size.Y };

	CHAR_INFO* lpBuffer = (CHAR_INFO*)calloc(game->size.X * game->size.Y, sizeof(CHAR_INFO));

	WriteConsoleOutput(game->hStdOut, lpBuffer, game->size, BufferCoord, &srWriteRegion);
	free(lpBuffer);
}
void DrawField(GAME* game)
{
	COORD BufferCoord = { 0, 0 };
	SMALL_RECT srWriteRegion = { 0, 0, game->size.X, game->size.Y };

	CHAR_INFO* lpBuffer = (CHAR_INFO*)malloc((size_t)(game->size.X * game->size.Y * sizeof(CHAR_INFO)));
	for (int i = 0; i < game->size.X * game->size.Y; ++i)
	{
		lpBuffer[i].Char.AsciiChar = game->field[i];
		lpBuffer[i].Attributes = 0x0080;
	}

	WriteConsoleOutput(game->hStdOut, lpBuffer, game->size, BufferCoord, &srWriteRegion);
	free(lpBuffer);
}
void EraseTail(SNAKE* snake)
{
	return;
}