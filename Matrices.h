#pragma once
#include <vector>
#include "Point.h"
#include <complex>
#define PI 3.14159265

class Matrix
{
public:
	Matrix(int rows, int columns);
	~Matrix();
	void setValues(std::vector<int> values);
	double getValue(const int row, const int column) { return matrix[row][column]; }
	bool canMultiply(Matrix other) { return this->get_columns() == other.get_rows(); }

	// Matrix mathematical operations                                                                                                                                                                                               
	Matrix operator+(const Matrix& other);
	int get_rows() const { return _rows; };
	int get_columns() const { return _columns; };
	Matrix & operator+=(const Matrix & other);
	Matrix  operator-(const Matrix & other);
	Matrix & operator-=(const Matrix & other);
	Matrix  operator*(const Matrix & other);
	Matrix & operator*=(const Matrix & other);

	Matrix translate(Point vector, int deltaX, int deltaY, int deltaZ);
	Matrix scale(Point vector, int scaleX, int scaleY, int scaleZ);
	Matrix rotate(Point vector, Point rotationPoint, int degrees);

	int dotProduct(Point vector1, Point vector2);
	Matrix crossProduct(Point vector1, Point vector2);
private:
	int _rows;
	int _columns;
	double matrix[4][4];
};

