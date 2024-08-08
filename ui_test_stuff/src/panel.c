#include "panel.h"

#include <stdlib.h>
#include <stdio.h>

//creates a panel with the given parameters
panel create_panel(int x, int y, int width, int height, Color color, int maxButtons, int maxImages) {
	panel retPnl;

	vec2 tempPos;
	tempPos.x = x;
	tempPos.y = y;

	vec2 tempSize;
	tempSize.x = width;
	tempSize.y = height;

	retPnl.pos        = tempPos;
	retPnl.size       = tempSize;
	retPnl.color      = color;
	retPnl.numButtons = 0;
	retPnl.numImages  = 0;
	retPnl.maxButtons = maxButtons;
	retPnl.maxImages  = maxImages;
	retPnl.buttons    = malloc(sizeof(button) * maxButtons); 
	retPnl.images     = malloc(sizeof(image)  * maxImages); 

	return retPnl;
}

void destroy_panel(panel* pnl) {
	free(pnl->buttons);
	free(pnl->images);
}

//add a button to the given panel
int panel_add_button(panel* pnl, const char* label, vec2 pos, vec2 size, Color color, Color labelColor, void (*fptr)(button* btn, vec2 mouse)) {

	//check if max buttons have already been added
	if(!(pnl->numButtons < pnl->maxButtons)) {
		printf("WARNING: Tried to add button to panel (already has %d of %d).\n", pnl->numButtons, pnl->maxButtons);
		return 0;
	}

	//if button hangs off either edge of panel, print warning
	if(!(pos.x + size.x < pnl->size.x)) {
		printf("WARNING: Tried to add button to panel (%d reaches past %d).\n", pos.x + size.x, pnl->size.x);
		return 0;
	}
	if(!(pos.y + size.y < pnl->size.y)) {
		printf("WARNING: Tried to add button to panel (%d reaches past %d).\n", pos.y + size.y, pnl->size.y);
		return 0;
	}
	
	vec2 translatedBtnPos;
	translatedBtnPos.x = pnl->pos.x + pos.x;
	translatedBtnPos.y = pnl->pos.y + pos.y;
	button btn;
	btn = create_button(label, translatedBtnPos, size, color, labelColor, fptr);

	pnl->buttons[pnl->numButtons] = btn;
	pnl->numButtons++;
		
	return 1;
}

//add an image to the given panel
int panel_add_image (panel* pnl, Texture2D sprite, vec2 pos, vec2 size, float scale) {

	//check if max buttons have already been added
	if(!(pnl->numImages < pnl->maxImages)) {
		printf("WARNING: Tried to add image to panel (already has %d of %d).\n", pnl->numImages, pnl->maxImages);
		return 0;
	}

	//if image hangs off either edge of panel, print warning
	if(!(pos.x + (size.x*scale) < pnl->size.x)) {
		printf("WARNING: Tried to add button to panel (%d reaches past %d).\n", pos.x + size.x, pnl->size.x);
		return 0;
	}
	if(!(pos.y + (size.y*scale) < pnl->size.y)) {
		printf("WARNING: Tried to add button to panel (%d reaches past %d).\n", pos.y + size.y, pnl->size.y);
		return 0;
	}
	
	vec2 translatedImgPos;
	translatedImgPos.x = pnl->pos.x + pos.x;
	translatedImgPos.y = pnl->pos.y + pos.y;
	image img;
	img = create_image(sprite, translatedImgPos, size, scale);

	pnl->images[pnl->numImages] = img;
	pnl->numImages++;

	return 1;
}

//draw the panel
void draw_panel(panel pnl) {

	Rectangle rect = {pnl.pos.x, pnl.pos.y, pnl.size.x, pnl.size.y};
	DrawRectangleRounded(rect, 0.1, 10, pnl.color);

	for(int i = 0; i < pnl.numButtons; i++) {
		draw_button(pnl.buttons[i]);
	}
	for(int i = 0; i < pnl.numImages; i++) {
		draw_image(pnl.images[i]);
	}
}

//when a panel is clicked this function runs... it essentially will just run all of its buttons' button_check_click
//functions...
void panel_on_click(panel* pnl, vec2 mouse) {
	for(int i = 0; i < pnl->numButtons; i++) {
		check_click(&(pnl->buttons[i]), mouse);	
	}		
}

//checks if a panel has been clicked. this function will then run panel_on_click if the panel was clicked
void panel_check_click(panel* pnl, vec2 mouse) {
	if(mouse.x > pnl->pos.x && mouse.y > pnl->pos.y && mouse.x < pnl->pos.x + pnl->size.x && mouse.y < pnl->pos.y + pnl->size.y) {
		panel_on_click(pnl, mouse);
	}
}
