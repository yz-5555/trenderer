# trenderer
Header-only ANSI library for drawing your idea in your terminal easily.

## Features
- **Beginner-friendly.**
- Cross-platform.
- Header-only and single-file.
- Free and open-source.
- I don't know if I'm putting hyphens correctly.
- Plain C99, no external dependencies.
- All color formats (ANSI 16, ANSI 256, True color) support.
- Various ANSI effects (e.g. BOLD, ITALIC, UNDERLINE, ...) support.
- Optimized rendering using framebuffer.
- Easy error handling.
- Minimal usage of macros.
- Made with heart.

## Installation & Usage
Just add `trenderer.h` to your project and it's good to go.

Do this:
```c
#define TRENDERER_IMPLEMENTATION
```
before you include `trenderer.h` **one** C or C++ file to create the implmentation.

Check the comments in the header for detailed info.

## Basic example
### Easy and simple ANSI usage
```c
#define TRENDERER_IMPLEMENTATION
#include "trenderer.h"

#include <stdio.h>

int main(void) {
    tr_add_effects(TR_UNDERLINE | TR_BOLD);      // Add effects.
    tr_set_fg(tr_rgb(255, 0, 0), TR_COLOR_TRUE); // Set foreground color to red using rgb (True colors)
    tr_set_bg(TR_BLUE_256, TR_COLOR_256);        // Set background color to blue using ANSI 256.
    printf("Hello, ");

    tr_remove_effects(TR_UNDERLINE);            // Remove effects.
    tr_add_effects(TR_BLINK);
    tr_set_bg(TR_BRIGHT_GREEN_16, TR_COLOR_16); // Set background color to bright green using ANSI 16.
    printf("World!");

    tr_reset_all(); // Reset effects, fg, bg to default.

    return 0;
}
```
### Optimized rendering for games and apps. (Double-buffering)
```c
#define TRENDERER_IMPLEMENTATION
#include "trenderer.h"

#include <conio.h>
#define ESC 27

int main(void) {
    TrRenderContext ctx;
    tr_ctx_init(&ctx, 0, 0, 50, 10);

    tr_open_alt(); // Open the alternative buffer
    tr_hide_cursor();
    while (1) {
        tr_ctx_clear(&ctx, TR_WHITE_16, TR_COLOR_16);

        // Draw an orange rect in the middle.
        tr_ctx_draw_rect(&ctx, 10, 3, 30, 4, TR_ORANGE, TR_COLOR_TRUE);

        tr_ctx_render(&ctx);

        if (_kbhit() && _getch() == ESC)
            break;
    }
    tr_close_alt(); // Close the alternative buffer

    return 0;
}
```
More examples in [./examples](https://github.com/yz-5555/trenderer/tree/main/examples)

## Notes
- Effects and colors may look different depending on your terminal. Check if yours support them.
- This is not a TUI library, it does not have widgets.
- Developed and tested on [wezterm](https://github.com/wezterm/wezterm), Windows 11 and clang-cl.

## Limitations
- No unicodes support.
- No z-buffer support.
- No image support.
- No complex OS specific window handling.

## Todo
- [ ] improved documents and comments.
- [ ] More demos
- [ ] unicodes supoort.
- [ ] z-buffer support.
- [ ] OS specific validations.

## Design goals
**1. Minimal abstraction**

It's explicit, straightforward. No hidden logic or global variables. Only necessary macros and typedefs.

**2. Your library**

It's under your control. It does not force you the way how you code. You can modify constants by defining them before including it.

**3. No need to learn**

It's designed to be easy to understand and make you focus on your own project rather than understanding mine. (At least I tried to)

## Inspiration
Library design and code structure inspired by [raylib](https://github.com/raysan5/raylib), [raygui](https://github.com/raysan5/raygui) and OpenGL.
