#pragma once
#include <vector>
#include "Point.h"
#include "WorldObject.h"
#define PI 3.14159265

class Matrix
{
public:
	Matrix(int rows, int columns);
	Matrix(WorldObject object);
	~Matrix();
	void setValues(std::vector<double> values);
	double getValue(const int row, const int column) { return matrix[row][column]; }
	void setValue(const int row, const int column, bool value) { matrix[row][column] = value; }
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

	Matrix translate(WorldObject object, double deltaX, double deltaY, double deltaZ);
	Matrix translate(double deltaX, double deltaY, double deltaZ);
	Matrix scale(WorldObject object, double scaleX, double scaleY, double scaleZ);
	Matrix rotate(WorldObject object, Point rotationPoint, int degrees);
	void print();

	int dotProduct(Point vector1, Point vector2);
	Matrix crossProduct(Point vector1, Point vector2);

	Matrix yaw(double degrees);
	Matrix pitch(double degrees);
	Matrix roll(double degrees);

private:
	int _rows;
	int _columns;
	double matrix[4][25];
};

