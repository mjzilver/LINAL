#pragma once
#include <vector>
#include "Vector.h"
#include "WorldObject.h"
#define PI 3.14159265

class Matrix
{
public:
	Matrix(int rows, int columns);
	Matrix(WorldObject object);
	void setValues(std::vector<float> values);
	float getValue(const int row, const int column) { return matrix[row][column]; }
	void setValue(const int row, const int column, float value) { matrix[row][column] = value; }
	void addValue(const int row, const int column, float value) { matrix[row][column] += value; }

	// Matrix operations                                                                                                                                                                                               
	Matrix operator+(const Matrix& other);
	int get_rows() const { return _rows; };
	int get_columns() const { return _columns; };
	Matrix & operator+=(const Matrix & other);
	Matrix  operator-(const Matrix & other);
	Matrix & operator-=(const Matrix & other);
	Matrix  operator*(const Matrix & other);
	Matrix & operator*=(const Matrix & other);

	Matrix translate(WorldObject object, float deltaX, float deltaY, float deltaZ);
	Matrix translate(float deltaX, float deltaY, float deltaZ);
	Matrix scale(WorldObject object, float scaleX, float scaleY, float scaleZ);
	Matrix rotate(WorldObject object, Vector rotationPoint, int degrees);

	Matrix getRelative(Vector source);
	Matrix getAbsolute(Vector source);

	Vector multiplyVector(Vector vector);

	static Matrix yaw(float degrees);
	static Matrix pitch(float degrees);
	static Matrix roll(float degrees);

	void print();// debug function 
private:
	int _rows;
	int _columns;
	float matrix[4][25];
};

