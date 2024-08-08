#include "button.h"
#include "image.h"
#include "panel.h"

#include <stdio.h>

int main() {

	InitWindow(1000, 500, "ui test");
	SetTargetFPS(144);

	button btn1;
	btn1 = create_button("button #1", 100, 100, 100, 50, BLUE, BLACK);
	btn1.on_click = on_click_change_color_red;

	button btn2;
	btn2 = create_button("but 2", 300, 100, 100, 50, BLUE, WHITE);
	btn2.on_click= on_click_change_color_red;

	image img1;
	Texture2D temp = LoadTexture("C:/polytopia_clone/sprites/water cube.png");
	img1 = create_image(temp, 200, 200, 2.0f);

	panel panel1;
	panel1 = create_panel(20, 20, 600, 400, PURPLE, 2, 1);
	panel_add_button(&panel1, btn1);
	panel_add_button(&panel1, btn2);
	panel_add_image (&panel1, img1);

	while(!WindowShouldClose()) {
		BeginDrawing();

		draw_panel(panel1);

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			vec2 mouse;
			mouse.x = GetMouseX();
			mouse.y = GetMouseY();
			panel_check_click(&panel1, mouse);
		}

		EndDrawing();
	}

	destroy_panel(&panel1);

	return 0;
}
