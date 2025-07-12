#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>
#include <stdint.h>

/******************************************************************************
 *
 * trenderer v0.1.0
 *     NOTES:
 *         It's a header-only, single file library. Which means, declaration and definition of functions are both inside this file.
 *         They are completely separated with TRENDERER_IMPLEMENTATION. There are no inline functions for coherent structure.
 *
 *     NAMESPACES AND CONVENTIONS:
 *         Everything is under `tr` namespace. Macros and enum members are ALL_CAPS, structs and enums are PascalCase, and anything else is snake_case.
 *         `tr_priv_XXX` means it's private, those are used inside the library logic.
 *         `tr_pa_XXX`(TrPixelArray), `tr_pv_XXX`(TrPixelVector), `tr_ctx_XXX`(TrRenderContext) mean they are OOP functions.
 *
 *     DEFINES:
 *         #define TRENDERER_IMPLEMENTATION
 *             Create the implmentation of the library. MUST BE DEFINED IN ONE SOURCE FILE BEFORE INCLUDING THE HEADER.
 *
 *         #define TR_PA_LENGTH 64
 *             It's the length of `TrPixelArray`. The default value is 64 and you can define other value before you include the header.
 *
 *         #define TR_FB_LENGTH 512
 *             It's the length of `TrFrameBufferBase`. The default value is 512 and you can define other value before you include the header.
 *
 *         There are no macro functions.
 *
 *****************************************************************************/

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
void tr_reset_all(void); // Reset current effects, colors to default value.

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

// Colors - Helper functions
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
void tr_pa_init(TrPixelArray *pa, int width, int height);

typedef struct TrPixelVector { // Vector that holds `TrPixel` in SoA style.
    char *letter;
    TrEffect *effects;
    uint32_t *fg_color, *bg_color;
    TrColorsMode *fg_mode, *bg_mode;
    int width, height;
} TrPixelVector;
void tr_pv_init(TrPixelVector *pv, int width, int height);
void tr_pv_cleanup(TrPixelVector *pv);

typedef TrPixelVector TrPixelSpan; // View for TrPixel containers. Similar to std::span in C++.

// ============================================================================

// Basic renderer
// ============================================================================
void tr_draw_sprite(TrPixelSpan sprite, int x, int y);            // Draw a sprite on the screen.
void tr_draw_text(const char *text, TrStyle style, int x, int y); // Draw a string on the screen.
// ============================================================================

// Double-buffering renderer
// ============================================================================
#ifndef TR_FB_LENGTH
#define TR_FB_LENGTH 512
#endif

typedef struct TrFrameBufferBase { // Data set for a framebuffer.
    char letter[TR_FB_LENGTH];
    TrEffect effects[TR_FB_LENGTH];
    uint32_t fg_color[TR_FB_LENGTH], bg_color[TR_FB_LENGTH];
    TrColorsMode fg_mode[TR_FB_LENGTH], bg_mode[TR_FB_LENGTH];
} TrFrameBufferBase;

typedef struct TrFrameBuffer {
    TrFrameBufferBase base;
    int width, height;
} TrFrameBuffer;
void tr_fb_clear(TrFrameBuffer *fb, uint32_t bg_color, TrColorsMode bg_mode); // Clear the framebuffer.

typedef struct TrRenderContext { // Render context for double-buffering. It holds two framebuffers.
    TrFrameBufferBase front, back;
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
void tr_print_effects(TrEffect effects);                       // Print the names of effects.
void tr_print_color(uint32_t color, TrColorsMode colors_mode); // Print the name of a color.
// ----------------------------------------------------------------------------

// Type conversion
// ----------------------------------------------------------------------------
TrPixelSpan tr_atos(const TrPixelArray *pa);                             // Stand for `tr_array_to_span`. Convert `TrPixelArray` to `TrPixelSpan`.
TrPixelSpan tr_ftos(const TrFrameBufferBase *fb, int width, int height); // Stand for `tr_framebuffer_to_span`. Convert `TrFrameBuffer` to `TrPixelSpan`.
// ----------------------------------------------------------------------------

// Pixel buffer
// ----------------------------------------------------------------------------
void tr_buf_clear(TrPixelSpan buf, uint32_t bg_color, TrColorsMode bg_mode); // Clear pixel buffer
// ----------------------------------------------------------------------------
// ============================================================================

// Helper functions (private)
// ============================================================================
void tr_priv_get_visible(int *result_size, int *result_idx, int fb_size, int size, int pos);
bool tr_priv_fb_memcmp(const TrRenderContext *ctx, int from, int len);
bool tr_priv_fb_cmp(const TrRenderContext *ctx, int idx);
void tr_priv_get_dirty_rect(int *left, int *top, int *right, int *bottom, const TrRenderContext *ctx);
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
void tr_reset_all(void) {
    fputs("\x1b[0m", stdout);
}

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

// Colors - Helper functions
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
void tr_pa_init(TrPixelArray *pa, int width, int height) {
    if ((width <= 0) || (height <= 0) || (width * height > TR_PA_LENGTH)) {
        pa->width = 0;
        pa->height = 0;
        return;
    }
    pa->width = width;
    pa->height = height;

    tr_buf_clear(tr_atos(pa), TR_DEFAULT_COLOR_16, TR_COLORS_16);
}
void tr_pv_init(TrPixelVector *pv, int width, int height) {
    if (width <= 0 || height <= 0) {
        pv->width = 0;
        pv->height = 0;
        return;
    }
    pv->width = width;
    pv->height = height;

    size_t l = width * height;

    pv->letter = (char *)malloc(l * sizeof(char));
    if (pv->letter == NULL)
        return;

    pv->effects = (TrEffect *)malloc(l * sizeof(TrEffect));
    if (pv->effects == NULL)
        return;

    pv->fg_color = (uint32_t *)malloc(l * sizeof(uint32_t));
    if (pv->fg_color == NULL)
        return;

    pv->bg_color = (uint32_t *)malloc(l * sizeof(uint32_t));
    if (pv->bg_color == NULL)
        return;

    pv->fg_mode = (TrColorsMode *)malloc(l * sizeof(TrColorsMode));
    if (pv->fg_mode == NULL)
        return;

    pv->bg_mode = (TrColorsMode *)malloc(l * sizeof(TrColorsMode));
    if (pv->bg_mode == NULL)
        return;

    tr_buf_clear(*pv, TR_DEFAULT_COLOR_16, TR_COLORS_16);
}
void tr_pv_cleanup(TrPixelVector *pv) {
    if (pv->letter != NULL) {
        free(pv->letter);
        pv->letter = NULL;
    }
    if (pv->effects != NULL) {
        free(pv->effects);
        pv->effects = NULL;
    }
    if (pv->fg_color != NULL) {
        free(pv->fg_color);
        pv->fg_color = NULL;
    }
    if (pv->bg_color != NULL) {
        free(pv->bg_color);
        pv->bg_color = NULL;
    }
    if (pv->fg_mode != NULL) {
        free(pv->fg_mode);
        pv->fg_mode = NULL;
    }
    if (pv->bg_mode != NULL) {
        free(pv->bg_mode);
        pv->bg_mode = NULL;
    }
}
// ============================================================================

// Basic renderer
// ============================================================================
void tr_draw_sprite(TrPixelSpan sprite, int x, int y) {
    if (sprite.width <= 0 || sprite.height <= 0)
        return;

    TrStyle curr = {
        .effects = TR_DEFAULT_EFFECT,
        .fg_color = TR_DEFAULT_COLOR_16,
        .fg_mode = TR_COLORS_16,
        .bg_color = TR_DEFAULT_COLOR_16,
        .bg_mode = TR_COLORS_16,
    };

    int idx = 0;
    for (int r = 0; r < sprite.height; r += 1) {
        tr_move_cursor(x, y + r);

        for (int c = 0; c < sprite.width; c += 1) {
            int i = c + r * sprite.width;
            bool changed = false;

            if (curr.effects != sprite.effects[i]) {
                tr_add_effects(sprite.effects[i] & ~curr.effects);
                tr_remove_effects(curr.effects & ~sprite.effects[i]);
                curr.effects = sprite.effects[i];
                changed = true;
            }

            if (curr.fg_color != sprite.fg_color[i] || curr.fg_mode != sprite.fg_mode[i]) {
                curr.fg_color = sprite.fg_color[i];
                curr.fg_mode = sprite.fg_mode[i];
                tr_set_fg(curr.fg_color, curr.fg_mode);
                changed = true;
            }

            if (curr.bg_color != sprite.bg_color[i] || curr.bg_mode != sprite.bg_mode[i]) {
                curr.bg_color = sprite.bg_color[i];
                curr.bg_mode = sprite.bg_mode[i];
                tr_set_bg(curr.bg_color, curr.bg_mode);
                changed = true;
            }

            if (changed || (c == sprite.width - 1)) {
                fwrite(sprite.letter + idx, sizeof(char), i - idx + 1, stdout);
                idx = i + 1;
            }
        }
        curr.bg_color = TR_DEFAULT_COLOR_16;
        curr.bg_mode = TR_COLORS_16;
        tr_reset_bg();
    }
}
void tr_draw_text(const char *text, TrStyle style, int x, int y) {
    tr_move_cursor(x, y);
    tr_set_style(style);
    fputs(text, stdout);
}
// ============================================================================

// Frame buffers
// ============================================================================
void tr_ctx_init(TrRenderContext *ctx, int width, int height) {
    if ((width <= 0) || (height <= 0) || (width * height > TR_FB_LENGTH)) {
        ctx->width = 0;
        ctx->height = 0;
        return;
    }
    ctx->width = width;
    ctx->height = height;

    tr_buf_clear(tr_ftos(&ctx->front, width, height), TR_DEFAULT_COLOR_16, TR_COLORS_16);
    tr_buf_clear(tr_ftos(&ctx->back, width, height), TR_DEFAULT_COLOR_16, TR_COLORS_16);
}
void tr_ctx_clear(TrRenderContext *ctx, uint32_t bg_color, TrColorsMode bg_mode) {
    tr_buf_clear(tr_ftos(&ctx->back, ctx->width, ctx->height), bg_color, bg_mode);
}
void tr_ctx_render(TrRenderContext *ctx) {
    tr_draw_sprite(tr_ftos(&ctx->front, ctx->width, ctx->height), 0, 0);
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

    int fb_idx = (x > 0 ? x : 0) + (y > 0 ? y : 0) * ctx->width;
    int sprite_idx = sprite_x_idx + sprite_y_idx * sprite.width;

    for (int r = 0; r < visible_height; r += 1) {
        memcpy(ctx->back.letter + fb_idx, sprite.letter + sprite_idx, visible_width * sizeof(char));
        memcpy(ctx->back.effects + fb_idx, sprite.effects + sprite_idx, visible_width * sizeof(TrEffect));

        for (int c = 0; c < visible_width; c += 1) {
            int si = c + sprite_idx;

            if (sprite.fg_color[si] != TR_TRANSPARENT) {
                int fi = c + fb_idx;

                ctx->back.fg_color[fi] = sprite.fg_color[si];
                ctx->back.fg_mode[fi] = sprite.fg_color[si];
            }
            if (sprite.bg_color[si] != TR_TRANSPARENT) {
                int fi = c + fb_idx;

                ctx->back.bg_color[fi] = sprite.bg_color[si];
                ctx->back.bg_mode[fi] = sprite.bg_mode[si];
            }
        }

        fb_idx += ctx->width;
        sprite_idx += sprite.width;
    }
}
void tr_ctx_draw_text(TrRenderContext *ctx, const char *text, size_t len, TrStyle style, int x, int y) {
    if ((len <= 0) || (y < 0) || (y >= ctx->height))
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
void tr_print_color(uint32_t color, TrColorsMode colors_mode) {
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
TrPixelSpan tr_ftos(const TrFrameBufferBase *fb, int width, int height) {
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
void tr_buf_clear(TrPixelSpan buf, uint32_t bg_color, TrColorsMode bg_mode) {
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
void tr_priv_get_visible(int *result_size, int *result_idx, int fb_size, int size, int pos) {
    if (pos >= 0) {
        if (size + pos < fb_size) {
            *result_size = size;
            *result_idx = 0;
        } else {
            *result_size = fb_size - pos;
            *result_idx = 0;
        }
    } else {
        if (size + pos > 0) {
            *result_size = size + pos;
            *result_idx = -pos;
        }
    }
}
bool tr_priv_fb_memcmp(const TrRenderContext *ctx, int from, int len) {
    if (memcmp(ctx->front.letter + from, ctx->back.letter + from, len * sizeof(char)))
        return false;

    if (memcmp(ctx->front.effects + from, ctx->back.effects + from, len * sizeof(TrEffect)))
        return false;

    if (memcmp(ctx->front.fg_color + from, ctx->back.fg_color + from, len * sizeof(uint32_t)))
        return false;

    if (memcmp(ctx->front.bg_color + from, ctx->back.bg_color + from, len * sizeof(uint32_t)))
        return false;

    if (memcmp(ctx->front.fg_mode + from, ctx->back.fg_mode + from, len * sizeof(TrColorsMode)))
        return false;

    if (memcmp(ctx->front.bg_mode + from, ctx->back.bg_mode + from, len * sizeof(TrColorsMode)))
        return false;

    return true;
}
bool tr_priv_fb_cmp(const TrRenderContext *ctx, int idx) {
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
void tr_priv_get_dirty_rect(int *left, int *top, int *right, int *bottom, const TrRenderContext *ctx) {
    int fb_idx = 0;
    for (int r = 0; r < ctx->height; r += 1) {
        if (tr_priv_fb_memcmp(ctx, fb_idx, ctx->width)) {
            fb_idx += ctx->width;
            continue;
        }
        for (int c = 0; c < ctx->width; c += 1) {
            int fi = c + fb_idx;
            if (tr_priv_fb_cmp(ctx, fi))
                continue;
        }
    }
}
// ============================================================================

#endif // TRENDERER_IMPLEMENTATION
