#include "../include/display.h"


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


bool init_window(void){
	// Initialize everything in the SDL window
	if(SDL_Init(SDL_INIT_EVERYTHING)==0){
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
				SDL_WINDOW_SHOWN // Borderless does not work yet
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
	else{
		printf("Error Initializing SDL\nerror = %s\n", SDL_GetError());
		return false;
	}
}


void free_resources(void){
	free(color_buffer_texture);

	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
