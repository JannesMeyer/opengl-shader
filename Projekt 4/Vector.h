#pragma once
#include <cmath>
#include <cassert>
#include <iostream>

/*
 * Simple Vector class
 * Author: Jannes Meyer
 */

// 3-dimensional Vector
template <typename T>
struct Vector3 {
	T x;
	T y;
	T z;
	
	// constructor
	Vector3() : x(0), y(0), z(0) {}
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

	// Makes the vector printable
	static friend std::ostream& operator<<(std::ostream& out, const Vector3& v) {
		return out << "( " << v.x << ", " << v.y << ", " << v.z << " )";
	}

	// Cross product
	Vector3 crossP(const Vector3& v) const {
		T x2, y2, z2;
		x2 =  (y * v.z) - (z * v.y);
		y2 = -(x * v.z) + (z * v.x);
		z2 =  (x * v.y) - (y * v.x);
		return Vector3(x2, y2, z2);
	}
	Vector3 operator%(const Vector3& v) const {
		return crossP(v);
	}
	/*static friend Vector3 operator%(Vector3& a, Vector3& b) {
		T x, y, z;
		x =  (a.y * b.z) - (a.z * b.y);
		y = -(a.x * b.z) + (a.z * b.x);
		z =  (a.x * b.y) - (a.y * b.x);
		return Vector3(x, y, z);
	}*/

	// Dot product
	T dotP(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	// Length
	T length() const {
		return std::sqrt(x*x + y*y + z*z);
	}

	// Normalize
	void normalize() {
		*this /= length();
	}

	// Normalized
	Vector3 normalized() const {
		Vector3 v = *this;
		v.normalize();
		return v;
	}


	// Addition
    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x,
		               y + v.y,
					   z + v.z);
    }
	Vector3& operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this; // useful for: a += b += c
		// TODO: auch bei anderen operationen
	}
	// TODO: outside of a class
	/*Vector3 operator+(Vector3& a, Vector3& b) {
		return Vector3(a.x + b.x,
		             a.y + b.y,
					 a.z + b.z);
	}*/

	// Subtraction
	Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x,
		               y - v.y,
					   z - v.z);
    }
	void operator-=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	// Unary minus
	Vector3 operator-() const {
		return Vector3(-x, -y, -z);
	}

	// Piecewise division
	Vector3 operator/(T denominator) const {
		//assert(denominator != 0);
		if (denominator == 0) return;
		return Vector3(x / denominator,
		               y / denominator,
		               z / denominator);
	}
	void operator/=(T denominator) {
		//assert(denominator != 0);
		if (denominator == 0) return;
		x /= denominator;
		y /= denominator;
		z /= denominator;
	}

	// Piecewise multiplication
	Vector3 operator*(T factor) const {
		return Vector3(x * factor,
		               y * factor,
		               z * factor);
	}
	void operator*=(T factor) const {
		x *= factor;
		y *= factor;
		z *= factor;
	}

	// Equality operator
	bool operator==(const Vector3& v) const {
		return (x == v.x && y == v.y && z == v.z);
	}
};

// Type definitions
typedef Vector3<int> ivec3;
typedef Vector3<float> fvec3;
typedef Vector3<double> vec3;