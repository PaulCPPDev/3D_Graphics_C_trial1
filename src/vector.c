#include "../include/vector.h"
#include <math.h>


///////////////////////////////////////
//////////////  VEC2 //////////////////
///////////////////////////////////////

vec2_t new_vec2(float x, float y){
	vec2_t new_vector = { .x = x, .y = y  };
	return new_vector;
}
float vec2_length(vec2_t v){
	return sqrt( pow(v.x,2) + pow(v.y,2) );
}
vec2_t vec2_add(vec2_t a, vec2_t b){
	vec2_t new_vector = {.x = (a.x + b.x), .y = (a.y + b.y)};
	return new_vector;
}
vec2_t vec2_sub(vec2_t a, vec2_t b){
	vec2_t new_vector = {.x = (a.x - b.x), .y = (a.y - b.y)};
	return new_vector;
}
vec2_t vec2_mul(vec2_t v, float factor){
	vec2_t new_vector = {.x = (v.x * factor), .y = (v.y * factor)};
	return new_vector;
}
vec2_t vec2_div(vec2_t v, float factor){
	if(factor == 0)
		return v;
	vec2_t new_vector = {.x = (v.x / factor), .y = (v.y / factor)};
        return new_vector;
}
void vec2_normalize(vec2_t* v){
	float length = vec2_length(*v);
	v->x /= length;
	v->y /= length;
}


///////////////////////////////////////
//////////////  VEC3 //////////////////
///////////////////////////////////////

vec3_t new_vec3(float x, float y, float z){
	vec3_t new_vector = { .x = x, .y = y, .z = z  };
        return new_vector;
}
float vec3_length(vec3_t v){
	return sqrt( pow(v.x,2) + pow(v.y,2) + pow(v.z,2) );
}
vec3_t vec3_add(vec3_t a, vec3_t b){
	vec3_t new_vector = {.x = (a.x + b.x), .y = (a.y + b.y), .z = (a.z + b.z) };
        return new_vector;
}
vec3_t vec3_sub(vec3_t a, vec3_t b){
	vec3_t new_vector = {.x = (a.x - b.x), .y = (a.y - b.y), .z = (a.z - b.z) };
        return new_vector;
}
vec3_t vec3_mul(vec3_t v, float factor){
	vec3_t new_vector = {.x = (v.x * factor), .y = (v.y * factor), .z = (v.z * factor) };
        return new_vector;
}
vec3_t vec3_div(vec3_t v, float factor){
	if(factor == 0)
                return v;
        vec3_t new_vector = {.x = (v.x / factor), .y = (v.y / factor), .z = (v.z / factor)  };
        return new_vector;
}
void vec3_normalize(vec3_t* v){
	float length = vec3_length(*v);
        v->x /= length;
        v->y /= length;
	v->z /= length;
}

vec3_t vec3_clone(vec3_t* v){
	vec3_t result = { v->x, v->y, v->z };
    	return result;
}
vec3_t vec3_cross(vec3_t a, vec3_t b){
	vec3_t cross_product = {
			.x = ( (a.y * b.z) - (a.z * b.y) ),
			.y = ( (a.z * b.x) - (a.x * b.z) ),
			.z = ( (a.x * b.y) - (a.y * b.x) )
	};
       return cross_product;	
}
float vec3_dot(vec3_t a, vec3_t b){
	return ( (a.x * b.x) + (a.y * b.y) + (a.z * b.z)  );
}
vec3_t vec3_rotate_x(vec3_t v, float angle){
	vec3_t rotated_vector = {
		.x = v.x,
		.y = v.y * cos(angle) - v.z *  sin(angle),
		.z = v.y * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}
vec3_t vec3_rotate_y(vec3_t v, float angle){
	vec3_t rotated_vector = {
		.x = v.x * cos(angle) + v.z * sin(angle),
		.y = v.y,
		.z = - v.x * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}
vec3_t vec3_rotate_z(vec3_t v, float angle){
	vec3_t rotated_vector = {
		.x = v.x * cos(angle) - v.y * sin(angle),
		.y = v.x * sin(angle) + v.y * cos(angle),
		.z = v.z
	};
	return rotated_vector;
}



/////////////////////////////////////////
///////// CONVERTIONS //////////////////
///////////////////////////////////////

vec4_t vec4_from_vec3(vec3_t v){
	vec4_t new_vector = {
		.x = v.x,
		.y = v.y,
		.z = v.z,
		.w = v.z
	};
	return new_vector;
}
vec3_t vec3_from_vec4(vec4_t v){
	vec3_t new_vector = {
                .x = v.x,
                .y = v.y,
                .z = v.z
        };
        return new_vector;
}
vec2_t vec2_from_vec4(vec4_t v){
	vec2_t new_vector = {
                .x = v.x,
                .y = v.y,
        };
        return new_vector;
}




