#include "print.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = COLOR_WHITE | COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for(size_t col=0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void screen_clear() {
    for(size_t i=0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void println() {
    col = 0;

    if(row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for(size_t row=1; row < NUM_ROWS; row++) {
        for(size_t col=0; col<NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_ROWS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void printchar(char character) {
    if(character == '\n') {
        println();
        return;
    }

    if(col > NUM_COLS) {
        println();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void printstr(char* str) {
    for(size_t i=0; 1; i++) {
        char character = (uint8_t) str[i];

        if(character == '\0') {
            return;
        }

        printchar(character);
    }
}


void screen_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}