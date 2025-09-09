# trenderer
A minimal, portable software renderer for terminals.

## Features
- **Beginner-friendly.**
- Cross-platform.
- Single-header.
- Free and open-source.
- Plain C99, no external dependencies.
- All color formats (ANSI 16, ANSI 256, True color) support.
- Various ANSI effects (e.g. BOLD, ITALIC, UNDERLINE, ...) support.
- Highly customizable.
- No global or hidden state.

## Limitations
- No widgets.
- No input system.
- No unicodes support.
- No z-buffer support.
- No OS-specific validations.

## Todo
- [ ] Improved documents and comments.
- [ ] More examples.
- [ ] Unicodes supoort.
- [ ] Z-buffer support.
- [ ] OS-specific validations.

## Installation & Usage
Just add `trenderer.h` to your project and it's good to go.

Do this:
```c
#define TR_IMPLEMENTATION
```
before you include `trenderer.h` **one** C or C++ file to create the implementation.

Check the comments in the header for detailed info.

## Basic example
### Easy and simple ANSI usage
```c
#define TR_IMPLEMENTATION
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
#define TR_IMPLEMENTATION
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
- Developed and tested on [wezterm](https://github.com/wezterm/wezterm), Windows 11 and clang.

## Inspiration
Library design and code structure inspired by [nuklear](https://github.com/Immediate-Mode-UI/Nuklear), [stb](https://github.com/nothings/stb) and OpenGL.
