#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>
#include <stdint.h>

/* ============================================================================
 *
 * trenderer v0.1.0
 *     NOTES:
 *         It's a header-only, single file library. Which means, declaration and definition of functions are both inside this file.
 *         They are completely separated with TRENDERER_IMPLEMENTATION. There are no inline functions for coherent structure.
 *
 *     NAMESPACES AND CONVENTIONS:
 *         Everything is under `tr` namespace. Macros and enum members are ALL_CAPS, structs and enums are PascalCase, and anything else is snake_case.
 *         `tr_priv_XXX` means it's private, those are used inside the library logic.
 *         `tr_parr_XXX`(TrPixelArray), `tr_pvec_XXX`(TrPixelVector), `tr_ctx_XXX`(TrRenderContext) mean they are OOP functions.
 *
 *     DEFINES:
 *         #define TRENDERER_IMPLEMENTATION
 *             Create the implmentation of the library. MUST BE DEFINED IN ONE SOURCE FILE BEFORE INCLUDING THE HEADER.
 *
 *         #define TR_PA_LENGTH 64
 *             It's the length of `TrPixelArray`. The default value is 64 and you can define other value before you include the header.
 *
 *         #define TR_FRAMEBUFFER_LENGTH 512
 *             It's the length of `TrFrameBufferBase`. The default value is 512 and you can define other value before you include the header.
 *
 *         There are no macro functions.
 *
 * ==========================================================================*/

// Screen
// ============================================================================
void tr_clear(void); // Clear the screen.
// ============================================================================

// Cursor
// ============================================================================
void tr_move_cursor(int x, int y);    // Move cursor to given position.
void tr_cursor_visible(bool visible); // Toggle visibility of cursor.
// ============================================================================

// Effects
// ============================================================================
typedef enum TrEffect {
    TR_DEFAULT_EFFECT = 0,
    TR_BOLD = 1 << 0,
    TR_DIM = 1 << 1,
    TR_ITALIC = 1 << 2,
    TR_UNDERLINE = 1 << 3,
    TR_BLINK = 1 << 4,
    TR_INVERT = 1 << 5,
    TR_INVISIBLE = 1 << 6,
    TR_STRIKETHROUGH = 1 << 7,
} TrEffect;
void tr_add_effects(TrEffect effects);    // Add effects to current buffer.
void tr_remove_effects(TrEffect effects); // Remove effects from current buffer.
void tr_reset_effects(void);              // Reset current effects to default value.
void tr_reset_all(void);                  // Reset current effects, colors to default value.
// ============================================================================

// Colors
// ============================================================================
typedef enum TrColorsMode {
    TR_COLORS_16,
    TR_COLORS_256,
    TR_COLORS_TRUE,
} TrColorsMode;
void tr_set_fg(uint32_t fg_color, TrColorsMode fg_mode); // Set foreground color of current buffer.
void tr_set_bg(uint32_t bg_color, TrColorsMode bg_mode); // Set background color of current buffer.
void tr_reset_fg(void);                                  // Reset foreground color to default value.
void tr_reset_bg(void);                                  // Reset background color to default value.

// Colors - Utility functions
// ----------------------------------------------------------------------------
uint32_t tr_gray_256(uint8_t scale);              // Create a gray scale value in ANSI 256 colors.
uint32_t tr_rgb(uint8_t r, uint8_t g, uint8_t b); // Create a rgb value.
uint8_t tr_rgb_r(uint32_t rgb);                   // Get `r` of a rgb value.
uint8_t tr_rgb_g(uint32_t rgb);                   // Get 'g' of a rgb value.
uint8_t tr_rgb_b(uint32_t rgb);                   // Get `b` of a rgb value.
// ----------------------------------------------------------------------------

// Colors - Constants - ANSI 16 colors
// ----------------------------------------------------------------------------
#define TR_BLACK_16 30
#define TR_RED_16 31
#define TR_GREEN_16 32
#define TR_YELLOW_16 33
#define TR_BLUE_16 34
#define TR_MAGENTA_16 35
#define TR_CYAN_16 36
#define TR_WHITE_16 37

#define TR_BRIGHT_BLACK_16 90
#define TR_BRIGHT_RED_16 91
#define TR_BRIGHT_GREEN_16 92
#define TR_BRIGHT_YELLOW_16 93
#define TR_BRIGHT_BLUE_16 94
#define TR_BRIGHT_MAGENTA_16 95
#define TR_BRIGHT_CYAN_16 96
#define TR_BRIGHT_WHITE_16 97

#define TR_DEFAULT_COLOR_16 39
// ----------------------------------------------------------------------------

// Colors - Constants - ANSI 256 colors
// ----------------------------------------------------------------------------
#define TR_BLACK_256 0
#define TR_RED_256 1
#define TR_GREEN_256 2
#define TR_YELLOW_256 3
#define TR_BLUE_256 4
#define TR_MAGENTA_256 5
#define TR_CYAN_256 6
#define TR_WHITE_256 7

#define TR_BRIGHT_BLACK_256 8
#define TR_BRIGHT_RED_256 9
#define TR_BRIGHT_GREEN_256 10
#define TR_BRIGHT_YELLOW_256 11
#define TR_BRIGHT_BLUE_256 12
#define TR_BRIGHT_MAGENTA_256 13
#define TR_BRIGHT_CYAN_256 14
#define TR_BRIGHT_WHITE_256 15
// ----------------------------------------------------------------------------

// Colors - Constants - True colors
// ----------------------------------------------------------------------------
#define TR_BLACK tr_rgb(0, 0, 0)
#define TR_RED tr_rgb(255, 0, 0)
#define TR_GREEN tr_rgb(0, 255, 0)
#define TR_YELLOW tr_rgb(255, 255, 0)
#define TR_BLUE tr_rgb(0, 0, 255)
#define TR_MAGENTA tr_rgb(255, 0, 255)
#define TR_CYAN tr_rgb(0, 255, 255)
#define TR_WHITE tr_rgb(255, 255, 255)

#define TR_GRAY tr_rgb(128, 128, 128)
#define TR_ORANGE tr_rgb(255, 165, 0)
#define TR_PINK tr_rgb(255, 105, 180)
#define TR_SKYBLUE tr_rgb(135, 206, 235)
// ----------------------------------------------------------------------------

#define TR_TRANSPARENT 0xFFFFFFFF // This is not a drawable value. It's meant to be used in software rendering.
// ============================================================================

// Styles
// ============================================================================
typedef struct TrStyle {
    TrEffect effects;
    uint32_t fg_color, bg_color;
    TrColorsMode fg_mode, bg_mode;
} TrStyle;
TrStyle tr_default_style(void);                 // Return a default style.
void tr_set_style(TrStyle style);               // Set style of current buffer.
void tr_copy_style(TrStyle *dest, TrStyle src); // Copy value of `src` into `dest`.
// ============================================================================

// Pixel
// ============================================================================
typedef struct TrPixel {
    char letter;
    TrEffect effects;
    uint32_t fg_color, bg_color;
    TrColorsMode fg_mode, bg_mode;
} TrPixel;

#ifndef TR_PA_LENGTH
#define TR_PA_LENGTH 64
#endif

typedef struct TrPixelArray { // Array that holds `TrPixel` in amount of `TR_PA_LENGTH` in SoA style.
    char letter[TR_PA_LENGTH];
    TrEffect effects[TR_PA_LENGTH];
    uint32_t fg_color[TR_PA_LENGTH], bg_color[TR_PA_LENGTH];
    TrColorsMode fg_mode[TR_PA_LENGTH], bg_mode[TR_PA_LENGTH];
    int width, height;
} TrPixelArray;
void tr_parr_init(TrPixelArray *parr, int width, int height);

typedef struct TrPixelVector { // Vector that holds `TrPixel` in SoA style.
    char *letter;
    TrEffect *effects;
    uint32_t *fg_color, *bg_color;
    TrColorsMode *fg_mode, *bg_mode;
    int width, height;
} TrPixelVector;
void tr_pvec_init(TrPixelVector *pvec, int width, int height);
void tr_pvec_cleanup(TrPixelVector *pvec);

typedef TrPixelVector TrPixelSpan; // View for TrPixel containers. Similar to std::span in C++.
// ============================================================================

// Basic renderer
// ============================================================================
void tr_draw_sprite(TrPixelSpan sprite, int x, int y);                                          // Draw a sprite on the screen.
void tr_draw_spritesheet(TrPixelSpan ss, int sp_x, int sp_y, int sp_w, int sp_h, int x, int y); // Draw a sprite in a spritesheet on the screen.
void tr_draw_text(const char *text, TrStyle style, int x, int y);                               // Draw a string on the screen.
// ============================================================================

// Double-buffering renderer
// ============================================================================
#ifndef TR_FRAMEBUFFER_LENGTH
#define TR_FRAMEBUFFER_LENGTH 512
#endif

typedef struct TrFramebufferBase { // Data set for a framebuffer.
    char letter[TR_FRAMEBUFFER_LENGTH];
    TrEffect effects[TR_FRAMEBUFFER_LENGTH];
    uint32_t fg_color[TR_FRAMEBUFFER_LENGTH], bg_color[TR_FRAMEBUFFER_LENGTH];
    TrColorsMode fg_mode[TR_FRAMEBUFFER_LENGTH], bg_mode[TR_FRAMEBUFFER_LENGTH];
} TrFramebufferBase;

typedef struct TrFramebuffer {
    TrFramebufferBase base;
    int width, height;
} TrFramebuffer;
void tr_fb_clear(TrFramebuffer *fb, uint32_t bg_color, TrColorsMode bg_mode); // Clear the framebuffer.

typedef struct TrRenderContext { // Render context for double-buffering. It holds two framebuffers.
    TrFramebufferBase front, back;
    int width, height;
} TrRenderContext;
void tr_ctx_init(TrRenderContext *ctx, int width, int height);                                          // Initialize the context.
void tr_ctx_clear(TrRenderContext *ctx, uint32_t bg_color, TrColorsMode bg_mode);                       // Clear `back`.
void tr_ctx_render(TrRenderContext *ctx);                                                               // Render the result using dirty rectangles.
void tr_ctx_draw_sprite(TrRenderContext *ctx, TrPixelSpan sprite, int x, int y);                        // Draw a sprite on `back`.
void tr_ctx_draw_text(TrRenderContext *ctx, const char *text, size_t len, TrStyle style, int x, int y); // Draw a string on `back`.
// ============================================================================

// Utility functions
// ============================================================================
// Debug
// ----------------------------------------------------------------------------
void tr_print_effects(TrEffect effects); // Print the names of effects.
// ----------------------------------------------------------------------------

// Type conversion
// ----------------------------------------------------------------------------
TrPixelSpan tr_atos(const TrPixelArray *pa);                             // Stand for `tr_array_to_span`. Convert `TrPixelArray` to `TrPixelSpan`.
TrPixelSpan tr_ftos(const TrFramebufferBase *fb, int width, int height); // Stand for `tr_framebuffer_to_span`. Convert `TrFrameBuffer` to `TrPixelSpan`.
// ----------------------------------------------------------------------------

// Pixel buffer
// ----------------------------------------------------------------------------
void tr_clear_buf(TrPixelSpan buf, uint32_t bg_color, TrColorsMode bg_mode); // Clear pixel buffer
// ----------------------------------------------------------------------------
// ============================================================================

// Helper functions (private)
// ============================================================================
void tr_priv_set_ansi(TrPixelSpan sprite, TrStyle *curr, bool *changed, int i);
void tr_priv_get_visible(int *result_size, int *result_idx, int fb_size, int size, int pos);
bool tr_priv_ctx_memcmp(const TrRenderContext *ctx, int idx, int len);
bool tr_priv_ctx_cmp(const TrRenderContext *ctx, int idx);
void tr_priv_ctx_swap(TrRenderContext *ctx);
void tr_priv_get_dirty_rect(int *x, int *y, int *width, int *height, const TrRenderContext *ctx);
// ============================================================================

#endif // TRENDERER_H

#define TRENDERER_IMPLEMENTATION // MUST BE REMOVED BEFORE RELEASE!!!!!!!!!!!

#ifdef TRENDERER_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Screen & Window control
// ============================================================================
void tr_clear(void) {
    fputs("\x1b[2J\x1b[H", stdout);
}
// ============================================================================

// Cursor control
// ============================================================================
void tr_move_cursor(int x, int y) {
    if (x < 0 || y < 0)
        return;
    printf("\x1b[%d;%dH", y + 1, x + 1);
}
void tr_cursor_visible(bool visible) {
    fputs(visible ? "\x1b[?25h" : "\x1b[?25l", stdout);
}
// ============================================================================

// Effects
// ============================================================================
void tr_add_effects(TrEffect effects) {
    if (effects & TR_BOLD)
        fputs("\x1b[1m", stdout);

    if (effects & TR_DIM)
        fputs("\x1b[2m", stdout);

    if (effects & TR_ITALIC)
        fputs("\x1b[3m", stdout);

    if (effects & TR_UNDERLINE)
        fputs("\x1b[4m", stdout);

    if (effects & TR_BLINK)
        fputs("\x1b[5m", stdout);

    if (effects & TR_INVERT)
        fputs("\x1b[7m", stdout);

    if (effects & TR_INVISIBLE)
        fputs("\x1b[8m", stdout);

    if (effects & TR_STRIKETHROUGH)
        fputs("\x1b[9m", stdout);
}
void tr_remove_effects(TrEffect effects) {
    if (effects & TR_BOLD || effects & TR_DIM)
        fputs("\x1b[22m", stdout);

    if (effects & TR_ITALIC)
        fputs("\x1b[23m", stdout);

    if (effects & TR_UNDERLINE)
        fputs("\x1b[24m", stdout);

    if (effects & TR_BLINK)
        fputs("\x1b[25m", stdout);

    if (effects & TR_INVERT)
        fputs("\x1b[27m", stdout);

    if (effects & TR_INVISIBLE)
        fputs("\x1b[28m", stdout);

    if (effects & TR_STRIKETHROUGH)
        fputs("\x1b[29m", stdout);
}
void tr_reset_effects(void) {
    fputs("\x1b[22;23;24;25;27;28;29m", stdout);
}
void tr_reset_all(void) {
    fputs("\x1b[0m", stdout);
}
// ============================================================================

// Colors
// ============================================================================
void tr_set_fg(uint32_t fg_color, TrColorsMode fg_mode) {
    if (fg_color == TR_TRANSPARENT)
        return;
    switch (fg_mode) {
    case TR_COLORS_16:
        printf("\x1b[%dm", fg_color);
        break;
    case TR_COLORS_256:
        printf("\x1b[38;5;%dm", fg_color);
        break;
    case TR_COLORS_TRUE:
        printf("\x1b[38;2;%d;%d;%dm", tr_rgb_r(fg_color), tr_rgb_g(fg_color), tr_rgb_b(fg_color));
        break;
    }
}
void tr_set_bg(uint32_t bg_color, TrColorsMode bg_mode) {
    if (bg_color == TR_TRANSPARENT)
        return;
    switch (bg_mode) {
    case TR_COLORS_16:
        printf("\x1b[%dm", 10 + bg_color);
        break;
    case TR_COLORS_256:
        printf("\x1b[48;5;%dm", bg_color);
        break;
    case TR_COLORS_TRUE:
        printf("\x1b[48;2;%d;%d;%dm", tr_rgb_r(bg_color), tr_rgb_g(bg_color), tr_rgb_b(bg_color));
        break;
    }
}
void tr_reset_fg(void) {
    fputs("\x1b[39m", stdout);
}
void tr_reset_bg(void) {
    fputs("\x1b[49m", stdout);
}

// Colors - Utility functions
// ----------------------------------------------------------------------------
uint32_t tr_gray_256(uint8_t scale) {
    return (scale > 23) ? 232 : (232 + scale);
}
uint32_t tr_rgb(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}
uint8_t tr_rgb_r(uint32_t rgb) {
    return (rgb >> 16) & 0xFF;
}
uint8_t tr_rgb_g(uint32_t rgb) {
    return (rgb >> 8) & 0xFF;
}
uint8_t tr_rgb_b(uint32_t rgb) {
    return rgb & 0xFF;
}
// ----------------------------------------------------------------------------
// ============================================================================

// Styles
// ============================================================================
TrStyle tr_default_style(void) {
    return (TrStyle){
        .effects = TR_DEFAULT_EFFECT,
        .fg_color = TR_DEFAULT_COLOR_16,
        .bg_color = TR_DEFAULT_COLOR_16,
        .fg_mode = TR_COLORS_16,
        .bg_mode = TR_COLORS_16};
}
void tr_set_style(TrStyle style) {
    tr_add_effects(style.effects);
    tr_set_fg(style.fg_color, style.fg_mode);
    tr_set_bg(style.bg_color, style.bg_mode);
}
void tr_copy_style(TrStyle *dest, TrStyle src) {
    dest->effects = src.effects;
    dest->fg_color = src.fg_color;
    dest->fg_mode = src.fg_mode;
    dest->bg_color = src.bg_color;
    dest->bg_mode = src.bg_mode;
}
// ============================================================================

// Pixels
// ============================================================================
void tr_parr_init(TrPixelArray *parr, int width, int height) {
    if (width <= 0 || height <= 0 || width * height > TR_PA_LENGTH) {
        parr->width = 0;
        parr->height = 0;
        return;
    }
    parr->width = width;
    parr->height = height;

    tr_clear_buf(tr_atos(parr), TR_DEFAULT_COLOR_16, TR_COLORS_16);
}
void tr_pvec_init(TrPixelVector *pvec, int width, int height) {
    if (width <= 0 || height <= 0) {
        pvec->width = 0;
        pvec->height = 0;
        return;
    }
    pvec->width = width;
    pvec->height = height;

    size_t l = width * height;

    pvec->letter = (char *)malloc(l * sizeof(char));
    if (pvec->letter == NULL)
        return;

    pvec->effects = (TrEffect *)malloc(l * sizeof(TrEffect));
    if (pvec->effects == NULL)
        return;

    pvec->fg_color = (uint32_t *)malloc(l * sizeof(uint32_t));
    if (pvec->fg_color == NULL)
        return;

    pvec->bg_color = (uint32_t *)malloc(l * sizeof(uint32_t));
    if (pvec->bg_color == NULL)
        return;

    pvec->fg_mode = (TrColorsMode *)malloc(l * sizeof(TrColorsMode));
    if (pvec->fg_mode == NULL)
        return;

    pvec->bg_mode = (TrColorsMode *)malloc(l * sizeof(TrColorsMode));
    if (pvec->bg_mode == NULL)
        return;

    tr_clear_buf(*pvec, TR_DEFAULT_COLOR_16, TR_COLORS_16);
}
void tr_pvec_cleanup(TrPixelVector *pvec) {
    if (pvec->letter != NULL) {
        free(pvec->letter);
        pvec->letter = NULL;
    }
    if (pvec->effects != NULL) {
        free(pvec->effects);
        pvec->effects = NULL;
    }
    if (pvec->fg_color != NULL) {
        free(pvec->fg_color);
        pvec->fg_color = NULL;
    }
    if (pvec->bg_color != NULL) {
        free(pvec->bg_color);
        pvec->bg_color = NULL;
    }
    if (pvec->fg_mode != NULL) {
        free(pvec->fg_mode);
        pvec->fg_mode = NULL;
    }
    if (pvec->bg_mode != NULL) {
        free(pvec->bg_mode);
        pvec->bg_mode = NULL;
    }
}
// ============================================================================

// Basic renderer
// ============================================================================
void tr_draw_sprite(TrPixelSpan sprite, int x, int y) {
    if (sprite.width <= 0 || sprite.height <= 0 || x < 0 || y < 0)
        return;

    TrStyle curr = {
        .effects = TR_DEFAULT_EFFECT,
        .fg_color = TR_DEFAULT_COLOR_16,
        .fg_mode = TR_COLORS_16,
        .bg_color = TR_DEFAULT_COLOR_16,
        .bg_mode = TR_COLORS_16,
    };

    int sp_row = 0;
    for (int row = 0; row < sprite.height; row += 1) {
        tr_move_cursor(x, y + row);

        for (int col = 0; col < sprite.width; col += 1) {
            int i = col + row * sprite.width;
            bool changed = false;

            tr_priv_set_ansi(sprite, &curr, &changed, i);

            if (changed || (col == sprite.width - 1)) {
                fwrite(sprite.letter + sp_row, sizeof(char), i - sp_row + 1, stdout);
                sp_row = i + 1;
            }
        }
        curr.bg_color = TR_DEFAULT_COLOR_16;
        curr.bg_mode = TR_COLORS_16;
        tr_reset_bg();
    }
    tr_reset_all();
}
void tr_draw_spritesheet(TrPixelSpan ss, int sp_x, int sp_y, int sp_w, int sp_h, int x, int y) {
    // spritesheet and position validation
    if (ss.width <= 0 || ss.height <= 0 || x < 0 || y < 0)
        return;
    // sprite validation
    if (sp_w <= 0 || sp_h <= 0 ||
        sp_x < 0 || sp_x >= ss.width ||
        sp_y < 0 || sp_y >= ss.height ||
        (sp_x + sp_w > ss.width) ||
        (sp_y + sp_h > ss.height))
        return;

    TrStyle curr = {
        .effects = TR_DEFAULT_EFFECT,
        .fg_color = TR_DEFAULT_COLOR_16,
        .fg_mode = TR_COLORS_16,
        .bg_color = TR_DEFAULT_COLOR_16,
        .bg_mode = TR_COLORS_16,
    };

    for (int row = 0; row < sp_h; row += 1) {
        tr_move_cursor(x, y + row);

        int sp_row = sp_x + (sp_y + row) * ss.width;
        for (int col = 0; col < sp_w; col += 1) {
            int sp_idx = col + sp_row;
            bool changed = false;

            tr_priv_set_ansi(ss, &curr, &changed, sp_idx);

            if (changed || (col == sp_w - 1)) {
                fwrite(ss.letter + sp_row, sizeof(char), sp_idx - sp_row + 1, stdout);

                if (changed)
                    sp_row = sp_idx + 1;
            }
        }
        curr.bg_color = TR_DEFAULT_COLOR_16;
        curr.bg_mode = TR_COLORS_16;
        tr_reset_bg();
    }
    tr_reset_all();
}
void tr_draw_text(const char *text, TrStyle style, int x, int y) {
    if (y < 0)
        return;
    tr_move_cursor(x, y);
    tr_set_style(style);
    fputs(text, stdout);
}
// ============================================================================

// Frame buffers
// ============================================================================
void tr_ctx_init(TrRenderContext *ctx, int width, int height) {
    if (width <= 0 || height <= 0 || (width * height > TR_FRAMEBUFFER_LENGTH)) {
        ctx->width = 0;
        ctx->height = 0;
        return;
    }
    ctx->width = width;
    ctx->height = height;

    tr_clear_buf(tr_ftos(&ctx->front, width, height), TR_DEFAULT_COLOR_16, TR_COLORS_16);
    tr_clear_buf(tr_ftos(&ctx->back, width, height), TR_DEFAULT_COLOR_16, TR_COLORS_16);
}
void tr_ctx_clear(TrRenderContext *ctx, uint32_t bg_color, TrColorsMode bg_mode) {
    tr_clear_buf(tr_ftos(&ctx->back, ctx->width, ctx->height), bg_color, bg_mode);
}
void tr_ctx_render(TrRenderContext *ctx) {
    int dirty_rect_x = 0, dirty_rect_y = 0;
    int dirty_rect_w = 0, dirty_rect_h = 0;
    tr_priv_get_dirty_rect(&dirty_rect_x, &dirty_rect_y, &dirty_rect_w, &dirty_rect_h, ctx);
    if (dirty_rect_w <= 0 || dirty_rect_h <= 0)
        return;

    // Draw only dirty rectangle.
    tr_draw_spritesheet(tr_ftos(&ctx->back, ctx->width, ctx->height), dirty_rect_x, dirty_rect_y, dirty_rect_w, dirty_rect_h, dirty_rect_x, dirty_rect_y);

    // Update `front` with `back`.
    tr_priv_ctx_swap(ctx);
}
void tr_ctx_draw_sprite(TrRenderContext *ctx, TrPixelSpan sprite, int x, int y) {
    if (sprite.width <= 0 || sprite.height <= 0)
        return;

    int visible_width = 0;
    int sprite_x_idx = 0;
    tr_priv_get_visible(&visible_width, &sprite_x_idx, ctx->width, sprite.width, x);
    if (visible_width <= 0)
        return;

    int visible_height = 0;
    int sprite_y_idx = 0;
    tr_priv_get_visible(&visible_height, &sprite_y_idx, ctx->height, sprite.height, y);
    if (visible_height <= 0)
        return;

    int fb_base = (x > 0 ? x : 0) + (y > 0 ? y : 0) * ctx->width;
    int sp_base = sprite_x_idx + sprite_y_idx * sprite.width;

    for (int row = 0; row < visible_height; row += 1) {
        int fb_row = fb_base + row * ctx->width;
        int sp_row = sp_base + row * sprite.width;

        memcpy(ctx->back.letter + fb_row, sprite.letter + sp_row, visible_width * sizeof(char));
        memcpy(ctx->back.effects + fb_row, sprite.effects + sp_row, visible_width * sizeof(TrEffect));

        for (int col = 0; col < visible_width; col += 1) {
            int sp_idx = col + sp_row;

            if (sprite.fg_color[sp_idx] != TR_TRANSPARENT) {
                int fb_idx = col + fb_row;

                ctx->back.fg_color[fb_idx] = sprite.fg_color[sp_idx];
                ctx->back.fg_mode[fb_idx] = sprite.fg_color[sp_idx];
            }
            if (sprite.bg_color[sp_idx] != TR_TRANSPARENT) {
                int fb_idx = col + fb_row;

                ctx->back.bg_color[fb_idx] = sprite.bg_color[sp_idx];
                ctx->back.bg_mode[fb_idx] = sprite.bg_mode[sp_idx];
            }
        }
    }
}
void tr_ctx_draw_text(TrRenderContext *ctx, const char *text, size_t len, TrStyle style, int x, int y) {
    if (len <= 0 || y < 0 || y >= ctx->height)
        return;
    int visible_len = 0;
    int text_idx = 0;
    tr_priv_get_visible(&visible_len, &text_idx, ctx->width, len, x);
    if (visible_len <= 0)
        return;

    int fb_idx = (x > 0 ? x : 0) + (y > 0 ? y : 0) * ctx->width;
    memcpy(ctx->back.letter + fb_idx, text + text_idx, visible_len * sizeof(char));

    for (int i = 0; i < visible_len; i += 1) {
        int fi = i + fb_idx;

        ctx->back.effects[fi] = style.effects;
        ctx->back.fg_color[fi] = style.fg_color;
        ctx->back.bg_color[fi] = style.bg_color;
        ctx->back.fg_mode[fi] = style.fg_mode;
        ctx->back.bg_mode[fi] = style.bg_mode;
    }
}
// ============================================================================

// Utility functions
// ============================================================================
// Debug
// ----------------------------------------------------------------------------
void tr_print_effects(TrEffect effects) {
    if (effects == TR_DEFAULT_EFFECT) {
        fputs("DEFAULT_EFFECT", stdout);
        return;
    }
    if (effects & TR_BOLD)
        fputs("BOLD ", stdout);

    if (effects & TR_DIM)
        fputs("DIM ", stdout);

    if (effects & TR_ITALIC)
        fputs("ITALIC ", stdout);

    if (effects & TR_UNDERLINE)
        fputs("UNDERLINE ", stdout);

    if (effects & TR_BLINK)
        fputs("BLINK ", stdout);

    if (effects & TR_INVERT)
        fputs("INVERT ", stdout);

    if (effects & TR_INVISIBLE)
        fputs("HIDDEN ", stdout);

    if (effects & TR_STRIKETHROUGH)
        fputs("STRIKETHROUGH ", stdout);
}
// ----------------------------------------------------------------------------

// Type conversion
// ----------------------------------------------------------------------------
TrPixelSpan tr_atos(const TrPixelArray *pa) {
    return (TrPixelSpan){
        .letter = (char *)pa->letter,
        .effects = (TrEffect *)pa->effects,
        .fg_color = (uint32_t *)pa->fg_color,
        .bg_color = (uint32_t *)pa->bg_color,
        .fg_mode = (TrColorsMode *)pa->fg_mode,
        .bg_mode = (TrColorsMode *)pa->bg_mode,
        .width = pa->width,
        .height = pa->height};
}
TrPixelSpan tr_ftos(const TrFramebufferBase *fb, int width, int height) {
    return (TrPixelSpan){
        .letter = (char *)fb->letter,
        .effects = (TrEffect *)fb->effects,
        .fg_color = (uint32_t *)fb->fg_color,
        .bg_color = (uint32_t *)fb->bg_color,
        .fg_mode = (TrColorsMode *)fb->fg_mode,
        .bg_mode = (TrColorsMode *)fb->bg_mode,
        .width = width,
        .height = height};
}
// ----------------------------------------------------------------------------

// Pixel buffer
// ----------------------------------------------------------------------------
void tr_clear_buf(TrPixelSpan buf, uint32_t bg_color, TrColorsMode bg_mode) {
    size_t l = buf.width * buf.height;

    memset(buf.letter, ' ', l * sizeof(char));
    memset(buf.effects, TR_DEFAULT_EFFECT, l * sizeof(TrEffect));
    memset(buf.fg_mode, TR_COLORS_16, l * sizeof(TrColorsMode));

    for (int i = 0; i < l; i += 1) {
        buf.fg_color[i] = TR_DEFAULT_COLOR_16;
        buf.bg_color[i] = bg_color;
        buf.bg_mode[i] = bg_mode;
    }
}
// ============================================================================

// Helper functions (private)
// ============================================================================
void tr_priv_set_ansi(TrPixelSpan sprite, TrStyle *curr, bool *changed, int i) {
    if (curr->effects != sprite.effects[i]) {
        tr_add_effects(sprite.effects[i] & ~curr->effects);
        tr_remove_effects(curr->effects & ~sprite.effects[i]);
        curr->effects = sprite.effects[i];
        *changed = true;
    }

    if (curr->fg_color != sprite.fg_color[i] || curr->fg_mode != sprite.fg_mode[i]) {
        curr->fg_color = sprite.fg_color[i];
        curr->fg_mode = sprite.fg_mode[i];
        tr_set_fg(curr->fg_color, curr->fg_mode);
        *changed = true;
    }

    if (curr->bg_color != sprite.bg_color[i] || curr->bg_mode != sprite.bg_mode[i]) {
        curr->bg_color = sprite.bg_color[i];
        curr->bg_mode = sprite.bg_mode[i];
        tr_set_bg(curr->bg_color, curr->bg_mode);
        *changed = true;
    }
}
void tr_priv_get_visible(int *result_size, int *result_idx, int fb_size, int size, int pos) {
    if (pos >= 0) {
        if (pos + size < fb_size) {
            *result_size = size;
            *result_idx = 0;
        } else {
            *result_size = fb_size - pos;
            *result_idx = 0;
        }
    } else {
        if (pos + size > 0) {
            *result_size = size + pos;
            *result_idx = -pos;
        }
    }
}
bool tr_priv_ctx_memcmp(const TrRenderContext *ctx, int idx, int len) {
    if (memcmp(ctx->front.letter + idx, ctx->back.letter + idx, len * sizeof(char)))
        return false;

    if (memcmp(ctx->front.effects + idx, ctx->back.effects + idx, len * sizeof(TrEffect)))
        return false;

    if (memcmp(ctx->front.fg_color + idx, ctx->back.fg_color + idx, len * sizeof(uint32_t)))
        return false;

    if (memcmp(ctx->front.bg_color + idx, ctx->back.bg_color + idx, len * sizeof(uint32_t)))
        return false;

    if (memcmp(ctx->front.fg_mode + idx, ctx->back.fg_mode + idx, len * sizeof(TrColorsMode)))
        return false;

    if (memcmp(ctx->front.bg_mode + idx, ctx->back.bg_mode + idx, len * sizeof(TrColorsMode)))
        return false;

    return true;
}
bool tr_priv_ctx_cmp(const TrRenderContext *ctx, int idx) {
    if (ctx->front.letter[idx] != ctx->back.letter[idx])
        return false;

    if (ctx->front.effects[idx] != ctx->back.effects[idx])
        return false;

    if (ctx->front.fg_color[idx] != ctx->back.fg_color[idx])
        return false;

    if (ctx->front.bg_color[idx] != ctx->back.bg_color[idx])
        return false;

    if (ctx->front.fg_mode[idx] != ctx->back.fg_mode[idx])
        return false;

    if (ctx->front.bg_mode[idx] != ctx->back.bg_mode[idx])
        return false;

    return true;
}
void tr_priv_ctx_swap(TrRenderContext *ctx) {
    size_t l = ctx->width * ctx->height;

    memcpy(ctx->front.letter, ctx->back.letter, l * sizeof(char));
    memcpy(ctx->front.effects, ctx->back.effects, l * sizeof(TrEffect));
    memcpy(ctx->front.fg_color, ctx->back.fg_color, l * sizeof(uint32_t));
    memcpy(ctx->front.bg_color, ctx->back.bg_color, l * sizeof(uint32_t));
    memcpy(ctx->front.fg_mode, ctx->back.fg_mode, l * sizeof(TrColorsMode));
    memcpy(ctx->front.bg_mode, ctx->back.bg_mode, l * sizeof(TrColorsMode));
}
void tr_priv_get_dirty_rect(int *x, int *y, int *width, int *height, const TrRenderContext *ctx) {
    int left = ctx->width - 1;
    int top = ctx->height - 1;
    int right = 0;
    int bottom = 0;

    int fb_ibxy = 0;
    for (int row = 0; row < ctx->height; row += 1) {
        if (tr_priv_ctx_memcmp(ctx, fb_ibxy, ctx->width)) {
            fb_ibxy += ctx->width;
            continue;
        }

        for (int col = 0; col < ctx->width; col += 1) {
            int fb_idx = col + fb_ibxy;
            if (tr_priv_ctx_cmp(ctx, fb_idx))
                continue;

            if (left > col)
                left = col;
            if (top > row)
                top = row;
            if (right < col)
                right = col;
            if (bottom < row)
                bottom = row;
        }
    }
    if (left > right || top > bottom) {
        *x = 0;
        *y = 0;
        *width = 0;
        *height = 0;
        return;
    }
    *x = left;
    *y = top;
    *width = right - left + 1;
    *height = bottom - top + 1;
}
// ============================================================================

#endif // TRENDERER_IMPLEMENTATION
