# TRENDERER
Another ANSI library for awesome text rendering in your terminal.

## Features
  - Beginner friendly.
  - Cross-platform.
  - Header-only.
  - Plain C99.
  - No external dependencies, only std headers used.
  - Open source.
  - All color formats (ANSI 16, ANSI 256, True colors) support.
  - All ANSI effects (e.g. BOLD, ITALIC, UNDERLINE) support.
  - Optimized rendering using frame buffers.
  - Minimal usage of macros.

## Installation & Usage
Just add `trenderer.h` to your project and it's good to go.

Do this:
```c
#define TRENDERER_IMPLMENTATION
```
before you include `trenderer.h` **one** C or C++ file to create the implmentation.
Check the comments in the header for detailed info.

## Notes
  - Effects and colors may look different depending on your terminal. Check if yours support them.

## Thanks to
Project and code structure inspired by [raylib](https://github.com/raysan5/raylib).
It's not that relevant but I just love raylib.
