#pragma once

#include "C:/polytopia_clone/include/raylib.h"

#include "math.h"

//button struct

typedef struct button {

	const char* label;

	vec2 pos;
	vec2 size;

	//TODO: add a function pointer for an 'on_hover' function that will be called if the button is hovered over
	void (*on_click)(struct button*, vec2);

	Color color;
	Color labelColor;

} button;

//create button with given parameters
//TODO: have parameter for on_click function. for now you will have to manually specify on_click function
button create_button(const char* label, vec2 pos, vec2 size, Color color, Color labelColor, void (*fptr)(button* btn, vec2 mouse)); 

//function that checks if the given button was pressed (requires mouse coordinates of click and the button itself)
void check_click(button* btn, vec2 mouse); 

//draws the button passed to the function
void draw_button(button btn); 

//example on_click function that can be set as a button's on_click function
void on_click_display_msg(button* btn, vec2 mouse); 

//example on_click function that can be set as a button's on_click function
void on_click_change_color_blue(button* btn, vec2 mouse);
void on_click_change_color_red(button* btn, vec2 mouse);
