#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ============================================================================
 *
 * trenderer v0.2.0
 *     NOTES:
 *         It's a header-only, single file library. Which means, declaration and definition of functions are both inside this file.
 *         They are completely separated with TRENDERER_IMPLEMENTATION. There are no inline functions for coherent structure.
 *
 *     NAMESPACES AND CONVENTIONS:
 *         Everything is under `tr` namespace. Macros and enum members are ALL_CAPS, structs and enums are PascalCase, and anything else is snake_case.
 *         `tr_priv_XXX` means it's private, those are used inside the library logic.
 *         `tr_carr_XXX`(TrCellArray), `tr_cvec_XXX`(TrCellVector), `tr_ctx_XXX`(TrRenderContext) mean they are OOP functions.
 *
 *     DEFINES:
 *         #define TRENDERER_IMPLEMENTATION
 *             Create the implmentation of the library. MUST BE DEFINED IN ONE SOURCE FILE BEFORE INCLUDING THE HEADER.
 *
 *         #define TR_CELL_ARRAY_LENGTH 64
 *             The length of `TrCellArray`. The default value is 64 and you can define other value before you include the header.
 *
 *         #define TR_FRAMEBUFFER_LENGTH 512
 *             The length of `TrFramebufferBase`. The default value is 512 and you can define other value before you include the header.
 *
 *         #define TR_RAW_BUFFER_LENGTH 2048
 *             The length of a buffer that stores all data including ANSI escape codes and characters, etc. The default value is 2048 and you can define other value before you include the header.
 *
 * ==========================================================================*/

// Screen
// ============================================================================
void tr_clear(void);     // Clear the screen.
void tr_open_alt(void);  // Enable alternative buffer.
void tr_close_alt(void); // Disable alternative buffer.
// ============================================================================

// Cursor
// ============================================================================
void tr_move_cursor(int x, int y); // Set position of cursor.
void tr_show_cursor(void);         // Set visibility of cursor.
void tr_hide_cursor(void);         // Set visibility of cursor.
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
void tr_add_effects(TrEffect effects);    // Add effects.
void tr_remove_effects(TrEffect effects); // Remove effects.
void tr_reset_effects(void);              // Reset current effects to default value.
void tr_reset_all(void);                  // Reset current effects, colors to default value.
// ============================================================================

// Color
// ============================================================================
typedef enum TrColorMode {
    TR_COLOR_16,
    TR_COLOR_256,
    TR_COLOR_TRUE,
} TrColorMode;
typedef struct TrColor {
    uint32_t code;
    TrColorMode mode;
} TrColor;
TrColor tr_default_color(void);                         // Returns default color.
void tr_set_fg(uint32_t fg_color, TrColorMode fg_mode); // Set foreground color of current buffer.
void tr_set_bg(uint32_t bg_color, TrColorMode bg_mode); // Set background color of current buffer.

// Color - Utility functions
// ----------------------------------------------------------------------------
uint32_t tr_gray_256(uint8_t scale);              // Create a gray scale value in ANSI 256 colors.
uint32_t tr_rgb(uint8_t r, uint8_t g, uint8_t b); // Create a rgb value.
uint8_t tr_rgb_r(uint32_t rgb);                   // Get `r` of a rgb value.
uint8_t tr_rgb_g(uint32_t rgb);                   // Get 'g' of a rgb value.
uint8_t tr_rgb_b(uint32_t rgb);                   // Get `b` of a rgb value.
// ----------------------------------------------------------------------------

// Color - Constants - ANSI 16
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

// Color - Constants - ANSI 256
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

// Color - Constants - True color
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

// Debug
// ============================================================================
typedef enum TrResult {
    TR_OK,
    TR_ERR_BAD_ARG,
    TR_ERR_ALLOC_FAIL,
    TR_ERR_BUF_OVERFLOW,
    TR_ERR_OUT_OF_BOUNDS,
} TrResult;
#define TR_CHK(x)              \
    do {                       \
        TrResult _r;           \
        if ((_r = x) != TR_OK) \
            return _r;         \
    } while (0)

#define TR_FAILED(x) (x != TR_OK)

void tr_print_effects(TrEffect effects); // Print the names of effects.
// ============================================================================

// Styles
// ============================================================================
typedef struct TrStyle {
    TrEffect effects;
    TrColor fg, bg;
} TrStyle;
TrStyle tr_default_style(void);                 // Return a default style.
void tr_set_style(TrStyle style);               // Set style of current buffer.
void tr_copy_style(TrStyle *dest, TrStyle src); // Copy value of `src` into `dest`.
// ============================================================================

// Pixel
// ============================================================================
typedef struct TrCell {
    char letter;
    TrEffect effects;
    TrColor fg, bg;
} TrCell;

#ifndef TR_CELL_ARRAY_LENGTH
#define TR_CELL_ARRAY_LENGTH 64
#endif

typedef struct TrCellArray { // Array that holds `TrCell` in amount of `TR_CELL_ARRAY_LENGTH` in SoA style.
    char letter[TR_CELL_ARRAY_LENGTH];
    TrEffect effects[TR_CELL_ARRAY_LENGTH];
    TrColor fg[TR_CELL_ARRAY_LENGTH], bg[TR_CELL_ARRAY_LENGTH];
    int width, height;
} TrCellArray;
TrResult tr_carr_init(TrCellArray *carr, int width, int height);

typedef struct TrCellVector { // Vector that holds `TrCell` in SoA style.
    char *letter;
    TrEffect *effects;
    TrColor *fg, *bg;
    int width, height;
} TrCellVector;
TrResult tr_cvec_init(TrCellVector *cvec, int width, int height);
void tr_cvec_cleanup(TrCellVector *cvec);

typedef TrCellVector TrCellSpan; // View for `TrCell` containers. Similar to std::span in C++.
// ============================================================================

// Basic renderer
// ============================================================================
#ifndef TR_RAW_BUFFER_LENGTH
#define TR_RAW_BUFFER_LENGTH 2048
#endif

// Cursor
// ----------------------------------------------------------------------------
TrResult tr_buf_move_cursor(char *buf, int *idx, size_t len, int x, int y); // Append a string that moves cursor to buf.
// ----------------------------------------------------------------------------

// Effect
// ----------------------------------------------------------------------------
TrResult tr_buf_add_effects(char *buf, int *idx, size_t len, TrEffect effects);    // Append a string that add effects to buf.
TrResult tr_buf_remove_effects(char *buf, int *idx, size_t len, TrEffect effects); // Append a string that removes effects to buf.
TrResult tr_buf_reset_effects(char *buf, int *idx, size_t len);                    // Append a string that resets effects to buf.
// ----------------------------------------------------------------------------

// Color
// ----------------------------------------------------------------------------
TrResult tr_buf_set_fg(char *buf, int *idx, size_t len, uint32_t fg_color, TrColorMode fg_mode); // Append a string that set fg color to buf.
TrResult tr_buf_set_bg(char *buf, int *idx, size_t len, uint32_t bg_color, TrColorMode bg_mode); // Append a string that set bg color to buf.
// ----------------------------------------------------------------------------

TrResult tr_draw_sprite(TrCellSpan sprite, int x, int y);                                          // Draw a sprite on the screen.
TrResult tr_draw_spritesheet(TrCellSpan ss, int sp_x, int sp_y, int sp_w, int sp_h, int x, int y); // Draw a sprite from a spritesheet on the screen.
TrResult tr_draw_text(const char *text, TrStyle style, int x, int y);                              // Draw a string on the screen.
// ============================================================================

// Double-buffering renderer
// ============================================================================
#ifndef TR_FRAMEBUFFER_LENGTH
#define TR_FRAMEBUFFER_LENGTH 512
#endif

typedef struct TrFramebufferBase { // Data set for a framebuffer.
    char letter[TR_FRAMEBUFFER_LENGTH];
    TrEffect effects[TR_FRAMEBUFFER_LENGTH];
    TrColor fg[TR_FRAMEBUFFER_LENGTH], bg[TR_FRAMEBUFFER_LENGTH];
} TrFramebufferBase;

typedef struct TrRenderContext { // Render context for double-buffering. It holds two framebuffers.
    TrFramebufferBase front, back;
    int x, y;
    int width, height;
} TrRenderContext;
TrResult tr_ctx_init(TrRenderContext *ctx, int x, int y, int width, int height);                                              // Initialize the context.
void tr_ctx_clear(TrRenderContext *ctx, uint32_t bg_color, TrColorMode bg_mode);                                              // Clear `back`.
TrResult tr_ctx_render(TrRenderContext *ctx);                                                                                 // Render the result using dirty rectangles.
TrResult tr_ctx_draw_rect(TrRenderContext *ctx, int x, int y, int width, int height, uint32_t color, TrColorMode color_mode); // Draw a rectangle on `back`.
TrResult tr_ctx_draw_sprite(TrRenderContext *ctx, TrCellSpan sprite, int x, int y);                                           // Draw a sprite on `back`.
TrResult tr_ctx_draw_text(TrRenderContext *ctx, const char *text, size_t len, TrStyle style, int x, int y);                   // Draw a string on `back`.
// void tr_ctx_draw_spritesheet(TrRenderContext *ctx, TrCellSpan ss, int sp_x, int sp_y, int sp_w, int sp_h, int x, int y); // Draw a sprite from a spritesheet on `back`.
// ============================================================================

// Utility functions
// ============================================================================
// Type conversion
// ----------------------------------------------------------------------------
TrCellSpan tr_atos(const TrCellArray *carr);                            // Stand for `tr_array_to_span`. Convert `TrCellArray` to `TrCellSpan`.
TrCellSpan tr_ftos(const TrFramebufferBase *fb, int width, int height); // Stand for `tr_framebuffer_to_span`. Convert `TrFrameBuffer` to `TrCellSpan`.
// ----------------------------------------------------------------------------

// Cell buffer
// ----------------------------------------------------------------------------
void tr_clear_buf(TrCellSpan buf, uint32_t bg_color, TrColorMode bg_mode); // Clear a cell buffer
// ----------------------------------------------------------------------------
// ============================================================================

// Helper functions (private)
// ============================================================================
TrResult tr_priv_set_ansi(char *buf, int *idx, size_t len, TrStyle *curr, TrCellSpan sprite, int sp_idx);
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
void tr_open_alt(void) {
    fputs("\x1b[?1049h", stdout);
}
void tr_close_alt(void) {
    fputs("\x1b[?1049l", stdout);
}
// ============================================================================

// Cursor control
// ============================================================================
void tr_move_cursor(int x, int y) {
    if (x < 0 || y < 0)
        return;

    printf("\x1b[%d;%dH", y + 1, x + 1);
}
void tr_show_cursor(void) {
    fputs("\x1b[?25h", stdout);
}
void tr_hide_cursor(void) {
    fputs("\x1b[?25l", stdout);
}
// ============================================================================

// Effect
// ============================================================================
void tr_add_effects(TrEffect effects) {
    if (effects == TR_DEFAULT_EFFECT) {
        tr_reset_effects();
        return;
    }
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

// Color
// ============================================================================
TrColor tr_default_color(void) {
    return (TrColor){
        .code = TR_DEFAULT_COLOR_16,
        .mode = TR_COLOR_16};
}
void tr_set_fg(uint32_t fg_color, TrColorMode fg_mode) {
    if (fg_color == TR_TRANSPARENT)
        return;

    switch (fg_mode) {
    case TR_COLOR_16:
        printf("\x1b[%dm", fg_color);
        break;
    case TR_COLOR_256:
        printf("\x1b[38;5;%dm", fg_color);
        break;
    case TR_COLOR_TRUE:
        printf("\x1b[38;2;%d;%d;%dm", tr_rgb_r(fg_color), tr_rgb_g(fg_color), tr_rgb_b(fg_color));
        break;
    }
}
void tr_set_bg(uint32_t bg_color, TrColorMode bg_mode) {
    if (bg_color == TR_TRANSPARENT)
        return;

    switch (bg_mode) {
    case TR_COLOR_16:
        printf("\x1b[%dm", 10 + bg_color);
        break;
    case TR_COLOR_256:
        printf("\x1b[48;5;%dm", bg_color);
        break;
    case TR_COLOR_TRUE:
        printf("\x1b[48;2;%d;%d;%dm", tr_rgb_r(bg_color), tr_rgb_g(bg_color), tr_rgb_b(bg_color));
        break;
    }
}

// Color - Utility functions
// ----------------------------------------------------------------------------
uint32_t tr_gray_256(uint8_t scale) {
    return (scale > 23) ? 255 : (232 + scale);
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

// Style
// ============================================================================
TrStyle tr_default_style(void) {
    return (TrStyle){
        .effects = TR_DEFAULT_EFFECT,
        .fg.code = TR_DEFAULT_COLOR_16,
        .fg.mode = TR_COLOR_16,
        .bg.code = TR_DEFAULT_COLOR_16,
        .bg.mode = TR_COLOR_16};
}
void tr_set_style(TrStyle style) {
    tr_add_effects(style.effects);
    tr_set_fg(style.fg.code, style.fg.mode);
    tr_set_bg(style.bg.code, style.bg.mode);
}
void tr_copy_style(TrStyle *dest, TrStyle src) {
    dest->effects = src.effects;
    dest->fg.code = src.fg.code;
    dest->fg.mode = src.fg.mode;
    dest->bg.code = src.bg.code;
    dest->bg.mode = src.bg.mode;
}
// ============================================================================

// Cell
// ============================================================================
TrResult tr_carr_init(TrCellArray *carr, int width, int height) {
    if (width <= 0 || height <= 0 || (width * height > TR_CELL_ARRAY_LENGTH)) {
        carr->width = 0;
        carr->height = 0;
        return TR_ERR_BAD_ARG;
    }

    carr->width = width;
    carr->height = height;

    tr_clear_buf(tr_atos(carr), TR_DEFAULT_COLOR_16, TR_COLOR_16);

    return TR_OK;
}
TrResult tr_cvec_init(TrCellVector *cvec, int width, int height) {
    if (width <= 0 || height <= 0) {
        cvec->width = 0;
        cvec->height = 0;
        return TR_ERR_BAD_ARG;
    }

    cvec->width = width;
    cvec->height = height;

    size_t len = width * height;

    cvec->letter = (char *)malloc(len * sizeof(char));
    if (cvec->letter == NULL)
        return TR_ERR_ALLOC_FAIL;

    cvec->effects = (TrEffect *)malloc(len * sizeof(TrEffect));
    if (cvec->effects == NULL)
        return TR_ERR_ALLOC_FAIL;

    cvec->fg = (TrColor *)malloc(len * sizeof(TrColor));
    if (cvec->fg == NULL)
        return TR_ERR_ALLOC_FAIL;

    cvec->bg = (TrColor *)malloc(len * sizeof(TrColor));
    if (cvec->bg == NULL)
        return TR_ERR_ALLOC_FAIL;

    tr_clear_buf(*cvec, TR_DEFAULT_COLOR_16, TR_COLOR_16);

    return TR_OK;
}
void tr_cvec_cleanup(TrCellVector *cvec) {
    if (cvec->letter != NULL) {
        free(cvec->letter);
        cvec->letter = NULL;
    }
    if (cvec->effects != NULL) {
        free(cvec->effects);
        cvec->effects = NULL;
    }
    if (cvec->fg != NULL) {
        free(cvec->fg);
        cvec->fg = NULL;
    }
    if (cvec->bg != NULL) {
        free(cvec->bg);
        cvec->bg = NULL;
    }
}
// ============================================================================

// Basic renderer
// ============================================================================

// Cursor
// ----------------------------------------------------------------------------
#define TR_PRIV_APPEND(str, ...) (*idx += snprintf(buf + (*idx), len - (*idx), str, __VA_ARGS__));

#define TR_PRIV_CHK_BO(idx, len)        \
    do {                                \
        if ((idx) >= (len - 1)) {       \
            return TR_ERR_BUF_OVERFLOW; \
        }                               \
    } while (0)

TrResult tr_buf_move_cursor(char *buf, int *idx, size_t len, int x, int y) {
    TR_PRIV_APPEND("\x1b[%d;%dH", y + 1, x + 1);
    TR_PRIV_CHK_BO(*idx, len);

    return TR_OK;
}
// ----------------------------------------------------------------------------

// Effect
// ----------------------------------------------------------------------------
TrResult tr_buf_add_effects(char *buf, int *idx, size_t len, TrEffect effects) {
    if (effects == TR_DEFAULT_EFFECT) {
        tr_buf_reset_effects(buf, idx, len);
        return TR_OK;
    }
    if (effects & TR_BOLD) {
        TR_PRIV_APPEND("\x1b[1m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_DIM) {
        TR_PRIV_APPEND("\x1b[2m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_ITALIC) {
        TR_PRIV_APPEND("\x1b[3m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_UNDERLINE) {
        TR_PRIV_APPEND("\x1b[4m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_BLINK) {
        TR_PRIV_APPEND("\x1b[5m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_INVERT) {
        TR_PRIV_APPEND("\x1b[7m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_INVISIBLE) {
        TR_PRIV_APPEND("\x1b[8m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_STRIKETHROUGH) {
        TR_PRIV_APPEND("\x1b[9m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    return TR_OK;
}
TrResult tr_buf_remove_effects(char *buf, int *idx, size_t len, TrEffect effects) {
    if (effects & TR_BOLD || effects & TR_DIM) {
        TR_PRIV_APPEND("\x1b[22m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_ITALIC) {
        TR_PRIV_APPEND("\x1b[23m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_UNDERLINE) {
        TR_PRIV_APPEND("\x1b[24m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_BLINK) {
        TR_PRIV_APPEND("\x1b[25m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_INVERT) {
        TR_PRIV_APPEND("\x1b[27m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_INVISIBLE) {
        TR_PRIV_APPEND("\x1b[28m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    if (effects & TR_STRIKETHROUGH) {
        TR_PRIV_APPEND("\x1b[29m");
        TR_PRIV_CHK_BO(*idx, len);
    }

    return TR_OK;
}
TrResult tr_buf_reset_effects(char *buf, int *idx, size_t len) {
    TR_PRIV_APPEND("\x1b[22;23;24;25;27;28;29m");
    TR_PRIV_CHK_BO(*idx, len);

    return TR_OK;
}
// ----------------------------------------------------------------------------

// Color
// ----------------------------------------------------------------------------
TrResult tr_buf_set_fg(char *buf, int *idx, size_t len, uint32_t fg_color, TrColorMode fg_mode) {
    if (fg_color == TR_TRANSPARENT)
        return TR_OK;

    switch (fg_mode) {
    case TR_COLOR_16:
        TR_PRIV_APPEND("\x1b[%dm", fg_color);
        TR_PRIV_CHK_BO(*idx, len);
        break;
    case TR_COLOR_256:
        TR_PRIV_APPEND("\x1b[38;5;%dm", fg_color);
        TR_PRIV_CHK_BO(*idx, len);
        break;
    case TR_COLOR_TRUE:
        TR_PRIV_APPEND("\x1b[38;2;%d;%d;%dm", tr_rgb_r(fg_color), tr_rgb_g(fg_color), tr_rgb_b(fg_color));
        TR_PRIV_CHK_BO(*idx, len);
        break;
    }

    return TR_OK;
}
TrResult tr_buf_set_bg(char *buf, int *idx, size_t len, uint32_t bg_color, TrColorMode bg_mode) {
    if (bg_color == TR_TRANSPARENT)
        return TR_OK;

    switch (bg_mode) {
    case TR_COLOR_16:
        TR_PRIV_APPEND("\x1b[%dm", 10 + bg_color);
        TR_PRIV_CHK_BO(*idx, len);
        break;
    case TR_COLOR_256:
        TR_PRIV_APPEND("\x1b[48;5;%dm", bg_color);
        TR_PRIV_CHK_BO(*idx, len);
        break;
    case TR_COLOR_TRUE:
        TR_PRIV_APPEND("\x1b[48;2;%d;%d;%dm", tr_rgb_r(bg_color), tr_rgb_g(bg_color), tr_rgb_b(bg_color));
        TR_PRIV_CHK_BO(*idx, len);
        break;
    }

    return TR_OK;
}
// ----------------------------------------------------------------------------
TrResult tr_draw_sprite(TrCellSpan sprite, int x, int y) {
    if (sprite.width <= 0 || sprite.height <= 0 || x < 0 || y < 0)
        return TR_ERR_BAD_ARG;

    TrStyle curr = {
        .effects = TR_DEFAULT_EFFECT,
        .fg.code = TR_DEFAULT_COLOR_16,
        .fg.mode = TR_COLOR_16,
        .bg.code = TR_DEFAULT_COLOR_16,
        .bg.mode = TR_COLOR_16,
    };
    int idx = 0;
    char raw_buf[TR_RAW_BUFFER_LENGTH];

    for (int row = 0; row < sprite.height; row += 1) {
        TR_CHK(tr_buf_move_cursor(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, x, y + row));

        for (int col = 0; col < sprite.width; col += 1) {
            int sp_idx = col + row * sprite.width; // [sp_idx] == [row][col]

            TR_CHK(tr_priv_set_ansi(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, &curr, sprite, sp_idx));

            raw_buf[idx++] = sprite.letter[sp_idx];
            if (idx >= TR_RAW_BUFFER_LENGTH - 1)
                return TR_ERR_BUF_OVERFLOW;
        }

        if (curr.bg.code != TR_DEFAULT_COLOR_16 || curr.bg.mode != TR_COLOR_16) {
            curr.bg.code = TR_DEFAULT_COLOR_16;
            curr.bg.mode = TR_COLOR_16;
            TR_CHK(tr_buf_set_bg(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, curr.bg.code, curr.bg.mode));
        }
    }
    if (idx >= TR_RAW_BUFFER_LENGTH - 1)
        return TR_ERR_BUF_OVERFLOW;

    raw_buf[idx] = '\0';
    fputs(raw_buf, stdout);
    tr_reset_all();

    return TR_OK;
}
TrResult tr_draw_spritesheet(TrCellSpan ss, int sp_x, int sp_y, int sp_w, int sp_h, int x, int y) {
    // Spritesheet and position validation
    if (ss.width <= 0 || ss.height <= 0 || x < 0 || y < 0)
        return TR_ERR_BAD_ARG;

    // Sprite validation
    if (sp_w <= 0 || sp_h <= 0 ||
        sp_x < 0 || sp_x >= ss.width ||
        sp_y < 0 || sp_y >= ss.height ||
        (sp_x + sp_w > ss.width) ||
        (sp_y + sp_h > ss.height))
        return TR_ERR_BAD_ARG;

    TrStyle curr = {
        .effects = TR_DEFAULT_EFFECT,
        .fg.code = TR_DEFAULT_COLOR_16,
        .fg.mode = TR_COLOR_16,
        .bg.code = TR_DEFAULT_COLOR_16,
        .bg.mode = TR_COLOR_16,
    };
    int idx = 0;
    char raw_buf[TR_RAW_BUFFER_LENGTH];

    for (int row = 0; row < sp_h; row += 1) {
        TR_CHK(tr_buf_move_cursor(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, x, y + row));

        int sp_row_base = sp_x + (sp_y + row) * ss.width; // [sp_row_base] == [sp_y + row][sp_x]

        for (int col = 0; col < sp_w; col += 1) {
            int sp_idx = col + sp_row_base; // [sp_idx] == [sp_y + row][sp_x + col]

            TR_CHK(tr_priv_set_ansi(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, &curr, ss, sp_idx));

            raw_buf[idx++] = ss.letter[sp_idx];
            if (idx >= TR_RAW_BUFFER_LENGTH - 1)
                return TR_ERR_BUF_OVERFLOW;
        }

        if (curr.bg.code != TR_DEFAULT_COLOR_16 || curr.bg.mode != TR_COLOR_16) {
            curr.bg.code = TR_DEFAULT_COLOR_16;
            curr.bg.mode = TR_COLOR_16;
            TR_CHK(tr_buf_set_bg(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, curr.bg.code, curr.bg.mode));
        }
    }
    if (idx >= TR_RAW_BUFFER_LENGTH - 1)
        return TR_ERR_BUF_OVERFLOW;

    raw_buf[idx] = '\0';
    fputs(raw_buf, stdout);
    tr_reset_all();

    return TR_OK;
}
TrResult tr_draw_text(const char *text, TrStyle style, int x, int y) {
    if (!text || y < 0)
        return TR_ERR_BAD_ARG;

    int idx = 0;
    char raw_buf[TR_RAW_BUFFER_LENGTH];

    TR_CHK(tr_buf_move_cursor(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, x, y));
    TR_CHK(tr_buf_reset_effects(raw_buf, &idx, TR_RAW_BUFFER_LENGTH));
    TR_CHK(tr_buf_add_effects(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, style.effects));
    TR_CHK(tr_buf_set_fg(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, style.fg.code, style.fg.mode));
    TR_CHK(tr_buf_set_bg(raw_buf, &idx, TR_RAW_BUFFER_LENGTH, style.bg.code, style.bg.mode));

    idx += snprintf(raw_buf + idx, TR_RAW_BUFFER_LENGTH - idx, "%s", text);
    if (idx >= TR_RAW_BUFFER_LENGTH - 1)
        return TR_ERR_BUF_OVERFLOW;

    raw_buf[idx] = '\0';
    fputs(raw_buf, stdout);

    return TR_OK;
}
// ============================================================================

// Frame buffers
// ============================================================================
TrResult tr_ctx_init(TrRenderContext *ctx, int x, int y, int width, int height) {
    if (x < 0 || y < 0 || width <= 0 || height <= 0 || (width * height > TR_FRAMEBUFFER_LENGTH)) {
        ctx->x = 0;
        ctx->y = 0;
        ctx->width = 0;
        ctx->height = 0;
        return TR_ERR_BAD_ARG;
    }

    ctx->x = x;
    ctx->y = y;
    ctx->width = width;
    ctx->height = height;

    tr_clear_buf(tr_ftos(&ctx->front, width, height), TR_DEFAULT_COLOR_16, TR_COLOR_16);
    tr_clear_buf(tr_ftos(&ctx->back, width, height), TR_DEFAULT_COLOR_16, TR_COLOR_16);

    return TR_OK;
}
void tr_ctx_clear(TrRenderContext *ctx, uint32_t bg_color, TrColorMode bg_mode) {
    tr_clear_buf(tr_ftos(&ctx->back, ctx->width, ctx->height), bg_color, bg_mode);
}
TrResult tr_ctx_render(TrRenderContext *ctx) {
    int dirty_rect_x = 0, dirty_rect_y = 0;
    int dirty_rect_w = 0, dirty_rect_h = 0;
    tr_priv_get_dirty_rect(&dirty_rect_x, &dirty_rect_y, &dirty_rect_w, &dirty_rect_h, ctx);
    if (dirty_rect_w <= 0 || dirty_rect_h <= 0)
        return TR_OK;

    // Draw only dirty rectangle.
    TR_CHK(tr_draw_spritesheet(tr_ftos(&ctx->back, ctx->width, ctx->height), dirty_rect_x, dirty_rect_y, dirty_rect_w, dirty_rect_h, ctx->x + dirty_rect_x, ctx->y + dirty_rect_y));

    // Update `front` with `back`.
    tr_priv_ctx_swap(ctx);

    return TR_OK;
}
TrResult tr_ctx_draw_rect(TrRenderContext *ctx, int x, int y, int width, int height, uint32_t color, TrColorMode color_mode) {
    if (width <= 0 || height <= 0 || color == TR_TRANSPARENT)
        return TR_ERR_BAD_ARG;

    int visible_width = 0;
    int temp0 = 0;
    tr_priv_get_visible(&visible_width, &temp0, ctx->width, width, x);
    if (visible_width <= 0)
        return TR_OK;

    int visible_height = 0;
    int temp1 = 0;
    tr_priv_get_visible(&visible_height, &temp1, ctx->width, height, y);
    if (visible_height <= 0)
        return TR_OK;

    int fb_base = (x > 0 ? x : 0) + (y > 0 ? y : 0) * ctx->width; // [fb_base] == [y or 0][x or 0]

    for (int row = 0; row < visible_height; row += 1) {
        int fb_row_base = fb_base + row * ctx->width; // [fb_row_base] == [y + row][x]

        memset(ctx->back.letter + fb_row_base, ' ', visible_width * sizeof(char));
        memset(ctx->back.effects + fb_row_base, TR_DEFAULT_EFFECT, visible_width * sizeof(TrEffect));

        for (int col = 0; col < visible_width; col += 1) {
            int idx = col + fb_row_base; // [idx] = [y + row][x + col]

            ctx->back.fg[idx].code = color;
            ctx->back.fg[idx].mode = color_mode;
            ctx->back.bg[idx].code = color;
            ctx->back.bg[idx].mode = color_mode;
        }
    }

    return TR_OK;
}
TrResult tr_ctx_draw_sprite(TrRenderContext *ctx, TrCellSpan sprite, int x, int y) {
    if (sprite.width <= 0 || sprite.height <= 0)
        return TR_ERR_BAD_ARG;

    int visible_width = 0;
    int sp_col = 0;
    tr_priv_get_visible(&visible_width, &sp_col, ctx->width, sprite.width, x);
    if (visible_width <= 0)
        return TR_OK;

    int visible_height = 0;
    int sp_row = 0;
    tr_priv_get_visible(&visible_height, &sp_row, ctx->height, sprite.height, y);
    if (visible_height <= 0)
        return TR_OK;

    int fb_base = (x > 0 ? x : 0) + (y > 0 ? y : 0) * ctx->width; // [fb_base] == [y or 0][x or 0]
    int sp_base = sp_col + sp_row * sprite.width;                 // [sp_base] == [sp_row][sp_col]

    for (int row = 0; row < visible_height; row += 1) {
        int fb_row_base = fb_base + row * ctx->width;   // [fb_row_base] == [y + row][x]
        int sp_row_base = sp_base + row * sprite.width; // [sp_row_base] == [sp_row + row][sp_col]

        memcpy(ctx->back.letter + fb_row_base, sprite.letter + sp_row_base, visible_width * sizeof(char));
        memcpy(ctx->back.effects + fb_row_base, sprite.effects + sp_row_base, visible_width * sizeof(TrEffect));

        for (int col = 0; col < visible_width; col += 1) {
            int sp_idx = col + sp_row_base; // [sp_idx] == [sp_row + row][sp_col + col]

            if (sprite.fg[sp_idx].code != TR_TRANSPARENT) {
                int fb_idx = col + fb_row_base; // [fb_idx] == [y + row][x + col]

                ctx->back.fg[fb_idx].code = sprite.fg[sp_idx].code;
                ctx->back.fg[fb_idx].mode = sprite.fg[sp_idx].mode;
            }
            if (sprite.bg[sp_idx].code != TR_TRANSPARENT) {
                int fb_idx = col + fb_row_base; // [fb_idx] == [y + row][x + col]

                ctx->back.bg[fb_idx].code = sprite.bg[sp_idx].code;
                ctx->back.bg[fb_idx].mode = sprite.bg[sp_idx].mode;
            }
        }
    }

    return TR_OK;
}
TrResult tr_ctx_draw_text(TrRenderContext *ctx, const char *text, size_t len, TrStyle style, int x, int y) {
    if (len <= 0 || y < 0 || y >= ctx->height)
        return TR_ERR_BAD_ARG;
    int visible_len = 0;
    int text_idx = 0;
    tr_priv_get_visible(&visible_len, &text_idx, ctx->width, len, x);
    if (visible_len <= 0)
        return TR_OK;

    int fb_base = (x > 0 ? x : 0) + (y > 0 ? y : 0) * ctx->width; // [fb_base] == [y or 0][x or 0]

    memcpy(ctx->back.letter + fb_base, text + text_idx, visible_len * sizeof(char));

    for (int col = 0; col < visible_len; col += 1) {
        int fb_idx = col + fb_base; // [fb_idx] == [y][x + col]

        if (ctx->back.letter[fb_idx] == '\0')
            ctx->back.letter[fb_idx] = ' ';
        ctx->back.effects[fb_idx] = style.effects;
        ctx->back.fg[fb_idx].code = style.fg.code;
        ctx->back.fg[fb_idx].mode = style.fg.mode;
        ctx->back.bg[fb_idx].code = style.bg.code;
        ctx->back.bg[fb_idx].mode = style.bg.mode;
    }

    return TR_OK;
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
TrCellSpan tr_atos(const TrCellArray *carr) {
    return (TrCellSpan){
        .letter = (char *)carr->letter,
        .effects = (TrEffect *)carr->effects,
        .fg = (TrColor *)carr->fg,
        .bg = (TrColor *)carr->bg,
        .width = carr->width,
        .height = carr->height};
}
TrCellSpan tr_ftos(const TrFramebufferBase *fb, int width, int height) {
    return (TrCellSpan){
        .letter = (char *)fb->letter,
        .effects = (TrEffect *)fb->effects,
        .fg = (TrColor *)fb->fg,
        .bg = (TrColor *)fb->bg,
        .width = width,
        .height = height};
}
// ----------------------------------------------------------------------------

// Pixel buffer
// ----------------------------------------------------------------------------
void tr_clear_buf(TrCellSpan buf, uint32_t bg_color, TrColorMode bg_mode) {
    size_t len = buf.width * buf.height;

    memset(buf.letter, ' ', len * sizeof(char));
    memset(buf.effects, TR_DEFAULT_EFFECT, len * sizeof(TrEffect));

    for (int i = 0; i < len; i += 1) {
        buf.fg[i].code = TR_DEFAULT_COLOR_16;
        buf.fg[i].mode = TR_COLOR_16;
        buf.bg[i].code = bg_color;
        buf.bg[i].mode = bg_mode;
    }
}
// ============================================================================

// Helper functions (private)
// ============================================================================
TrResult tr_priv_set_ansi(char *buf, int *idx, size_t len, TrStyle *curr, TrCellSpan sprite, int sp_idx) {
    TrResult res = TR_OK;

    if (curr->effects != sprite.effects[sp_idx]) {
        TR_CHK(tr_buf_add_effects(buf, idx, len, sprite.effects[sp_idx] & ~curr->effects));
        TR_CHK(tr_buf_remove_effects(buf, idx, len, curr->effects & ~sprite.effects[sp_idx]));
        curr->effects = sprite.effects[sp_idx];
    }

    if (curr->fg.code != sprite.fg[sp_idx].code || curr->fg.mode != sprite.fg[sp_idx].mode) {
        curr->fg.code = sprite.fg[sp_idx].code;
        curr->fg.mode = sprite.fg[sp_idx].mode;
        TR_CHK(tr_buf_set_fg(buf, idx, len, curr->fg.code, curr->fg.mode));
    }

    if (curr->bg.code != sprite.bg[sp_idx].code || curr->bg.mode != sprite.bg[sp_idx].mode) {
        curr->bg.code = sprite.bg[sp_idx].code;
        curr->bg.mode = sprite.bg[sp_idx].mode;
        TR_CHK(tr_buf_set_bg(buf, idx, len, curr->bg.code, curr->bg.mode));
    }

    return TR_OK;
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
    if (memcmp(ctx->front.letter + idx, ctx->back.letter + idx, len * sizeof(char)) != 0)
        return false;

    if (memcmp(ctx->front.effects + idx, ctx->back.effects + idx, len * sizeof(TrEffect)) != 0)
        return false;

    if (memcmp(ctx->front.fg + idx, ctx->back.fg + idx, len * sizeof(TrColor)) != 0)
        return false;

    if (memcmp(ctx->front.bg + idx, ctx->back.bg + idx, len * sizeof(TrColor)) != 0)
        return false;

    return true;
}
bool tr_priv_ctx_cmp(const TrRenderContext *ctx, int idx) {
    if (ctx->front.letter[idx] != ctx->back.letter[idx])
        return false;

    if (ctx->front.effects[idx] != ctx->back.effects[idx])
        return false;

    if (ctx->front.fg[idx].code != ctx->back.fg[idx].code)
        return false;

    if (ctx->front.fg[idx].mode != ctx->back.fg[idx].mode)
        return false;

    if (ctx->front.bg[idx].code != ctx->back.bg[idx].code)
        return false;

    if (ctx->front.bg[idx].mode != ctx->back.bg[idx].mode)
        return false;

    return true;
}
void tr_priv_ctx_swap(TrRenderContext *ctx) {
    size_t len = ctx->width * ctx->height;

    memcpy(ctx->front.letter, ctx->back.letter, len * sizeof(char));
    memcpy(ctx->front.effects, ctx->back.effects, len * sizeof(TrEffect));
    memcpy(ctx->front.fg, ctx->back.fg, len * sizeof(TrColor));
    memcpy(ctx->front.bg, ctx->back.bg, len * sizeof(TrColor));
}
void tr_priv_get_dirty_rect(int *x, int *y, int *width, int *height, const TrRenderContext *ctx) {
    int left = ctx->width - 1;
    int top = ctx->height - 1;
    int right = 0;
    int bottom = 0;

    for (int row = 0; row < ctx->height; row += 1) {
        int fb_row_base = 0 + row * ctx->width; // [fb_row_base] == [row][0]

        if (tr_priv_ctx_memcmp(ctx, fb_row_base, ctx->width))
            continue;

        for (int col = 0; col < ctx->width; col += 1) {
            int fb_idx = col + fb_row_base; // [fb_idx] == [row][col]

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
