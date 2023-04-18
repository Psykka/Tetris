#include <stdlib.h>
#include <time.h>

#include "SDL.h"

#define PIXEL 30
#define WIDTH PIXEL * 10
#define HEIGHT PIXEL * 20

#define ROTATION_TESTS 5
#define ORIENTATIONS 4

enum piece_type
{
    PIECE_I = 0,
    PIECE_J,
    PIECE_L,
    PIECE_O,
    PIECE_S,
    PIECE_T,
    PIECE_Z,
};

enum rotation_direction
{
    CLOCKWISE = 0,
    COUNTER_CLOCKWISE,
};

typedef struct point
{
    int x;
    int y;
} point_t;

static point_t offset_I[ORIENTATIONS][ROTATION_TESTS] = {
    {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
    {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
    {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},
};

static point_t offset_JLSTZ[ORIENTATIONS][ROTATION_TESTS] = {
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
    {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
    {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
};

static point_t offset_O[ORIENTATIONS][ROTATION_TESTS] = {
    {{0, 0}},
    {{0, -1}},
    {{0, -1}},
    {{0, -1}}};

typedef struct
{
    int tiles[4][4];
    int color;
} piece_format_t;

typedef struct
{
    int type;
    int rotation;
    point_t *position;
    piece_format_t *format;
} piece_t;

piece_format_t piece_formats[] = {
    {
        // PIECE_I
        .tiles = {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
        },
        .color = 0x00ffff,
    },
    {
        // PIECE_J
        .tiles = {
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        .color = 0x0000ff,
    },
    {
        // PIECE_L
        .tiles = {
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        .color = 0xff8100,
    },
    {
        // PIECE_O
        .tiles = {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        .color = 0xffff00,
    },
    {
        // PIECE_S
        .tiles = {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        .color = 0x00ff00,
    },
    {
        // PIECE_T
        .tiles = {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        .color = 0xff00ff,
    },
    {
        // PIECE_Z
        .tiles = {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        .color = 0xff0000,
    },
};

typedef struct
{
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
    piece->position = malloc(sizeof(point_t));

    srand(time(0));
    int type = rand() % 7;

    piece->position->x = 0;
    piece->position->y = 0;
    piece->type = type;
    piece->rotation = 0;
    piece->format = &piece_formats[type];

    return piece;
}

void draw_piece(SDL_Renderer *renderer, piece_t *piece)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (piece->format->tiles[i][j])
            {
                draw_pixel(renderer, (piece->position->x + j) * PIXEL, (piece->position->y + i) * PIXEL, piece->format->color);
            }
        }
    }
}

void rotate_piece(piece_t *piece, int direction)
{
    int old_orientation = piece->rotation;
    int rotation_index = direction == 1 ? 0 : 1;
    rotation_index = (rotation_index % ORIENTATIONS + ORIENTATIONS) % ORIENTATIONS;
}

game_t *new_game(game_t *game)
{
    if(game != NULL)
    {
        free(game);
    } else {
        game = malloc(sizeof(game_t));
    }

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
    game->current_piece->position->y++;
    draw_game(game, renderer);
}

int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
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

    game_t *game = new_game(NULL);

    while (running)
    {
        int speed = 2;
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
                free(game);
                break;
            case SDLK_DOWN:
                speed = 60;
                break;
            case SDLK_LEFT:
                game->current_piece->position->x--;
                draw_game(game, renderer);
                SDL_RenderPresent(renderer);
                break;
            case SDLK_RIGHT:
                game->current_piece->position->x++;
                draw_game(game, renderer);
                SDL_RenderPresent(renderer);
                break;
            case SDLK_x:
                rotate_piece(game->current_piece, CLOCKWISE);
                draw_game(game, renderer);
                SDL_RenderPresent(renderer);
                break;
            case SDLK_z:
                rotate_piece(game->current_piece, COUNTER_CLOCKWISE);
                draw_game(game, renderer);
                SDL_RenderPresent(renderer);
                break;
            case SDLK_SPACE:
                // drop
                break;
            }
        }

        if (delta > 1000 / speed)
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
