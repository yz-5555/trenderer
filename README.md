# trenderer
A minimal, portable single-header C library for terminals.

## Features
- **Beginner-friendly.**
- Cross-platform.
- Single-header.
- Free and open-source.
- Minimal, portable, explicit.
- Plain C99, no external dependencies.
- All color formats (ANSI 16, ANSI 256, True color) support.
- Various ANSI effects (e.g. BOLD, ITALIC, UNDERLINE, ...) support.
- Highly customizable.
- No global or hidden state.

## Limitations
- No widgets.
- Not thread-safe.
- No input system.
- Partial unicode support. Wide characters and emojis are not supported.
- No z-buffer support.
- No transformations.
- No 3D support.

## Installation & Usage
Just add `trenderer.h` to your project and it's good to go.

Do this:
```c
#define TR_IMPLEMENTATION
```
before you include `trenderer.h` **one** C or C++ file to create the implementation.

Check the comments in the header for detailed info.

## Basic examples
### Easy and simple ANSI usage
```c
#define TR_NO_RENDERER
#define TR_IMPLEMENTATION
#include "trenderer.h"

#include <stdio.h>

int main(void) {
    tr_init(false); // Flush old buffers to prevent unwanted output.

    tr_add_effects(TR_UNDERLINE | TR_BOLD); // Add effects.
    tr_set_fg(tr_rgb(255, 0, 0));           // Set foreground color to red using rgb(True colors).
    tr_set_bg(TR_BLUE_256);                 // Set background color to blue using ANSI 256.
    printf("Hello, ");

    tr_remove_effects(TR_UNDERLINE); // Remove effects.
    tr_add_effects(TR_BLINK);
    tr_set_bg(TR_BRIGHT_GREEN_16);   // Set background color to bright green using ANSI 16.
    printf("World!");

    tr_reset_all(); // Reset effects, fg, bg to default.

    return 0;
}
```
### Optimized rendering for games and apps.
```c
#define TR_IMPLEMENTATION
#include "trenderer.h"

#include <conio.h>
#define ESC 27

int main(void) {
    TrRenderContext ctx;
    tr_ctx_init(&ctx, 0, 0, 50, 10);

    tr_init(false); // tr_init(true); if you want to use unicode.

    tr_open_alt(); // Open the alternative buffer.
    tr_hide_cursor();
    while (1) {
        if (_kbhit() && _getch() == ESC)
            break;
        
        tr_ctx_clear(&ctx, TR_WHITE_16);
        tr_ctx_draw_rect(&ctx, 10, 3, 30, 4, TR_ORANGE); // Draws an orange rect in the middle.
        tr_ctx_render(&ctx);
    }
    tr_close_alt(); // Closes the alternative buffer.

    return 0;
}
```
More examples in [./examples](https://github.com/yz-5555/trenderer/tree/main/examples)

> [!NOTE]
> Effects and colors may look different depending on your terminal. Check if yours support them.

## License
trenderer is licensed under MIT License. See [LICENSE](https://github.com/yz-5555/trenderer/blob/main/LICENSE) for more info.

## Inspiration
Library design and code structure inspired by [nuklear](https://github.com/Immediate-Mode-UI/Nuklear), [stb](https://github.com/nothings/stb) and OpenGL.
