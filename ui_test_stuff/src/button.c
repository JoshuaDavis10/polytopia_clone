#include "button.h"

#include <stdio.h>
#include <string.h>

#define FONT_SIZE_MULTIPLIER 100


//create button with given parameters
//TODO: have parameter for on_click function. for now you will have to manually specify on_click function
button create_button(const char* label, int x, int y, int width, int height, Color color, Color labelColor) {

	button retBtn;

	vec2 tempPos;
	tempPos.x = x;
	tempPos.y = y;

	vec2 tempSize;
	tempSize.x = width;
	tempSize.y = height;

	retBtn.label      = label;
	retBtn.pos        = tempPos;
	retBtn.size       = tempSize;
	retBtn.color      = color;
	retBtn.labelColor = labelColor;

	return retBtn;

}

//function that checks if the given button was pressed (requires mouse coordinates of click and the button itself)
int check_click(button* button, vec2 mouse) {
	//TODO: code here
	//if button was clicked, run its on_click function
}

//draws the button passed to the function
void draw_button(button btn) {
	DrawRectangle(btn.pos.x, btn.pos.y, btn.size.x, btn.size.y, btn.color);
	double labelSize = (double)(strlen(btn.label));
	int fontSize = btn.size.y * (0.5 - labelSize/FONT_SIZE_MULTIPLIER);
	DrawText(btn.label, btn.pos.x, btn.pos.y, fontSize, btn.labelColor);

	//TODO: if labelSize > some threshold, split the string into parts. do this until all the parts are < some threshold. then draw each line
	//separately. there's a lot of math you'll have to do here haha
}

//example on_click function that can be set as a button's on_click function
void on_click_display_msg(button* btn, vec2 mouse) {
	printf("button clicked!\n");
}

//example on_click function that can be set as a button's on_click function
void on_click_change_color_red(button* btn, vec2 mouse) {
	btn->color = RED;
	btn->on_click = on_click_change_color_blue;
}

void on_click_change_color_blue(button* btn, vec2 mouse) {
	btn->color = BLUE;
	btn->on_click = on_click_change_color_red;
}
