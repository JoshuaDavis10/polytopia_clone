#pragma once

#include "button.h"
#include "image.h"

typedef struct panel {
	
	vec2 pos;
	vec2 size;

	Color color;

	int maxButtons;
	int numButtons;
	button* buttons;

	int maxImages;
	int numImages;
	image* images;

} panel;

//creates a panel with the given parameters
panel create_panel(int x, int y, int width, int height, Color color, int maxButtons, int maxImages); 

//free memory that was dynamically allocated in create_panel
void destroy_panel(panel* pnl); 

//add a button or image to the given panel
//TODO: should these functions have more parameters and create the actual image rather than just passing one that's already been initialized. also all the parameters would be relative to the panel not the window!
int panel_add_button(panel* pnl, const char* label, vec2 pos, vec2 size, Color color, Color labelColor, void (*fptr)(button* btn, vec2 mouse)); 
int panel_add_image (panel* pnl, Texture2D sprite, vec2 pos, vec2 size, float scale);

//draw the panel
void draw_panel(panel pnl);

//similar checks if a panel has been clicked. this function will then run panel_on_click if the panel was clicked
//(panel_on_click is a private function... see 'panel.c')
void panel_check_click(panel* pnl, vec2 mouse);
