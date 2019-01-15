#include "Matrices.h"
#include "WorldObject.h"


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


Matrix::~Matrix()
{
}

void Matrix::setValues(std::vector<double> values)
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
	std::vector<double> values;

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
	std::vector<double> values;

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
	std::vector<double> values;

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < other.get_columns(); j++) {
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

Matrix Matrix::translate(WorldObject object, double deltaX, double deltaY, double deltaZ)
{
	Matrix translation{4,4};
	Matrix objectMatrix{object};
	translation.setValues(std::vector<double>{1, 0, 0, deltaX, 0, 1, 0, deltaY, 0, 0, 1, deltaZ, 0, 0, 0, 1});
	return translation * objectMatrix;
}

Matrix Matrix::translate(double deltaX, double deltaY, double deltaZ)
{
	Matrix translation{ 4,4 };
	translation.setValues(std::vector<double>{1, 0, 0, deltaX, 0, 1, 0, deltaY, 0, 0, 1, deltaZ, 0, 0, 0, 1});
	return translation;
}

Matrix Matrix::scale(WorldObject object, double scaleX, double scaleY, double scaleZ)
{
	Matrix scale{ 4,4 };
	Matrix objectMatrix{object};
	scale.setValues(std::vector<double>{scaleX, 0, 0, 0, 0, scaleY, 0, 0, 0, 0, scaleZ, 0, 0, 0, 0, 1});
	Matrix toSource = translate(-object.get_source().getX(), -object.get_source().getY(), -object.get_source().getZ());
	Matrix backToPosition = translate(object.get_source().getX(), object.get_source().getY(), object.get_source().getZ());
	return backToPosition * scale * toSource * objectMatrix;
}

Matrix Matrix::rotate(WorldObject object, Point rotationPoint, int degrees)
{
	Matrix objectMatrix{ object };
	Matrix M1{ 4,4 };
	Matrix M2{ 4,4 };
	Matrix M3{ 4,4 };
	Matrix M4{ 4,4 };
	Matrix M5{ 4,4 };
	double radian = degrees * PI / 180.0;
	//x delen door wortel van x2 + y2
	double rotateXY1 = rotationPoint.getX() / std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getZ(), 2));
	//z delen door wortel van x2 + y2
	double rotateXY2 = rotationPoint.getZ() / std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getZ(), 2));
	//y delen door wortel van x2 + y2 + z2
	double rotateToX1 = rotationPoint.getY() / std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getY(), 2) + std::pow((double)rotationPoint.getZ(), 2));
	//wortel van x2 + z2 delen door wortel van x2 + y2 + z2
	double rotateToX2 = std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getZ(), 2)) / std::sqrt(std::pow((double)rotationPoint.getX(), 2) + std::pow((double)rotationPoint.getY(), 2) + std::pow((double)rotationPoint.getZ(), 2));


	//
	M5.setValues(std::vector<double>{
		rotateXY1, 0, -rotateXY2, 0,
			0, 1, 0, 0,
			rotateXY2, 0, rotateXY1, 0,
			0, 0, 0, 1
	});
	//
	M4.setValues(std::vector<double>{
		rotateToX2, -rotateToX1, 0, 0,
			rotateToX1, rotateToX2, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	});
	//
	M3.setValues(std::vector<double>{
		1, 0, 0, 0,
			0, cos(radian), -sin(radian), 0,
			0, sin(radian), cos(radian), 0,
			0, 0, 0, 1
	});
	//
	M2.setValues(std::vector<double>{
		rotateToX2, rotateToX1, 0, 0,
			-rotateToX1, rotateToX2, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	});
	//
	M1.setValues(std::vector<double>{
		rotateXY1, 0, rotateXY2, 0,
			0, 1, 0, 0,
			-rotateXY2, 0, rotateXY1, 0,
			0, 0, 0, 1
	});
	return M5 * M4 * M3 * M2 * M1 * objectMatrix;
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
