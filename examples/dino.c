#include "../trenderer.h"
#include <Windows.h>
#include <conio.h>

#define KEY_SPACE 32
#define KEY_ESC 27

#define GRAVITY_FORCE 2
#define JUMP_FORCE 3

#define BG_WIDTH 20
#define BG_HEIGHT 10

#define DINO_WIDTH 1
#define DINO_HEIGHT 2

typedef struct Vec2 {
    int x;
    int y;
} Vec2;
typedef struct Obstacle {
    Vec2 pos;
    int vel;
    Vec2 size;
} Obstacle;
typedef struct Dino {
    Vec2 pos;
    Vec2 size;
    int vel;
    bool is_jumping;
    bool is_alive;
} Dino;

void dino_init(Dino *dino);
void dino_sprite_init(TrPixel *dino_sprite);
void dino_update(Dino *dino);
void dino_draw(const Dino *dino, const TrPixel *dino_sprite);

void background_init(TrPixel *bg);
void background_draw(const TrPixel *bg);

int main(void) {
    tr_cursor_visible(false);

    Dino dino;
    dino_init(&dino);

    TrPixel dino_sprite[DINO_WIDTH * DINO_HEIGHT];
    dino_sprite_init(dino_sprite);

    TrPixel bg[BG_WIDTH * BG_HEIGHT];
    background_init(bg);

    while (dino.is_alive) {
        tr_clear();
        dino_update(&dino);
        background_draw(bg);
        dino_draw(&dino, dino_sprite);
        Sleep(33);
    }

    return 0;
}

void dino_init(Dino *dino) {
    dino->pos.x = 1;
    dino->pos.y = BG_HEIGHT;

    dino->vel = 0;

    dino->size.x = DINO_WIDTH;
    dino->size.y = DINO_HEIGHT;

    dino->is_jumping = false;
    dino->is_alive = true;
}
void dino_sprite_init(TrPixel *dino_sprite) {
    dino_sprite[0].ch = 'P';
    dino_sprite[0].effect = TR_BOLD;
    dino_sprite[0].fg_color = TR_GREEN;
    dino_sprite[0].fg_bright = true;
    dino_sprite[0].bg_color = TR_DEFAULT;
    dino_sprite[0].bg_bright = true;

    dino_sprite[1].ch = 'n';
    dino_sprite[1].effect = TR_BOLD;
    dino_sprite[1].fg_color = TR_GREEN;
    dino_sprite[1].fg_bright = true;
    dino_sprite[1].bg_color = TR_DEFAULT;
    dino_sprite[1].bg_bright = true;
}
void dino_update(Dino *dino) {
    if (!dino->is_alive)
        return;

    if (_kbhit()) {
        switch (_getch()) {
        case KEY_SPACE:
            if (dino->is_jumping)
                break;
            dino->is_jumping = true;
            dino->vel = -JUMP_FORCE;
            break;
        case KEY_ESC:
            dino->is_alive = false;
            break;
        }
    }
    if (dino->is_jumping) {
        dino->pos.y += dino->vel;
        dino->vel += GRAVITY_FORCE;
    }
    if (dino->pos.y >= BG_HEIGHT) {
        dino->is_jumping = false;
        dino->vel = 0;
        dino->pos.y = BG_HEIGHT;
    }
}
void dino_draw(const Dino *dino, const TrPixel *dino_sprite) {
    tr_draw_sprite(dino_sprite, dino->pos.x, dino->pos.y, dino->size.x, dino->size.y);
}
void background_init(TrPixel *bg) {
    for (int y = 0; y < BG_HEIGHT; y += 1) {
        for (int x = 0; x < BG_WIDTH; x += 1) {
            int i = y * BG_WIDTH + x;
        }
    }
}
void background_draw(const TrPixel *bg) {
    tr_draw_sprite(bg, 0, 0, BG_WIDTH, BG_HEIGHT);
}
