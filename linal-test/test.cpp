#include "pch.h"
#include "Vector.h"
#include "Vector.cpp"

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