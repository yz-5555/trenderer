#ifndef TR_H
#define TR_H

/* ============================================================================
 *
 * trenderer v0.3.2
 *     NOTES:
 *         This is a single-header library. Declaration and definition of functions are both inside this file.
 *         They are completely separated with TR_IMPLEMENTATION. There are no inline functions for coherent structure.
 *
 *     NAMESPACES AND CONVENTIONS:
 *         Everything is in `tr` namespace. Macros and enum members are ALL_CAPS, structs and enums are PascalCase, and anything else is snake_case.
 *         `tr_carr_XXX`(TrCellArray), `tr_cvec_XXX`(TrCellVector), `tr_ctx_XXX`(TrRenderContext) mean they are OOP functions.
 *
 *     DEFINES:
 *         #define TR_IMPLEMENTATION
 *             Create the implementation of the library. MUST BE DEFINED IN ONE SOURCE FILE BEFORE INCLUDING THE HEADER.
 *
 *         #define TR_NO_RENDERER
 *             Exclude renderer related types, functions, constants. Include only IO related.
 *
 *         #define TR_MAX_CELL_ARRAY_LEN 64
 *             The length of `TrCellArray`. The default value is 64 and you can define other value before you include the header.
 *
 *         #define TR_MAX_FRAMEBUFFER_LEN 512
 *             The length of `TrFramebufferBase`. The default value is 512 and you can define other value before you include the header.
 *
 *         #define TR_MAX_RAW_BUFFER_LEN 2048
 *             The length of a buffer that stores all data including ANSI escape codes and characters, etc. The default value is 2048 and you can define other value before you include the header.
 *
 * ==========================================================================*/

#include <stdbool.h>
#include <stdint.h>

// clang-format off
#ifndef TR_API
    #ifdef TR_PRIVATE
        #ifdef __cplusplus
            #define TR_API inline
        #else
            #define TR_API static inline
        #endif
    #else
        #define TR_API extern
    #endif
#endif
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

// Screen
// ============================================================================
TR_API void tr_clear(void);     // Clear the screen.
TR_API void tr_open_alt(void);  // Enable alternative buffer.
TR_API void tr_close_alt(void); // Disable alternative buffer.
// ============================================================================

// Cursor
// ============================================================================
TR_API void tr_move_cursor(int x, int y); // Set position of cursor.
TR_API void tr_show_cursor(void);         // Set visibility of cursor.
TR_API void tr_hide_cursor(void);         // Set visibility of cursor.
// ============================================================================

// Effects
// ============================================================================
#define TR_EFFECTS_LEN 8
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
TR_API void tr_add_effects(TrEffect effects);    // Add effects.
TR_API void tr_remove_effects(TrEffect effects); // Remove effects.
TR_API void tr_reset_effects(void);              // Reset current effects to default value.
TR_API void tr_reset_all(void);                  // Reset current effects, colors to default value.
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
TR_API TrColor tr_default_color(void);                         // Returns default color.
TR_API void tr_set_fg(uint32_t fg_color, TrColorMode fg_mode); // Set foreground color of current buffer.
TR_API void tr_set_bg(uint32_t bg_color, TrColorMode bg_mode); // Set background color of current buffer.

// Color - Utility functions
// ----------------------------------------------------------------------------
TR_API uint32_t tr_gray_256(uint8_t scale);              // Create a gray scale value in ANSI 256 colors.
TR_API uint32_t tr_rgb(uint8_t r, uint8_t g, uint8_t b); // Create a rgb value.
TR_API uint8_t tr_rgb_r(uint32_t rgb);                   // Get `r` of a rgb value.
TR_API uint8_t tr_rgb_g(uint32_t rgb);                   // Get 'g' of a rgb value.
TR_API uint8_t tr_rgb_b(uint32_t rgb);                   // Get `b` of a rgb value.
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

#ifndef TR_NO_RENDERER

#include <stddef.h>

// Debug
// ============================================================================
typedef enum TrResult {
    TR_OK,
    TR_ERR_BAD_ARG,
    TR_ERR_ALLOC_FAIL,
    TR_ERR_BUF_OVERFLOW,
    TR_ERR_OUT_OF_BOUNDS,
} TrResult;
// ============================================================================

// Styles
// ============================================================================
typedef struct TrStyle {
    TrEffect effects;
    TrColor fg, bg;
} TrStyle;
TR_API TrStyle tr_default_style(void);                // Return a default style.
TR_API void tr_set_style(TrStyle style);              // Set style of current buffer.
TR_API void tr_copy_style(TrStyle *dst, TrStyle src); // Copy value of `src` into `dest`.
// ============================================================================

// Cell
// ============================================================================
typedef struct TrCell {
    char letter;
    TrEffect effects;
    TrColor fg, bg;
} TrCell;

// clang-format off
#ifndef TR_MAX_CELL_ARRAY_LEN
    #define TR_MAX_CELL_ARRAY_LEN 64
#endif
// clang-format on
typedef struct TrCellArray { // Array that holds `TrCell` in amount of `TR_MAX_CELL_ARRAY_LEN` in SoA style.
    char letter[TR_MAX_CELL_ARRAY_LEN];
    TrEffect effects[TR_MAX_CELL_ARRAY_LEN];
    TrColor fg[TR_MAX_CELL_ARRAY_LEN], bg[TR_MAX_CELL_ARRAY_LEN];
    int width, height;
} TrCellArray;
TR_API TrResult tr_carr_init(TrCellArray *carr, int width, int height);

typedef struct TrCellVector { // Vector that holds `TrCell` in SoA style.
    char *letter;
    TrEffect *effects;
    TrColor *fg, *bg;
    int width, height;
} TrCellVector;
TR_API TrResult tr_cvec_init(TrCellVector *cvec, int width, int height);
TR_API void tr_cvec_cleanup(TrCellVector *cvec);

typedef TrCellVector TrCellSpan; // View for `TrCell` containers. Similar to std::span in C++.
// ============================================================================

// Basic renderer
// ============================================================================
// clang-format off
#ifndef TR_MAX_RAW_BUFFER_LEN
    #define TR_MAX_RAW_BUFFER_LEN 2048
#endif
// clang-format on
// Cursor
// ----------------------------------------------------------------------------
TR_API TrResult tr_strcat_move_cursor(char *dst, size_t len, size_t *idx, int x, int y); // Append a string that moves cursor to dst.
// ----------------------------------------------------------------------------

// Effect
// ----------------------------------------------------------------------------
TR_API TrResult tr_strcat_add_effects(char *dst, size_t len, size_t *idx, TrEffect effects);    // Append a string that add effects to dst.
TR_API TrResult tr_strcat_remove_effects(char *dst, size_t len, size_t *idx, TrEffect effects); // Append a string that removes effects to dst.
TR_API TrResult tr_strcat_reset_effects(char *dst, size_t len, size_t *idx);                    // Append a string that resets current effects tp default value to dst.
TR_API TrResult tr_strcat_reset_all(char *dst, size_t len, size_t *idx);                        // Append a string that resets current effects, colors to default value to dst.
// ----------------------------------------------------------------------------

// Color
// ----------------------------------------------------------------------------
TR_API TrResult tr_strcat_set_fg(char *dst, size_t len, size_t *idx, uint32_t fg_color, TrColorMode fg_mode); // Append a string that set fg color to dst.
TR_API TrResult tr_strcat_set_bg(char *dst, size_t len, size_t *idx, uint32_t bg_color, TrColorMode bg_mode); // Append a string that set bg color to dst.
// ----------------------------------------------------------------------------

// Rendering functions
// ----------------------------------------------------------------------------
TR_API TrResult tr_draw_sprite(TrCellSpan sprite, int x, int y);                                              // Draw a sprite on the screen.
TR_API TrResult tr_draw_spritesheet(TrCellSpan ss, int spr_x, int spr_y, int spr_w, int spr_h, int x, int y); // Draw a sprite from a spritesheet on the screen.
TR_API TrResult tr_draw_text(const char *text, TrStyle style, int x, int y);                                  // Draw a string on the screen.
// ----------------------------------------------------------------------------
// ============================================================================

// Double-buffering renderer
// ============================================================================
// clang-format off
#ifndef TR_MAX_FRAMEBUFFER_LEN
    #define TR_MAX_FRAMEBUFFER_LEN 512
#endif
// clang-format on
typedef struct TrFramebufferBase { // Data set for a framebuffer.
    char letter[TR_MAX_FRAMEBUFFER_LEN];
    TrEffect effects[TR_MAX_FRAMEBUFFER_LEN];
    TrColor fg[TR_MAX_FRAMEBUFFER_LEN], bg[TR_MAX_FRAMEBUFFER_LEN];
} TrFramebufferBase;

typedef struct TrRenderContext { // Render context for double-buffering. It holds two framebuffers.
    TrFramebufferBase front, back;
    int x, y;
    int width, height;
} TrRenderContext;
TR_API TrResult tr_ctx_init(TrRenderContext *ctx, int x, int y, int width, int height);                                              // Initialize the context.
TR_API void tr_ctx_clear(TrRenderContext *ctx, uint32_t bg_color, TrColorMode bg_mode);                                              // Clear `back`.
TR_API TrResult tr_ctx_render(TrRenderContext *ctx);                                                                                 // Render the result using dirty rectangles.
TR_API TrResult tr_ctx_draw_rect(TrRenderContext *ctx, int x, int y, int width, int height, uint32_t color, TrColorMode color_mode); // Draw a rectangle on `back`.
TR_API TrResult tr_ctx_draw_sprite(TrRenderContext *ctx, TrCellSpan sprite, int x, int y);                                           // Draw a sprite on `back`.
TR_API TrResult tr_ctx_draw_text(TrRenderContext *ctx, const char *text, size_t len, TrStyle style, int x, int y);                   // Draw a string on `back`.
// TR_API void tr_ctx_draw_spritesheet(TrRenderContext *ctx, TrCellSpan ss, int spr_x, int spr_y, int spr_w, int spr_h, int x, int y); // Draw a sprite from a spritesheet on `back`.
// ============================================================================

// Utility functions
// ============================================================================
// Type conversion
// ----------------------------------------------------------------------------
TR_API TrCellSpan tr_atos(TrCellArray *carr);                            // Stand for `tr_array_to_span`. Convert `TrCellArray` to `TrCellSpan`.
TR_API TrCellSpan tr_ftos(TrFramebufferBase *fb, int width, int height); // Stand for `tr_framebuffer_to_span`. Convert `TrFrameBuffer` to `TrCellSpan`.
// ----------------------------------------------------------------------------

// Cell buffer
// ----------------------------------------------------------------------------
TR_API void tr_clear_buf(TrCellSpan buf, uint32_t bg_color, TrColorMode bg_mode); // Clear a cell buffer
// ----------------------------------------------------------------------------
// ============================================================================
#endif // TR_NO_RENDERER

#ifdef __cplusplus
}
#endif

#endif // TR_H

#define TR_IMPLEMENTATION // MUST BE REMOVED BEFORE RELEASE!!!!!!!!!!!

#ifdef TR_IMPLEMENTATION

#include <stdio.h>
#include <string.h>

// Screen & Window control
// ============================================================================
TR_API void tr_clear(void) {
    fputs("\x1b[2J\x1b[H", stdout);
}
TR_API void tr_open_alt(void) {
    fputs("\x1b[?1049h", stdout);
}
TR_API void tr_close_alt(void) {
    fputs("\x1b[?1049l", stdout);
}
// ============================================================================

// Cursor control
// ============================================================================
TR_API void tr_move_cursor(int x, int y) {
    if (x < 0 || y < 0)
        return;

    printf("\x1b[%d;%dH", y + 1, x + 1);
}
TR_API void tr_show_cursor(void) {
    fputs("\x1b[?25h", stdout);
}
TR_API void tr_hide_cursor(void) {
    fputs("\x1b[?25l", stdout);
}
// ============================================================================

// Effect
// ============================================================================

// TODO: Find a way to use `sizeof` instead of using constants.
#define TR_PRIV_ADD_EFFECTS_LEN 4
#define TR_PRIV_REMOVE_EFFECTS_LEN 5
#define TR_PRIV_RESET_EFFECTS_LEN 23
#define TR_PRIV_RESET_ALL_LEN 4

static const char tr_priv_add_effects_ansi[][TR_PRIV_ADD_EFFECTS_LEN + 1] = {
    "\x1b[1m",
    "\x1b[2m",
    "\x1b[3m",
    "\x1b[4m",
    "\x1b[5m",
    "\x1b[7m",
    "\x1b[8m",
    "\x1b[9m"
};
static const char tr_priv_remove_effects_ansi[][TR_PRIV_REMOVE_EFFECTS_LEN + 1] = {
    "\x1b[22m",
    "\x1b[22m",
    "\x1b[23m",
    "\x1b[24m",
    "\x1b[25m",
    "\x1b[27m",
    "\x1b[28m",
    "\x1b[29m"
};
static const char tr_priv_reset_effects_ansi[TR_PRIV_RESET_EFFECTS_LEN + 1] = "\x1b[22;23;24;25;27;28;29m";
static const char tr_priv_reset_all_ansi[TR_PRIV_RESET_ALL_LEN + 1] = "\x1b[0m";

TR_API void tr_add_effects(TrEffect effects) {
    if (effects == TR_DEFAULT_EFFECT) {
        tr_reset_effects();
        return;
    }
    for (int i = 0; i < TR_EFFECTS_LEN; i += 1) {
        if (effects & (TrEffect)(1 << i))
            fputs(tr_priv_add_effects_ansi[i], stdout);
    }
}
TR_API void tr_remove_effects(TrEffect effects) {
    for (int i = 0; i < TR_EFFECTS_LEN; i += 1) {
        if (effects & (TrEffect)(1 << i)) {
            fputs(tr_priv_remove_effects_ansi[i], stdout);
        }
    }
}
TR_API void tr_reset_effects(void) {
    fputs(tr_priv_reset_effects_ansi, stdout);
}
TR_API void tr_reset_all(void) {
    fputs(tr_priv_reset_all_ansi, stdout);
}
// ============================================================================

// Color
// ============================================================================
static const char *tr_priv_fg_ansi[] = {
    // fg
    "\x1b[%dm",
    "\x1b[38;5;%dm",
    "\x1b[38;2;%d;%d;%dm"
};
static const char *tr_priv_bg_ansi[] = {
    // bg
    "\x1b[%dm",
    "\x1b[48;5;%dm",
    "\x1b[48;2;%d;%d;%dm"
};

TR_API TrColor tr_default_color(void) {
    return (TrColor){
        .code = TR_DEFAULT_COLOR_16,
        .mode = TR_COLOR_16
    };
}
TR_API void tr_set_fg(uint32_t fg_color, TrColorMode fg_mode) {
    if (fg_color == TR_TRANSPARENT)
        return;

    switch (fg_mode) {
    case TR_COLOR_16:
    case TR_COLOR_256:
        printf(tr_priv_fg_ansi[fg_mode], fg_color);
        break;
    case TR_COLOR_TRUE:
        printf(tr_priv_fg_ansi[fg_mode], tr_rgb_r(fg_color), tr_rgb_g(fg_color), tr_rgb_b(fg_color));
        break;
    }
}
TR_API void tr_set_bg(uint32_t bg_color, TrColorMode bg_mode) {
    if (bg_color == TR_TRANSPARENT)
        return;

    switch (bg_mode) {
    case TR_COLOR_16:
        printf(tr_priv_bg_ansi[bg_mode], 10 + bg_color);
        break;
    case TR_COLOR_256:
        printf(tr_priv_bg_ansi[bg_mode], bg_color);
        break;
    case TR_COLOR_TRUE:
        printf(tr_priv_bg_ansi[bg_mode], tr_rgb_r(bg_color), tr_rgb_g(bg_color), tr_rgb_b(bg_color));
        break;
    }
}

// Color - Utility functions
// ----------------------------------------------------------------------------
TR_API uint32_t tr_gray_256(uint8_t scale) {
    return (scale > 23) ? 255 : (232 + scale);
}
TR_API uint32_t tr_rgb(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}
TR_API uint8_t tr_rgb_r(uint32_t rgb) {
    return (rgb >> 16) & 0xFF;
}
TR_API uint8_t tr_rgb_g(uint32_t rgb) {
    return (rgb >> 8) & 0xFF;
}
TR_API uint8_t tr_rgb_b(uint32_t rgb) {
    return rgb & 0xFF;
}
// ----------------------------------------------------------------------------
// ============================================================================

#ifndef TR_NO_RENDERER

// clang-format off
#if defined(TR_MALLOC) && defined(TR_FREE)
// ok
#elif !defined(TR_MALLOC) && !defined(TR_FREE)
    #include <stdlib.h>
    #define TR_MALLOC(sz) malloc(sz)
    #define TR_FREE(p) free(p)
#else
    #error "Must define all or none of TR_MALLOC, and TR_FREE."
#endif

#ifndef TR_CHK
    #define TR_CHK(x)                \
        do {                         \
            TrResult _r;             \
            if ((_r = (x)) != TR_OK) \
                return _r;           \
        } while (0)
#endif
// clang-format on

// Style
// ============================================================================
TR_API TrStyle tr_default_style(void) {
    return (TrStyle){
        .effects = TR_DEFAULT_EFFECT,
        .fg.code = TR_DEFAULT_COLOR_16,
        .fg.mode = TR_COLOR_16,
        .bg.code = TR_DEFAULT_COLOR_16,
        .bg.mode = TR_COLOR_16
    };
}
TR_API void tr_set_style(TrStyle style) {
    tr_add_effects(style.effects);
    tr_set_fg(style.fg.code, style.fg.mode);
    tr_set_bg(style.bg.code, style.bg.mode);
}
TR_API void tr_copy_style(TrStyle *dst, TrStyle src) {
    dst->effects = src.effects;
    dst->fg.code = src.fg.code;
    dst->fg.mode = src.fg.mode;
    dst->bg.code = src.bg.code;
    dst->bg.mode = src.bg.mode;
}
// ============================================================================

// Cell
// ============================================================================
TR_API TrResult tr_carr_init(TrCellArray *carr, int width, int height) {
    if (width <= 0 || height <= 0 || (width * height > TR_MAX_CELL_ARRAY_LEN)) {
        carr->width = 0;
        carr->height = 0;
        return TR_ERR_BAD_ARG;
    }

    carr->width = width;
    carr->height = height;

    tr_clear_buf(tr_atos(carr), TR_DEFAULT_COLOR_16, TR_COLOR_16);

    return TR_OK;
}
TR_API TrResult tr_cvec_init(TrCellVector *cvec, int width, int height) {
    if (width <= 0 || height <= 0) {
        cvec->width = 0;
        cvec->height = 0;
        return TR_ERR_BAD_ARG;
    }

    cvec->width = width;
    cvec->height = height;

    size_t len = (size_t)(width * height);

    cvec->letter = (char *)TR_MALLOC(len * sizeof(char));
    if (cvec->letter == NULL)
        return TR_ERR_ALLOC_FAIL;

    cvec->effects = (TrEffect *)TR_MALLOC(len * sizeof(TrEffect));
    if (cvec->effects == NULL)
        return TR_ERR_ALLOC_FAIL;

    cvec->fg = (TrColor *)TR_MALLOC(len * sizeof(TrColor));
    if (cvec->fg == NULL)
        return TR_ERR_ALLOC_FAIL;

    cvec->bg = (TrColor *)TR_MALLOC(len * sizeof(TrColor));
    if (cvec->bg == NULL)
        return TR_ERR_ALLOC_FAIL;

    tr_clear_buf(*cvec, TR_DEFAULT_COLOR_16, TR_COLOR_16);

    return TR_OK;
}
TR_API void tr_cvec_cleanup(TrCellVector *cvec) {
    if (cvec->letter != NULL) {
        TR_FREE(cvec->letter);
        cvec->letter = NULL;
    }
    if (cvec->effects != NULL) {
        TR_FREE(cvec->effects);
        cvec->effects = NULL;
    }
    if (cvec->fg != NULL) {
        TR_FREE(cvec->fg);
        cvec->fg = NULL;
    }
    if (cvec->bg != NULL) {
        TR_FREE(cvec->bg);
        cvec->bg = NULL;
    }
}
// ============================================================================

// Basic renderer
// ============================================================================
// Helper functions (private)
// ----------------------------------------------------------------------------
#define TR_PRIV_STRCAT_FMT(dst, dst_len, idx, fmt, ...)                      \
    do {                                                                     \
        int _i = snprintf(dst + (*idx), dst_len - (*idx), fmt, __VA_ARGS__); \
        size_t _s = _i > 0 ? (size_t)_i : 0;                                 \
        if (((*idx) + _s >= len - 1) || _s == 0)                             \
            return TR_ERR_BUF_OVERFLOW;                                      \
        (*idx) += _s;                                                        \
    } while (0)

static TrResult tr_priv_strcat(char *dst, size_t dst_len, size_t *idx, const char *src, size_t src_len) {
    if (*idx + src_len >= dst_len - 1)
        return TR_ERR_BUF_OVERFLOW;

    memcpy(dst + (*idx), src, src_len);
    *idx += src_len;

    return TR_OK;
}
#define TR_PRIV_STRCAT_FIXED(dst, dst_len, idx, src) tr_priv_strcat(dst, dst_len, idx, src, sizeof(src) - 1)

static TrResult tr_priv_emit_ansi(char *dst, size_t len, size_t *idx, TrStyle *curr, TrCellSpan sprite, int spr_idx) {
    if (curr->effects != sprite.effects[spr_idx]) {
        TR_CHK(tr_strcat_add_effects(dst, len, idx, sprite.effects[spr_idx] & ~curr->effects));
        TR_CHK(tr_strcat_remove_effects(dst, len, idx, curr->effects & ~sprite.effects[spr_idx]));
        curr->effects = sprite.effects[spr_idx];
    }

    if (curr->fg.code != sprite.fg[spr_idx].code || curr->fg.mode != sprite.fg[spr_idx].mode) {
        TR_CHK(tr_strcat_set_fg(dst, len, idx, sprite.fg[spr_idx].code, sprite.fg[spr_idx].mode));
        curr->fg.code = sprite.fg[spr_idx].code;
        curr->fg.mode = sprite.fg[spr_idx].mode;
    }

    if (curr->bg.code != sprite.bg[spr_idx].code || curr->bg.mode != sprite.bg[spr_idx].mode) {
        TR_CHK(tr_strcat_set_bg(dst, len, idx, sprite.bg[spr_idx].code, sprite.bg[spr_idx].mode));
        curr->bg.code = sprite.bg[spr_idx].code;
        curr->bg.mode = sprite.bg[spr_idx].mode;
    }

    return TR_OK;
}
// ----------------------------------------------------------------------------

// Cursor
// ----------------------------------------------------------------------------
TR_API TrResult tr_strcat_move_cursor(char *dst, size_t len, size_t *idx, int x, int y) {
    if (x < 0 || y < 0)
        return TR_ERR_BAD_ARG;

    TR_PRIV_STRCAT_FMT(dst, len, idx, "\x1b[%d;%dH", y + 1, x + 1);

    return TR_OK;
}
// ----------------------------------------------------------------------------

// Effect
// ----------------------------------------------------------------------------
TR_API TrResult tr_strcat_add_effects(char *dst, size_t len, size_t *idx, TrEffect effects) {
    if (effects == TR_DEFAULT_EFFECT) {
        TR_CHK(tr_strcat_reset_effects(dst, len, idx));
        return TR_OK;
    }
    for (int i = 0; i < TR_EFFECTS_LEN; i += 1) {
        if (effects & (TrEffect)(1 << i)) {
            TR_CHK(TR_PRIV_STRCAT_FIXED(dst, len, idx, tr_priv_add_effects_ansi[i]));
        }
    }

    return TR_OK;
}
TR_API TrResult tr_strcat_remove_effects(char *dst, size_t len, size_t *idx, TrEffect effects) {
    for (int i = 0; i < TR_EFFECTS_LEN; i += 1) {
        if (effects & (TrEffect)(1 << i)) {
            TR_CHK(TR_PRIV_STRCAT_FIXED(dst, len, idx, tr_priv_remove_effects_ansi[i]));
        }
    }

    return TR_OK;
}
TR_API TrResult tr_strcat_reset_effects(char *dst, size_t len, size_t *idx) {
    TR_CHK(TR_PRIV_STRCAT_FIXED(dst, len, idx, tr_priv_reset_effects_ansi));

    return TR_OK;
}
TR_API TrResult tr_strcat_reset_all(char *dst, size_t len, size_t *idx) {
    TR_CHK(TR_PRIV_STRCAT_FIXED(dst, len, idx, tr_priv_reset_all_ansi));

    return TR_OK;
}
// ----------------------------------------------------------------------------

// Color
// ----------------------------------------------------------------------------
TR_API TrResult tr_strcat_set_fg(char *dst, size_t len, size_t *idx, uint32_t fg_color, TrColorMode fg_mode) {
    if (fg_color == TR_TRANSPARENT)
        return TR_OK;

    switch (fg_mode) {
    case TR_COLOR_16:
    case TR_COLOR_256:
        TR_PRIV_STRCAT_FMT(dst, len, idx, tr_priv_fg_ansi[fg_mode], fg_color);
        break;
    case TR_COLOR_TRUE:
        TR_PRIV_STRCAT_FMT(dst, len, idx, tr_priv_fg_ansi[fg_mode], tr_rgb_r(fg_color), tr_rgb_g(fg_color), tr_rgb_b(fg_color));
        break;
    }

    return TR_OK;
}
TR_API TrResult tr_strcat_set_bg(char *dst, size_t len, size_t *idx, uint32_t bg_color, TrColorMode bg_mode) {
    if (bg_color == TR_TRANSPARENT)
        return TR_OK;

    switch (bg_mode) {
    case TR_COLOR_16:
        TR_PRIV_STRCAT_FMT(dst, len, idx, tr_priv_bg_ansi[bg_mode], 10 + bg_color);
        break;
    case TR_COLOR_256:
        TR_PRIV_STRCAT_FMT(dst, len, idx, tr_priv_bg_ansi[bg_mode], bg_color);
        break;
    case TR_COLOR_TRUE:
        TR_PRIV_STRCAT_FMT(dst, len, idx, tr_priv_bg_ansi[bg_mode], tr_rgb_r(bg_color), tr_rgb_g(bg_color), tr_rgb_b(bg_color));
        break;
    }

    return TR_OK;
}
// ----------------------------------------------------------------------------

// Rendering functions
// ----------------------------------------------------------------------------
TR_API TrResult tr_draw_sprite(TrCellSpan sprite, int x, int y) {
    if (sprite.width <= 0 || sprite.height <= 0 || x < 0 || y < 0)
        return TR_ERR_BAD_ARG;

    TrStyle curr = {
        .effects = TR_DEFAULT_EFFECT,
        .fg.code = TR_DEFAULT_COLOR_16,
        .fg.mode = TR_COLOR_16,
        .bg.code = TR_DEFAULT_COLOR_16,
        .bg.mode = TR_COLOR_16,
    };
    size_t raw_buf_idx = 0;
    char raw_buf[TR_MAX_RAW_BUFFER_LEN];

    for (int row = 0; row < sprite.height; row += 1) {
        TR_CHK(tr_strcat_move_cursor(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, x, y + row));

        for (int col = 0; col < sprite.width; col += 1) {
            int spr_idx = col + row * sprite.width; // [spr_idx] == [row][col]

            TR_CHK(tr_priv_emit_ansi(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, &curr, sprite, spr_idx));

            raw_buf[raw_buf_idx++] = sprite.letter[spr_idx];
            if (raw_buf_idx >= TR_MAX_RAW_BUFFER_LEN - 1)
                return TR_ERR_BUF_OVERFLOW;
        }

        if (curr.bg.code != TR_DEFAULT_COLOR_16 || curr.bg.mode != TR_COLOR_16) {
            curr.bg.code = TR_DEFAULT_COLOR_16;
            curr.bg.mode = TR_COLOR_16;
            TR_CHK(tr_strcat_set_bg(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, curr.bg.code, curr.bg.mode));
        }
    }
    TR_CHK(tr_strcat_reset_all(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx));

    raw_buf[raw_buf_idx] = '\0';
    fputs(raw_buf, stdout);

    return TR_OK;
}
TR_API TrResult tr_draw_spritesheet(TrCellSpan ss, int spr_x, int spr_y, int spr_w, int spr_h, int x, int y) {
    // Spritesheet and position validation
    if (ss.width <= 0 || ss.height <= 0 || x < 0 || y < 0)
        return TR_ERR_BAD_ARG;

    // Sprite validation
    if (spr_w <= 0 || spr_h <= 0 ||
        spr_x < 0 || spr_x >= ss.width ||
        spr_y < 0 || spr_y >= ss.height ||
        (spr_x + spr_w > ss.width) ||
        (spr_y + spr_h > ss.height))
        return TR_ERR_BAD_ARG;

    TrStyle curr = {
        .effects = TR_DEFAULT_EFFECT,
        .fg.code = TR_DEFAULT_COLOR_16,
        .fg.mode = TR_COLOR_16,
        .bg.code = TR_DEFAULT_COLOR_16,
        .bg.mode = TR_COLOR_16,
    };
    size_t raw_buf_idx = 0;
    char raw_buf[TR_MAX_RAW_BUFFER_LEN];

    for (int row = 0; row < spr_h; row += 1) {
        TR_CHK(tr_strcat_move_cursor(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, x, y + row));

        int spr_row_base = spr_x + (spr_y + row) * ss.width; // [spr_row_base] == [spr_y + row][spr_x]

        for (int col = 0; col < spr_w; col += 1) {
            int spr_idx = col + spr_row_base; // [spr_idx] == [spr_y + row][spr_x + col]

            TR_CHK(tr_priv_emit_ansi(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, &curr, ss, spr_idx));

            raw_buf[raw_buf_idx++] = ss.letter[spr_idx];
            if (raw_buf_idx >= TR_MAX_RAW_BUFFER_LEN - 1)
                return TR_ERR_BUF_OVERFLOW;
        }

        if (curr.bg.code != TR_DEFAULT_COLOR_16 || curr.bg.mode != TR_COLOR_16) {
            curr.bg.code = TR_DEFAULT_COLOR_16;
            curr.bg.mode = TR_COLOR_16;
            TR_CHK(tr_strcat_set_bg(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, curr.bg.code, curr.bg.mode));
        }
    }
    TR_CHK(tr_strcat_reset_all(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx));

    raw_buf[raw_buf_idx] = '\0';
    fputs(raw_buf, stdout);

    return TR_OK;
}
TR_API TrResult tr_draw_text(const char *text, TrStyle style, int x, int y) {
    if (!text || y < 0)
        return TR_ERR_BAD_ARG;

    size_t raw_buf_idx = 0;
    char raw_buf[TR_MAX_RAW_BUFFER_LEN];

    TR_CHK(tr_strcat_move_cursor(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, x, y));
    TR_CHK(tr_strcat_reset_effects(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx));
    TR_CHK(tr_strcat_add_effects(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, style.effects));
    TR_CHK(tr_strcat_set_fg(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, style.fg.code, style.fg.mode));
    TR_CHK(tr_strcat_set_bg(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, style.bg.code, style.bg.mode));

    TR_CHK(tr_priv_strcat(raw_buf, TR_MAX_RAW_BUFFER_LEN, &raw_buf_idx, text, strlen(text)));

    raw_buf[raw_buf_idx] = '\0';
    fputs(raw_buf, stdout);

    return TR_OK;
}
// ----------------------------------------------------------------------------
// ============================================================================

// Frame buffers
// ============================================================================
// Helper functions (private)
// ----------------------------------------------------------------------------
static void tr_priv_get_visible(int *result_size, int *result_idx, int fb_size, int size, int pos) {
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
static bool tr_priv_ctx_memcmp(const TrRenderContext *ctx, int idx, size_t len) {
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
static bool tr_priv_ctx_cmp(const TrRenderContext *ctx, int idx) {
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
static void tr_priv_get_dirty_rect(int *x, int *y, int *width, int *height, const TrRenderContext *ctx) {
    int left = ctx->width - 1;
    int top = ctx->height - 1;
    int right = 0;
    int bottom = 0;

    for (int row = 0; row < ctx->height; row += 1) {
        int fb_row_base = 0 + row * ctx->width; // [fb_row_base] == [row][0]

        if (tr_priv_ctx_memcmp(ctx, fb_row_base, (size_t)(ctx->width)))
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
static void tr_priv_ctx_swap(TrRenderContext *ctx) {
    size_t len = (size_t)(ctx->width * ctx->height);

    memcpy(ctx->front.letter, ctx->back.letter, len * sizeof(char));
    memcpy(ctx->front.effects, ctx->back.effects, len * sizeof(TrEffect));
    memcpy(ctx->front.fg, ctx->back.fg, len * sizeof(TrColor));
    memcpy(ctx->front.bg, ctx->back.bg, len * sizeof(TrColor));
}
// ----------------------------------------------------------------------------
TR_API TrResult tr_ctx_init(TrRenderContext *ctx, int x, int y, int width, int height) {
    if (x < 0 || y < 0 || width <= 0 || height <= 0 || (width * height > TR_MAX_FRAMEBUFFER_LEN)) {
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
TR_API void tr_ctx_clear(TrRenderContext *ctx, uint32_t bg_color, TrColorMode bg_mode) {
    tr_clear_buf(tr_ftos(&ctx->back, ctx->width, ctx->height), bg_color, bg_mode);
}
TR_API TrResult tr_ctx_render(TrRenderContext *ctx) {
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
TR_API TrResult tr_ctx_draw_rect(TrRenderContext *ctx, int x, int y, int width, int height, uint32_t color, TrColorMode color_mode) {
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

        memset(ctx->back.letter + fb_row_base, ' ', (size_t)visible_width * sizeof(char));
        memset(ctx->back.effects + fb_row_base, TR_DEFAULT_EFFECT, (size_t)visible_width * sizeof(TrEffect));

        for (int col = 0; col < visible_width; col += 1) {
            int idx = col + fb_row_base; // [idx] == [y + row][x + col]

            ctx->back.fg[idx].code = color;
            ctx->back.fg[idx].mode = color_mode;
            ctx->back.bg[idx].code = color;
            ctx->back.bg[idx].mode = color_mode;
        }
    }

    return TR_OK;
}
TR_API TrResult tr_ctx_draw_sprite(TrRenderContext *ctx, TrCellSpan sprite, int x, int y) {
    if (sprite.width <= 0 || sprite.height <= 0)
        return TR_ERR_BAD_ARG;

    int visible_width = 0;
    int spr_col = 0;
    tr_priv_get_visible(&visible_width, &spr_col, ctx->width, sprite.width, x);
    if (visible_width <= 0)
        return TR_OK;

    int visible_height = 0;
    int spr_row = 0;
    tr_priv_get_visible(&visible_height, &spr_row, ctx->height, sprite.height, y);
    if (visible_height <= 0)
        return TR_OK;

    int fb_base = (x > 0 ? x : 0) + (y > 0 ? y : 0) * ctx->width; // [fb_base] == [y or 0][x or 0]
    int spr_base = spr_col + spr_row * sprite.width;              // [spr_base] == [spr_row][spr_col]

    for (int row = 0; row < visible_height; row += 1) {
        int fb_row_base = fb_base + row * ctx->width;     // [fb_row_base] == [y + row][x]
        int spr_row_base = spr_base + row * sprite.width; // [spr_row_base] == [spr_row + row][spr_col]

        memcpy(ctx->back.letter + fb_row_base, sprite.letter + spr_row_base, (size_t)visible_width * sizeof(char));
        memcpy(ctx->back.effects + fb_row_base, sprite.effects + spr_row_base, (size_t)visible_width * sizeof(TrEffect));

        for (int col = 0; col < visible_width; col += 1) {
            int spr_idx = col + spr_row_base; // [spr_idx] == [spr_row + row][spr_col + col]

            if (sprite.fg[spr_idx].code != TR_TRANSPARENT) {
                int fb_idx = col + fb_row_base; // [fb_idx] == [y + row][x + col]

                ctx->back.fg[fb_idx].code = sprite.fg[spr_idx].code;
                ctx->back.fg[fb_idx].mode = sprite.fg[spr_idx].mode;
            }
            if (sprite.bg[spr_idx].code != TR_TRANSPARENT) {
                int fb_idx = col + fb_row_base; // [fb_idx] == [y + row][x + col]

                ctx->back.bg[fb_idx].code = sprite.bg[spr_idx].code;
                ctx->back.bg[fb_idx].mode = sprite.bg[spr_idx].mode;
            }
        }
    }

    return TR_OK;
}
TR_API TrResult tr_ctx_draw_text(TrRenderContext *ctx, const char *text, size_t len, TrStyle style, int x, int y) {
    if (len <= 0 || y < 0 || y >= ctx->height)
        return TR_ERR_BAD_ARG;

    int visible_len = 0;
    int text_idx = 0;
    tr_priv_get_visible(&visible_len, &text_idx, ctx->width, (int)len, x);
    if (visible_len <= 0)
        return TR_OK;

    int fb_base = (x > 0 ? x : 0) + (y > 0 ? y : 0) * ctx->width; // [fb_base] == [y or 0][x or 0]

    memcpy(ctx->back.letter + fb_base, text + text_idx, (size_t)visible_len * sizeof(char));

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
// Type conversion
// ----------------------------------------------------------------------------
TR_API TrCellSpan tr_atos(TrCellArray *carr) {
    return (TrCellSpan){
        .letter = (char *)carr->letter,
        .effects = (TrEffect *)carr->effects,
        .fg = (TrColor *)carr->fg,
        .bg = (TrColor *)carr->bg,
        .width = carr->width,
        .height = carr->height
    };
}
TR_API TrCellSpan tr_ftos(TrFramebufferBase *fb, int width, int height) {
    return (TrCellSpan){
        .letter = (char *)fb->letter,
        .effects = (TrEffect *)fb->effects,
        .fg = (TrColor *)fb->fg,
        .bg = (TrColor *)fb->bg,
        .width = width,
        .height = height
    };
}
// ----------------------------------------------------------------------------

// Cell buffer
// ----------------------------------------------------------------------------
TR_API void tr_clear_buf(TrCellSpan buf, uint32_t bg_color, TrColorMode bg_mode) {
    size_t len = (size_t)(buf.width * buf.height);

    memset(buf.letter, ' ', len * sizeof(char));
    memset(buf.effects, TR_DEFAULT_EFFECT, len * sizeof(TrEffect));

    for (size_t i = 0; i < len; i += 1) {
        buf.fg[i].code = TR_DEFAULT_COLOR_16;
        buf.fg[i].mode = TR_COLOR_16;
        buf.bg[i].code = bg_color;
        buf.bg[i].mode = bg_mode;
    }
}
// ============================================================================
#endif // TR_NO_RENDERER

#endif // TR_IMPLEMENTATION
