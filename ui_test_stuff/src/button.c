#include "button.h"

#include <stdio.h>
#include <string.h>

#define FONT_SIZE_MULTIPLIER 100


//create button with given parameters
button create_button(const char* label, vec2 pos, vec2 size, Color color, Color labelColor, void (*fptr)(button* btn, vec2 mouse)) {

	button retBtn;

	retBtn.label      = label;
	retBtn.pos        = pos;
	retBtn.size       = size;
	retBtn.color      = color;
	retBtn.labelColor = labelColor;
	retBtn.on_click   = fptr;

	return retBtn;

}

//function that checks if the given button was pressed (requires mouse coordinates of click and the button itself)
void check_click(button* btn, vec2 mouse) {
	if(mouse.x > btn->pos.x && mouse.y > btn->pos.y && mouse.x < btn->pos.x + btn->size.x && mouse.y < btn->pos.y + btn->size.y) {
		void (*fptr)(button*, vec2) = btn->on_click;
		fptr(btn, mouse);
	}
}

//draws the button passed to the function
void draw_button(button btn) {
	Rectangle rect = {btn.pos.x, btn.pos.y, btn.size.x, btn.size.y};
	DrawRectangleRounded(rect, 0.5f, 10, btn.color);


	//TODO: fix label drawing to look super clean and crips and PROfessional
	double labelSize = (double)(strlen(btn.label));
	int fontSize = btn.size.y * (0.5 - labelSize/FONT_SIZE_MULTIPLIER);
	DrawText(btn.label, btn.pos.x, btn.pos.y, fontSize, btn.labelColor);
	//if labelSize > some threshold, split the string into parts. do this until all the parts are < some threshold. then draw each line
	//separately. there's a lot of math you'll have to do here haha
}



//TODO: delete all these example on_click functions later

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
