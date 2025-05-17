#include "dino.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void init_background(TrPixel *bg) {
    for (int i = 0; i < BG_WIDTH * BG_HEIGHT; i += 1) {
        bg[i].ch = ' ';
        bg[i].style.effect = TR_EFFECT_NONE;
        bg[i].style.fg_color = TR_DEFAULT;
        bg[i].style.fg_bright = false;
        bg[i].style.bg_color = BG_COLOR;
        bg[i].style.bg_bright = false;
    }
}
void draw_background(const TrPixel *bg) {
    tr_draw_sprite(bg, 0, 0, BG_WIDTH, BG_HEIGHT);
}
void init_dino(Dino *dino, TrPixel *dino_sprite) {
    dino->pos.x = 1;
    dino->pos.y = BG_HEIGHT;

    dino->vel_y = 0;

    dino->size.x = DINO_WIDTH;
    dino->size.y = DINO_HEIGHT;

    dino->is_jumping = false;
    dino->is_alive = true;

    dino_sprite[0].ch = 'P';
    dino_sprite[0].style.effect = TR_BOLD | TR_UNDERLINE;
    dino_sprite[0].style.fg_color = TR_GREEN;
    dino_sprite[0].style.fg_bright = false;
    dino_sprite[0].style.bg_color = BG_COLOR;
    dino_sprite[0].style.bg_bright = false;

    dino_sprite[1].ch = 'n';
    dino_sprite[1].style.effect = TR_BOLD;
    dino_sprite[1].style.fg_color = TR_GREEN;
    dino_sprite[1].style.fg_bright = false;
    dino_sprite[1].style.bg_color = BG_COLOR;
    dino_sprite[1].style.bg_bright = false;
}
void update_dino(Dino *dino) {
    if (!dino->is_alive)
        return;

    if (_kbhit()) {
        switch (_getch()) {
        case KEY_SPACE:
            if (dino->is_jumping)
                break;
            dino->is_jumping = true;
            dino->vel_y = -JUMP_SPEED;
            break;
        case KEY_ESC:
            dino->is_alive = false;
            break;
        }
    }
    if (dino->is_jumping) {
        dino->pos.y += dino->vel_y;
        dino->vel_y += GRAVITY_ACCEL;
    }
    if (dino->pos.y >= (BG_HEIGHT - DINO_HEIGHT)) {
        dino->is_jumping = false;
        dino->vel_y = 0;
        dino->pos.y = BG_HEIGHT - DINO_HEIGHT;
    }
}
void draw_dino(const Dino *dino, const TrPixel *dino_sprite) {
    tr_draw_sprite(dino_sprite, dino->pos.x, dino->pos.y, dino->size.x, dino->size.y);
}
void init_obstacle(Obstacle *obstacle, ObstacleType type) {
    int width = 0, height = 0;
    int speed = 0;

    switch (type) {
    case OT_SMALL_CACTUS: {
        width = SMALL_CACTUS_WIDTH;
        height = SMALL_CACTUS_HEIGHT;
        speed = CACTUS_SPEED;
    } break;
    case OT_BIG_CACTUS: {
        width = BIG_CACTUS_WIDTH;
        height = BIG_CACTUS_HEIGHT;
        speed = CACTUS_SPEED;
    } break;
    case OT_BIRD: {
        width = BIRD_WIDTH;
        height = BIRD_HEIGHT;
        speed = BIRD_SPEED;
    } break;
    }

    obstacle->type = type;

    obstacle->pos.x = BG_WIDTH - width;
    obstacle->pos.y = BG_HEIGHT - height;

    obstacle->size.x = width;
    obstacle->size.y = height;

    obstacle->vel_x = -speed;

    obstacle->is_alive = false;
}
void init_obstacles(Obstacle *obstacles) {
    for (int i = 0; i < OBS_LENGTH; i += 1) {
        init_obstacle(&obstacles[i], OT_SMALL_CACTUS);
    }
    srand(time(NULL));
}
void update_obstacles(Obstacle *obstacles) {
    for (int i = 0; i < OBS_LENGTH; i += 1) {
        if (!obstacles[i].is_alive) {
            init_obstacle(&obstacles[i], (ObstacleType)(rand() % 3));
            obstacles[i].is_alive = true;
            continue;
        }
        obstacles[i].pos.x += obstacles[i].vel_x;
    }
}
void draw_obstacles(const Obstacle *obstacles) {
    for (int i = 0; i < OBS_LENGTH; i += 1) {
    }
}
void init_small_cactus_sprite(TrPixel *small_cactus_sprite) {
    small_cactus_sprite->ch = 'A';
    small_cactus_sprite->style.effect = TR_BOLD | TR_UNDERLINE;
    small_cactus_sprite->style.fg_color = TR_GREEN;
    small_cactus_sprite->style.fg_bright = false;
    small_cactus_sprite->style.bg_color = BG_COLOR;
    small_cactus_sprite->style.bg_bright = false;
}
void init_big_cactus_sprite(TrPixel *big_cactus_sprite) {
}
void init_bird_sprite(TrPixel *bird_sprite) {
}
