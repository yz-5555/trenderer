#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>
#include <stdint.h>

// Screen
// ============================================================================
void tr_clear(void);
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
    TR_HIDDEN = 1 << 6,
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

// Colors - ANSI 16 colors
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

// Colors - ANSI 256 colors
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

// Colors - True colors
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
// ============================================================================

// Styles
// ============================================================================
typedef struct TrStyle {
    TrEffect effects;
    uint32_t fg_color;
    TrColorsMode fg_mode;
    uint32_t bg_color;
    TrColorsMode bg_mode;
} TrStyle;
void tr_set_style(const TrStyle *style);               // Set style of current buffer.
void tr_init_style(TrStyle *style);                    // Assign default values to `style`.
void tr_copy_style(TrStyle *dest, const TrStyle *src); // Copy value of `src` into `dest`.
// ============================================================================

// Pixels
// ============================================================================
typedef struct TrPixel {
    char ch;
    TrStyle style;
} TrPixel;
// ============================================================================

// Basic renderer
// ============================================================================
void tr_draw_sprite(const TrPixel *sprite, int width, int height, int x, int y); // Draw a sprite on the screen.
void tr_draw_text(const char *text, const TrStyle *style, int x, int y);         // Draw a string on the screen.
// ============================================================================

// Frame buffers
// ============================================================================
#ifndef TR_FB_LENGTH
#define TR_FB_LENGTH 512
#endif

typedef struct TrFrameBuffers {
    TrPixel front[TR_FB_LENGTH];
    TrPixel back[TR_FB_LENGTH];
    int width, height;
} TrFrameBuffers;
void tr_fb_init(TrFrameBuffers *fb, int width, int height);                                             // Initialize the framebuffers.
void tr_fb_render(TrFrameBuffers *fb);                                                                  // Render the framebuffers.
void tr_fb_draw_sprite(TrFrameBuffers *fb, const TrPixel *sprite, int width, int height, int x, int y); // Draw a sprite on the framebuffers.
void tr_fb_draw_text(TrFrameBuffers *fb, const char *text, const TrStyle *style, int x, int y);         // Draw a string on the framebuffers.
// ============================================================================

// Helper functions
// ============================================================================
void tr_print_effects(TrEffect effects);                       // Print the names of effects.
void tr_print_color(uint32_t color, TrColorsMode colors_mode); // Print the name of a color.
// ============================================================================

// Helper functions (private)
// ============================================================================
void tr_priv_get_visible(int fb_size, int size, int pos, size_t *result_size, int *result_idx);
// ============================================================================

#endif // TRENDERER_H

#define TRENDERER_IMPLEMENTATION // MUST BE REMOVED BEFORE RELEASE!!!!!!!!!!!

#ifdef TRENDERER_IMPLEMENTATION

#include <stdio.h>
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

    if (effects & TR_HIDDEN)
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

    if (effects & TR_HIDDEN)
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
void tr_set_style(const TrStyle *style) {
    tr_add_effects(style->effects);
    tr_set_fg(style->fg_color, style->fg_mode);
    tr_set_bg(style->bg_color, style->bg_mode);
}
void tr_init_style(TrStyle *style) {
    style->effects = TR_DEFAULT_EFFECT;
    style->fg_color = TR_DEFAULT_COLOR_16;
    style->fg_mode = TR_COLORS_16;
    style->bg_color = TR_DEFAULT_COLOR_16;
    style->bg_mode = TR_COLORS_16;
}
void tr_copy_style(TrStyle *dest, const TrStyle *src) {
    dest->effects = src->effects;
    dest->fg_color = src->fg_color;
    dest->fg_mode = src->fg_mode;
    dest->bg_color = src->bg_color;
    dest->bg_mode = src->bg_mode;
}
// ============================================================================

// Basic renderer
// ============================================================================
void tr_draw_sprite(const TrPixel *sprite, int width, int height, int x, int y) {
    if (width <= 0 || height <= 0)
        return;

    TrStyle style = {
        .effects = TR_DEFAULT_EFFECT,
        .fg_color = TR_DEFAULT_COLOR_16,
        .fg_mode = TR_COLORS_16,
        .bg_color = TR_DEFAULT_COLOR_16,
        .bg_mode = TR_COLORS_16,
    };

    for (int iy = 0; iy < height; iy += 1) {
        tr_move_cursor(x, y + iy);

        for (int ix = 0; ix < width; ix += 1) {
            int i = ix + iy * width;

            if (style.effects != sprite[i].style.effects) {
                tr_add_effects(sprite[i].style.effects & ~style.effects);
                tr_remove_effects(style.effects & ~sprite[i].style.effects);
                style.effects = sprite[i].style.effects;
            }

            if (style.fg_color != sprite[i].style.fg_color || style.fg_mode != sprite[i].style.fg_mode) {
                style.fg_color = sprite[i].style.fg_color;
                style.fg_mode = sprite[i].style.fg_mode;
                tr_set_fg(style.fg_color, style.fg_mode);
            }

            if (style.bg_color != sprite[i].style.bg_color || style.bg_mode != sprite[i].style.bg_mode) {
                style.bg_color = sprite[i].style.bg_color;
                style.bg_mode = sprite[i].style.bg_mode;
                tr_set_bg(style.bg_color, style.bg_mode);
            }

            putchar(sprite[i].ch);
        }
        style.bg_color = TR_DEFAULT_COLOR_16;
        style.bg_mode = TR_COLORS_16;
        tr_reset_bg();
    }
}
void tr_draw_text(const char *text, const TrStyle *style, int x, int y) {
    tr_move_cursor(x, y);
    tr_set_style(style);
    fputs(text, stdout);
}
// ============================================================================

// Frame buffers
// ============================================================================
void tr_fb_init(TrFrameBuffers *fb, int width, int height) {
    if (width <= 0 || height <= 0 || width * height > TR_FB_LENGTH) {
        fb->width = 0;
        fb->height = 0;
        return;
    }
    fb->width = width;
    fb->height = height;

    for (int i = 0; i < width * height; i += 1) {
        fb->front[i].ch = ' ';
        tr_init_style(&(fb->front[i].style));

        fb->back[i].ch = ' ';
        tr_init_style(&(fb->back[i].style));
    }
}
void tr_fb_render(TrFrameBuffers *fb) {
}
void tr_fb_draw_sprite(TrFrameBuffers *fb, const TrPixel *sprite, int width, int height, int x, int y) {
    if (width <= 0 || height <= 0)
        return;

    size_t visible_width = 0;
    int sprite_x_idx = 0;
    tr_priv_get_visible(fb->width, width, x, &visible_width, &sprite_x_idx);
    if (visible_width <= 0)
        return;

    size_t visible_height = 0;
    int sprite_y_idx = 0;
    tr_priv_get_visible(fb->height, height, y, &visible_height, &sprite_y_idx);
    if (visible_height <= 0)
        return;

    int fb_idx = fb->width * (y > 0 ? y : 0) + (x > 0 ? x : 0);
    int sprite_idx = width * sprite_y_idx + sprite_x_idx;

    for (int i = 0; i < visible_height; i += 1) {
        memcpy(fb->back + fb_idx, sprite + sprite_idx, sizeof(TrPixel) * visible_width);
        fb_idx += fb->width;
        sprite_idx += width;
    }
}
void tr_fb_draw_text(TrFrameBuffers *fb, const char *text, const TrStyle *style, int x, int y) {
    // TODO: uhhh...uhh,....uhh...umm...need validation.
}
// ============================================================================

// Helper functions
// ============================================================================
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

    if (effects & TR_HIDDEN)
        fputs("HIDDEN ", stdout);

    if (effects & TR_STRIKETHROUGH)
        fputs("STRIKETHROUGH ", stdout);
}
void tr_print_color(uint32_t color, TrColorsMode colors_mode) {
}
// ============================================================================

// Helper functions (private)
// ============================================================================
void tr_priv_get_visible(int fb_size, int size, int pos, size_t *result_size, int *result_idx) {
    if (pos >= 0) {
        if (size + pos < fb_size)
            *result_size = size;
        else
            *result_size = fb_size - pos;
    } else {
        if (size + pos > 0) {
            *result_size = size + pos;
            *result_idx = -pos;
        }
    }
}
// ============================================================================

#endif // TRENDERER_IMPLEMENTATION
