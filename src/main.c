#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/display.h"

// Global Variables
bool is_running = true;


void setup(){
	// Initialize SDL
	is_running = init_window();
}

void process_input(){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			is_running = false;
		}
		if(event.key.keysym.sym == SDLK_ESCAPE){
			is_running = false;
		}	
	}
}

void update(){
}

void render(){
	clear_color_buffer(0xFF000000);
	render_color_buffer();
}




int main(void){

	setup();

	while(is_running){
		process_input();
		update();
		render();
	}
}


