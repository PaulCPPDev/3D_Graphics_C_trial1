#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/display.h"
#include "../include/vector.h"
#include "../include/camera.h"

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

// Global Variables
bool is_running = false;
int previous_frame_time = 0;


//HAND MADE CUBE
#define N_POINTS (9 * 9 * 9)
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
float fov_factor = 640;
vec3_t cube_rotation = {0,0,0};


vec2_t orthographic_project(vec3_t v){
	vec2_t projected_vector = {
		.x = fov_factor * v.x,
		.y = fov_factor * v.y
	};
	return projected_vector;
}

vec2_t perspective_project(vec3_t v){
        vec2_t projected_vector = {
                .x = (fov_factor * v.x)/v.z,
                .y = (fov_factor * v.y)/v.z
        };
        return projected_vector;
}


void setup(){
	// Initialize SDL
	is_running = init_window();

	//initialize the camera
	vec3_t camera_position = {0,0,-5};
	vec3_t camera_direction = {0,0,1};
	init_camera(camera_position, camera_direction);


	
	// initialize cube values
	int point_count = 0;
	for(float x = -1; x <=1; x+=0.25){
		for(float y = -1; y <= 1; y += 0.25){
			for(float z = -1; z <= 1; z += 0.25){
				vec3_t new_point = {x,y,z};
				cube_points[point_count] = new_point;
				point_count++;	
			}
		}
	}
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
	
	// rotate the cube
	cube_rotation.y += 0.01;

	// loop through every point in the cube array
	for(int i = 0; i < N_POINTS; i++){
		vec3_t point = cube_points[i];

		// Transform the points (Scale, Rotate, Translate)
		// Rotate
		vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
        	transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
        	transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);
		// Translate to camera
		transformed_point.z -= get_camera_position().z;
		

		// Project transformed points
		vec2_t projected_point = perspective_project(transformed_point);
		projected_points[i] = projected_point;
	}
}

void render(){
	
	clear_color_buffer(0xFF000000);
	draw_grid(); 
	// loop all projected points and render them
	for (int i = 0; i< N_POINTS; i++){
		vec2_t projected_point = projected_points[i];
		draw_rect(
			projected_point.x + (get_window_width()/2),
			projected_point.y + (get_window_height()/2),
			4,
			4,
			0xFFFFFF00	
				);
	}

	//clear_color_buffer(0xFF000000);

	//draw_rect(100,100, 200, 100, 0xFFFF00FF);
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


