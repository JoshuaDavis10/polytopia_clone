#include "math.h"

vec2 vecAdd(vec2 vecOne, vec2 vecTwo) {
	vec2 result;
	result.x = vecOne.x + vecTwo.x;
	result.y = vecOne.y + vecTwo.y;
	return result;
}
