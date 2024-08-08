#include "button.h"
#include "image.h"

int main() {

	InitWindow(1000, 500, "ui test");
	SetTargetFPS(144);

	button btn1;
	btn1 = create_button("button #1", 100, 100, 100, 50, BLUE, BLACK);
	btn1.on_click = on_click_change_color_red;

	button btn2;
	btn2 = create_button("but 2", 300, 100, 100, 50, GREEN, GRAY);
	btn2.on_click= on_click_change_color_red;

	image img1;
	Texture2D temp = LoadTexture("C:/polytopia_clone/sprites/water cube.png");
	img1 = create_image(temp, 200, 200, 10.0f);

	while(!WindowShouldClose()) {
		BeginDrawing();
		
		draw_button(btn1);
		draw_button(btn2);
		draw_image(img1);

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			vec2 mouse;
			mouse.x = GetMouseX();
			mouse.y = GetMouseY();

			if(mouse.x > btn1.pos.x && mouse.y > btn1.pos.y && mouse.x < btn1.pos.x + btn1.size.x && mouse.y < btn1.pos.y + btn1.size.y) {
				void (*fptr)(button*, vec2) = btn1.on_click;
				fptr(&btn1, mouse);
			}

			if(mouse.x > btn2.pos.x && mouse.y > btn2.pos.y && mouse.x < btn2.pos.x + btn2.size.x && mouse.y < btn2.pos.y + btn2.size.y) {
				void (*fptr)(button*, vec2) = btn2.on_click;
				fptr(&btn2, mouse);
			}
		}

		EndDrawing();
	}

	return 0;
}
