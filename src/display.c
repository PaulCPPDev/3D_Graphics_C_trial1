#include "../include/display.h"
#include <math.h>


static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
int window_width = 800;
int window_height = 600;

static uint32_t* color_buffer = NULL;
static SDL_Texture* color_buffer_texture = NULL;



void render_color_buffer(void)	{
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int) (window_width * sizeof(uint32_t)));
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}


void clear_color_buffer(uint32_t color){
	int size = window_width * window_height;
	for(int i = 0; i < size; i++ )
		color_buffer[i] = color;
}

int get_window_width(void) {
    return window_width;
}

int get_window_height(void) {
    return window_height;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// DRAWING /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_grid(void) {
    for (int y = 0; y < window_height; y += 10) {
        for (int x = 0; x < window_width; x += 10) {
            color_buffer[(window_width * y) + x] = 0xFF444444;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color){
	if(x >= 0 && x < window_width && y >= 0 && y < window_height)
		color_buffer[(window_width*y)+x] = color;
}

void draw_rect(int x, int y, int width, int height, uint32_t color){
	for (int i = 0; i< width; i++){
		for (int j = 0; j< height; j++){
			int current_x = x + i;
			int current_y = y + j;
			draw_pixel(current_x, current_y, color);
		}
	}
} 


void draw_line(int x0, int y0, int x1, int y1,  uint32_t color){
	// DDA line drawing algorithm
	//
	// calculate rise and run
	int dx = (x1 - x0);
	int dy = (y1 - y0);
	//
	// get the steps
	int steps = fmax( abs(dx), abs(dy)  );
	
	//
	// calculate x and y increments
	float xIncrement = dx / (float)steps;
	float yIncrement = dy / (float)steps;
	//
	// starting position
	float x_current = x0;
	float y_current = y0;

	// loop every point and draw it
	for(int i = 0; i<= steps; i++){
		draw_pixel(round(x_current), round(y_current), color);
		x_current += xIncrement;
		y_current += yIncrement;
	}

}






bool init_window(void){
	// Initialize everything in the SDL window
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		fprintf(stderr, "Error Initializing SDL.\n");
		return false;
	}

	// Set width and height of SDL window to max Screen Resolution
	SDL_DisplayMode display_mode;
    	SDL_GetCurrentDisplayMode(0, &display_mode);
    	window_width = display_mode.w;
    	window_height = display_mode.h;

	// create window
	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			window_width,
			window_height,
			SDL_WINDOW_BORDERLESS // Borderless does not work yet
			);
	if(window == NULL){
		printf("Error Initializing SDL_Window\nerro = %s\n", SDL_GetError());
		return false;
	}
		
	// create renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer==NULL){
		printf("Error Initializing SDL_Renderer\nerro = %s\n", SDL_GetError());
		return false;
	}

	// initialize the color buffer
	color_buffer = (uint32_t*) malloc( sizeof(uint32_t) * window_width * window_height );

	// color buffer texture
	color_buffer_texture = SDL_CreateTexture(
				renderer, 
				SDL_PIXELFORMAT_RGBA32, 
				SDL_TEXTUREACCESS_STREAMING,
				window_width,
				window_height
			);

	return true;
}


void destroy_window(void){
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
