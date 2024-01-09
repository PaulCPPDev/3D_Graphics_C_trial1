#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/display.h"
#include "../include/vector.h"
#include "../include/camera.h"
#include "../include/mesh.h"
#include "../include/triangle.h"
#include "../include/array.h"

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

// Global Variables
bool is_running = false;
int previous_frame_time = 0;


//HAND MADE CUBE
#define N_POINTS (9 * 9 * 9)
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
triangle_t* triangles_to_render = NULL;

float fov_factor = 640;
// vec3_t cube_rotation = {0,0,0};



/////////////////////////////////////////////////////////////////
//////////////// MESH.H ////////////////////////////////////////
////////////////////////////////////////////////////////////////
/*
#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2) // 6 cube faces, 2 triangles per face

vec3_t cube_vertices[N_CUBE_VERTICES];
face_t cube_faces[N_CUBE_FACES];
mesh_t mesh;*/







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

	// load_cube_mesh_data();
	load_obj_file_data("./assets/f22.obj");
	
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
	
	// clear the array of triangles to render
	triangles_to_render = NULL;

	mesh.rotation.x += 0.01;

	// Loop all triangle faces of our mesh
	int num_faces = array_length(mesh.faces);
    	for (int i = 0; i < num_faces; i++) {
        	face_t mesh_face = mesh.faces[i];
	
        	vec3_t face_vertices[3];
        	face_vertices[0] = mesh.vertices[mesh_face.a - 1];
       		face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        	face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        	triangle_t projected_triangle;

        	// Loop all three vertices of this current face and apply transformations
        	for (int j = 0; j < 3; j++) {
            		vec3_t transformed_vertex = face_vertices[j];

            		transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            		transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            		transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

            		// Translate the vertex away from the camera
            		transformed_vertex.z -= get_camera_position().z;

            		// Project the current vertex
            		vec2_t projected_point = perspective_project(transformed_vertex);

            		// Scale and translate the projected points to the middle of the screen
            		projected_point.x += (get_window_width() / 2);
            		projected_point.y += (get_window_height() / 2);

            		projected_triangle.points[j] = projected_point;
        		}

        	// Save the projected triangle in the array of triangles to render
        	// triangles_to_render[i] = projected_triangle;
		array_push(triangles_to_render, projected_triangle);
    	}


	// loop through every triangle 

	// rotate the cube
	// cube_rotation.y += 0.01;

	//1  loop through every point in the cube array
	/*for(int i = 0; i < N_POINTS; i++){
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
	}*/
}

void render(){
	
	clear_color_buffer(0xFF000000);
	draw_grid(); 



	// Loop all projected triangles and render them
	//
	// Get the number of triangles to render
	int num_triangles = array_length(triangles_to_render);
	// loop
    	for (int i = 0; i < num_triangles; i++) {
        	triangle_t triangle = triangles_to_render[i];
        	draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFFFF00);
        	draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFFFF00);
        	draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFFFF00);

		draw_unfilled_triangle(
				triangle.points[0].x, triangle.points[0].y,
				triangle.points[1].x, triangle.points[1].y,
				triangle.points[2].x, triangle.points[2].y,
				0xFFFFFF00
				);
    	}





	// loop all projected points and render them
	/*for (int i = 0; i< N_POINTS; i++){
		vec2_t projected_point = projected_points[i];
		draw_rect(
			projected_point.x + (get_window_width()/2),
			projected_point.y + (get_window_height()/2),
			4,
			4,
			0xFFFFFF00	
				);
	}*/
	
	// draw_line(100, 200, 300, 50, 0xFFFF00FF);
	// draw_filled_triangle(100, 100, 300, 200, 50, 400, 0xFFFF00FF);
	// draw_rect(100,100, 200, 100, 0xFFFF00FF);
	array_free(triangles_to_render);
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


