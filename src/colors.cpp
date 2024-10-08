#include <stdarg.h>
#include <stdio.h>

#include "colors.h"
#include "custom_assert.h"

enum printing_state_t {
    PRINTING_SUCCESS,
    PRINTING_FAILURE
};

//text colors
static const char *red_text     = "31";
static const char *green_text   = "32";
static const char *yellow_text  = "33";
static const char *blue_text    = "34";
static const char *magenta_text = "35";
static const char *cyan_text    = "36";
static const char *white_text   = "37";

//background colors
static const char *black_background  = "40";
static const char *red_background    = "41";
static const char *green_background  = "42";
static const char *yellow_background = "43";
static const char *blue_background   = "44";
static const char *purple_background = "45";
static const char *cyan_background   = "46";
static const char *white_background  = "47";

//bold flag
static const char *bold = "1";

//start of color code
static const char *color_code_start = "\033[";

static printing_state_t reset_color(void);
static printing_state_t print_color_code(color_t      color,
                                         boldness_t   is_bold,
                                         background_t background);
static void print_color_line(size_t height, background_t background);
static const char *background_code(background_t background);
static const char *color_code(color_t color);

int color_printf(color_t      color,
                 boldness_t   is_bold,
                 background_t background,
                 const char * format, ...) {
    C_ASSERT(format != NULL, return -1);

    print_color_code(color, is_bold, background);

    va_list args;
    va_start(args, format);
    int printed_symbols = vprintf(format, args);

    reset_color();
    va_end(args);
    return printed_symbols;
}

printing_state_t print_color_code(color_t      color,
                                  boldness_t   is_bold,
                                  background_t background) {
    printf("%s", color_code_start);
    if(is_bold == BOLD_TEXT) {
        printf("%s", bold);
        if(color != DEFAULT_TEXT || background != DEFAULT_BACKGROUND)
            putchar(';');

        else {
            putchar('m');
            return PRINTING_SUCCESS;
        }
    }
    if(color != DEFAULT_TEXT) {
        const char *code = color_code(color);
        C_ASSERT(code != NULL, );
        printf("%s", code);
        if(background != DEFAULT_BACKGROUND)
            putchar(';');
        else {
            putchar('m');
            return PRINTING_SUCCESS;
        }
    }
    if(background != DEFAULT_BACKGROUND) {
        const char *code = background_code(background);
        C_ASSERT(code != NULL, );
        printf("%sm", code);
        return PRINTING_SUCCESS;
    }
    return reset_color();
}

printing_state_t reset_color(void){
    if(printf("%s0m", color_code_start) <= 0)
        return PRINTING_FAILURE;
    return PRINTING_SUCCESS;
}

const char *color_code(color_t color) {
    switch(color) {
        case     RED_TEXT:
            return     red_text;
        case   GREEN_TEXT:
            return   green_text;
        case  YELLOW_TEXT:
            return  yellow_text;
        case    BLUE_TEXT:
            return    blue_text;
        case MAGENTA_TEXT:
            return magenta_text;
        case    CYAN_TEXT:
            return    cyan_text;
        case   WHITE_TEXT:
            return   white_text;
        case DEFAULT_TEXT:
            return NULL;
        default:
            return NULL;
    }
}

const char *background_code(background_t background) {
    switch(background) {
        case   BLACK_BACKGROUND:
            return  black_background;
        case     RED_BACKGROUND:
            return    red_background;
        case   GREEN_BACKGROUND:
            return  green_background;
        case  YELLOW_BACKGROUND:
            return yellow_background;
        case    BLUE_BACKGROUND:
            return   blue_background;
        case  PURPLE_BACKGROUND:
            return purple_background;
        case    CYAN_BACKGROUND:
            return   cyan_background;
        case   WHITE_BACKGROUND:
            return  white_background;
        case DEFAULT_BACKGROUND:
            return NULL;
        default:
            return NULL;
    }
}

void patriot() {
    const size_t line_height = 2;
    print_color_line(line_height, WHITE_BACKGROUND);
    print_color_line(line_height, BLUE_BACKGROUND );
    print_color_line(line_height, RED_BACKGROUND  );
    putchar('\n');
}

void print_color_line(size_t height, background_t background) {
    print_color_code(DEFAULT_TEXT, NORMAL_TEXT, background);
    for(size_t h = 0; h < height; h++)
        putchar('\n');
    reset_color();
}
