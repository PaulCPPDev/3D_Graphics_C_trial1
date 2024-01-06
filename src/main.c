#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/display.h"

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

// Global Variables
bool is_running = false;
int previous_frame_time = 0;


void setup(){
	// Initialize SDL
	is_running = init_window();
}

void process_input(){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				is_running = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					is_running = false;
				break;
		}
	}
}

void update(){
	// fix the time step
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
	if( time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
		SDL_Delay(time_to_wait);
	previous_frame_time = SDL_GetTicks();
}

void render(){
	clear_color_buffer(0xFF000000);

	draw_rect(100,100, 200, 100, 0xFFFF00FF);
	render_color_buffer();
}



void free_resources(void){
	destroy_window();
}

int main(void){

	setup();

	while(is_running){
		process_input();
		update();
		render();
	}
	
	free_resources();
	return 0;
}


