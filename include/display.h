#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

void render_color_buffer(void);
void clear_color_buffer(uint32_t color);

bool init_window(void);
void free_resources(void);



#endif
