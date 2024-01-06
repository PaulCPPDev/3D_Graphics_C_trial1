#include "../include/camera.h"

static camera_t camera;

void init_camera(vec3_t position, vec3_t direction) {
    camera.position = position;
    camera.direction = direction;
    camera.forward_velocity = vec3_new(0, 0, 0);
    camera.yaw = 0.0;
    camera.pitch = 0.0;
};

vec3_t get_camera_position(void) {
    return camera.position;
}

vec3_t get_camera_direction(void) {
    return camera.direction;
}

vec3_t get_camera_forward_velocity(void) {
    return camera.forward_velocity;
}

float get_camera_yaw(void) {
    return camera.yaw;
}

float get_camera_pitch(void) {
    return camera.pitch;
}

void update_camera_position(vec3_t position) {
    camera.position = position;
}

void update_camera_direction(vec3_t direction) {
    camera.direction = direction;
}

void update_camera_forward_velocity(vec3_t forward_velocity) {
    camera.forward_velocity = forward_velocity;
}

void rotate_camera_yaw(float angle) {
    camera.yaw += angle;
}

void rotate_camera_pitch(float angle) {
    camera.pitch += angle;
}


