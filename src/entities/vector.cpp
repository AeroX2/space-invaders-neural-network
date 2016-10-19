#include "vector.hpp"

Vector::Vector(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector Vector::operator+(const Vector rhs)
{
	Vector new_vector(this->x, this->y);
	new_vector += rhs;
	return new_vector;
}

Vector Vector::operator-(const Vector rhs)
{
	Vector new_vector(this->x, this->y);
	new_vector -= rhs;
	return new_vector;
}

Vector Vector::operator*(const Vector rhs)
{
	Vector new_vector(this->x, this->y);
	new_vector *= rhs;
	return new_vector;
}

Vector Vector::operator*(const float rhs)
{
	Vector new_vector(this->x, this->y);
	new_vector.x *= rhs;
	new_vector.y *= rhs;
	return new_vector;
}

Vector& Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector& Vector::operator*=(const Vector& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vector& Vector::operator*=(const float rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

float Vector::distance()
{
	return sqrt(x*x+y*y);
}

Vector Vector::normalise()
{
	float length = distance();
	Vector new_vector = Vector(x, y);
	if (length != 0)
	{
		new_vector.x = new_vector.x / length;
		new_vector.y = new_vector.y / length;
	}
	return new_vector;
}

Vector Vector::copy()
{
	return Vector(this->x, this->y);
}

void Vector::print()
{
	cout << "X: " << x << endl;
	cout << "Y: " << y << endl;
}
