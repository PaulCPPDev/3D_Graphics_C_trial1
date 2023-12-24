#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"


#define N_POINTS (9 * 9 * 9) // 9x9x9 cube
// vec3_t cube_points[N_POINTS];
// vec2_t  projected_points[N_POINTS];


triangle_t triangles_to_render[N_MESH_FACES];

vec3_t camera_position = {.x= 0, .y = 0, .z = -5};
vec3_t cube_rotation = {.x = 0, .y = 0, .z = 0};

float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;



void setup(void){
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t)* window_width * window_height);
	
	color_buffer_texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			window_width,
			window_height
			);

}

void process_input(void){
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
			break;
	}
}

vec2_t project(vec3_t point){
	vec2_t projected_point = {
		.x = (fov_factor * point.x)/ point.z,
		.y = (fov_factor * point.y)/ point.z
	};
	return projected_point;
}

void update(void){

	// wait some time until we reach the target frametime in milliseconds
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	//Only delay execution if we are running too fast
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
		SDL_Delay(time_to_wait);

	previous_frame_time = SDL_GetTicks();

	cube_rotation.x += 0.015;
	cube_rotation.y += 0.015;
	cube_rotation.z += 0.015;
	
	
	// Loop all triangle faces of our mesh
	for (int i = 0; i < N_MESH_FACES; i++){
		// get the current mesh face
		face_t mesh_face = mesh_faces[i];
		// get all the vertices of the current face
		vec3_t face_vertices[3];
		face_vertices[0] = mesh_vertices[mesh_face.a -1];
		face_vertices[1] = mesh_vertices[mesh_face.b -1];
		face_vertices[2] = mesh_vertices[mesh_face.b -1];
		
		triangle_t projected_triangle;

		// Loop al three vertices of the current face  and apply transformations
		for (int j = 0; j < 3; j++){
			vec3_t transformed_vertex = face_vertices[j];

			transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
			transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
			transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

			// take into acount the zoom of the camera
			transformed_vertex.z -= camera_position.z;

			// Project the current vertex
			vec2_t projected_point = project(transformed_vertex);

			// Scale and translate the projected points to the middle of screen
			projected_point.x += (window_width /2);
			projected_point.y += (window_height/2);

			projected_triangle.points[j] = projected_point;
		}

		triangles_to_render[i] = projected_triangle;
	}
	
	/*
	for(int i = 0; i <N_POINTS; i++) {
		vec3_t point = cube_points[i];
		
		//transform the points
		vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
		transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
		transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);


		// Update the position of the points(vectors) according to the camera pos
		 transformed_point.z -= camera_position.z;

		// project each point in the array
		vec2_t projected_point = project(transformed_point);

		// add all the projected points to the array of projected points
		projected_points[i] = projected_point;
	}*/

}


void render(void){
	
	draw_grid();

	// Loop all projected triangles and render them
	
	for( int i= 0; i < N_MESH_FACES; i++ ){
		triangle_t triangle = triangles_to_render[i];
		draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFFFF00);
		draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFFFF00);
		draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFFFF00);

		// draw each triangle
		draw_triangle(triangle.points[0].x, triangle.points[0].y,
				triangle.points[1].x, triangle.points[1].y,
				triangle.points[2].x, triangle.points[2].y,
				0xFFFFFF00
				);
	}

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}



//////////////////////////////////////////////////////////////////////////////
///////////////////////       MAIN         ///////////////////////////////////

int main (){

	is_running = initialize_window();

	setup();


	while(is_running){
		process_input();
		update();
		render();
	}
	
	destroy_window();

	return 0;
}
