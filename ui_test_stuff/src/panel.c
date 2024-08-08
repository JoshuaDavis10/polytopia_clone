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

//add a button or image to the given panel
//TODO: should these functions have more parameters and create the actual image rather than just passing one that's already been initialized. also all the parameters would be relative to the panel not the window!
int panel_add_button(panel* pnl, button btn) {
	if(!(pnl->numButtons < pnl->maxButtons)) {
		printf("WARNING: Tried to add button to panel (already has %d of %d).\n", pnl->numButtons, pnl->maxButtons);
		return 0;
	}

	//TODO: check if button is within bounds of the panel (i.e. button isn't outside of or hanging off the panel)
	//return 0 and print corresponding error message if the button is not within the panel

	pnl->buttons[pnl->numButtons] = btn;
	pnl->numButtons++;
		
	return 1;
}

//TODO: should these functions have more parameters and create the actual image rather than just passing one that's already been initialized. also all the parameters would be relative to the panel not the window!
int panel_add_image (panel* pnl, image  img) {
	if(!(pnl->numImages < pnl->maxImages)) {
		printf("WARNING: Tried to add image to panel (already has %d of %d).\n", pnl->numImages, pnl->maxImages);
		return 0;
	}

	//TODO: check if image is within bounds of the panel (i.e. image isn't outside of or hanging off the panel)
	//return 0 and print corresponding error message if the image is not within the panel

	pnl->images[pnl->numImages] = img;
	pnl->numImages++;

	return 1;
}

//draw the panel
void draw_panel(panel pnl) {
	Rectangle rect = {pnl.pos.x, pnl.pos.y, pnl.size.x, pnl.size.y};
	DrawRectangleRounded(rect, 0.5, 10, pnl.color);

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
