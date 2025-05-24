#ifndef DINO_H
#define DINO_H

#include "../../trenderer.h"

// Utils
typedef struct Vec2 {
    int x;
    int y;
} Vec2;

// Background
#define BG_WIDTH 50
#define BG_HEIGHT 10

#define BG_COLOR TR_YELLOW

void init_background(TrPixel *bg);
void draw_background(const TrPixel *bg);

// Dino
#define KEY_SPACE 32
#define KEY_ESC 27

#define GRAVITY_ACCEL 2
#define JUMP_SPEED 3

#define DINO_WIDTH 1
#define DINO_HEIGHT 2

typedef struct Dino {
    Vec2 pos;
    Vec2 size;
    int vel_y;
    bool is_jumping;
    bool is_alive;
} Dino;

void init_dino(Dino *dino, TrPixel *dino_sprite);
void update_dino(Dino *dino);
void draw_dino(const Dino *dino, const TrPixel *dino_sprite);

// Obstacles
#define OBS_LENGTH 2
#define CACTUS_SPEED 5
#define BIRD_SPEED 10

#define SMALL_CACTUS_WIDTH 1
#define SMALL_CACTUS_HEIGHT 1

#define BIG_CACTUS_WIDTH 1
#define BIG_CACTUS_HEIGHT 2

#define BIRD_WIDTH 2
#define BIRD_HEIGHT 1

typedef enum ObstacleType {
    OT_SMALL_CACTUS = 0,
    OT_BIG_CACTUS = 1,
    OT_BIRD = 2
} ObstacleType;
typedef struct Obstacle {
    ObstacleType type;
    Vec2 pos;
    Vec2 size;
    int vel_x;
    bool is_alive;
} Obstacle;

void delay(int ms);

void init_obstacle(Obstacle *obstacle, ObstacleType type);

void init_obstacles(Obstacle *obstacles);
void update_obstacles(Obstacle *obstacles);
void draw_obstacles(const Obstacle *obstacles);

void init_small_cactus_sprite(TrPixel *small_cactus_sprite);
void init_big_cactus_sprite(TrPixel *big_cactus_sprite);
void init_bird_sprite(TrPixel *bird_sprite);

#endif
