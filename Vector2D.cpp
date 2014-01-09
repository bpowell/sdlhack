#include "Vector2D.h"

Vector2D::Vector2D(int x, int y) : x(x), y(y){}

int Vector2D::get_x() const {return x;}
int Vector2D::get_y() const {return y;}

void Vector2D::set_x(int x1){x = x1;}
void Vector2D::set_y(int y1){y = y1;}

SDL_Rect Vector2D::to_SDL_Rect(){
	SDL_Rect tmp;
	tmp.x = x;
	tmp.y = y;

	return tmp;
}

SDL_Rect Vector2D::to_SDL_Rect(int width, int height){
	SDL_Rect tmp;
	tmp.x = x;
	tmp.y = y;

	tmp.w = x + width;
	tmp.h = y + height;

	return tmp;
}

Vector2D Vector2D::operator + (const Vector2D &param){
	return Vector2D(x+param.get_x(), y+param.get_y());
}

Vector2D Vector2D::operator - (const Vector2D &param){
	return Vector2D(x-param.get_x(), y-param.get_y());
}

Vector2D Vector2D::operator * (const Vector2D &param){
	return Vector2D(x*param.get_x(), y*param.get_y());
}

Vector2D Vector2D::operator / (const Vector2D &param){
	return Vector2D(x/param.get_x(), y/param.get_y());
}
