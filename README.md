# TRENDERER
It's tee-renderer. Or might be trendy enough to call it trenderer.

## Why TRENDERER?
  - Beginner friendly.
  - Cross-platform.
  - Header-only.
  - I am too lazy to test. (Might include bugs, but currently not found.)

## Key features
#### 1. Adding styles to console.
```c
void tr_effect(TrEffect e); // BOLD, DIM, UNDERLINE, BLINK, INVERT, HIDDEN, STRIKETHROUGH
void tr_fg_color(TrColor c, bool bright); // BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
void tr_bg_color(TrColor c, bool bright);
void tr_reset(void);
```
#### 2. Rendering text based sprites & pixels.
```c
void tr_draw_pixel(TrPixel pixel);
void tr_draw_sprite(const TrPixel *sprite, int x, int y, int width, int height);
```
#### 3. More controls
```c
void tr_clear(void);
void tr_cursor_move(int x, int y);
void tr_cursor_visible(bool visible);
```
## Installation
Just add `trenderer.h` to your project and it's good to go.

## Todo
- [ ] Add more example codes.
