#include "../trenderer.h"
#include <Windows.h>
#include <conio.h>

#define KEY_SPACE 32
#define KEY_ESC 27

#define GRAVITY_FORCE 2
#define JUMP_FORCE 3

#define BG_WIDTH 50
#define BG_HEIGHT 10
#define BG_COLOR TR_YELLOW

#define DINO_WIDTH 1
#define DINO_HEIGHT 2

#define OBS_COUNT 2
#define OBS_A_WIDTH 1
#define OBS_A_HEIGHT 1

typedef struct Vec2 {
    int x;
    int y;
} Vec2;
typedef struct Dino {
    Vec2 pos;
    Vec2 size;
    int vel_y;
    bool is_jumping;
    bool is_alive;
} Dino;
typedef struct Obstacle {
    Vec2 pos;
    Vec2 size;
    int vel_x;
    int type;
} Obstacle;

void init_background(TrPixel *bg);
void draw_background(const TrPixel *bg);

void init_dino(Dino *dino);
void init_dino_sprite(TrPixel *dino_sprite);
void update_dino(Dino *dino);
void draw_dino(const Dino *dino, const TrPixel *dino_sprite);

void init_obstacles(Obstacle *obstacles);
void update_obstacles(Obstacle *obstacles);
void draw_obstacles(const Obstacle *obstacles);

void init_obs_a_sprite(TrPixel *sprite); // Small one
void init_obs_b_sprite(TrPixel *sprite); // Tall one

int main(void) {
    tr_show_cursor(false);

    TrPixel bg[BG_WIDTH * BG_HEIGHT];
    init_background(bg);

    Dino dino;
    init_dino(&dino);

    TrPixel dino_sprite[DINO_WIDTH * DINO_HEIGHT];
    init_dino_sprite(dino_sprite);

    Obstacle obstacles[OBS_COUNT];
    init_obstacles(obstacles);

    TrPixel obs_a_sprite[OBS_A_WIDTH * OBS_A_HEIGHT];
    init_obs_a_sprite(obs_a_sprite);

    while (dino.is_alive) {
        tr_clear();
        update_dino(&dino);

        draw_background(bg);
        draw_dino(&dino, dino_sprite);

        Sleep(33);
    }

    return 0;
}

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
void init_dino(Dino *dino) {
    dino->pos.x = 1;
    dino->pos.y = BG_HEIGHT;

    dino->vel_y = 0;

    dino->size.x = DINO_WIDTH;
    dino->size.y = DINO_HEIGHT;

    dino->is_jumping = false;
    dino->is_alive = true;
}
void init_dino_sprite(TrPixel *dino_sprite) {
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
            dino->vel_y = -JUMP_FORCE;
            break;
        case KEY_ESC:
            dino->is_alive = false;
            break;
        }
    }
    if (dino->is_jumping) {
        dino->pos.y += dino->vel_y;
        dino->vel_y += GRAVITY_FORCE;
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
}
void update_obstacles(Obstacle *obstacles) {

}
void draw_obstacles(const Obstacle *obstacles) {

}
void init_obs_a_sprite(TrPixel *sprite) {
    for (int i = 0; i < OBS_A_WIDTH * OBS_A_HEIGHT; i += 1) {
        sprite[i].ch = 'A';
        sprite[i].effect = TR_BOLD;
        sprite[i].fg_color = TR_DEFAULT;
        sprite[i].fg_bright = false;
        sprite[i].bg_color = BG_COLOR;
        sprite[i].bg_bright = false;
    }
}
