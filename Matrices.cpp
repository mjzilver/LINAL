#include "Matrices.h"



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


Matrix::~Matrix()
{
}

void Matrix::setValues(std::vector<int> values)
{
	int value = 0;
	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _columns; ++j) {
			matrix[i][j] = values.at(value);
			value++;
		}
	}
}

//optellen
Matrix Matrix::operator+(const Matrix & other)
{
	Matrix result(_rows,_columns);
	std::vector<int> values;

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

//aftrekken
Matrix Matrix::operator-(const Matrix & other)
{
	Matrix result(_rows, _columns);
	std::vector<int> values;

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

//vermenigvuldigen
Matrix Matrix::operator*(const Matrix & other)
{
	Matrix result(_rows, other.get_columns());
	std::vector<int> values;

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _rows; j++) {
			double multiplyresult = 0;
			for (int k = 0; k < _columns; k++) {
				multiplyresult += this->matrix[i][k] * other.matrix[k][j];
			}
			values.push_back(multiplyresult);
		}
	}
	result.setValues(values);
	return result;
}

Matrix & Matrix::operator*=(const Matrix & other)
{
	Matrix result = (*this) * other;
	(*this) = result;
	return *this;
}

Matrix Matrix::translate(Point vector, int deltaX, int deltaY, int deltaZ)
{
	Matrix translation{4,4};
	Matrix vectorMatrix{ 4,1 };
	translation.setValues(std::vector<int>{1, 0, 0, deltaX, 0, 1, 0, deltaY, 0, 0, 1, deltaZ, 0, 0, 0, 1});	
	vectorMatrix.setValues(std::vector<int>{vector.getX(),vector.getY(),vector.getZ(),1});
	return translation * vectorMatrix;
}

Matrix Matrix::scale(Point vector, int scaleX, int scaleY, int scaleZ)
{
	Matrix scale{ 4,4 };
	Matrix vectorMatrix{ 4,1 };
	scale.setValues(std::vector<int>{scaleX, 0, 0, 0, 0, scaleY, 0, 0, 0, 0, scaleZ, 0, 0, 0, 0, 1});
	vectorMatrix.setValues(std::vector<int>{vector.getX(), vector.getY(), vector.getZ(), 1});
	return scale * vectorMatrix;
}

Matrix Matrix::rotate(Point vector, Point rotationPoint, int degrees)
{
	Matrix vectorMatrix{ 4,1 };
	vectorMatrix.setValues(std::vector<int>{vector.getX(), vector.getY(), vector.getZ(), 1});

	Matrix M1{ 4,4 };
	Matrix M2{ 4,4 };
	Matrix M3{ 4,4 };
	Matrix M4{ 4,4 };
	Matrix M5{ 4,4 };
	//x delen door wortel van x2 + y2
	int rotateXY1 = (int)rotationPoint.getX() / std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getY(), 2));
	//z delen door wortel van x2 + y2
	int rotateXY2 = (int)rotationPoint.getZ() / std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getY(), 2));
	//y delen door wortel van x2 + y2 + z2
	int rotateToX1 = (int)rotationPoint.getY() / std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getY(), 2) + std::pow((double)rotationPoint.getZ(), 2));
	//wortel van x2 + z2 delen door wortel van x2 + y2 + z2
	int rotateToX2 = std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getZ(), 2)) / std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getY(), 2) + std::pow((double)rotationPoint.getZ(), 2));


	//
	M5.setValues(std::vector<int>{
		rotateXY1, 0, -rotateXY2, 0,
			0, 1, 0, 0,
			rotateXY2, 0, rotateXY1, 0,
			0, 0, 0, 1
	});
	//
	M4.setValues(std::vector<int>{
		rotateToX2, -rotateToX1, 0, 0,
			rotateToX1, rotateToX2, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	});
	//
	M3.setValues(std::vector<int>{
		1, 0, 0, 0,
			0, (int)cos(degrees * PI / 180), -(int)sin(degrees * PI / 180), 0,
			0, (int)sin(degrees * PI / 180), (int)cos(degrees * PI / 180), 0,
			0, 0, 0, 1
	});
	//
	M2.setValues(std::vector<int>{
		rotateToX2, rotateToX1, 0, 0,
			-rotateToX1, rotateToX2, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	});
	//
	M1.setValues(std::vector<int>{
		rotateXY1, 0, rotateXY2, 0,
			0, 1, 0, 0,
			-rotateXY2, 0, rotateXY1, 0,
			0, 0, 0, 1
	});

	return M5 * M4*M3*M2*M1*vectorMatrix;
}

int Matrix::dotProduct(Point vector1, Point vector2)
{
	return (vector1.getX()*vector2.getX())+(vector1.getY()*vector2.getY());
}

Matrix Matrix::crossProduct(Point vector1, Point vector2)
{
	Matrix result{ 3,1 };
	result.setValues({
		(vector1.getY()*vector2.getZ()) - (vector1.getZ()*vector2.getY()),
		(vector1.getZ()*vector2.getX()) - (vector1.getX()*vector2.getZ()),
		(vector1.getX()*vector2.getY()) - (vector1.getY()*vector2.getX())
		});
	return result;
}
