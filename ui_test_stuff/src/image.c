#include "image.h"

//creates the image with the given parameters
image create_image(Texture2D sprite, vec2 pos, vec2 size, float scale) {
	
	image retImg;

	retImg.sprite = sprite;
	retImg.pos    = pos;
	retImg.size   = size;
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
