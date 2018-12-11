#pragma once
class Shape
{
public:
	Shape();
	~Shape();

	virtual int QueryWidth();
	virtual int QueryHeight();

	int QueryArea() { return _area; }

protected:
	int _area = 0;
};

