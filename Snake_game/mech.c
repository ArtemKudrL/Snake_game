#include "snake.h"

int Initialisation(GAME* game)
{
	game->hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD MaxSize, initial_pos;
	MaxSize = GetLargestConsoleWindowSize(game->hStdOut);

	FILE* file;
	fopen_s(&file, "configs.cfg", "r");
	if (file == NULL)
		return 1;

	// нймн

	while (fgetc(file) != '\n');
	fscanf_s(file, "%hd%hd%*c", &(game->size.X), &(game->size.Y));
	if (game->size.X > MaxSize.X || game->size.X < 0)
		game->size.X = MaxSize.X;
	if (game->size.Y > MaxSize.Y || game->size.Y < 0)
		game->size.Y = MaxSize.Y;

	MaxSize.X = game->size.X;
	MaxSize.Y = game->size.Y;
	SetConsoleScreenBufferSize(game->hStdOut, MaxSize);
	
	// яйнпнярэ

	while (fgetc(file) != '\n');
	fscanf_s(file, "%d%*c", &(game->speed));
	if (game->speed <= 0 || game->speed > 10)
		return 1;

	game->delay = 500 / game->speed;

	// мюкхвхе цпюмхж

	while (fgetc(file) != '\n');
	fscanf_s(file, "%d%*c", &(game->border));
	game->border %= 2;

	// мювюкэмши пюглеп глех
	
	while (fgetc(file) != '\n');
	fscanf_s(file, "%d%*c", &(game->snake.size));
	if (game->snake.size <= 0)
		game->snake.size = 1;

	// мювюкэмюъ онгхжхъ он цнпхгнмрюкх

	while (fgetc(file) != '\n');
	fscanf_s(file, "%hd", &(initial_pos.X));
	if (initial_pos.X <= 0 || initial_pos.X >= game->size.X)
		initial_pos.X = game->size.X / 2;

	// мювюкэмюъ онгхжхъ он бепрхйюкх

	while (fgetc(file) != '\n');
	fscanf_s(file, "%hd%*c", &(initial_pos.Y));
	if (initial_pos.Y <= 0 || initial_pos.Y >= game->size.Y)
		initial_pos.Y = game->size.Y / 2;

	// яхлбнкш бепрхйюкэмшу цпюмхж

	while (fgetc(file) != '\n');
	game->vertical_border_sym = fgetc(file);
	while (fgetc(file) != '\n');

	// яхбнкш цнпхгнмрюкэмшу цпюмхж

	while (fgetc(file) != '\n');
	game->horizontal_border_sym = fgetc(file);
	while (fgetc(file) != '\n');

	// яхлбнк цнкнбш глех

	while (fgetc(file) != '\n');
	game->snake_head_sym = fgetc(file);
	while (fgetc(file) != '\n');

	// яхлбнк рекю глех

	while (fgetc(file) != '\n');
	game->snake_body_sym = fgetc(file);
	while (fgetc(file) != '\n');

	fclose(file);

	// янгдюел глеч

	game->snake.velocity.X = 0;
	game->snake.velocity.Y = 0;

	game->snake.head = (LIST*)malloc(sizeof(LIST));
	game->snake.head->pos = initial_pos;
	game->snake.head->next = game->snake.head;

	for (int i = 1; i < game->snake.size; ++i)
		if (AddBody(&(game->snake)))
			return 1;

	// янгдюмхе онкъ

	game->field = (char*)calloc(game->size.X * game->size.Y, sizeof(char));
	if (game->field == NULL)
		return 1;
	
	for (int i = 0; i < game->size.Y; ++i)
	{
		for (int j = 0; j < game->size.X; ++j)
		{
			if(i == 0 || i == game->size.Y - 1)
				game->field[i * game->size.X + j] = game->horizontal_border_sym;
			else if (j == 0 || j == game->size.X - 1)
				game->field[i * game->size.X + j] = game->vertical_border_sym;
			else
				game->field[i * game->size.X + j] = ' ';
		}
	}

	return 0;
}

int AddBody(SNAKE* snake)
{
	LIST* temp = (LIST*)malloc(sizeof(LIST));
	if (temp == NULL)
		return 1;

	temp->pos = snake->head->pos;
	if(snake->velocity.Y == 0)
		temp->pos.X += snake->velocity.X;
	else
		temp->pos.Y += snake->velocity.Y;
	temp->next = snake->head->next;
	snake->head->next = temp;
	snake->head = temp;

	return 0;
}

int MoveSnake(SNAKE* snake)
{
	snake->head->next->pos = snake->head->pos;
	snake->head = snake->head->next;
	snake->head->pos.X += snake->velocity.X;
	snake->head->pos.Y += snake->velocity.Y;

	return 0;
}