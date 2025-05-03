#include "dino.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void init_background(TrPixel *bg) {
    for (int i = 0; i < BG_WIDTH * BG_HEIGHT; i += 1) {
        bg[i].ch = ' ';
        bg[i].effect = TR_EFFECT_NONE;
        bg[i].fg_color = TR_DEFAULT;
        bg[i].fg_bright = false;
        bg[i].bg_color = BG_COLOR;
        bg[i].bg_bright = false;
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
    dino_sprite[0].effect = TR_BOLD | TR_UNDERLINE;
    dino_sprite[0].fg_color = TR_GREEN;
    dino_sprite[0].fg_bright = false;
    dino_sprite[0].bg_color = BG_COLOR;
    dino_sprite[0].bg_bright = false;

    dino_sprite[1].ch = 'n';
    dino_sprite[1].effect = TR_BOLD;
    dino_sprite[1].fg_color = TR_GREEN;
    dino_sprite[1].fg_bright = false;
    dino_sprite[1].bg_color = BG_COLOR;
    dino_sprite[1].bg_bright = false;
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
void init_obstacles(Obstacle *obstacles) {
    for (int i = 0; i < OBS_LENGTH; i += 1) {
        obstacles[i].pos.x = BG_WIDTH - SMALL_CACTUS_WIDTH;
        obstacles[i].pos.y = BG_HEIGHT - SMALL_CACTUS_HEIGHT;

        obstacles[i].size.x = SMALL_CACTUS_WIDTH;
        obstacles[i].size.y = SMALL_CACTUS_HEIGHT;

        obstacles[i].vel_x = CACTUS_SPEED;

        obstacles[i].type = OT_SMALL_CACTUS;
    }
    srand(time(NULL));
}
void update_obstacles(Obstacle *obstacles) {
    int r = rand() % 3;

    if (r == 0) {
    }
}
void draw_obstacles(const Obstacle *obstacles) {
}
void init_small_cactus_sprite(TrPixel *small_cactus_sprite) {
    small_cactus_sprite->ch = 'A';
    small_cactus_sprite->effect = TR_BOLD | TR_UNDERLINE;
    small_cactus_sprite->fg_color = TR_GREEN;
    small_cactus_sprite->fg_bright = false;
    small_cactus_sprite->bg_color = BG_COLOR;
    small_cactus_sprite->bg_bright = false;
}
void init_big_cactus_sprite(TrPixel *big_cactus_sprite) {
}
void init_bird_sprite(TrPixel *bird_sprite) {
}
