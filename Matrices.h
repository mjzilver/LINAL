#pragma once
#include <vector>

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
private:
	int _rows;
	int _columns;
	double matrix[4][4];
};

struct TranslationMatrix : public Matrix
{
	TranslationMatrix(int deltaX, int deltaY, int deltaZ) : Matrix{4, 4}
	{
		setValues(std::vector<int>{1, 0, 0, deltaX, 0, 1, 0, deltaY, 0, 0, 1, deltaZ, 0, 0, 0, 1});
	}
};

struct ScalingMatrix : public Matrix
{
	ScalingMatrix(int scaleX, int scaleY, int scaleZ) : Matrix{ 4, 4 }
	{
		setValues(std::vector<int>{scaleX,0,0,0,0,scaleY,0,0,0,0,scaleZ,0,0,0,0,1});
	}
};

