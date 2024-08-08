#include "button.h"
#include "image.h"
#include "panel.h"

#include <stdio.h>

int main() {

	InitWindow(1920, 1080, "ui test");
	SetTargetFPS(144);
	ToggleFullscreen();

	panel panel1;
	panel1 = create_panel(400, 200, 600, 400, BLACK, 2, 1);
	vec2 btn1pos  = {20, 20};
	vec2 btn1size = {100, 50};
	vec2 btn2pos  = {220, 20};
	vec2 btn2size = {100, 50};
	panel_add_button(&panel1, "", btn1pos, btn1size, BLUE, BLACK, on_click_change_color_red);
	panel_add_button(&panel1, "", btn2pos, btn2size, BLUE, WHITE, on_click_change_color_red);

	vec2 img1pos = {120, 120};
	vec2 img1size = {40, 40};
	Texture2D temp = LoadTexture("C:/polytopia_clone/sprites/water cube.png");
	panel_add_image(&panel1, temp, img1pos, img1size, 2.0f);

	panel panel2;
	panel2 = create_panel(1300, 400, 600, 400, GRAY, 2, 1);
	panel_add_button(&panel2, "", btn1pos, btn1size, BLUE, BLACK, on_click_change_color_red);
	panel_add_button(&panel2, "", btn2pos, btn2size, BLUE, WHITE, on_click_change_color_red);
	panel_add_image(&panel2, temp, img1pos, img1size, 2.0f);

	while(!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(WHITE);

		draw_panel(panel1);
		draw_panel(panel2);

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

			vec2 mouse;
			mouse.x = GetMouseX();
			mouse.y = GetMouseY();
			panel_check_click(&panel1, mouse);
			panel_check_click(&panel2, mouse);

		}

		EndDrawing();
	}

	destroy_panel(&panel1);

	return 0;
}
