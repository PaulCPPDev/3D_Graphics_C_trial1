#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

void render_color_buffer(void);
void clear_color_buffer(uint32_t color);

void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);

bool init_window(void);
void destroy_window(void);

int get_window_width(void) ;
int get_window_height(void);
void draw_grid(void);


#endif
