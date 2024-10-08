#pragma once

#include "C:/polytopia_clone/include/raylib.h"

#include "math.h"

//image struct

typedef struct image {

	Texture2D sprite;
	vec2 pos;
	vec2 size;
	float scale;

} image;

//creates the image with the given parameters
image create_image(Texture2D sprite, vec2 pos, vec2 size, float scale);

//draws the image passed to the function
void draw_image(image img); 
