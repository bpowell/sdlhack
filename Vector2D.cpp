#include "Vector2D.h"

Vector2D::Vector2D(int x, int y) : x(x), y(y){}

int Vector2D::get_x() const {return x;}
int Vector2D::get_y() const {return y;}

void Vector2D::set_x(int x1){x = x1;}
void Vector2D::set_y(int y1){y = y1;}

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
