#include "../trenderer.h"

#define DINO_WIDTH 1
#define DINO_HEIGHT 2

typedef struct Vec2 {
	int x;
	int y;
} Vec2;
typedef struct Object {
	Vec2 pos;
	Vec2 vel;
	Vec2 size;
} Object;

void object_draw(TrPixel *sprite, const Object *object);

void dino_init(Object *dino);
void dino_sprite_init(TrPixel *dino_sprite);

int main(void) {
	Object dino;
	dino_init(&dino);

	TrPixel dino_sprite[DINO_WIDTH * DINO_HEIGHT];
	dino_sprite_init(dino_sprite);

	tr_clear();
	tr_draw_sprite(dino_sprite, 0, 0, DINO_WIDTH, DINO_HEIGHT);
	return 0;
}

void dino_init(Object *dino) {
	dino->pos.x = 1;
	dino->pos.y = 10;

	dino->vel.x = 0;
	dino->vel.y = 0;

	dino->size.x = DINO_WIDTH;
	dino->size.y = DINO_HEIGHT;
}
void dino_sprite_init(TrPixel *dino_sprite) {
	dino_sprite[0].ch = 'F';
	dino_sprite[0].effect = TR_BOLD;
	dino_sprite[0].fg_color = TR_GREEN;
	dino_sprite[0].fg_bright = true;
	dino_sprite[0].bg_color = TR_DEFAULT;
	dino_sprite[0].bg_bright = true;

	dino_sprite[1].ch = 'N';
	dino_sprite[1].effect = TR_BOLD | TR_BLINK;
	dino_sprite[1].fg_color = TR_GREEN;
	dino_sprite[1].fg_bright = true;
	dino_sprite[1].bg_color = TR_DEFAULT;
	dino_sprite[1].bg_bright = false;
}
