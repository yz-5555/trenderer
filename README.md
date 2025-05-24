# TRENDERER
It's tee-renderer. Surely out of the trend to be trenderer

## Why TRENDERER?
  - Beginner friendly.
  - Cross-platform.
  - Header-only.
## Key features
#### 1. Adding styles to console.
```c
void tr_effect(TrEffect e); // BOLD, DIM, UNDERLINE, BLINK, INVERT, HIDDEN, STRIKETHROUGH
void tr_fg_color(TrColor c, bool bright); // BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
void tr_bg_color(TrColor c, bool bright);
```
#### 2. State renderer
```c
void tr_state_init(TrState *state);
void tr_state_add_effects(TrState *state, TrEffect effects);
void tr_state_remove_effects(TrState *state, TrEffect effects);
void tr_state_fg_color(TrState *state, TrColor fg_color, bool bright);
void tr_state_bg_color(TrState *state, TrColor bg_color, bool bright);
void tr_state_apply(TrState *state);
```
#### 3. Rendering text based sprites & pixels.
```c
void tr_draw_pixel(TrPixel pixel);
void tr_draw_sprite(const TrPixel *sprite, int x, int y, int width, int height);
```
#### 4. More controls
```c
void tr_clear(void); // Clear the screen
void tr_move_cursor(int x, int y);
void tr_show_cursor(bool visible);
```
## Installation
Just add `trenderer.h` to your project and it's good to go.

## Todo
- [ ] Add more example codes.
- [ ] Write detailed API docs.
- [ ] Add 256 colors support.
