#include "snake.h"

int Events(GAME* game)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 37:
			if (game->snake.velocity.Y == 0)
				game->snake.velocity.X = -1;
			break;
		case 38:
			if (game->snake.velocity.X == 0)
				game->snake.velocity.Y = -1;
			break;
		case 39:
			if (game->snake.velocity.Y == 0)
				game->snake.velocity.X = 1;
			break;
		case 40:
			if (game->snake.velocity.X == 0)
				game->snake.velocity.Y = 1;
			break;
		}
	}

	return 0;
}

int CheckCollision(GAME* game)
{
	COORD move = game->snake.head->pos;
	move.X += game->snake.velocity.X;
	move.Y += game->snake.velocity.Y;

	// ÂÇÀÈÌÎÄÅÉÑÒÂÈÅ Ñ ÃÐÀÍÈÖÀÌÈ

	if (game->border)
	{
		if (game->snake.velocity.Y == 0)
		{
			if (move.X <= 0 || move.X >= (game->size.X - 1))
				return 1;
		}
		else
		{
			if (move.Y <= 0 || move.Y >= (game->size.Y - 1))
				return 1;
		}
	}
	else
	{
		if (game->snake.velocity.Y == 0)
		{
			if (move.X <= 0 || move.X >= (game->size.X - 1))
				game->snake.head->pos.X = move.X % game->size.X - game->snake.velocity.X;
		}
		else
		{
			if (move.Y <= 0 || move.Y >= (game->size.Y - 1))
				game->snake.head->pos.Y = move.Y % game->size.Y - game->snake.velocity.Y;
		}
	}

	// ÑÒÎËÊÍÎÂÅÍÈÅ Ñ ÕÂÎÑÒÎÌ

	if (game->snake.velocity.Y == 0)
	{
		for (LIST* head = game->snake.head->next; head != game->snake.head; head = head->next)
		{
			if (head->pos.Y == move.Y)
				if (head->pos.X >= game->snake.head->pos.X || head->pos.X <= move.X)
					return 1;
		}
	}
	else
	{
		for (LIST* head = game->snake.head->next; head != game->snake.head; head = head->next)
		{
			if (head->pos.X == move.X)
				if (head->pos.Y >= game->snake.head->pos.Y || head->pos.Y <= move.Y)
					return 1;
		}
	}

	return 0;
}