#include "dino.h"

int main(void) {
    TrPixel bg[BG_WIDTH * BG_HEIGHT];
    init_background(bg);

    Dino dino;
    TrPixel dino_sprite[DINO_WIDTH * DINO_HEIGHT];
    init_dino(&dino, dino_sprite);

    Obstacle obstacles[OBS_LENGTH];
    init_obstacles(obstacles);

    TrPixel small_cactus_sprite[SMALL_CACTUS_WIDTH * SMALL_CACTUS_HEIGHT];
    init_small_cactus_sprite(small_cactus_sprite);

    TrPixel big_cactus_sprite[BIG_CACTUS_WIDTH * BIG_CACTUS_HEIGHT];
    init_big_cactus_sprite(big_cactus_sprite);

    TrPixel bird_sprite[BIRD_WIDTH * BIRD_HEIGHT];
    init_bird_sprite(bird_sprite);

    TrRenderContext ctx;
    tr_ctx_init(&ctx, BG_WIDTH, BG_HEIGHT);

    tr_cursor_visible(false);

    while (dino.is_alive) {
        tr_ctx_clear(&ctx, TR_YELLOW_16, TR_COLOR_16);

        update_dino(&dino);

        draw_background(bg);
        draw_dino(&dino, dino_sprite);

        tr_ctx_render(&ctx);

        delay(33);
    }
    return 0;
}
