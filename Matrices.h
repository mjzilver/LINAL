#pragma once
#include <vector>

class Matrix
{
public:
	Matrix(int rows, int columns);
	~Matrix();
	void setValues(std::vector<double> values);
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
private:
	int _rows;
	int _columns;
	double matrix[4][4];
};

