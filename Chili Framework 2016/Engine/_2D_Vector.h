#pragma once



struct _2D_Point
{
	double x;
	double y;

	_2D_Point & operator-(const _2D_Point & rhs) {
		_2D_Point result;
		result.x = x - rhs.x;
		result.y = y - rhs.y;
		return result;
	}

	_2D_Point & operator+(const _2D_Point & rhs) {
		_2D_Point result;
		result.x = x + rhs.x;
		result.y = y + rhs.y;
		return result;
	}
};

class _2D_Vector
{
public:
	_2D_Vector();
	_2D_Vector(_2D_Point p1, _2D_Point p2);
	~_2D_Vector();

	double Length();

	_2D_Point p1;
	_2D_Point p2;
private:

};
