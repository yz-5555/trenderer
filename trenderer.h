#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum TrEffect {
    TR_PLAIN = -1,
    TR_BOLD = 1,
    TR_DIM = 2,
    TR_ITALIC = 3,
    TR_UNDERLINE = 4,
    TR_BLINK = 5,
    TR_REVERSE = 7,
    TR_HIDE = 8,
    TR_STRIKETHROUGH = 9,
    TR_TEXTBRIGHT = -2,
    TR_BGBRIGHT = -3,
} TrEffect;

typedef enum TrColor {
    TR_BLACK = 30,
    TR_RED = 31,
    TR_GREEN = 32,
    TR_YELLOW = 33,
    TR_BLUE = 34,
    TR_MAGENTA = 35,
    TR_CYAN = 36,
    TR_WHITE = 37,
    TR_DEFAULT = 39
} TrColor;

typedef struct TrStyle {
    TrEffect effects;
    TrColor text_color;
    TrColor bg_color;
} TrStyle;

typedef struct TrChar {
    char data;
    TrStyle style;
} TrChar;

typedef struct TrImage {
    TrChar *data;
    int width;
    int height;
} TrImage;

void tr_char_init(TrChar *c);

TrImage *tr_image_create(int width, int height);
void tr_image_fill(TrImage *image, char ch, TrEffect effects, TrColor text_color, TrColor bg_color);
void tr_image_free(TrImage *image);
void tr_image_draw(const TrImage *image);

void tr_style_begin(TrEffect effects, TrColor text_color, TrColor bg_color);
void tr_style_end(void);
bool tr_style_compare(const TrStyle *a, const TrStyle *b);

#ifdef TRENDERER_IMPLEMENTATION
void tr_char_init(TrChar *c) {
    if (c == NULL)
        return;
    c->data = ' ';
    c->style.effects = TR_PLAIN;
    c->style.text_color = TR_DEFAULT;
    c->style.bg_color = TR_DEFAULT;
}
TrImage *tr_image_create(int width, int height) {
    TrImage *image = malloc(sizeof(TrImage));
    image->data = malloc(sizeof(TrChar) * (width + height));
    image->width = width;
    image->height = height;

    return image;
}
void tr_image_fill(TrImage *image, char ch, TrEffect effects, TrColor text_color, TrColor bg_color) {
    for (int i = 0; i < image->width * image->height; i += 1) {
        image->data[i].data = ch;
        image->data[i].style.effects = effects;
        image->data[i].style.text_color = text_color;
        image->data[i].style.bg_color = bg_color;
    }
}
void tr_image_free(TrImage *image) {
    free(image->data);
    free(image);
}
void tr_image_draw(const TrImage *image) {
    TrStyle curr = {
        .effects = TR_PLAIN,
        .text_color = TR_DEFAULT,
        .bg_color = TR_DEFAULT};

    for (int y = 0; y < image->height; y += 1) {
        tr_style_begin(curr.effects, curr.text_color, curr.bg_color);
        for (int x = 0; x < image->width; x += 1) {
            int i = y * image->height + x;

            if (tr_style_compare(&image->data[i].style, &curr))
                continue;

            tr_style_end();

            curr.effects = image->data[i].style.effects;
            curr.text_color = image->data[i].style.text_color;
            curr.bg_color = image->data[i].style.bg_color;

            tr_style_begin(curr.effects, curr.text_color, curr.bg_color);
        }
        tr_style_end();
        printf("\n");
    }
}
void tr_style_begin(TrEffect effects, TrColor text_color, TrColor bg_color) {
    int e = (int)effects;
    int t = (int)text_color;
    if (effects == TR_TEXTBRIGHT)
        t += 60;
    int b = (int)bg_color + 10;
    if (effects == TR_BGBRIGHT)
        b += 60;
    printf("\x1b[%d;%dm", t, b);
}
void tr_style_end(void) {
    printf("\x1b[0m");
}
bool tr_style_compare(const TrStyle *a, const TrStyle *b) {
    if (a->effects != b->effects)
        return false;
    if (a->text_color != b->text_color)
        return false;
    if (a->bg_color != b->bg_color)
        return false;
    return true;
}
#endif

#endif
