#pragma once

struct Vector2
{
	int x = -10;
	int y = -10;


	// Overloading the + operator
	Vector2 operator+(const Vector2 &v)
	{
		return Vector2{ x + v.x,y + v.y };
	}

	// Overloading the = operator
	Vector2& operator=(const Vector2 &v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	// Overloading the == operator
	bool operator== (const Vector2 &v) const {
		return this->x == v.x && y == v.y;
	}

	// Overloading the != operator
	bool operator!= (const Vector2 &v) const {
		return !(*this == v);
	}

};