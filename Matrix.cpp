#include "Matrix.h"
#include "WorldObject.h"
#include <cmath>
#include <iostream>

Matrix::Matrix(int rows, int columns) : _rows{rows}, _columns{columns}
{
	int value = 0;
	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _columns; ++j) {
			matrix[i][j] = 0;
			value++;
		}
	}
}

Matrix::Matrix(WorldObject object)
{
	_rows = 4;
	_columns = object.get_object()->size();

	auto points = object.get_object();
	for (int i = 0; i < _columns; ++i) {
		matrix[0][i] = points->at(i).getX();
		matrix[1][i] = points->at(i).getY();
		matrix[2][i] = points->at(i).getZ();
		matrix[3][i] = 1;
	}
}

void Matrix::setValues(std::vector<float> values)
{
	int value = 0;
	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _columns; ++j) {
			matrix[i][j] = values.at(value);
			value++;
		}
	}
}

Matrix Matrix::operator+(const Matrix & other)
{
	Matrix result(_rows,_columns);
	std::vector<float> values;

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			values.push_back(this->matrix[i][j] + other.matrix[i][j]);
		}
	}
	result.setValues(values);
	return result;
}

Matrix & Matrix::operator+=(const Matrix & other)
{
	for (int i = 0; i < other.get_rows(); i++) {
		for (int j = 0; j < other.get_columns(); j++) {
			this->matrix[i][j] += other.matrix[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator-(const Matrix & other)
{
	Matrix result(_rows, _columns);
	std::vector<float> values;

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			values.push_back(this->matrix[i][j] - other.matrix[i][j]);
		}
	}
	result.setValues(values);
	return result;
}

Matrix & Matrix::operator-=(const Matrix & other)
{
	for (int i = 0; i < other.get_rows(); i++) {
		for (int j = 0; j < other.get_columns(); j++) {
			this->matrix[i][j] -= other.matrix[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator*(const Matrix & other)
{
	Matrix result(_rows, other.get_columns());

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < other.get_columns(); j++) {
			for (int k = 0; k < _columns; k++) {
				result.addValue(i,j, this->matrix[i][k] * other.matrix[k][j]);
			}
		}
	}
	return result;
}

Matrix & Matrix::operator*=(const Matrix & other)
{
	Matrix result = (*this) * other;
	(*this) = result;
	return *this;
}

Matrix Matrix::translate(float deltaX, float deltaY, float deltaZ)
{
	Matrix translation{ 4,4 };
	translation.setValues(std::vector<float>{1, 0, 0, deltaX, 0, 1, 0, deltaY, 0, 0, 1, deltaZ, 0, 0, 0, 1});
	return translation;
}

Matrix Matrix::scale(WorldObject object, float scaleX, float scaleY, float scaleZ)
{
	Matrix scale{ 4,4 };
	Matrix objectMatrix{object};
	scale.setValues(std::vector<float>{scaleX, 0, 0, 0, 0, scaleY, 0, 0, 0, 0, scaleZ, 0, 0, 0, 0, 1});
	return scale;
}

void Matrix::print()
{
	std::cout << "This matrix has " << _rows << " rows and " << _columns << " columns" << std::endl;
	std::cout << getValue(0, 0) << ", " << getValue(0, 1) << ", " << getValue(0, 2) << ", " << getValue(0, 3) << std::endl;
	std::cout << getValue(1, 0) << ", " << getValue(1, 1) << ", " << getValue(1, 2) << ", " << getValue(1, 3) << std::endl;
	std::cout << getValue(2, 0) << ", " << getValue(2, 1) << ", " << getValue(2, 2) << ", " << getValue(2, 3) << std::endl;
	std::cout << getValue(3, 0) << ", " << getValue(3, 1) << ", " << getValue(3, 2) << ", " << getValue(3, 3) << std::endl;
}

// RotationX
Matrix Matrix::pitch(float degrees)
{
	float radian = degrees * PI / 180;
	Matrix rotMat{ 4,4 };

	rotMat.setValues(std::vector<float>{
		1, 0, 0, 0,
		0, cos(radian), -sin(radian), 0,
		0, sin(radian), cos(radian), 0,
		0, 0, 0, 1
	});
	return rotMat;
}

// RotationY
Matrix Matrix::yaw(float degrees)
{
	float radian = degrees * PI / 180;
	Matrix rotMat{ 4,4 };

	rotMat.setValues(std::vector<float>{
		cos(radian), 0, sin(radian), 0,
		0, 1, 0, 0,
		-sin(radian), 0, cos(radian), 0,
		0, 0, 0, 1
	});
	return rotMat;
}

// RotationZ
Matrix Matrix::roll(float degrees)
{
	float radian = degrees * PI / 180;
	Matrix rotMat{ 4,4 };

	rotMat.setValues(std::vector<float>{
		cos(radian), -sin(radian), 0, 0,
		sin(radian), cos(radian), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	});
	return rotMat;
}

Matrix Matrix::getRelative(Vector source)
{
	Matrix result{ _rows, _columns };
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			float value = 0;
			if (i == 0)
				value = source.getX();
			if (i == 1)
				value = source.getY();
			if (i == 2)
				value = source.getZ();

			result.addValue(i, j, this->matrix[i][j] - value);
		}
	}

	return result;
}

Matrix Matrix::getAbsolute(Vector source)
{
	Matrix result{ _rows, _columns };
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			float value = 0;
			if (i == 0)
				value = source.getX();
			if (i == 1)
				value = source.getY();
			if (i == 2)
				value = source.getZ();

			result.addValue(i, j, this->matrix[i][j] + value);
		}
	}

	return result;
}

Vector Matrix::multiplyVector(Vector vector)
{
	Vector result = Vector(0,0,0);

	result.setX(this->matrix[0][0] * vector.getX() 
		+ this->matrix[0][1] * vector.getY()
		+ this->matrix[0][2] * vector.getZ()
		+ this->matrix[0][3] * vector.getW()
	);
	result.setY(this->matrix[1][0] * vector.getX()
		+ this->matrix[1][1] * vector.getY()
		+ this->matrix[1][2] * vector.getZ()
		+ this->matrix[1][3] * vector.getW()
	);
	result.setZ(this->matrix[2][0] * vector.getX()
		+ this->matrix[2][1] * vector.getY()
		+ this->matrix[2][2] * vector.getZ()
		+ this->matrix[2][3] * vector.getW()
	);
	result.setW(this->matrix[3][0] * vector.getX()
		+ this->matrix[3][1] * vector.getY()
		+ this->matrix[3][2] * vector.getZ()
		+ this->matrix[3][3] * vector.getW()
	);

	return result;
}
