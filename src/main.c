#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define PIXEL 30
#define WIDTH PIXEL * 10
#define HEIGHT PIXEL * 20

enum piece_type {
    PIECE_I = 0,
    PIECE_J,
    PIECE_L,
    PIECE_O,
    PIECE_S,
    PIECE_T,
    PIECE_Z,
};

typedef struct {
    int points[4][2];
    int color;
} piece_format_t;

typedef struct {
    int x;
    int y;
    int type;
    int rotation;
    piece_format_t *format;
} piece_t;

piece_format_t piece_formats[] = {
    { // PIECE_I
        .points = {
            {1, 0},
            {1, 0},
            {1, 0},
            {1, 0},
        },
        .color = 0x00ffff,
    },
    { // PIECE_J
        .points = {
            {0, 1},
            {0, 1},
            {1, 1},
            {0, 0},
        },
        .color = 0x0000ff,
    },
    { // PIECE_L
        .points = {
            {1, 0},
            {1, 0},
            {1, 1},
            {0, 0},
        },
        .color = 0xff8100,
    },
    { // PIECE_O
        .points = {
            {1, 1},
            {1, 1},
            {0, 0},
            {0, 0},
        },
        .color = 0xffff00,
    },
    { // PIECE_S
        .points = {
            {0, 1},
            {1, 1},
            {1, 0},
            {0, 0},
        },
        .color = 0x00ff00,
    },
    { // PIECE_T
        .points = {
            {0, 1},
            {1, 1},
            {0, 1},
            {0, 0},
        },
        .color = 0xff00ff,
    },
    { // PIECE_Z
        .points = {
            {1, 0},
            {1, 1},
            {0, 1},
            {0, 0},
        },
        .color = 0xff0000,
    },
};

typedef struct {
    int score;
    int piece_count;
    int board;
    piece_t *current_piece;
} game_t;

int running = 1;

void draw_pixel(SDL_Renderer *renderer, int x, int y, int color)
{
    SDL_Rect rect;

    rect.h = PIXEL;
    rect.w = PIXEL;
    rect.x = x;
    rect.y = y;

    SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 0xff);
    SDL_RenderFillRect(renderer, &rect);
}

piece_t *create_piece()
{
    piece_t *piece = malloc(sizeof(piece_t));

    srand(time(0));
    int type = rand() % 7;

    piece->x = 0;
    piece->y = 0;
    piece->type = type;
    piece->rotation = 0;
    piece->format = &piece_formats[type];

    return piece;
}

void draw_piece(SDL_Renderer *renderer, piece_t *piece)
{

    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if (piece->format->points[i][j])
            {
                draw_pixel(renderer, (piece->x + j) * PIXEL, (piece->y + i) * PIXEL, piece->format->color);
            }
        }
    }
}

game_t *new_game()
{
    game_t *game = malloc(sizeof(game_t));

    game->score = 0;
    game->piece_count = 1;
    game->board = 0;
    game->current_piece = create_piece();

    return game;
}

void draw_game(game_t *game, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    draw_piece(renderer, game->current_piece);
}

void game_loop(game_t *game, SDL_Renderer *renderer)
{
    game->current_piece->y++;
    draw_game(game, renderer);
}

int main(int argc, char** argv)
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;

    game_t *game = new_game();

    while (running)
    {
        a = SDL_GetTicks();
        delta = a - b;

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            running = 0;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    running = 0;
                case SDLK_DOWN:
                    // speed up
                    break;
                case SDLK_LEFT:
                    game->current_piece->x--;
                    draw_game(game, renderer);
                    SDL_RenderPresent(renderer);
                    break;
                case SDLK_RIGHT:
                    game->current_piece->x++;
                    draw_game(game, renderer);
                    SDL_RenderPresent(renderer);
                    break;
                case SDLK_UP:
                    game->current_piece->rotation++;
                    draw_game(game, renderer);
                    SDL_RenderPresent(renderer);
                    break;
            }
        }

        if (delta > 1000 / 2)
        {
            b = a;
            game_loop(game, renderer);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}



// int main() {
//     int size = 5;
//     int *myArray = malloc(size * sizeof(int));

//     // inicializa o vetor com valores
//     for (int i = 0; i < size; i++) {
//         myArray[i] = i + 1;
//     }

//     // imprime o vetor antes da remoção
//     printf("Antes da remocao:\n");
//     for (int i = 0; i < size; i++) {
//         printf("%d ", myArray[i]);
//     }
//     printf("\n");

//     int indexToRemove = 2; // índice do elemento a ser removido
//     // realoca a memória para reduzir o tamanho do vetor
//     size--;
//     myArray = realloc(myArray, size * sizeof(int));
//     // move os elementos para preencher o espaço deixado pelo elemento removido
//     for (int i = indexToRemove; i < size; i++) {
//         myArray[i] = myArray[i+1];
//     }

//     // imprime o vetor após a remoção
//     printf("Depois da remocao:\n");
//     for (int i = 0; i < size; i++) {
//         printf("%d ", myArray[i]);
//     }
//     printf("\n");

//     free(myArray);
//     return 0;
// }