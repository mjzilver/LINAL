#include "pch.h"
#include "Vector.h"
#include "Vector.cpp"
#include "Matrix.h"
#include "Matrix.cpp"

#include <cmath>

bool compareFloat(float a, float b)
{
	return fabs(a - b) < 0.001;
}

// Test the Cross Product of vector
TEST(VectorTests, CrossProduct) {
	Vector a = Vector(2, 4, 3);
	Vector b = Vector(3, 5, 7);

	// = 13 -5 -2 1
	Vector c = a * b;
	ASSERT_EQ(c.getX(), 13);
	ASSERT_EQ(c.getY(), -5);
	ASSERT_EQ(c.getZ(), -2);
	ASSERT_EQ(c.getW(), 1);
}

// Test the dot product of vectors
TEST(VectorTests, DotProduct) {
	Vector a = Vector(1, 2, 3);
	Vector b = Vector(1, 5, 7);

	// = 32
	float c = a.dotProduct(b);
	ASSERT_EQ(c, 32);
}

// Test the addition of vectors
TEST(VectorTests, Addition) {
	Vector a = Vector(1, 0, 3);
	Vector b = Vector(-1, 4, 2);

	// = (0, 4, 5)
	Vector c = a + b;
	ASSERT_EQ(c.getX(), 0);
	ASSERT_EQ(c.getY(), 4);
	ASSERT_EQ(c.getZ(), 5);
	ASSERT_EQ(c.getW(), 1);
} 

// Test the subtraction of vectors
TEST(VectorTests, Subtraction) {
	Vector a = Vector(2, 4, 3);
	Vector b = Vector(3, 5, 4);

	// = (-1, -1, -1, 1)
	Vector c = a - b;
	ASSERT_EQ(c.getX(), -1);
	ASSERT_EQ(c.getY(), -1);
	ASSERT_EQ(c.getZ(), -1);
	ASSERT_EQ(c.getW(), 1);
}

TEST(MatrixTests, Roll) {

	// -4.37114e-08, -1, 0, 0
	// 1, -4.37114e-08, 0, 0
	//	0, 0, 1, 0
	//	0, 0, 0, 1
	Matrix roll = Matrix::roll(90);
	ASSERT_TRUE(compareFloat(roll.getValue(0, 0), -4.37114e-08));
	ASSERT_TRUE(compareFloat(roll.getValue(1, 1), -4.37114e-08));
	ASSERT_EQ(roll.getValue(0, 1), -1);
	ASSERT_EQ(roll.getValue(1, 0), 1);
	ASSERT_EQ(roll.getValue(2, 2), 1);
	ASSERT_EQ(roll.getValue(3, 3), 1);
}

TEST(MatrixTests, Yaw) {
	/*
	-4.37114e-08, 0, 1, 0
	0, 1, 0, 0
	-1, 0, -4.37114e-08, 0
	0, 0, 0, 1
	*/
	Matrix yaw = Matrix::yaw(90);
	ASSERT_TRUE(compareFloat(yaw.getValue(0, 0), -4.37114e-08));
	ASSERT_TRUE(compareFloat(yaw.getValue(2, 2), -4.37114e-08));
	ASSERT_EQ(yaw.getValue(0, 2), 1);
	ASSERT_EQ(yaw.getValue(1, 1), 1);
	ASSERT_EQ(yaw.getValue(2, 0), -1);
	ASSERT_EQ(yaw.getValue(3, 3), 1);
}

TEST(MatrixTests, Pitch) {
	/*
	1, 0, 0, 0
	0, -4.37114e-08, -1, 0
	0, 1, -4.37114e-08, 0
	0, 0, 0, 1
	*/
	Matrix pitch = Matrix::pitch(90);
	ASSERT_TRUE(compareFloat(pitch.getValue(1, 1), -4.37114e-08));
	ASSERT_TRUE(compareFloat(pitch.getValue(2, 2), -4.37114e-08));
	ASSERT_EQ(pitch.getValue(0, 0), 1);
	ASSERT_EQ(pitch.getValue(1, 2), -1);
	ASSERT_EQ(pitch.getValue(2, 1), 1);
	ASSERT_EQ(pitch.getValue(3, 3), 1);
}

TEST(MatrixTests, Multiply) {
	Matrix a = Matrix(4, 4);
	a.setValues(std::vector<float>{
		5, 2, 6, 1,
		0, 6, 2, 0,
		3, 8, 1, 4,
		1, 8, 5, 6
	});

	Matrix b = Matrix(4, 4);
	b.setValues(std::vector<float>{
		7, 5, 8, 0,
		1, 8, 2, 6,
		9, 4, 3, 8,
		5, 3, 7, 9
	});

	Matrix c = Matrix(4, 4);
	c = a * b;

	ASSERT_EQ(c.getValue(0, 0), 96);
	ASSERT_EQ(c.getValue(0, 1), 68);
	ASSERT_EQ(c.getValue(0, 2), 69);
	ASSERT_EQ(c.getValue(0, 3), 69);

	ASSERT_EQ(c.getValue(1, 0), 24);
	ASSERT_EQ(c.getValue(1, 1), 56);
	ASSERT_EQ(c.getValue(1, 2), 18);
	ASSERT_EQ(c.getValue(1, 3), 52);

	ASSERT_EQ(c.getValue(2, 0), 58);
	ASSERT_EQ(c.getValue(2, 1), 95);
	ASSERT_EQ(c.getValue(2, 2), 71);
	ASSERT_EQ(c.getValue(2, 3), 92);

	ASSERT_EQ(c.getValue(3, 0), 90);
	ASSERT_EQ(c.getValue(3, 1), 107);
	ASSERT_EQ(c.getValue(3, 2), 81);
	ASSERT_EQ(c.getValue(3, 3), 142);
}

TEST(MatrixTests, Subtract) {
	Matrix a = Matrix(2, 2);
	a.setValues(std::vector<float>{
		2, 5,
		-1, 3
	});

	Matrix b = Matrix(2, 2);
	b.setValues(std::vector<float>{
		1, 1,
		4, -2
	});

	Matrix c = Matrix(2, 2);
	c = a - b;

	ASSERT_EQ(c.getValue(0, 0), 1);
	ASSERT_EQ(c.getValue(0, 1), 4);

	ASSERT_EQ(c.getValue(1, 0), -5);
	ASSERT_EQ(c.getValue(1, 1), 5);
}
TEST(MatrixTests, Addition) {
	Matrix a = Matrix(2, 2);
	a.setValues(std::vector<float>{
		1, 5,
		7, 3
	});

	Matrix b = Matrix(2, 2);
	b.setValues(std::vector<float>{
		12, -1,
		0, 9
	});

	Matrix c = Matrix(2, 2);
	c = a + b;

	ASSERT_EQ(c.getValue(0, 0), 13);
	ASSERT_EQ(c.getValue(0, 1), 4);

	ASSERT_EQ(c.getValue(1, 0), 7);
	ASSERT_EQ(c.getValue(1, 1), 12);
}

TEST(MatrixVectorTest, MultiplyVector) {
	Matrix a = Matrix(4, 4);
	a.setValues(std::vector<float>{
		1, 0, 2, 0,
		-1, 4, 3, 7,
		-1, 9, 3, 7,
		1, -2, 2, 1
	});

	Vector b = Vector(4, -2, 1, 1);
	Vector c = a.multiplyVector(b);

	ASSERT_EQ(c.getX(), 6);
	ASSERT_EQ(c.getY(), -2);
	ASSERT_EQ(c.getZ(), -12);
	ASSERT_EQ(c.getW(), 11);
}
