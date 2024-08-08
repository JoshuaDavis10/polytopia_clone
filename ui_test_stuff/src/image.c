#include "image.h"

//creates the image with the given parameters
image create_image(Texture2D sprite, int x, int y, float scale) {
	
	image retImg;

	vec2 tempPos;
	tempPos.x = x;
	tempPos.y = y;

	retImg.sprite = sprite;
	retImg.pos    = tempPos;
	retImg.scale  = scale;

	return retImg;

}

//draws the given image
void draw_image(image img) {
	Vector2 temp;
	temp.x = img.pos.x;
	temp.y = img.pos.y;
	DrawTextureEx(img.sprite, temp, 0.0f, img.scale, WHITE);
}
