#ifndef _VECTOR_2D_
#define _VECTOR_2D_

class Vector2D{
	private:
		int x;
		int y;

	public:
		Vector2D(int x, int y);
		int get_x() const;
		int get_y() const;
		void set_x(int x);
		void set_y(int y);

		Vector2D operator + (const Vector2D &param);
		Vector2D operator - (const Vector2D &param);
		Vector2D operator * (const Vector2D &param);
		Vector2D operator / (const Vector2D &param);
};

#endif
