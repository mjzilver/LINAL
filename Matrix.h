#pragma once
#include <vector>
#include "Vector.h"
#include "WorldObject.h"
#define PI 3.14159265

class Matrix
{
public:
	Matrix();
	Matrix(int rows, int columns);
	Matrix(WorldObject object);
	~Matrix();
	void setValues(std::vector<double> values);
	double getValue(const int row, const int column) { return matrix[row][column]; }
	void setValue(const int row, const int column, double value) { matrix[row][column] = value; }
	void addValue(const int row, const int column, double value) { matrix[row][column] += value; }

	// Matrix operations                                                                                                                                                                                               
	Matrix operator+(const Matrix& other);
	int get_rows() const { return _rows; };
	int get_columns() const { return _columns; };
	Matrix & operator+=(const Matrix & other);
	Matrix  operator-(const Matrix & other);
	Matrix & operator-=(const Matrix & other);
	Matrix  operator*(const Matrix & other);
	Matrix & operator*=(const Matrix & other);

	Matrix translate(WorldObject object, double deltaX, double deltaY, double deltaZ);
	Matrix translate(double deltaX, double deltaY, double deltaZ);
	Matrix scale(WorldObject object, double scaleX, double scaleY, double scaleZ);
	Matrix rotate(WorldObject object, Vector rotationPoint, int degrees);

	Matrix getRelative(Vector source);
	Matrix getAbsolute(Vector source);

	Vector multiplyVector(Vector vector);

	static Matrix yaw(double degrees);
	static Matrix pitch(double degrees);
	static Matrix roll(double degrees);

	void print();// debug function 
private:
	int _rows;
	int _columns;
	double matrix[4][25];
};

