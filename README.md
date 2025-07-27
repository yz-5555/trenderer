# trenderer
Another ANSI library for awesome text rendering in your terminal.

## Features
  - Beginner-friendly.
  - Cross-platform.
  - Header-only and single-file.
  - Free and open-source.
  - I don't know if I'm putting hyphens correctly.
  - Plain C99, no external dependencies.
  - All color formats (ANSI 16, ANSI 256, True colors) support.
  - Various ANSI effects (e.g. BOLD, ITALIC, UNDERLINE) support.
  - Optimized rendering using frame buffers.
  - Minimal usage of macros.
  - Made with heart.

## Installation & Usage
Just add `trenderer.h` to your project and it's good to go.

Do this:
```c
#define TRENDERER_IMPLMENTATION
```
before you include `trenderer.h` **one** C or C++ file to create the implmentation.

Check the comments in the header for detailed info.

## Basic example
```c
#define TRENDERER_IMPLMENTATION
#include "trenderer.h"

int main(void) {
    TrRenderContext ctx;
    tr_ctx_init(&ctx, 50, 10);

    while (true) {
        tr_ctx_clear(&ctx, TR_DEFAULT_COLOR_16, TR_COLOR_16);

        // Draw an orange rectangle.
        tr_ctx_draw_rect(&ctx, 0, 0, 50, 10, TR_ORANGE, TR_COLOR_TRUE);

        tr_ctx_render(&ctx);
    }

    return 0;
}
```

## Notes
Effects and colors may look different depending on your terminal. Check if yours support them.

## Limitations
  - No unicodes support.
  - No z-buffer support.

## Todo
- [ ] debugging functions
- [ ] documents and comments
- [ ] z-buffer support
- [ ] OS specific validations

## Credits
Library design and code structure inspired by [raylib](https://github.com/raysan5/raylib), [raygui](https://github.com/raysan5/raygui) and OpenGL.
