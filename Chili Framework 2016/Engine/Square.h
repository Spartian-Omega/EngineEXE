#pragma once
#include "Shape.h"
class Square :
	public Shape
{
public:
	Square(int s);
	~Square();

	int QueryWidth() { return _size; }
	int QueryHeight() { return _size; }

	protected:
		int _size;
};

