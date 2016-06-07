
// Author: Christian Vallentin <mail@vallentinsource.com>
// Website: http://vallentinsource.com
// Repository: https://github.com/MrVallentin/LinearAlgebra
//
// Date Created: October 01, 2013
// Last Modified: June 07, 2016

#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP


#include <math.h>


#ifndef LINALG_DEFAULT_SCALAR
#	define LINALG_DEFAULT_SCALAR float
#endif


// Disable structure padding
#pragma pack(push, 1)


template<typename T> class vec2_t;
template<typename T> class vec3_t;
template<typename T> class vec4_t;

template<typename T> class mat2_t;
template<typename T> class mat3_t;
template<typename T> class mat4_t;


typedef vec2_t<LINALG_DEFAULT_SCALAR> vec2;

typedef vec2_t<float> fvec2;
typedef vec2_t<double> dvec2;

typedef vec2_t<signed int> ivec2;
typedef vec2_t<unsigned int> uvec2;

typedef vec2_t<bool> bvec2;

typedef vec2_t<signed long> lvec2;
typedef vec2_t<unsigned long> ulvec2;

typedef vec2_t<signed long long> llvec2;
typedef vec2_t<unsigned long long> ullvec2;


typedef vec3_t<LINALG_DEFAULT_SCALAR> vec3;

typedef vec3_t<float> fvec3;
typedef vec3_t<double> dvec3;

typedef vec3_t<signed int> ivec3;
typedef vec3_t<unsigned int> uvec3;

typedef vec3_t<bool> bvec3;

typedef vec3_t<signed long> lvec3;
typedef vec3_t<unsigned long> ulvec3;

typedef vec3_t<signed long long> llvec3;
typedef vec3_t<unsigned long long> ullvec3;


typedef vec4_t<LINALG_DEFAULT_SCALAR> vec4;

typedef vec4_t<float> fvec4;
typedef vec4_t<double> dvec4;

typedef vec4_t<signed int> ivec4;
typedef vec4_t<unsigned int> uvec4;

typedef vec4_t<bool> bvec4;

typedef vec4_t<signed long> lvec4;
typedef vec4_t<unsigned long> ulvec4;

typedef vec4_t<signed long long> llvec4;
typedef vec4_t<unsigned long long> ullvec4;


typedef mat2_t<LINALG_DEFAULT_SCALAR> mat2;

typedef mat2_t<float> fmat2;
typedef mat2_t<double> dmat2;

template<typename T> using mat2x2_t = mat2_t<T>;

typedef mat2x2_t<LINALG_DEFAULT_SCALAR> mat2x2;

typedef mat2x2_t<float> fmat2x2;
typedef mat2x2_t<double> dmat2x2;


typedef mat3_t<LINALG_DEFAULT_SCALAR> mat3;

typedef mat3_t<float> fmat3;
typedef mat3_t<double> dmat3;

template<typename T> using mat3x3_t = mat3_t<T>;

typedef mat3x3_t<LINALG_DEFAULT_SCALAR> mat3x3;

typedef mat3x3_t<float> fmat3x3;
typedef mat3x3_t<double> dmat3x3;


typedef mat4_t<LINALG_DEFAULT_SCALAR> mat4;

typedef mat4_t<float> fmat4;
typedef mat4_t<double> dmat4;

template<typename T> using mat4x4_t = mat4_t<T>;

typedef mat4x4_t<LINALG_DEFAULT_SCALAR> mat4x4;

typedef mat4x4_t<float> fmat4x4;
typedef mat4x4_t<double> dmat4x4;


#if defined(_DEBUG) && !defined(DEBUG)
#	define DEBUG 1
#endif


// This was changed from 1E-6 to 1E-4, as asserting rotate(90deg) didn't match.
#define LINALG_EPSILON 1E-4f

#define LINALG_FEQUAL(x, y) ((((y) - LINALG_EPSILON) < (x)) && ((x) < ((y) + LINALG_EPSILON)))
#define LINALG_DEQUAL(x, y) ((((y) - LINALG_EPSILON) < (x)) && ((x) < ((y) + LINALG_EPSILON)))

#define LINALG_PI 3.1415926535897932

#define LINALG_DEG2RAD (LINALG_PI / 180.0)
#define LINALG_RAD2DEG (180.0 / LINALG_DPI)


// These annoyingly named Windows macros are interfering with the related vector methods!

#ifdef min
#	undef min
#endif

#ifdef max
#	undef max
#endif


template<typename T>
class vec2_t
{
private:

	typedef vec2_t<T> vec2;


public:

	static const vec2_t<T> zero;
	static const vec2_t<T> one;

	static const vec2_t<T> up, down;
	static const vec2_t<T> left, right;


public:

	// Performs Gram-Schmidt Orthogonalization on 2 basis vectors to turn them into orthonormal basis vectors
	static vec2 orthogonalize(const vec2 &a, vec2 &b)
	{
		b = b - b.project(a);
		b = b.normalize();
	}


public:

	T x, y;


public:

	vec2_t(void) : x(T(0)), y(T(0)) {}

	template<typename T2> vec2_t(const vec2_t<T2> &v) : x(T(v.x)), y(T(v.y)) {}

	template<typename T2> vec2_t(const T2 &xy) : x(T(xy)), y(T(xy)) {}
	template<typename T2> vec2_t(const T2 &x, const T2 &y) : x(T(x)), y(T(y)) {}

	template<typename T2> vec2_t(const T2 *xy) : x(T(xy[0])), y(T(xy[1])) {}

	~vec2_t(void) {}


#pragma region Operator Overloading

#pragma region Member Access Operators

	inline T& operator[](const int index) { return (reinterpret_cast<T*>(this))[index]; }
	// inline T operator[](const int index) const { return (reinterpret_cast<T*>(this))[index]; }
	inline T operator[](const int index) const { return ((T*) this)[index]; }

#pragma endregion

#pragma region Arithmetic Operators

	vec2 operator+(void) const { return vec2(+this->x, +this->y); }
	vec2 operator-(void) const { return vec2(-this->x, -this->y); }

	friend vec2 operator+(const vec2 &lhs, const vec2 &rhs) { return vec2((lhs.x + rhs.x), (lhs.y + rhs.y)); }
	friend vec2 operator-(const vec2 &lhs, const vec2 &rhs) { return vec2((lhs.x - rhs.x), (lhs.y - rhs.y)); }
	friend vec2 operator*(const vec2 &lhs, const vec2 &rhs) { return vec2((lhs.x * rhs.x), (lhs.y * rhs.y)); }
	friend vec2 operator/(const vec2 &lhs, const vec2 &rhs) { return vec2((lhs.x / rhs.x), (lhs.y / rhs.y)); }
	friend vec2 operator%(const vec2 &lhs, const vec2 &rhs) { return vec2((lhs.x % rhs.x), (lhs.y % rhs.y)); }

	friend inline vec2 operator+(const vec2 &lhs, const T &rhs) { return (lhs + vec2(rhs)); }
	friend inline vec2 operator+(const T &lhs, const vec2 &rhs) { return (vec2(lhs) + rhs); }

	friend inline vec2 operator-(const vec2 &lhs, const T &rhs) { return (lhs - vec2(rhs)); }
	friend inline vec2 operator-(const T &lhs, const vec2 &rhs) { return (vec2(lhs) - rhs); }

	friend inline vec2 operator*(const vec2 &lhs, const T &rhs) { return (lhs * vec2(rhs)); }
	friend inline vec2 operator*(const T &lhs, const vec2 &rhs) { return (vec2(lhs) * rhs); }

	friend inline vec2 operator/(const vec2 &lhs, const T &rhs) { return (lhs / vec2(rhs)); }
	friend inline vec2 operator/(const T &lhs, const vec2 &rhs) { return (vec2(lhs) / rhs); }

	friend inline vec2 operator%(const vec2 &lhs, const T &rhs) { return (lhs % vec2(rhs)); }
	friend inline vec2 operator%(const T &lhs, const vec2 &rhs) { return (vec2(lhs) % rhs); }

#pragma endregion
#pragma region Increment & Decrement Operators

	vec2& operator++(void) // Prefix
	{
		++this->x;
		++this->y;

		return (*this);
	}
	inline vec2 operator++(int) { return ++(*this); } // Postfix

	vec2& operator--(void) // Prefix
	{
		--this->x;
		--this->y;

		return (*this);
	}
	inline vec2 operator--(int) { return --(*this); } // Postfix

#pragma endregion
#pragma region Assignment Operators

	inline vec2& operator+=(const vec2 &rhs) { return ((*this) = ((*this) + rhs)); }
	inline vec2& operator+=(const T &rhs) { return ((*this) = ((*this) + rhs)); }

	inline vec2& operator-=(const vec2 &rhs) { return ((*this) = ((*this) - rhs)); }
	inline vec2& operator-=(const T &rhs) { return ((*this) = ((*this) - rhs)); }

	inline vec2& operator*=(const vec2 &rhs) { return ((*this) = ((*this) * rhs)); }
	inline vec2& operator*=(const T &rhs) { return ((*this) = ((*this) * rhs)); }

	inline vec2& operator/=(const vec2 &rhs) { return ((*this) = ((*this) / rhs)); }
	inline vec2& operator/=(const T &rhs) { return ((*this) = ((*this) / rhs)); }

	inline vec2& operator%=(const vec2 &rhs) { return ((*this) = ((*this) % rhs)); }
	inline vec2& operator%=(const T &rhs) { return ((*this) = ((*this) % rhs)); }

	vec2& operator=(const T &rhs)
	{
		(*this) = vec2(rhs);

		return (*this);
	}

	vec2& operator=(const vec2 &rhs)
	{
		// memcpy(this, &rhs, sizeof(rhs));
		// for (int i = 0; i < 2; i++) (*this)[i] = rhs[i];

		this->x = rhs.x;
		this->y = rhs.y;

		return (*this);
	}

#pragma endregion

#pragma region Logical Operators
#pragma endregion
#pragma region Comparison Operators

	bool operator==(const vec2 &rhs) const;

	friend inline bool operator==(const vec2 &lhs, const T &rhs) { return (lhs == vec2(rhs)); }
	friend inline bool operator==(const T &lhs, const vec2 &rhs) { return (vec2(lhs) == rhs); }

	friend inline bool operator!=(const vec2 &lhs, const vec2 &rhs) { return !(lhs == rhs); }
	friend inline bool operator!=(const vec2 &lhs, const T &rhs) { return (lhs != vec2(rhs)); }
	friend inline bool operator!=(const T &lhs, const vec2 &rhs) { return (vec2(lhs) != rhs); }

	friend inline bool operator>(const vec2 &lhs, const vec2 &rhs) { return ((lhs.x > rhs.x) && (lhs.y > rhs.y)); }
	friend inline bool operator>=(const vec2 &lhs, const vec2 &rhs) { return ((lhs.x >= rhs.x) && (lhs.y >= rhs.y)); }
	friend inline bool operator<(const vec2 &lhs, const vec2 &rhs) { return ((lhs.x < rhs.x) && (lhs.y < rhs.y)); }
	friend inline bool operator<=(const vec2 &lhs, const vec2 &rhs) { return ((lhs.x <= rhs.x) && (lhs.y <= rhs.y)); }

	friend inline bool operator>(const vec2 &lhs, const T &rhs) { return (lhs > vec2(rhs)); }
	friend inline bool operator>(const T &lhs, const vec2 &rhs) { return (vec2(lhs) > rhs); }

	friend inline bool operator>=(const vec2 &lhs, const T &rhs) { return (lhs >= vec2(rhs)); }
	friend inline bool operator>=(const T &lhs, const vec2 &rhs) { return (vec2(lhs) >= rhs); }

	friend inline bool operator<(const vec2 &lhs, const T &rhs) { return (lhs < vec2(rhs)); }
	friend inline bool operator<(const T &lhs, const vec2 &rhs) { return (vec2(lhs) < rhs); }

	friend inline bool operator<=(const vec2 &lhs, const T &rhs) { return (lhs <= vec2(rhs)); }
	friend inline bool operator<=(const T &lhs, const vec2 &rhs) { return (vec2(lhs) <= rhs); }

#pragma endregion

#pragma region Cast Operators

	explicit inline operator T*(void) const { return reinterpret_cast<T*>(this); }

	inline operator vec2_t<float>(void) const { return vec2_t<float>(static_cast<float>(this->x), static_cast<float>(this->y)); }
	inline operator vec2_t<double>(void) const { return vec2_t<double>(static_cast<double>(this->x), static_cast<double>(this->y)); }

	inline operator vec2_t<signed int>(void) const { return vec2_t<signed int>(static_cast<signed int>(this->x), static_cast<signed int>(this->y)); }
	inline operator vec2_t<unsigned int>(void) const { return vec2_t<unsigned int>(static_cast<unsigned int>(this->x), static_cast<unsigned int>(this->y)); }

	inline operator vec2_t<bool>(void) const { return vec2_t<bool>(static_cast<bool>(this->x), static_cast<bool>(this->y)); }

	inline operator vec2_t<signed long>(void) const { return vec2_t<signed long>(static_cast<signed long>(this->x), static_cast<signed long>(this->y)); }
	inline operator vec2_t<unsigned long>(void) const { return vec2_t<unsigned long>(static_cast<unsigned long>(this->x), static_cast<unsigned long>(this->y)); }
	inline operator vec2_t<signed long long>(void) const { return vec2_t<signed long long>(static_cast<signed long long>(this->x), static_cast<signed long long>(this->y)); }
	inline operator vec2_t<unsigned long long>(void) const { return vec2_t<unsigned long long>(static_cast<unsigned long long>(this->x), static_cast<unsigned long long>(this->y)); }

#pragma endregion

#pragma region Stream Operators

#ifdef _IOSTREAM_

	friend inline std::ostream& operator<<(std::ostream &stream, const vec2 &rhs)
	{
		// return (stream << "vec2 (" << rhs.x << ", " << rhs.y << ")");
		return (stream << "vec2 {x=" << rhs.x << ", y=" << rhs.y << "}");
	}

	friend inline std::wostream& operator<<(std::wostream &stream, const vec2 &rhs)
	{
		// return (stream << L"vec2 (" << rhs.x << L", " << rhs.y << L")");
		return (stream << L"vec2 {x=" << rhs.x << L", y=" << rhs.y << L"}");
	}

#endif

#pragma endregion

#pragma endregion

#pragma region

	inline T dot(const vec2 &rhs) const
	{
		return (this->x * rhs.x + this->y * rhs.y);
	}
	friend inline T dot(const vec2 &lhs, const vec2 &rhs) { return lhs.dot(rhs); }


	vec2 cross(const vec2 &rhs) const
	{
		return vec2(
			((this->y * rhs.z) - (this->z * rhs.y)),
			((this->z * rhs.x) - (this->x * rhs.z))
		);
	}
	friend inline vec2 cross(const vec2 &lhs, const vec2 &rhs) { return lhs.cross(rhs); }


	// inline T magnitudeSquared(void) const { return (this->x * this->x + this->y * this->y); }
	// friend inline T magnitudeSquared(const vec2 &lhs) { return lhs.magnitudeSquared(); }

	// inline T magnitude(void) const { return sqrt(this->magnitudeSquared()); }
	// friend inline T magnitude(const vec2 &lhs) { return lhs.magnitude(); }


	inline T lengthSquared(void) const { return (this->x * this->x + this->y * this->y); }
	friend inline T lengthSquared(const vec2 &lhs) { return lhs.lengthSquared(); }

	inline T length(void) const { return sqrt(this->lengthSquared()); }
	friend inline T length(const vec2 &lhs) { return lhs.length(); }


	inline T distanceSquared(const vec2 &rhs) { return ((*this) - rhs).lengthSquared(); }
	friend inline T distanceSquared(const vec2 &lhs, const vec2 &rhs) { return lhs.distanceSquared(rhs); }

	inline T distance(const vec2 &rhs) { return ((*this) - rhs).length(); }
	friend inline T distance(const vec2 &lhs, const vec2 &rhs) { return lhs.distance(rhs); }


	vec2 normalize(const T &to = T(1.0)) const;
	friend inline vec2 normalize(const vec2 &lhs, const T &to = T(1.0)) { return lhs.normalize(to); }


	T angle(const vec2 &rhs) const
	{
		// return acos(this->dot(rhs) / (this->length() * rhs.length()));
		return (this->dot(rhs) / (this->length() * rhs.length()));
	}
	friend inline T angle(const vec2 &lhs, const vec2 &rhs) { return lhs.angle(rhs); }


	// Calculates the projection of a onto b
	// 
	// Reference: http://en.wikipedia.org/wiki/Vector_projection#Vector_projection_2
	inline vec2 project(const vec2 &b) const
	{
		const float length = b.length();

		return ((this->dot(b) / (length * length)) * b);
	}
	friend inline vec2 project(const vec2 &a, const vec2 &b) { return a.project(b); }


	// Calculates the components of a perpendicular to b
	inline vec2 perpendicular(const vec2 &b) const
	{
		const float length = b.length();

		return ((*this) - ((this->dot(b) / (length * length)) * b));
	}
	friend inline vec2 perpendicular(const vec2 &a, const vec2 &b) { return a.perpendicular(b); }


	// Calculates the reflection vector from entering ray direction a and surface normal b
	inline vec2 reflect(const vec2 &b) const
	{
		// return a - TYPE(2.0) * vec2::project(a, b);
		// return (TYPE(2.0) * vec2::project(a, b) - a);

		return (T(2) * this->project(b) - (*this));
	}
	friend inline vec2 reflect(const vec2 &a, const vec2 &b) { return a.reflect(b); }


	inline T cosine(const vec2 &b) const
	{
		return this->normalize().dot(b.normalize());
	}
	friend inline T cosine(const vec2 &a, const vec2 &b) { return a.cosine(b); }


	inline vec2 rotate(const T theta) const
	{
		const T c = cos(theta), s = sin(theta);

		return vec2(
			(c * this->x - s * this->y),
			(s * this->x + c * this->y)
		);
	}
	friend inline vec2 rotate(const vec2 &a, const T theta) { return a.rotate(theta); }

#pragma endregion

#pragma region

	inline bool isNullVector(void) const;
	friend inline bool isNullVector(const vec2 &v) { return v.isNullVector(); }

	inline bool isUnitVector(void) const;
	friend inline bool isUnitVector(const vec2 &v) { return v.isUnitVector(); }

	inline bool isNormalized(const T &to = T(1.0)) const;
	friend inline bool isNormalized(const vec2 &v) { return v.isNormalized(); }


	inline bool isOrthogonalTo(const vec2 &rhs) const;
	friend inline bool isOrthogonalTo(const vec2 &lhs, const vec2 &rhs) { return (lhs.isOrthogonalTo(rhs)); }

	inline bool isPerpendicularTo(const vec2 &rhs) const;
	friend inline bool isPerpendicularTo(const vec2 &lhs, const vec2 &rhs) { return (lhs.isPerpendicularTo(rhs)); }

	inline bool isParallelTo(const vec2 &rhs) const;
	friend inline bool isParallelTo(const vec2 &lhs, const vec2 &rhs) { return (lhs.isParallelTo(rhs)); }

#pragma endregion

#pragma region

	inline vec2 abs(void) const { return vec2(abs(this->x), abs(this->y), abs(this->z)); }
	friend inline vec2 abs(const vec2 &v) { return v.abs(); }


	inline vec2 max(const vec2 &rhs) const
	{
		return vec2(
			((this->x > rhs.x) ? this->x : rhs.x),
			((this->y > rhs.y) ? this->y : rhs.y)
		);
	}
	friend inline vec2 max(const vec2 &lhs, const vec2 &rhs) { return lhs.max(rhs); }

	inline vec2 min(const vec2 &rhs) const
	{
		return vec2(
			((this->x < rhs.x) ? this->x : rhs.x),
			((this->y < rhs.y) ? this->y : rhs.y)
		);
	}
	friend inline vec2 min(const vec2 &lhs, const vec2 &rhs) { return lhs.min(rhs); }

	inline vec2 clamp(const vec2 &min, const vec2 &max) const
	{
		return this->min(max).max(min);
	}
	friend inline vec2 clamp(const vec2 &v, const vec2 &min, const vec2 &max) { return v.clamp(min, max); }


	inline vec2 lerp(const vec2 &to, const T &t) const { return ((*this) + t * (to - (*this))); }
	friend inline vec2 lerp(const vec2 &from, const vec2 &to, const T &t) { return from.lerp(to, t); }

	inline vec2 lerp(const vec2 &to, const vec2 &t) const { return ((*this) + t * (to - (*this))); }
	friend inline vec2 lerp(const vec2 &from, const vec2 &to, const vec2 &t) { return from.lerp(to, t); }


	// Reference: https://en.wikipedia.org/wiki/Slerp
	// Referemce: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	inline vec2 slerp(const vec2 &to, const T &t) const
	{
		const T dot = this->normalize().dot(to.normalize());
		const T theta = acos(dot);
		const T s = sin(theta);

		return (sin((T(1) - t) * theta) / s * (*this) + sin(t * theta) / s * to);
	}
	friend inline vec2 slerp(const vec2 &from, const vec2 &to, const T &t) { return from.slerp(to, t); }

	// Reference: https://en.wikipedia.org/wiki/Slerp
	// Referemce: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	inline vec2 slerp(const vec2 &to, const vec2 &t) const
	{
		const T dot = this->normalize().dot(to.normalize());
		const T theta = acos(dot);
		const T s = sin(theta);

		return (sin((T(1) - t) * theta) / s * (*this) + sin(t * theta) / s * to);
	}
	friend inline vec2 slerp(const vec2 &from, const vec2 &to, const vec2 &t) { return from.slerp(to, t); }


	// Reference: https://en.wikipedia.org/wiki/Sign_function
	inline const vec2 signum(void) const
	{
		return vec2(
			((this->x < T(0)) ? T(-1) : ((this->x > T(0)) ? T(1) : T(0))),
			((this->y < T(0)) ? T(-1) : ((this->y > T(0)) ? T(1) : T(0)))
		);
	}
	friend inline vec2 signum(const vec2 &v) { return v.signum(); }

#pragma endregion

#pragma region Swizzling

#define LINALG_SWIZZLE_INDEX(index, c) \
		if ((c == 'X') || (c == 'X') || (c == 'r') || (c == 'R') || (c == 's') || (c == 'S')) index = 0; \
		else if ((c == 'y') || (c == 'Y') || (c == 'g') || (c == 'G') || (c == 't') || (c == 'T')) index = 1; \
		else index = 0;

	vec2 swizzle(const char x, const char y) const
	{
		int x_index = 0, y_index = 1;

		LINALG_SWIZZLE_INDEX(x_index, x);
		LINALG_SWIZZLE_INDEX(y_index, y);

		return vec2((*this)[x_index], (*this)[y_index]);
	}

#undef LINALG_SWIZZLE_INDEX

#pragma endregion
};


template<typename T>
class vec3_t
{
private:

	typedef vec2_t<T> vec2;
	typedef vec3_t<T> vec3;


public:

	static const vec3_t<T> zero;
	static const vec3_t<T> one;

	static const vec3_t<T> up, down;
	static const vec3_t<T> left, right;
	static const vec3_t<T> forward, backward;


public:

	// Performs Gram-Schmidt Orthogonalization on 2 basis vectors to turn them into orthonormal basis vectors
	static vec3 orthogonalize(const vec3 &a, vec3 &b)
	{
		b = b - b.project(a);
		b = b.normalize();
	}

	// Performs Gram-Schmidt Orthogonalization on 3 basis vectors to turn them into orthonormal basis vectors
	static void orthogonalize(const vec3 &a, vec3 &b, vec3 &c)
	{
		b = b - b.project(a);
		b = b.normalize();

		c = c - c.project(a) - c.project(b);
		c = c.normalize();
	}


public:

	T x, y, z;


public:

	vec3_t(void) : x(T(0)), y(T(0)), z(T(0)) {}

	template<typename T2> vec3_t(const vec3_t<T2> &v) : x(T(v.x)), y(T(v.y)), z(T(v.z)) {}

	template<typename T2> vec3_t(const T2 &xyz) : x(T(xyz)), y(T(xyz)), z(T(xyz)) {}
	template<typename T2> vec3_t(const T2 &x, const T2 &y, const T2 &z = T(0)) : x(T(x)), y(T(y)), z(T(z)) {}

	template<typename T2> vec3_t(const T2 *xyz) : x(T(xyz[0])), y(T(xyz[1])), z(T(xyz[2])) {}

	template<typename T2, typename T3> vec3_t(const vec2_t<T2> &xy, const T3 &z = T3(0)) : x(T(xy.x)), y(T(xy.y)), z(T(z)) {}
	template<typename T2, typename T3> vec3_t(const T2 &x, const vec2_t<T3> &yz) : x(T(x)), y(T(yz.x)), z(T(yz.y)) {}

	~vec3_t(void) {}


#pragma region Operator Overloading

#pragma region Member Access Operators

	inline T& operator[](const int index) { return (reinterpret_cast<T*>(this))[index]; }
	// inline T operator[](const int index) const { return (reinterpret_cast<T*>(this))[index]; }
	inline T operator[](const int index) const { return ((T*) this)[index]; }

#pragma endregion

#pragma region Arithmetic Operators

	vec3 operator+(void) const { return vec3(+this->x, +this->y, +this->z); }
	vec3 operator-(void) const { return vec3(-this->x, -this->y, -this->z); }

	friend vec3 operator+(const vec3 &lhs, const vec3 &rhs) { return vec3((lhs.x + rhs.x), (lhs.y + rhs.y), (lhs.z + rhs.z)); }
	friend vec3 operator-(const vec3 &lhs, const vec3 &rhs) { return vec3((lhs.x - rhs.x), (lhs.y - rhs.y), (lhs.z - rhs.z)); }
	friend vec3 operator*(const vec3 &lhs, const vec3 &rhs) { return vec3((lhs.x * rhs.x), (lhs.y * rhs.y), (lhs.z * rhs.z)); }
	friend vec3 operator/(const vec3 &lhs, const vec3 &rhs) { return vec3((lhs.x / rhs.x), (lhs.y / rhs.y), (lhs.z / rhs.z)); }
	friend vec3 operator%(const vec3 &lhs, const vec3 &rhs) { return vec3((lhs.x % rhs.x), (lhs.y % rhs.y), (lhs.z % rhs.z)); }

	friend inline vec3 operator+(const vec3 &lhs, const T &rhs) { return (lhs + vec3(rhs)); }
	friend inline vec3 operator+(const T &lhs, const vec3 &rhs) { return (vec3(lhs) + rhs); }

	friend inline vec3 operator-(const vec3 &lhs, const T &rhs) { return (lhs - vec3(rhs)); }
	friend inline vec3 operator-(const T &lhs, const vec3 &rhs) { return (vec3(lhs) - rhs); }

	friend inline vec3 operator*(const vec3 &lhs, const T &rhs) { return (lhs * vec3(rhs)); }
	friend inline vec3 operator*(const T &lhs, const vec3 &rhs) { return (vec3(lhs) * rhs); }

	friend inline vec3 operator/(const vec3 &lhs, const T &rhs) { return (lhs / vec3(rhs)); }
	friend inline vec3 operator/(const T &lhs, const vec3 &rhs) { return (vec3(lhs) / rhs); }

	friend inline vec3 operator%(const vec3 &lhs, const T &rhs) { return (lhs % vec3(rhs)); }
	friend inline vec3 operator%(const T &lhs, const vec3 &rhs) { return (vec3(lhs) % rhs); }

#pragma endregion
#pragma region Increment & Decrement Operators

	vec3& operator++(void) // Prefix
	{
		++this->x;
		++this->y;
		++this->z;

		return (*this);
	}
	inline vec3 operator++(int) { return ++(*this); } // Postfix

	vec3& operator--(void) // Prefix
	{
		--this->x;
		--this->y;
		--this->z;

		return (*this);
	}
	inline vec3 operator--(int) { return --(*this); } // Postfix

#pragma endregion
#pragma region Assignment Operators

	inline vec3& operator+=(const vec3 &rhs) { return ((*this) = ((*this) + rhs)); }
	inline vec3& operator+=(const T &rhs) { return ((*this) = ((*this) + rhs)); }

	inline vec3& operator-=(const vec3 &rhs) { return ((*this) = ((*this) - rhs)); }
	inline vec3& operator-=(const T &rhs) { return ((*this) = ((*this) - rhs)); }

	inline vec3& operator*=(const vec3 &rhs) { return ((*this) = ((*this) * rhs)); }
	inline vec3& operator*=(const T &rhs) { return ((*this) = ((*this) * rhs)); }

	inline vec3& operator/=(const vec3 &rhs) { return ((*this) = ((*this) / rhs)); }
	inline vec3& operator/=(const T &rhs) { return ((*this) = ((*this) / rhs)); }

	inline vec3& operator%=(const vec3 &rhs) { return ((*this) = ((*this) % rhs)); }
	inline vec3& operator%=(const T &rhs) { return ((*this) = ((*this) % rhs)); }

	vec3& operator=(const T &rhs)
	{
		(*this) = vec3(rhs);

		return (*this);
	}

	vec3& operator=(const vec2 &rhs)
	{
		(*this) = vec3(rhs, this->z, this->w);

		return (*this);
	}

	vec3& operator=(const vec3 &rhs)
	{
		// memcpy(this, &rhs, sizeof(rhs));
		// for (int i = 0; i < 3; i++) (*this)[i] = rhs[i];

		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;

		return (*this);
	}

#pragma endregion

#pragma region Logical Operators
#pragma endregion
#pragma region Comparison Operators

	bool operator==(const vec3 &rhs) const;

	friend inline bool operator==(const vec3 &lhs, const T &rhs) { return (lhs == vec3(rhs)); }
	friend inline bool operator==(const T &lhs, const vec3 &rhs) { return (vec3(lhs) == rhs); }

	friend inline bool operator!=(const vec3 &lhs, const vec3 &rhs) { return !(lhs == rhs); }
	friend inline bool operator!=(const vec3 &lhs, const T &rhs) { return (lhs != vec3(rhs)); }
	friend inline bool operator!=(const T &lhs, const vec3 &rhs) { return (vec3(lhs) != rhs); }

	friend inline bool operator>(const vec3 &lhs, const vec3 &rhs) { return ((lhs.x > rhs.x) && (lhs.y > rhs.y) && (lhs.z > rhs.z)); }
	friend inline bool operator>=(const vec3 &lhs, const vec3 &rhs) { return ((lhs.x >= rhs.x) && (lhs.y >= rhs.y) && (lhs.z >= rhs.z)); }
	friend inline bool operator<(const vec3 &lhs, const vec3 &rhs) { return ((lhs.x < rhs.x) && (lhs.y < rhs.y) && (lhs.z < rhs.z)); }
	friend inline bool operator<=(const vec3 &lhs, const vec3 &rhs) { return ((lhs.x <= rhs.x) && (lhs.y <= rhs.y) && (lhs.z <= rhs.z)); }

	friend inline bool operator>(const vec3 &lhs, const T &rhs) { return (lhs > vec3(rhs)); }
	friend inline bool operator>(const T &lhs, const vec3 &rhs) { return (vec3(lhs) > rhs); }

	friend inline bool operator>=(const vec3 &lhs, const T &rhs) { return (lhs >= vec3(rhs)); }
	friend inline bool operator>=(const T &lhs, const vec3 &rhs) { return (vec3(lhs) >= rhs); }

	friend inline bool operator<(const vec3 &lhs, const T &rhs) { return (lhs < vec3(rhs)); }
	friend inline bool operator<(const T &lhs, const vec3 &rhs) { return (vec3(lhs) < rhs); }

	friend inline bool operator<=(const vec3 &lhs, const T &rhs) { return (lhs <= vec3(rhs)); }
	friend inline bool operator<=(const T &lhs, const vec3 &rhs) { return (vec3(lhs) <= rhs); }

#pragma endregion

#pragma region Cast Operators

	explicit inline operator T*(void) const { return reinterpret_cast<T*>(this); }

	inline operator vec3_t<float>(void) const { return vec3_t<float>(static_cast<float>(this->x), static_cast<float>(this->y), static_cast<float>(this->z)); }
	inline operator vec3_t<double>(void) const { return vec3_t<double>(static_cast<double>(this->x), static_cast<double>(this->y), static_cast<double>(this->z)); }

	inline operator vec3_t<signed int>(void) const { return vec3_t<signed int>(static_cast<signed int>(this->x), static_cast<signed int>(this->y), static_cast<signed int>(this->z)); }
	inline operator vec3_t<unsigned int>(void) const { return vec3_t<unsigned int>(static_cast<unsigned int>(this->x), static_cast<unsigned int>(this->y), static_cast<unsigned int>(this->z)); }

	inline operator vec3_t<bool>(void) const { return vec3_t<bool>(static_cast<bool>(this->x), static_cast<bool>(this->y), static_cast<bool>(this->z)); }

	inline operator vec3_t<signed long>(void) const { return vec3_t<signed long>(static_cast<signed long>(this->x), static_cast<signed long>(this->y), static_cast<signed long>(this->z)); }
	inline operator vec3_t<unsigned long>(void) const { return vec3_t<unsigned long>(static_cast<unsigned long>(this->x), static_cast<unsigned long>(this->y), static_cast<unsigned long>(this->z)); }
	inline operator vec3_t<signed long long>(void) const { return vec3_t<signed long long>(static_cast<signed long long>(this->x), static_cast<signed long long>(this->y), static_cast<signed long long>(this->z)); }
	inline operator vec3_t<unsigned long long>(void) const { return vec3_t<unsigned long long>(static_cast<unsigned long long>(this->x), static_cast<unsigned long long>(this->y), static_cast<unsigned long long>(this->z)); }

#pragma endregion

#pragma region Stream Operators

#ifdef _IOSTREAM_

	friend inline std::ostream& operator<<(std::ostream &stream, const vec3 &rhs)
	{
		// return (stream << "vec3 (" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")");
		return (stream << "vec3 {x=" << rhs.x << ", y=" << rhs.y << ", z=" << rhs.z << "}");
	}

	friend inline std::wostream& operator<<(std::wostream &stream, const vec3 &rhs)
	{
		// return (stream << L"vec3 (" << rhs.x << L", " << rhs.y << L", " << rhs.z << L")");
		return (stream << L"vec3 {x=" << rhs.x << L", y=" << rhs.y << L", z=" << rhs.z << L"}");
	}

#endif

#pragma endregion

#pragma endregion

#pragma region

	inline T dot(const vec3 &rhs) const
	{
		return (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z);
	}
	friend inline T dot(const vec3 &lhs, const vec3 &rhs) { return lhs.dot(rhs); }


	vec3 cross(const vec3 &rhs) const
	{
		return vec3(
			((this->y * rhs.z) - (this->z * rhs.y)),
			((this->z * rhs.x) - (this->x * rhs.z)),
			((this->x * rhs.y) - (this->y * rhs.x))
		);
	}
	friend inline vec3 cross(const vec3 &lhs, const vec3 &rhs) { return lhs.cross(rhs); }


	// inline T magnitudeSquared(void) const { return (this->x * this->x + this->y * this->y + this->z * this->z); }
	// friend inline T magnitudeSquared(const vec3 &lhs) { return lhs.magnitudeSquared(); }

	// inline T magnitude(void) const { return sqrt(this->magnitudeSquared()); }
	// friend inline T magnitude(const vec3 &lhs) { return lhs.magnitude(); }


	inline T lengthSquared(void) const { return (this->x * this->x + this->y * this->y + this->z * this->z); }
	friend inline T lengthSquared(const vec3 &lhs) { return lhs.lengthSquared(); }

	inline T length(void) const { return sqrt(this->lengthSquared()); }
	friend inline T length(const vec3 &lhs) { return lhs.length(); }


	inline T distanceSquared(const vec3 &rhs) { return ((*this) - rhs).lengthSquared(); }
	friend inline T distanceSquared(const vec3 &lhs, const vec3 &rhs) { return lhs.distanceSquared(rhs); }

	inline T distance(const vec3 &rhs) { return ((*this) - rhs).length(); }
	friend inline T distance(const vec3 &lhs, const vec3 &rhs) { return lhs.distance(rhs); }


	vec3 normalize(const T &to = T(1.0)) const;
	friend inline vec3 normalize(const vec3 &lhs, const T &to = T(1.0)) { return lhs.normalize(to); }


	T angle(const vec3 &rhs) const
	{
		// return acos(this->dot(rhs) / (this->length() * rhs.length()));
		return (this->dot(rhs) / (this->length() * rhs.length()));
	}
	friend inline T angle(const vec3 &lhs, const vec3 &rhs) { return lhs.angle(rhs); }


	// Calculates the projection of a onto b
	// 
	// Reference: http://en.wikipedia.org/wiki/Vector_projection#Vector_projection_2
	inline vec3 project(const vec3 &b) const
	{
		const float length = b.length();

		return ((this->dot(b) / (length * length)) * b);
	}
	friend inline vec3 project(const vec3 &a, const vec3 &b) { return a.project(b); }


	// Calculates the components of a perpendicular to b
	inline vec3 perpendicular(const vec3 &b) const
	{
		const float length = b.length();

		return ((*this) - ((this->dot(b) / (length * length)) * b));
	}
	friend inline vec3 perpendicular(const vec3 &a, const vec3 &b) { return a.perpendicular(b); }


	// Calculates the reflection vector from entering ray direction a and surface normal b
	inline vec3 reflect(const vec3 &b) const
	{
		// return a - TYPE(2.0) * vec3::project(a, b);
		// return (TYPE(2.0) * vec3::project(a, b) - a);

		return (T(2) * this->project(b) - (*this));
	}
	friend inline vec3 reflect(const vec3 &a, const vec3 &b) { return a.reflect(b); }


	inline T cosine(const vec3 &b) const
	{
		return this->normalize().dot(b.normalize());
	}
	friend inline T cosine(const vec3 &a, const vec3 &b) { return a.cosine(b); }

#pragma endregion

#pragma region

	inline bool isNullVector(void) const;
	friend inline bool isNullVector(const vec3 &v) { return v.isNullVector(); }

	inline bool isUnitVector(void) const;
	friend inline bool isUnitVector(const vec3 &v) { return v.isUnitVector(); }

	inline bool isNormalized(const T &to = T(1.0)) const;
	friend inline bool isNormalized(const vec3 &v) { return v.isNormalized(); }


	inline bool isOrthogonalTo(const vec3 &rhs) const;
	friend inline bool isOrthogonalTo(const vec3 &lhs, const vec3 &rhs) { return (lhs.isOrthogonalTo(rhs)); }

	inline bool isPerpendicularTo(const vec3 &rhs) const;
	friend inline bool isPerpendicularTo(const vec3 &lhs, const vec3 &rhs) { return (lhs.isPerpendicularTo(rhs)); }

	inline bool isParallelTo(const vec3 &rhs) const;
	friend inline bool isParallelTo(const vec3 &lhs, const vec3 &rhs) { return (lhs.isParallelTo(rhs)); }

#pragma endregion

#pragma region

	inline vec3 abs(void) const { return vec3(abs(this->x), abs(this->y), abs(this->z)); }
	friend inline vec3 abs(const vec3 &v) { return v.abs(); }


	inline vec3 max(const vec3 &rhs) const
	{
		return vec3(
			((this->x > rhs.x) ? this->x : rhs.x),
			((this->y > rhs.y) ? this->y : rhs.y),
			((this->z > rhs.z) ? this->z : rhs.z)
		);
	}
	friend inline vec3 max(const vec3 &lhs, const vec3 &rhs) { return lhs.max(rhs); }

	inline vec3 min(const vec3 &rhs) const
	{
		return vec3(
			((this->x < rhs.x) ? this->x : rhs.x),
			((this->y < rhs.y) ? this->y : rhs.y),
			((this->z < rhs.z) ? this->z : rhs.z)
		);
	}
	friend inline vec3 min(const vec3 &lhs, const vec3 &rhs) { return lhs.min(rhs); }

	inline vec3 clamp(const vec3 &min, const vec3 &max) const
	{
		return this->min(max).max(min);
	}
	friend inline vec3 clamp(const vec3 &v, const vec3 &min, const vec3 &max) { return v.clamp(min, max); }


	inline vec3 lerp(const vec3 &to, const T &t) const { return ((*this) + t * (to - (*this))); }
	friend inline vec3 lerp(const vec3 &from, const vec3 &to, const T &t) { return from.lerp(to, t); }

	inline vec3 lerp(const vec3 &to, const vec3 &t) const { return ((*this) + t * (to - (*this))); }
	friend inline vec3 lerp(const vec3 &from, const vec3 &to, const vec3 &t) { return from.lerp(to, t); }


	// Reference: https://en.wikipedia.org/wiki/Slerp
	// Referemce: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	inline vec3 slerp(const vec3 &to, const T &t) const
	{
		const T dot = this->normalize().dot(to.normalize());
		const T theta = acos(dot);
		const T s = sin(theta);

		return (sin((T(1) - t) * theta) / s * (*this) + sin(t * theta) / s * to);
	}
	friend inline vec3 slerp(const vec3 &from, const vec3 &to, const T &t) { return from.slerp(to, t); }

	// Reference: https://en.wikipedia.org/wiki/Slerp
	// Referemce: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	inline vec3 slerp(const vec3 &to, const vec3 &t) const
	{
		const T dot = this->normalize().dot(to.normalize());
		const T theta = acos(dot);
		const T s = sin(theta);

		return (sin((T(1) - t) * theta) / s * (*this) + sin(t * theta) / s * to);
	}
	friend inline vec3 slerp(const vec3 &from, const vec3 &to, const vec3 &t) { return from.slerp(to, t); }


	// Reference: https://en.wikipedia.org/wiki/Sign_function
	inline const vec3 signum(void) const
	{
		return vec3(
			((this->x < T(0)) ? T(-1) : ((this->x > T(0)) ? T(1) : T(0))),
			((this->y < T(0)) ? T(-1) : ((this->y > T(0)) ? T(1) : T(0))),
			((this->z < T(0)) ? T(-1) : ((this->z > T(0)) ? T(1) : T(0)))
		);
	}
	friend inline vec3 signum(const vec3 &v) { return v.signum(); }

#pragma endregion

#pragma region Swizzling

#define LINALG_SWIZZLE_INDEX(index, c) \
		if ((c == 'X') || (c == 'X') || (c == 'r') || (c == 'R') || (c == 's') || (c == 'S')) index = 0; \
		else if ((c == 'y') || (c == 'Y') || (c == 'g') || (c == 'G') || (c == 't') || (c == 'T')) index = 1; \
		else if ((c == 'z') || (c == 'Z') || (c == 'b') || (c == 'B') || (c == 'p') || (c == 'P')) index = 2; \
		else index = 0;

	vec2 swizzle(const char x, const char y) const
	{
		int x_index = 0, y_index = 1;

		LINALG_SWIZZLE_INDEX(x_index, x);
		LINALG_SWIZZLE_INDEX(y_index, y);

		return vec2((*this)[x_index], (*this)[y_index]);
	}

	vec3 swizzle(const char x, const char y, const char z) const
	{
		int x_index = 0, y_index = 1, z_index = 2;

		LINALG_SWIZZLE_INDEX(x_index, x);
		LINALG_SWIZZLE_INDEX(y_index, y);
		LINALG_SWIZZLE_INDEX(z_index, z);

		return vec3((*this)[x_index], (*this)[y_index], (*this)[z_index]);
	}

#undef LINALG_SWIZZLE_INDEX

#pragma endregion
};


template<typename T>
class vec4_t
{
private:

	typedef vec2_t<T> vec2;
	typedef vec3_t<T> vec3;
	typedef vec4_t<T> vec4;


public:

	static const vec4_t<T> zero;
	static const vec4_t<T> one;


public:

	T x, y, z, w;


public:

	vec4_t(void) : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}

	template<typename T2> vec4_t(const vec4_t<T2> &v) : x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w)) {}

	template<typename T2> vec4_t(const T2 &xyzw) : x(T(xyzw)), y(T(xyzw)), z(T(xyzw)), w(T(xyzw)) {}
	template<typename T2> vec4_t(const T2 &x, const T2 &y, const T2 &z, const T2 &w) : x(T(x)), y(T(y)), z(T(z)), w(T(w)) {}

	template<typename T2> vec4_t(const T2 *xyzw) : x(T(xyzw[0])), y(T(xyzw[0])), z(T(xyzw[0])), w(T(xyzw[0])) {}

	template<typename T2, typename T3> vec4_t(const vec3_t<T2> &xyz, const T3 &w = T3(0)) : x(T(xyz.x)), y(T(xyz.y)), z(T(xyz.z)), w(T(w)) {}
	template<typename T2, typename T3> vec4_t(const T2 &x, const vec3_t<T3> &yzw) : x(T(x)), y(T(yzw.x)), z(T(yzw.y)), w(T(yzw.z)) {}

	~vec4_t(void) {}


#pragma region Operator Overloading

#pragma region Member Access Operators

	inline T& operator[](const int index) { return (reinterpret_cast<T*>(this))[index]; }
	// inline T operator[](const int index) const { return (reinterpret_cast<T*>(this))[index]; }
	inline T operator[](const int index) const { return ((T*) this)[index]; }

#pragma endregion

#pragma region Arithmetic Operators

	vec4 operator+(void) const { return vec4(+this->x, +this->y, +this->z, +this->w); }
	vec4 operator-(void) const { return vec4(-this->x, -this->y, -this->z, -this->w); }

	friend vec4 operator+(const vec4 &lhs, const vec4 &rhs) { return vec4((lhs.x + rhs.x), (lhs.y + rhs.y), (lhs.z + rhs.z), (lhs.w + rhs.w)); }
	friend vec4 operator-(const vec4 &lhs, const vec4 &rhs) { return vec4((lhs.x - rhs.x), (lhs.y - rhs.y), (lhs.z - rhs.z), (lhs.w - rhs.w)); }
	friend vec4 operator*(const vec4 &lhs, const vec4 &rhs) { return vec4((lhs.x * rhs.x), (lhs.y * rhs.y), (lhs.z * rhs.z), (lhs.w * rhs.w)); }
	friend vec4 operator/(const vec4 &lhs, const vec4 &rhs) { return vec4((lhs.x / rhs.x), (lhs.y / rhs.y), (lhs.z / rhs.z), (lhs.w / rhs.w)); }
	friend vec4 operator%(const vec4 &lhs, const vec4 &rhs) { return vec4((lhs.x % rhs.x), (lhs.y % rhs.y), (lhs.z % rhs.z), (lhs.w % rhs.w)); }

	friend inline vec4 operator+(const vec4 &lhs, const T &rhs) { return (lhs + vec4(rhs)); }
	friend inline vec4 operator+(const T &lhs, const vec4 &rhs) { return (vec4(lhs) + rhs); }

	friend inline vec4 operator-(const vec4 &lhs, const T &rhs) { return (lhs - vec4(rhs)); }
	friend inline vec4 operator-(const T &lhs, const vec4 &rhs) { return (vec4(lhs) - rhs); }

	friend inline vec4 operator*(const vec4 &lhs, const T &rhs) { return (lhs * vec4(rhs)); }
	friend inline vec4 operator*(const T &lhs, const vec4 &rhs) { return (vec4(lhs) * rhs); }

	friend inline vec4 operator/(const vec4 &lhs, const T &rhs) { return (lhs / vec4(rhs)); }
	friend inline vec4 operator/(const T &lhs, const vec4 &rhs) { return (vec4(lhs) / rhs); }

	friend inline vec4 operator%(const vec4 &lhs, const T &rhs) { return (lhs % vec4(rhs)); }
	friend inline vec4 operator%(const T &lhs, const vec4 &rhs) { return (vec4(lhs) % rhs); }

#pragma endregion
#pragma region Increment & Decrement Operators

	vec4& operator++(void) // Prefix
	{
		++this->x;
		++this->y;
		++this->z;
		++this->w;

		return (*this);
	}
	inline vec4 operator++(int) { return ++(*this); } // Postfix

	vec4& operator--(void) // Prefix
	{
		--this->x;
		--this->y;
		--this->z;
		--this->w;

		return (*this);
	}
	inline vec4 operator--(int) { return --(*this); } // Postfix

#pragma endregion
#pragma region Assignment Operators

	inline vec4& operator+=(const vec4 &rhs) { return ((*this) = ((*this) + rhs)); }
	inline vec4& operator+=(const T &rhs) { return ((*this) = ((*this) + rhs)); }

	inline vec4& operator-=(const vec4 &rhs) { return ((*this) = ((*this) - rhs)); }
	inline vec4& operator-=(const T &rhs) { return ((*this) = ((*this) - rhs)); }

	inline vec4& operator*=(const vec4 &rhs) { return ((*this) = ((*this) * rhs)); }
	inline vec4& operator*=(const T &rhs) { return ((*this) = ((*this) * rhs)); }

	inline vec4& operator/=(const vec4 &rhs) { return ((*this) = ((*this) / rhs)); }
	inline vec4& operator/=(const T &rhs) { return ((*this) = ((*this) / rhs)); }

	inline vec4& operator%=(const vec4 &rhs) { return ((*this) = ((*this) % rhs)); }
	inline vec4& operator%=(const T &rhs) { return ((*this) = ((*this) % rhs)); }

	vec4& operator=(const T &rhs)
	{
		(*this) = vec4(rhs);

		return (*this);
	}

	vec4& operator=(const vec2 &rhs)
	{
		(*this) = vec4(rhs, this->z, this->w);

		return (*this);
	}

	vec4& operator=(const vec3 &rhs)
	{
		(*this) = vec4(rhs, this->w);

		return (*this);
	}

	vec4& operator=(const vec4 &rhs)
	{
		// memcpy(this, &rhs, sizeof(rhs));
		// for (int i = 0; i < 4; i++) (*this)[i] = rhs[i];

		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		this->w = rhs.w;

		return (*this);
	}

#pragma endregion

#pragma region Logical Operators
#pragma endregion
#pragma region Comparison Operators

	bool operator==(const vec4 &rhs) const;

	friend inline bool operator==(const vec4 &lhs, const T &rhs) { return (lhs == vec4(rhs)); }
	friend inline bool operator==(const T &lhs, const vec4 &rhs) { return (vec4(lhs) == rhs); }

	friend inline bool operator!=(const vec4 &lhs, const vec4 &rhs) { return !(lhs == rhs); }
	friend inline bool operator!=(const vec4 &lhs, const T &rhs) { return (lhs != vec4(rhs)); }
	friend inline bool operator!=(const T &lhs, const vec4 &rhs) { return (vec4(lhs) != rhs); }

	friend inline bool operator>(const vec4 &lhs, const vec4 &rhs) { return ((lhs.x > rhs.x) && (lhs.y > rhs.y) && (lhs.z > rhs.z) && (lhs.w > rhs.w)); }
	friend inline bool operator>=(const vec4 &lhs, const vec4 &rhs) { return ((lhs.x >= rhs.x) && (lhs.y >= rhs.y) && (lhs.z >= rhs.z) && (lhs.w >= rhs.w)); }
	friend inline bool operator<(const vec4 &lhs, const vec4 &rhs) { return ((lhs.x < rhs.x) && (lhs.y < rhs.y) && (lhs.z < rhs.z) && (lhs.w < rhs.w)); }
	friend inline bool operator<=(const vec4 &lhs, const vec4 &rhs) { return ((lhs.x <= rhs.x) && (lhs.y <= rhs.y) && (lhs.z <= rhs.z) && (lhs.w <= rhs.w)); }

	friend inline bool operator>(const vec4 &lhs, const T &rhs) { return (lhs > vec4(rhs)); }
	friend inline bool operator>(const T &lhs, const vec4 &rhs) { return (vec4(lhs) > rhs); }

	friend inline bool operator>=(const vec4 &lhs, const T &rhs) { return (lhs >= vec4(rhs)); }
	friend inline bool operator>=(const T &lhs, const vec4 &rhs) { return (vec4(lhs) >= rhs); }

	friend inline bool operator<(const vec4 &lhs, const T &rhs) { return (lhs < vec4(rhs)); }
	friend inline bool operator<(const T &lhs, const vec4 &rhs) { return (vec4(lhs) < rhs); }

	friend inline bool operator<=(const vec4 &lhs, const T &rhs) { return (lhs <= vec4(rhs)); }
	friend inline bool operator<=(const T &lhs, const vec4 &rhs) { return (vec4(lhs) <= rhs); }

#pragma endregion

#pragma region Cast Operators

	explicit inline operator T*(void) const { return reinterpret_cast<T*>(this); }

	inline operator vec4_t<float>(void) const { return vec4_t<float>(static_cast<float>(this->x), static_cast<float>(this->y), static_cast<float>(this->z), static_cast<float>(this->w)); }
	inline operator vec4_t<double>(void) const { return vec4_t<double>(static_cast<double>(this->x), static_cast<double>(this->y), static_cast<double>(this->z), static_cast<double>(this->w)); }

	inline operator vec4_t<signed int>(void) const { return vec4_t<signed int>(static_cast<signed int>(this->x), static_cast<signed int>(this->y), static_cast<signed int>(this->z), static_cast<signed int>(this->w)); }
	inline operator vec4_t<unsigned int>(void) const { return vec4_t<unsigned int>(static_cast<unsigned int>(this->x), static_cast<unsigned int>(this->y), static_cast<unsigned int>(this->z), static_cast<unsigned int>(this->w)); }

	inline operator vec4_t<bool>(void) const { return vec4_t<bool>(static_cast<bool>(this->x), static_cast<bool>(this->y), static_cast<bool>(this->z), static_cast<bool>(this->w)); }

	inline operator vec4_t<signed long>(void) const { return vec4_t<signed long>(static_cast<signed long>(this->x), static_cast<signed long>(this->y), static_cast<signed long>(this->z), static_cast<signed long>(this->w)); }
	inline operator vec4_t<unsigned long>(void) const { return vec4_t<unsigned long>(static_cast<unsigned long>(this->x), static_cast<unsigned long>(this->y), static_cast<unsigned long>(this->z), static_cast<unsigned long>(this->w)); }
	inline operator vec4_t<signed long long>(void) const { return vec4_t<signed long long>(static_cast<signed long long>(this->x), static_cast<signed long long>(this->y), static_cast<signed long long>(this->z), static_cast<signed long long>(this->w)); }
	inline operator vec4_t<unsigned long long>(void) const { return vec4_t<unsigned long long>(static_cast<unsigned long long>(this->x), static_cast<unsigned long long>(this->y), static_cast<unsigned long long>(this->z), static_cast<unsigned long long>(this->w)); }

#pragma endregion

#pragma region Stream Operators

#ifdef _IOSTREAM_

	friend inline std::ostream& operator<<(std::ostream &stream, const vec4 &rhs)
	{
		// return (stream << "vec4 (" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")");
		return (stream << "vec4 {x=" << rhs.x << ", y=" << rhs.y << ", z=" << rhs.z << ", w=" << rhs.w << "}");
	}

	friend inline std::wostream& operator<<(std::wostream &stream, const vec4 &rhs)
	{
		// return (stream << L"vec4 (" << rhs.x << L", " << rhs.y << L", " << rhs.z << L", " << rhs.w << L")");
		return (stream << L"vec4 {x=" << rhs.x << L", y=" << rhs.y << L", z=" << rhs.z << L", w=" << rhs.w << L"}");
	}

#endif

#pragma endregion

#pragma endregion

#pragma region

	inline T dot(const vec4 &rhs) const
	{
		return (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z + this->w * rhs.w);
	}
	friend inline T dot(const vec4 &lhs, const vec4 &rhs) { return lhs.dot(rhs); }


	// A 4D vector doesn't per se have a cross product, not a feasible one at least


	// inline T magnitudeSquared(void) const { return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w); }
	// friend inline T magnitudeSquared(const vec4 &lhs) { return lhs.magnitudeSquared(); }

	// inline T magnitude(void) const { return sqrt(this->magnitudeSquared()); }
	// friend inline T magnitude(const vec4 &lhs) { return lhs.magnitude(); }


	inline T lengthSquared(void) const { return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w); }
	friend inline T lengthSquared(const vec4 &lhs) { return lhs.lengthSquared(); }

	inline T length(void) const { return sqrt(this->lengthSquared()); }
	friend inline T length(const vec4 &lhs) { return lhs.length(); }


	inline T distanceSquared(const vec4 &rhs) { return ((*this) - rhs).lengthSquared(); }
	friend inline T distanceSquared(const vec4 &lhs, const vec4 &rhs) { return lhs.distanceSquared(rhs); }

	inline T distance(const vec4 &rhs) { return ((*this) - rhs).length(); }
	friend inline T distance(const vec4 &lhs, const vec4 &rhs) { return lhs.distance(rhs); }


	vec4 normalize(const T &to = T(1.0)) const;
	friend inline vec4 normalize(const vec4 &lhs, const T &to = T(1.0)) { return lhs.normalize(to); }


	T angle(const vec4 &rhs) const
	{
		// return acos(this->dot(rhs) / (this->length() * rhs.length()));
		return (this->dot(rhs) / (this->length() * rhs.length()));
	}
	friend inline T angle(const vec4 &lhs, const vec4 &rhs) { return lhs.angle(rhs); }

#pragma endregion

#pragma region

	inline bool isNullVector(void) const;
	friend inline bool isNullVector(const vec4 &v) { return v.isNullVector(); }

	inline bool isUnitVector(void) const;
	friend inline bool isUnitVector(const vec4 &v) { return v.isUnitVector(); }

	inline bool isNormalized(const T &to = T(1.0)) const;
	friend inline bool isNormalized(const vec4 &v) { return v.isNormalized(); }


	inline bool isOrthogonalTo(const vec4 &rhs) const;
	friend inline bool isOrthogonalTo(const vec4 &lhs, const vec4 &rhs) { return (lhs.isOrthogonalTo(rhs)); }

	inline bool isPerpendicularTo(const vec4 &rhs) const;
	friend inline bool isPerpendicularTo(const vec4 &lhs, const vec4 &rhs) { return (lhs.isPerpendicularTo(rhs)); }

	inline bool isParallelTo(const vec4 &rhs) const;
	friend inline bool isParallelTo(const vec4 &lhs, const vec4 &rhs) { return (lhs.isParallelTo(rhs)); }

#pragma endregion

#pragma region

	inline vec4 abs(void) const { return vec4(abs(this->x), abs(this->y), abs(this->z), abs(this->w)); }
	friend inline vec4 abs(const vec4 &v) { return v.abs(); }


	inline vec4 max(const vec4 &rhs) const
	{
		return vec4(
			((this->x > rhs.x) ? this->x : rhs.x),
			((this->y > rhs.y) ? this->y : rhs.y),
			((this->z > rhs.z) ? this->z : rhs.z),
			((this->w > rhs.w) ? this->w : rhs.w)
		);
	}
	friend inline vec4 max(const vec4 &lhs, const vec4 &rhs) { return lhs.max(rhs); }

	inline vec4 min(const vec4 &rhs) const
	{
		return vec4(
			((this->x < rhs.x) ? this->x : rhs.x),
			((this->y < rhs.y) ? this->y : rhs.y),
			((this->z < rhs.z) ? this->z : rhs.z),
			((this->w < rhs.w) ? this->w : rhs.w)
		);
	}
	friend inline vec4 min(const vec4 &lhs, const vec4 &rhs) { return lhs.min(rhs); }

	inline vec4 clamp(const vec4 &min, const vec4 &max) const
	{
		return this->min(max).max(min);
	}
	friend inline vec4 clamp(const vec4 &v, const vec4 &min, const vec4 &max) { return v.clamp(min, max); }


	inline vec4 lerp(const vec4 &to, const T &t) const { return ((*this) + t * (to - (*this))); }
	friend inline vec4 lerp(const vec4 &from, const vec4 &to, const T &t) { return from.lerp(to, t); }

	inline vec4 lerp(const vec4 &to, const vec4 &t) const { return ((*this) + t * (to - (*this))); }
	friend inline vec4 lerp(const vec4 &from, const vec4 &to, const vec4 &t) { return from.lerp(to, t); }


	// Reference: https://en.wikipedia.org/wiki/Slerp
	// Referemce: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	vec4 slerp(const vec4 &to, const T &t) const
	{
		const T dot = this->normalize().dot(to.normalize());
		const T theta = acos(dot);
		const T s = sin(theta);

		return (sin((T(1) - t) * theta) / s * (*this) + sin(t * theta) / s * to);
	}
	friend inline vec4 slerp(const vec4 &from, const vec4 &to, const T &t) { return from.slerp(to, t); }

	// Reference: https://en.wikipedia.org/wiki/Slerp
	// Referemce: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	vec4 slerp(const vec4 &to, const vec4 &t) const
	{
		const T dot = this->normalize().dot(to.normalize());
		const T theta = acos(dot);
		const T s = sin(theta);

		return (sin((T(1) - t) * theta) / s * (*this) + sin(t * theta) / s * to);
	}
	friend inline vec4 slerp(const vec4 &from, const vec4 &to, const vec4 &t) { return from.slerp(to, t); }


	// Reference: https://en.wikipedia.org/wiki/Sign_function
	inline const vec4 signum(void) const
	{
		return vec4(
			((this->x < T(0)) ? T(-1) : ((this->x > T(0)) ? T(1) : T(0))),
			((this->y < T(0)) ? T(-1) : ((this->y > T(0)) ? T(1) : T(0))),
			((this->z < T(0)) ? T(-1) : ((this->z > T(0)) ? T(1) : T(0))),
			((this->w < T(0)) ? T(-1) : ((this->w > T(0)) ? T(1) : T(0)))
		);
	}
	friend inline vec4 signum(const vec4 &v) { return v.signum(); }

#pragma endregion

#pragma region Swizzling

#define LINALG_SWIZZLE_INDEX(index, c) \
		if ((c == 'X') || (c == 'X') || (c == 'r') || (c == 'R') || (c == 's') || (c == 'S')) index = 0; \
		else if ((c == 'y') || (c == 'Y') || (c == 'g') || (c == 'G') || (c == 't') || (c == 'T')) index = 1; \
		else if ((c == 'z') || (c == 'Z') || (c == 'b') || (c == 'B') || (c == 'p') || (c == 'P')) index = 2; \
		else if ((c == 'w') || (c == 'W') || (c == 'a') || (c == 'A') || (c == 'q') || (c == 'Q')) index = 3; \
		else index = 0;

	vec2 swizzle(const char x, const char y) const
	{
		int x_index = 0, y_index = 1;

		LINALG_SWIZZLE_INDEX(x_index, x);
		LINALG_SWIZZLE_INDEX(y_index, y);

		return vec2((*this)[x_index], (*this)[y_index]);
	}

	vec3 swizzle(const char x, const char y, const char z) const
	{
		int x_index = 0, y_index = 1, z_index = 2;

		LINALG_SWIZZLE_INDEX(x_index, x);
		LINALG_SWIZZLE_INDEX(y_index, y);
		LINALG_SWIZZLE_INDEX(z_index, z);

		return vec3((*this)[x_index], (*this)[y_index], (*this)[z_index]);
	}

	vec4 swizzle(const char x, const char y, const char z, const char w) const
	{
		int x_index = 0, y_index = 1, z_index = 2, w_index = 3;

		LINALG_SWIZZLE_INDEX(x_index, x);
		LINALG_SWIZZLE_INDEX(y_index, y);
		LINALG_SWIZZLE_INDEX(z_index, z);
		LINALG_SWIZZLE_INDEX(w_index, w);

		return vec4((*this)[x_index], (*this)[y_index], (*this)[z_index], (*this)[w_index]);
	}

#undef LINALG_SWIZZLE_INDEX

#pragma endregion
};


template<typename T>
class mat2_t
{
private:

	typedef vec2_t<T> vec2;

	typedef mat2_t<T> mat2;


public:

	static const mat2_t<T> zero;
	static const mat2_t<T> identity;


public:

	vec2 columns[2];


public:

	mat2_t(const T mainDiagonalValue = T(1))
	{
		this->columns[0] = vec2(mainDiagonalValue, T(0));
		this->columns[1] = vec2(T(0), mainDiagonalValue);
	}

	mat2_t(
		const vec2 &column1, // first column
		const vec2 &column2) // second column
	{
		this->columns[0] = column1;
		this->columns[1] = column2;
	}

	mat2_t(const vec2 columns[2])
	{
		this->columns[0] = column1;
		this->columns[1] = column2;
	}

	mat2_t(const T values[2 * 2])
	{
		for (int i = 0; i < 2 * 2; i++)
			(reinterpret_cast<T*>(this))[i] = values[i];
	}

	mat2_t(
		const T a, const T b,
		const T c, const T d)
	{
		(*this) = mat2(
			vec2(a, b),
			vec2(c, d)
		);
	}

	~mat2_t(void) {}


#pragma region Operator Overloading

#pragma region Member Access Operators

	inline vec2& operator[](const int index) { return (reinterpret_cast<vec2*>(this))[index]; }
	inline vec2 operator[](const int index) const { return ((vec2*) this)[index]; }

#pragma endregion

#pragma region Arithmetic Operators

	mat2 operator+(const mat2 &rhs) const
	{
		mat2 result;

		for (int i = 0; i < 2; i++)
			result[i] = (*this)[i] + rhs[i];

		return result;
	}

	mat2 operator-(const mat2 &rhs) const
	{
		mat2 result;

		for (int i = 0; i < 2; i++)
			result[i] = (*this)[i] - rhs[i];

		return result;
	}

	mat2 operator*(const mat2 &rhs) const
	{
		mat2 result;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				result.value(i, j, this->row(i).dot(rhs.col(j)));

		return result;
	}

	vec2 operator*(const vec2 &rhs) const
	{
		return vec2(
			(rhs.x * (*this)[0].x) + (rhs.y * (*this)[1].x),
			(rhs.x * (*this)[0].y) + (rhs.y * (*this)[1].y)
		);
	}

	friend vec2 operator*(const vec2 &lhs, const mat2 &rhs)
	{
		return vec2(
			lhs.dot(rhs[0]),
			lhs.dot(rhs[1])
		);
	}

	mat2 operator*(const T &rhs) const
	{
		mat2 result;

		for (int i = 0; i < 2; i++)
			result[i] = (*this)[i] * rhs;

		return result;
	}
	friend inline mat2 operator*(const T &lhs, const mat2 &rhs) { return (rhs * lhs); }

	mat2 operator/(const T &rhs) const
	{
		mat2 result;

		for (int i = 0; i < 2; i++)
			result[i] = (*this)[i] / rhs;

		return result;
	}

#pragma endregion
#pragma region Assignment Operators

	mat2& operator+=(const mat2 &rhs) { return ((*this) = (*this) + rhs); }
	mat2& operator-=(const mat2 &rhs) { return ((*this) = (*this) - rhs); }
	mat2& operator*=(const mat2 &rhs) { return ((*this) = (*this) * rhs); }
	mat2& operator*=(const T rhs) { return ((*this) = (*this) * rhs); }
	mat2& operator/=(const T rhs) { return ((*this) = (*this) / rhs); }

	mat2& operator=(const mat2 &rhs)
	{
		for (int i = 0; i < 2; i++)
			this->columns[i] = rhs[i];

		return (*this);
	}

#pragma endregion

#pragma region Comparison Operators
	
	bool operator==(const mat2 &rhs) const;

	inline bool operator!=(const mat2 &rhs) const { return !((*this) == rhs); }

#pragma endregion

#pragma region Cast Operators

	explicit inline operator T*(void) const { return reinterpret_cast<T*>(this); }

	inline operator mat2_t<float>(void) const { return mat2_t<float>(static_cast<vec2_t<float>>(this->columns[0]), static_cast<vec2_t<float>>(this->columns[1])); }
	inline operator mat2_t<double>(void) const { return mat2_t<double>(static_cast<vec2_t<double>>(this->columns[0]), static_cast<vec2_t<double>>(this->columns[1])); }

#pragma endregion

#pragma region Stream Operators

#ifdef _IOSTREAM_

	friend inline std::ostream& operator<<(std::ostream &stream, const mat2 &rhs)
	{
		// return (stream << "mat2 (" << rhs[0] << "," << std::endl
		// 			   << "      " << rhs[1] << ")");

		return (stream << "mat2 {" << rhs[0] << "," << std::endl
					   << "      " << rhs[1] << "}");
	}

	friend inline std::wostream& operator<<(std::wostream &stream, const mat2 &rhs)
	{
		// return (stream << L"mat2 (" << rhs[0] << L"," << std::endl
		// 			   << L"      " << rhs[1] << L")");

		return (stream << L"mat2 {" << rhs[0] << L"," << std::endl
					   << L"      " << rhs[1] << L"}");
	}

#endif

#pragma endregion

#pragma endregion


	T determinant(void) const
	{
		return ((*this)[0][0] * (*this)[1][1]) - ((*this)[1][0] * (*this)[0][1]);
	}
	friend inline T determinant(const mat2 &m) { return mat2(m).determinant(); }


	mat2& inverse(void)
	{
		const T d = T(1) / this->determinant();

		return ((*this) = (d * mat2(
			(*this)[1][1], -(*this)[0][1],
			-(*this)[1][0], (*this)[0][0]
		)));
	}
	friend inline mat2 inverse(const mat2 &m) { return mat2(m).inverse(); }


	mat2& transpose(void)
	{
		return ((*this) = mat2(
			vec2((*this)[0].x, (*this)[1].x),
			vec2((*this)[0].y, (*this)[1].y)
		));
	}
	friend inline mat2 transpose(const mat2 &m) { return mat2(m).transpose(); }


	inline vec2 col(const int index) const
	{
		return (*this)[index];
	}

	inline vec2 row(const int index) const
	{
		return vec2(
			(*this)[0][index],
			(*this)[1][index]
		);
	}


	inline T value(const int row, const int column) const
	{
		return (*this)[column][row];
	}

	inline void value(const int row, const int column, const T &value)
	{
		(*this)[column][row] = value;
	}
};


template<typename T>
class mat3_t
{
private:

	typedef vec2_t<T> vec2;
	typedef vec3_t<T> vec3;

	typedef mat2_t<T> mat2;
	typedef mat3_t<T> mat3;


public:

	static const mat3_t<T> zero;
	static const mat3_t<T> identity;


public:

	vec3 columns[3];


public:

	mat3_t(const T mainDiagonalValue = T(1))
	{
		this->columns[0] = vec3(mainDiagonalValue, T(0), T(0));
		this->columns[1] = vec3(T(0), mainDiagonalValue, T(0));
		this->columns[2] = vec3(T(0), T(0), mainDiagonalValue);
	}

	mat3_t(
		const vec3 &column1, // first column
		const vec3 &column2, // second column
		const vec3 &column3) // third column
	{
		this->columns[0] = column1;
		this->columns[1] = column2;
		this->columns[2] = column3;
	}

	mat3_t(const vec3 columns[3])
	{
		this->columns[0] = column1;
		this->columns[1] = column2;
		this->columns[2] = column3;
	}

	mat3_t(const T values[3 * 3])
	{
		for (int i = 0; i < 3 * 3; i++)
			(reinterpret_cast<T*>(this))[i] = values[i];
	}

	mat3_t(
		const T a, const T b, const T c,
		const T d, const T e, const T f,
		const T g, const T h, const T i)
	{
		(*this) = mat3(
			vec3(a, b, c),
			vec3(d, e, f),
			vec3(g, h, i)
		);
	}

	~mat3_t(void) {}


#pragma region Operator Overloading

#pragma region Member Access Operators

	inline vec3& operator[](const int index) { return (reinterpret_cast<vec3*>(this))[index]; }
	inline vec3 operator[](const int index) const { return ((vec3*) this)[index]; }

#pragma endregion

#pragma region Arithmetic Operators

	mat3 operator+(const mat3 &rhs) const
	{
		mat3 result;

		for (int i = 0; i < 3; i++)
			result[i] = (*this)[i] + rhs[i];

		return result;
	}

	mat3 operator-(const mat3 &rhs) const
	{
		mat3 result;

		for (int i = 0; i < 3; i++)
			result[i] = (*this)[i] - rhs[i];

		return result;
	}

	mat3 operator*(const mat3 &rhs) const
	{
		mat3 result;

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				result.value(i, j, this->row(i).dot(rhs.col(j)));

		return result;
	}

	vec3 operator*(const vec3 &rhs) const
	{
		return vec3(
			(rhs.x * (*this)[0].x) + (rhs.y * (*this)[1].x) + (rhs.z * (*this)[2].x),
			(rhs.x * (*this)[0].y) + (rhs.y * (*this)[1].y) + (rhs.z * (*this)[2].y),
			(rhs.x * (*this)[0].z) + (rhs.y * (*this)[1].z) + (rhs.z * (*this)[2].z)
		);
	}

	friend vec3 operator*(const vec3 &lhs, const mat3 &rhs)
	{
		return vec3(
			lhs.dot(rhs[0]),
			lhs.dot(rhs[1]),
			lhs.dot(rhs[2])
		);
	}

	mat3 operator*(const T &rhs) const
	{
		mat3 result;

		for (int i = 0; i < 3; i++)
			result[i] = (*this)[i] * rhs;

		return result;
	}
	friend inline mat3 operator*(const T &lhs, const mat3 &rhs) { return (rhs * lhs); }

	mat3 operator/(const T &rhs) const
	{
		mat3 result;

		for (int i = 0; i < 3; i++)
			result[i] = (*this)[i] / rhs;

		return result;
	}

#pragma endregion
#pragma region Assignment Operators

	mat3& operator+=(const mat3 &rhs) { return ((*this) = (*this) + rhs); }
	mat3& operator-=(const mat3 &rhs) { return ((*this) = (*this) - rhs); }
	mat3& operator*=(const mat3 &rhs) { return ((*this) = (*this) * rhs); }
	mat3& operator*=(const T rhs) { return ((*this) = (*this) * rhs); }
	mat3& operator/=(const T rhs) { return ((*this) = (*this) / rhs); }

	mat3& operator=(const mat3 &rhs)
	{
		for (int i = 0; i < 3; i++)
			this->columns[i] = rhs[i];

		return (*this);
	}

#pragma endregion

#pragma region Comparison Operators

	bool operator==(const mat3 &rhs) const;

	inline bool operator!=(const mat3 &rhs) const { return !((*this) == rhs); }

#pragma endregion

#pragma region Cast Operators

	explicit inline operator T*(void) const { return reinterpret_cast<T*>(this); }

	inline operator mat3_t<float>(void) const { return mat3_t<float>(static_cast<vec3_t<float>>(this->columns[0]), static_cast<vec3_t<float>>(this->columns[1]), static_cast<vec3_t<float>>(this->columns[2])); }
	inline operator mat3_t<double>(void) const { return mat3_t<double>(static_cast<vec3_t<double>>(this->columns[0]), static_cast<vec3_t<double>>(this->columns[1]), static_cast<vec3_t<double>>(this->columns[2])); }

#pragma endregion

#pragma region Stream Operators

#ifdef _IOSTREAM_

	friend inline std::ostream& operator<<(std::ostream &stream, const mat3 &rhs)
	{
		return (stream << "mat3 {" << rhs[0] << "," << std::endl
					   << "      " << rhs[1] << "," << std::endl
					   << "      " << rhs[2] << "}");
	}

	friend inline std::wostream& operator<<(std::wostream &stream, const mat3 &rhs)
	{
		return (stream << L"mat3 {" << rhs[0] << L"," << std::endl
					   << L"      " << rhs[1] << L"," << std::endl
					   << L"      " << rhs[2] << L"}");
	}

#endif

#pragma endregion

#pragma endregion


	T determinant(void) const
	{
		return (*this)[0][0] * ((*this)[1][1] * (*this)[2][2]) - ((*this)[2][1] * (*this)[1][2])
			- (*this)[1][0] * ((*this)[0][1] * (*this)[2][2]) - ((*this)[2][1] * (*this)[0][2])
			+ (*this)[2][0] * ((*this)[0][1] * (*this)[1][2]) - ((*this)[1][1] * (*this)[0][2]);
	}
	friend inline T determinant(const mat3 &m) { return mat3(m).determinant(); }


	mat3& inverse(void)
	{
		const T d = T(1) / this->determinant();

		return ((*this) = (d * mat3(
			((*this)[2][2] * (*this)[1][1]) - ((*this)[1][2] * (*this)[2][1]),
			((*this)[1][2] * (*this)[2][0]) - ((*this)[2][2] * (*this)[1][0]),
			((*this)[2][1] * (*this)[1][0]) - ((*this)[1][1] * (*this)[2][0]),

			((*this)[0][2] * (*this)[2][1]) - ((*this)[2][2] * (*this)[0][1]),
			((*this)[2][2] * (*this)[0][0]) - ((*this)[0][2] * (*this)[2][0]),
			((*this)[0][1] * (*this)[2][0]) - ((*this)[2][1] * (*this)[0][0]),

			((*this)[1][2] * (*this)[0][1]) - ((*this)[0][2] * (*this)[1][1]),
			((*this)[0][2] * (*this)[1][0]) - ((*this)[1][2] * (*this)[0][0]),
			((*this)[1][1] * (*this)[0][0]) - ((*this)[0][1] * (*this)[1][0])
		)));
	}
	friend inline mat3 inverse(const mat3 &m) { return mat3(m).inverse(); }


	mat3& transpose(void)
	{
		return ((*this) = mat3(
			vec3((*this)[0].x, (*this)[1].x, (*this)[2].x),
			vec3((*this)[0].y, (*this)[1].y, (*this)[2].y),
			vec3((*this)[0].z, (*this)[1].z, (*this)[2].z)
		));
	}
	friend inline mat3 transpose(const mat3 &m) { return mat3(m).transpose(); }


	inline vec3 col(const int index) const
	{
		return (*this)[index];
	}

	inline vec3 row(const int index) const
	{
		return vec3(
			(*this)[0][index],
			(*this)[1][index],
			(*this)[2][index]
		);
	}


	inline T value(const int row, const int column) const
	{
		return (*this)[column][row];
	}

	inline void value(const int row, const int column, const T &value)
	{
		(*this)[column][row] = value;
	}
};


template<typename T>
class mat4_t
{
private:

	typedef vec2_t<T> vec2;
	typedef vec3_t<T> vec3;
	typedef vec4_t<T> vec4;

	typedef mat2_t<T> mat2;
	typedef mat3_t<T> mat3;
	typedef mat4_t<T> mat4;


public:

	static const mat4_t<T> zero;
	static const mat4_t<T> identity;


public:

	vec4 columns[4];


public:

	mat4_t(const T mainDiagonalValue = T(1))
	{
		this->columns[0] = vec4(mainDiagonalValue, T(0), T(0), T(0));
		this->columns[1] = vec4(T(0), mainDiagonalValue, T(0), T(0));
		this->columns[2] = vec4(T(0), T(0), mainDiagonalValue, T(0));
		this->columns[3] = vec4(T(0), T(0), T(0), mainDiagonalValue);
	}

	mat4_t(
		const vec4 &column1, // first column
		const vec4 &column2, // second column
		const vec4 &column3, // third column
		const vec4 &column4) // fourth column
	{
		this->columns[0] = column1;
		this->columns[1] = column2;
		this->columns[2] = column3;
		this->columns[3] = column4;
	}

	mat4_t(const vec4 columns[4])
	{
		this->columns[0] = column1;
		this->columns[1] = column2;
		this->columns[2] = column3;
		this->columns[3] = column4;
	}

	mat4_t(const T values[4 * 4])
	{
		for (int i = 0; i < 4 * 4; i++)
			(reinterpret_cast<T*>(this))[i] = values[i];
	}

	mat4_t(
		const T a, const T b, const T c, const T d, // first column
		const T e, const T f, const T g, const T h, // second column
		const T i, const T j, const T k, const T l, // third column
		const T m, const T n, const T o, const T p) // fourth column
	{
		(*this) = mat4(
			vec4(a, b, c, d),
			vec4(e, f, g, h),
			vec4(i, j, k, l),
			vec4(m, n, o, p)
		);
	}

	mat4_t(const mat2 &m)
	{
		(*this) = mat4(
			vec4(m[0], T(0), T(0)),
			vec4(m[1], T(0), T(0)),
			vec4(T(0), T(0), T(1), T(0)),
			vec4(T(0), T(0), T(0), T(1))
		);
	}

	mat4_t(const mat3 &m)
	{
		(*this) = mat4(
			vec4(m[0], T(0)),
			vec4(m[1], T(0)),
			vec4(m[2], T(0)),
			vec4(T(0), T(0), T(0), T(1))
		);
	}

	~mat4_t(void) {}


#pragma region Operator Overloading

#pragma region Member Access Operators

	inline vec4& operator[](const int index) { return (reinterpret_cast<vec4*>(this))[index]; }
	inline vec4 operator[](const int index) const { return ((vec4*) this)[index]; }

#pragma endregion

#pragma region Arithmetic Operators

	mat4 operator+(const mat4 &rhs) const
	{
		mat4 result;

		for (int i = 0; i < 4; i++)
			result[i] = (*this)[i] + rhs[i];

		return result;
	}

	mat4 operator-(const mat4 &rhs) const
	{
		mat4 result;

		for (int i = 0; i < 4; i++)
			result[i] = (*this)[i] - rhs[i];

		return result;
	}

	mat4 operator*(const mat4 &rhs) const
	{
		mat4 result;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				result.value(i, j, this->row(i).dot(rhs.col(j)));

		return result;
	}

	vec4 operator*(const vec4 &rhs) const
	{
		return vec4(
			(rhs.x * (*this)[0].x) + (rhs.y * (*this)[1].x) + (rhs.z * (*this)[2].x) + (rhs.w * (*this)[3].x),
			(rhs.x * (*this)[0].y) + (rhs.y * (*this)[1].y) + (rhs.z * (*this)[2].y) + (rhs.w * (*this)[3].y),
			(rhs.x * (*this)[0].z) + (rhs.y * (*this)[1].z) + (rhs.z * (*this)[2].z) + (rhs.w * (*this)[3].z),
			(rhs.x * (*this)[0].w) + (rhs.y * (*this)[1].w) + (rhs.z * (*this)[2].w) + (rhs.w * (*this)[3].w)
		);
	}

	friend vec4 operator*(const vec4 &lhs, const mat4 &rhs)
	{
		return vec4(
			lhs.dot(rhs[0]),
			lhs.dot(rhs[1]),
			lhs.dot(rhs[2]),
			lhs.dot(rhs[3])
		);
	}

	mat4 operator*(const T &rhs) const
	{
		mat4 result;

		for (int i = 0; i < 4; i++)
			result[i] = (*this)[i] * rhs;

		return result;
	}
	friend inline mat4 operator*(const T &lhs, const mat4 &rhs) { return (rhs * lhs); }

	mat4 operator/(const T &rhs) const
	{
		mat4 result;

		for (int i = 0; i < 4; i++)
			result[i] = (*this)[i] / rhs;

		return result;
	}

#pragma endregion
#pragma region Assignment Operators

	mat4& operator+=(const mat4 &rhs) { return ((*this) = (*this) + rhs); }
	mat4& operator-=(const mat4 &rhs) { return ((*this) = (*this) - rhs); }
	mat4& operator*=(const mat4 &rhs) { return ((*this) = (*this) * rhs); }
	mat4& operator*=(const T rhs) { return ((*this) = (*this) * rhs); }
	mat4& operator/=(const T rhs) { return ((*this) = (*this) / rhs); }

	mat4& operator=(const mat4 &rhs)
	{
		for (int i = 0; i < 4; i++)
			this->columns[i] = rhs[i];

		return (*this);
	}

#pragma endregion

#pragma region Comparison Operators

	bool operator==(const mat4 &rhs) const;

	inline bool operator!=(const mat4 &rhs) const { return !((*this) == rhs); }

#pragma endregion

#pragma region Cast Operators

	explicit inline operator T*(void) const { return reinterpret_cast<T*>(this); }

	inline operator mat4_t<float>(void) const { return mat4_t<float>(static_cast<vec4_t<float>>(this->columns[0]), static_cast<vec4_t<float>>(this->columns[1]), static_cast<vec4_t<float>>(this->columns[2]), static_cast<vec4_t<float>>(this->columns[3])); }
	inline operator mat4_t<double>(void) const { return mat4_t<double>(static_cast<vec4_t<double>>(this->columns[0]), static_cast<vec4_t<double>>(this->columns[1]), static_cast<vec4_t<double>>(this->columns[2]), static_cast<vec4_t<double>>(this->columns[3])); }

#pragma endregion

#pragma region Stream Operators

#ifdef _IOSTREAM_

	friend inline std::ostream& operator<<(std::ostream &stream, const mat4 &rhs)
	{
		return (stream << "mat4 {" << rhs[0] << "," << std::endl
					   << "      " << rhs[1] << "," << std::endl
					   << "      " << rhs[2] << "," << std::endl
					   << "      " << rhs[3] << "}");
	}

	friend inline std::wostream& operator<<(std::wostream &stream, const mat4 &rhs)
	{
		return (stream << L"mat4 {" << rhs[0] << L"," << std::endl
					   << L"      " << rhs[1] << L"," << std::endl
					   << L"      " << rhs[2] << L"," << std::endl
					   << L"      " << rhs[3] << L"}");
	}

#endif

#pragma endregion

#pragma endregion


	T determinant(void) const
	{
		return (
			((*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0]) *
			((*this)[2][2] * (*this)[3][3] - (*this)[2][3] * (*this)[3][2]) -
			((*this)[0][0] * (*this)[1][2] - (*this)[0][2] * (*this)[1][0]) *
			((*this)[2][1] * (*this)[3][3] - (*this)[2][3] * (*this)[3][1]) +
			((*this)[0][0] * (*this)[1][3] - (*this)[0][3] * (*this)[1][0]) *
			((*this)[2][1] * (*this)[3][2] - (*this)[2][2] * (*this)[3][1]) +
			((*this)[0][1] * (*this)[1][2] - (*this)[0][2] * (*this)[1][1]) *
			((*this)[2][0] * (*this)[3][3] - (*this)[2][3] * (*this)[3][0]) -
			((*this)[0][1] * (*this)[1][3] - (*this)[0][3] * (*this)[1][1]) *
			((*this)[2][0] * (*this)[3][2] - (*this)[2][2] * (*this)[3][0]) +
			((*this)[0][2] * (*this)[1][3] - (*this)[0][3] * (*this)[1][2]) *
			((*this)[2][0] * (*this)[3][1] - (*this)[2][1] * (*this)[3][0])
		);
	}
	friend inline T determinant(const mat4 &m) { return mat4(m).determinant(); }


	mat4& inverse(void)
	{
		T *m = reinterpret_cast<T*>(this);
		T inv[4 * 4];

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		T det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (LINALG_FEQUAL(det, 0.0))
		{
			(*this) = mat4::identity;
		}
		else
		{
			det = T(1) / det;

			for (int i = 0; i < 4 * 4; i++)
				m[i] = inv[i] * det;
		}

		return (*this);
	}
	friend inline mat4 inverse(const mat4 &m) { return mat4(m).inverse(); }


	mat4& transpose(void)
	{
		return ((*this) = mat4(
			vec4((*this)[0].x, (*this)[1].x, (*this)[2].x, (*this)[3].x),
			vec4((*this)[0].y, (*this)[1].y, (*this)[2].y, (*this)[3].y),
			vec4((*this)[0].z, (*this)[1].z, (*this)[2].z, (*this)[3].z),
			vec4((*this)[0].w, (*this)[1].w, (*this)[2].w, (*this)[3].w)
		));
	}
	friend inline mat4 transpose(const mat4 &m) { return mat4(m).transpose(); }


	inline vec4 col(const int index) const
	{
		return (*this)[index];
	}

	inline vec4 row(const int index) const
	{
		return vec4(
			(*this)[0][index],
			(*this)[1][index],
			(*this)[2][index],
			(*this)[3][index]
		);
	}


	inline T value(const int row, const int column) const
	{
		return (*this)[column][row];
	}

	inline void value(const int row, const int column, const T &value)
	{
		(*this)[column][row] = value;
	}


	mat4& translate(const vec3 &translation)
	{
		return ((*this) *= mat4(
			vec4(T(1), T(0), T(0), T(0)),
			vec4(T(0), T(1), T(0), T(0)),
			vec4(T(0), T(0), T(1), T(0)),
			vec4(translation.x, translation.y, translation.z, T(1))
		));
	}
	friend inline mat4 translate(const mat4 &m, const vec3 &translation) { return mat4(m).translate(translation); }

	inline mat4& translate(const T tx, const T ty, const T tz = T(0)) { return (*this).translate(vec3(tx, ty, tz)); }
	friend inline mat4 translate(const mat4 &m, const T tx, const T ty, const T tz = T(0)) { return mat4(m).translate(tx, ty, tz); }


	mat4& scale(const vec3 &scaling)
	{
		return ((*this) *= mat4(
			vec4(scaling.x, T(0), T(0), T(0)),
			vec4(T(0), scaling.y, T(0), T(0)),
			vec4(T(0), T(0), scaling.z, T(0)),
			vec4(T(0), T(0), T(0), T(1))
		));
	}
	friend inline mat4 scale(const mat4 &m, const vec3 &scaling) { return mat4(m).scale(scaling); }

	inline mat4& scale(const T sx, const T sy, const T sz = T(1)) { return (*this).scale(vec3(sx, sy, sz)); }
	friend inline mat4 scale(const mat4 &m, const T sx, const T sy, const T sz = T(1)) { return mat4(m).scale(sx, sy, sz); }

	inline mat4& scale(const T scaling) { return (*this).scale(vec3(scaling, scaling, scaling)); }
	friend inline mat4 scale(const mat4 &m, const T scaling) { return mat4(m).scale(scaling, scaling, scaling); }


	mat4& rotate(const T radians, const vec3 &axis)
	{
		vec3 axisNormalized = axis;

		if (!axisNormalized.isUnitVector())
			axisNormalized.normalize();

		const T s = sin(radians);
		const T c = cos(radians);

		const T x = axisNormalized.x;
		const T y = axisNormalized.y;
		const T z = axisNormalized.z;

		return ((*this) *= mat4(
			(x * x * (T(1) - c) + c),
			(x * y * (T(1) - c) - z * s),
			(x * z * (T(1) - c) + y * s),
			T(0),

			(y * x * (T(1) - c) + z * s),
			(y * y * (T(1) - c) + c),
			(y * z * (T(1) - c) - x * s),
			T(0),

			(x * z * (T(1) - c) - y * s),
			(y * z * (T(1) - c) + x * s),
			(z * z * (T(1) - c) + c),
			T(0),

			T(0), T(0), T(0), T(1)
		));
	}
	friend inline mat4 rotate(const mat4 &m, const T radians, const vec3 &axis) { return mat4(m).rotate(radians, axis); }

	inline mat4& rotate(const T radians, const T ax, const T ay, const T az) { return (*this).rotate(radians, vec3(ax, ay, az)); }
	friend inline mat4 rotate(const mat4 &m, const T radians, const T ax, const T ay, const T az) { return mat4(m).rotate(radians, ax, ay, az); }


	inline mat4& rotateDegrees(const T degrees, const vec3 &axis) { return this->rotate(degrees * T(LINALG_DEG2RAD), axis); }
	friend inline mat4 rotateDegrees(const mat4 &m, const T degrees, const vec3 &axis) { return mat4(m).rotateDegrees(degrees, axis); }

	inline mat4& rotateDegrees(const T degrees, const T ax, const T ay, const T az) { return (*this).rotateDegrees(degrees, vec3(ax, ay, az)); }
	friend inline mat4 rotateDegrees(const mat4 &m, const T degrees, const T ax, const T ay, const T az) { return mat4(m).rotateDegrees(degrees, ax, ay, az); }


	mat4& rotateX(const T radians)
	{
		const T s = sin(radians);
		const T c = cos(radians);

		return ((*this) *= mat4(
			vec4(T(1), T(0), T(0), T(0)),
			vec4(T(0), c, -s, T(0)),
			vec4(T(0), s, c, T(0)),
			vec4(T(0), T(0), T(0), T(1))
		));
	}
	friend inline mat4 rotateX(const mat4 &m, const T radians) { return mat4(m).rotateX(radians); }

	inline mat4& rotateXDegrees(const T degrees) { return this->rotateX(degrees * T(LINALG_DEG2RAD)); }
	friend inline mat4 rotateXDegrees(const mat4 &m, const T degrees) { return mat4(m).rotateXDegrees(degrees); }


	mat4& rotateY(const T radians)
	{
		const T s = sin(radians);
		const T c = cos(radians);

		return ((*this) *= mat4(
			vec4(c, T(0), s, T(0)),
			vec4(T(0), T(1), T(0), T(0)),
			vec4(-s, T(0), c, T(0)),
			vec4(T(0), T(0), T(0), T(1))
		));
	}
	friend inline mat4 rotateY(const mat4 &m, const T radians) { return mat4(m).rotateY(radians); }

	inline mat4& rotateYDegrees(const T degrees) { return this->rotateY(degrees * T(LINALG_DEG2RAD)); }
	friend inline mat4 rotateYDegrees(const mat4 &m, const T degrees) { return mat4(m).rotateYDegrees(degrees); }


	mat4& rotateZ(const T radians)
	{
		const T s = sin(radians);
		const T c = cos(radians);

		return ((*this) *= mat4(
			vec4(c, -s, T(0), T(0)),
			vec4(s, c, T(0), T(0)),
			vec4(T(0), T(0), T(1), T(0)),
			vec4(T(0), T(0), T(0), T(1))
		));
	}
	friend inline mat4 rotateZ(const mat4 &m, const T radians) { return mat4(m).rotateZ(radians); }

	inline mat4& rotateZDegrees(const T degrees) { return this->rotateZ(degrees * T(LINALG_DEG2RAD)); }
	friend inline mat4 rotateZDegrees(const mat4 &m, const T degrees) { return mat4(m).rotateZDegrees(degrees); }


	// Skew along the x-axis and y-axis
	mat4& skew(const T x, const T y)
	{
		return ((*this) *= mat4(
			T(1), tan(x), T(0), T(0),
			tan(y), T(1), T(0), T(0),
			T(0), T(0), T(1), T(0),
			T(0), T(0), T(0), T(1)
		));
	}
	friend inline mat4 skew(const mat4 &m, const T x, const T y) { return mat4(m).skew(x, y); }

	inline mat4& skewDegrees(const T x, const T y) { return this->skew(x * T(LINALG_DEG2RAD), y * T(LINALG_DEG2RAD)); }
	friend inline mat4 skewDegrees(const mat4 &m, const T x, const T y) { return mat4(m).skewDegrees(x, y); }


	// Skew along the x-axis
	mat4& skewX(const T radians)
	{
		return ((*this) *= mat4(
			T(1), tan(radians), T(0), T(0),
			T(0), T(1), T(0), T(0),
			T(0), T(0), T(1), T(0),
			T(0), T(0), T(0), T(1)
		));
	}
	friend inline mat4 skewX(const mat4 &m, const T radians) { return mat4(m).skewX(radians); }

	inline mat4& skewXDegrees(const T degrees) { return this->skewX(degrees * T(LINALG_DEG2RAD)); }
	friend inline mat4 skewXDegrees(const mat4 &m, const T degrees) { return mat4(m).skewXDegrees(degrees); }


	// Skew along the y-axis
	mat4& skewY(const T radians)
	{
		return ((*this) *= mat4(
			T(1), T(0), T(0), T(0),
			tan(radians), T(1), T(0), T(0),
			T(0), T(0), T(1), T(0),
			T(0), T(0), T(0), T(1)
		));
	}
	friend inline mat4 skewY(const mat4 &m, const T radians) { return mat4(m).skewY(radians); }

	inline mat4& skewYDegrees(const T degrees) { return this->skewY(degrees * T(LINALG_DEG2RAD)); }
	friend inline mat4 skewYDegrees(const mat4 &m, const T degrees) { return mat4(m).skewYDegrees(degrees); }


	mat4& perspective(const T fov, const T aspect, const T zNear, const T zFar)
	{
		const T fovRads = fov * T(LINALG_DEG2RAD);

		const T range = tan(fovRads * T(0.5)) * zNear;
		const T sx = (zNear * T(2)) / (range * aspect + range * aspect);
		const T sy = zNear / range;
		const T sz = -(zFar + zNear) / (zFar - zNear);
		const T pz = -(zFar * zNear * T(2)) / (zFar - zNear);

		return ((*this) *= mat4(
			vec4(sx, T(0), T(0), T(0)),
			vec4(T(0), sy, T(0), T(0)),
			vec4(T(0), T(0), sz, T(-1)),
			vec4(T(0), T(0), pz, T(0))
		));
	}


	mat4& orthographic(const T left, const T right, const T bottom, const T top, const T zNear = T(-1), const T zFar = T(1))
	{
		return ((*this) *= mat4(
			vec4((T(2) / (right - left)), T(0), T(0), T(0)),
			vec4(T(0), (T(2) / (top - bottom)), T(0), T(0)),
			vec4(T(0), T(0), (T(-2) / (zFar - zNear)), T(0)),
			vec4(-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((zFar + zNear) / (zFar - zNear)), T(1))
		));
	}

	mat4& frustum(const T left, const T right, const T bottom, const T top, const T zNear = T(-1), const T zFar = T(1))
	{
		return (*this).orthographic(left, right, bottom, top, zNear, zFar);
	}


	mat4& viewport(const T x, const T y, const T width, const T height)
	{
		const T half_width = width * T(0.5);
		const T half_height = height * T(0.5);

		// This is only correct when glDepthRangef(0.0f, 1.0f)
		const T zNear = T(0);
		const T zFar = T(1);

		return ((*this) *= mat4(
			half_width, T(0), T(0), T(0),
			T(0), half_height, T(0), T(0),
			T(0), T(0), (zFar - zNear) * T(0.5), T(0),
			x + half_width, y + half_height, (zNear + zFar) * T(0.5), T(1)
		));
	}


	mat4& lookAt(const vec3 &eye, const vec3 &at, const vec3 &up = vec3(T(0), T(1), T(0)))
	{
		vec3 z_axis = (eye - at).normalize();
		vec3 x_axis = up.cross(z_axis).normalize();
		vec3 y_axis = z_axis.cross(x_axis);

		return ((*this) *= mat4(
			x_axis.x, y_axis.x, z_axis.x, T(0),
			x_axis.y, y_axis.y, z_axis.y, T(0),
			x_axis.z, y_axis.z, z_axis.z, T(0),
			-x_axis.dot(eye), -y_axis.dot(eye), -z_axis.dot(eye), T(1)
		));
	}


	inline vec3 getTranslation(void) const
	{
		const vec4 translation = (*this)[3];

		return vec3(translation.x, translation.y, translation.z);
	}
};


// It isn't an optimal solution, to inline all template functions that has explicit specialization.
// But it is needed if we don't want to run into "multiple definitions" compilation error.


#pragma region vec2

#pragma region Static Members

template<typename T> const vec2_t<T> vec2_t<T>::zero = vec2_t<T>(T(0), T(0));
template<typename T> const vec2_t<T> vec2_t<T>::one = vec2_t<T>(T(1), T(1));

template<typename T> const vec2_t<T> vec2_t<T>::up = vec2_t<T>(T(0), T(1));
template<typename T> const vec2_t<T> vec2_t<T>::down = vec2_t<T>(T(0), T(-1));

template<typename T> const vec2_t<T> vec2_t<T>::left = vec2_t<T>(T(-1), T(0));
template<typename T> const vec2_t<T> vec2_t<T>::right = vec2_t<T>(T(1), T(0));

#pragma endregion

#pragma region Comparison Operators

template<typename T> inline bool vec2_t<T>::operator==(const vec2 &rhs) const
{
	return ((this->x == rhs.x) && (this->y == rhs.y));
}

template<> inline bool fvec2::operator==(const fvec2 &rhs) const
{
	return (LINALG_FEQUAL(this->x, rhs.x) && LINALG_FEQUAL(this->y, rhs.y));
}

template<> inline bool dvec2::operator==(const dvec2 &rhs) const
{
	return (LINALG_DEQUAL(this->x, rhs.x) && LINALG_DEQUAL(this->y, rhs.y));
}

#pragma endregion

#pragma region Normalize

template<> inline fvec2 fvec2::normalize(const float &to) const
{
	float length = this->length();

	if (!LINALG_FEQUAL(length, 0.0f) && !LINALG_FEQUAL(length, to))
	{
		length = to / length;

		return fvec2(*this) * length;
	}

	return (*this);
}

template<> inline dvec2 dvec2::normalize(const double &to) const
{
	double length = this->length();

	if (!LINALG_DEQUAL(length, 0.0) && !LINALG_DEQUAL(length, to))
	{
		length = to / length;

		return dvec2(*this) * length;
	}

	return (*this);
}

#pragma endregion

#pragma region Check Vector Kind

template<typename T> bool vec2_t<T>::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return ((this->x == 0) && (this->y == 0));
}

template<> bool fvec2::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return (LINALG_FEQUAL(this->x, 0.0f) && LINALG_FEQUAL(this->y, 0.0f));
}

template<> bool dvec2::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return (LINALG_DEQUAL(this->x, 0.0) && LINALG_DEQUAL(this->y, 0.0));
}


template<> inline bool fvec2::isUnitVector() const
{
	return LINALG_FEQUAL(this->lengthSquared(), 1.0f);
}

template<> inline bool dvec2::isUnitVector() const
{
	return LINALG_DEQUAL(this->lengthSquared(), 1.0f);
}


template<> bool fvec2::isNormalized(const float &to) const
{
	const float length = this->length();

	return LINALG_FEQUAL(length, to);
}

template<> bool dvec2::isNormalized(const double &to) const
{
	const double length = this->length();

	return LINALG_DEQUAL(length, to);
}


template<typename T> bool vec2_t<T>::isOrthogonalTo(const vec2 &rhs) const
{
	return (this->dot(rhs) == 0);
}

template<> bool fvec2::isOrthogonalTo(const vec2 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 0.0f));
}

template<> bool dvec2::isOrthogonalTo(const vec2 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 0.0));
}


template<typename T> bool vec2_t<T>::isPerpendicularTo(const vec2 &rhs) const
{
	return (this->dot(rhs) == 0);
}

template<> bool fvec2::isPerpendicularTo(const vec2 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 0.0f));
}

template<> bool dvec2::isPerpendicularTo(const vec2 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 0.0));
}


template<typename T> bool vec2_t<T>::isParallelTo(const vec2 &rhs) const
{
	return (this->dot(rhs) == 1);
}

template<> bool fvec2::isParallelTo(const vec2 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 1.0f));
}

template<> bool dvec2::isParallelTo(const vec2 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 1.0));
}

#pragma endregion

#pragma region Validate sizeof Templated Objects

#ifdef DEBUG

#ifndef STATIC_ASSERT
#	define STATIC_ASSERT(bool_constexpr) static_assert(bool_constexpr, #bool_constexpr)
#endif

STATIC_ASSERT(sizeof(vec2_t<float>) == (sizeof(float) * 2));
STATIC_ASSERT(sizeof(vec2_t<double>) == (sizeof(double) * 2));

STATIC_ASSERT(sizeof(vec2_t<signed int>) == (sizeof(signed int) * 2));
STATIC_ASSERT(sizeof(vec2_t<unsigned int>) == (sizeof(unsigned int) * 2));

STATIC_ASSERT(sizeof(vec2_t<bool>) == (sizeof(bool) * 2));

STATIC_ASSERT(sizeof(vec2_t<signed long>) == (sizeof(signed long) * 2));
STATIC_ASSERT(sizeof(vec2_t<unsigned long>) == (sizeof(unsigned long) * 2));

STATIC_ASSERT(sizeof(vec2_t<signed long long>) == (sizeof(signed long long) * 2));
STATIC_ASSERT(sizeof(vec2_t<unsigned long long>) == (sizeof(unsigned long long) * 2));

#endif

#pragma endregion

#pragma endregion


#pragma region vec3

#pragma region Static Members

template<typename T> const vec3_t<T> vec3_t<T>::zero = vec3_t<T>(T(0), T(0), T(0));
template<typename T> const vec3_t<T> vec3_t<T>::one = vec3_t<T>(T(1), T(1), T(1));

template<typename T> const vec3_t<T> vec3_t<T>::up = vec3_t<T>(T(0), T(1), T(0));
template<typename T> const vec3_t<T> vec3_t<T>::down = vec3_t<T>(T(0), T(-1), T(0));

template<typename T> const vec3_t<T> vec3_t<T>::left = vec3_t<T>(T(-1), T(0), T(0));
template<typename T> const vec3_t<T> vec3_t<T>::right = vec3_t<T>(T(1), T(0), T(0));

template<typename T> const vec3_t<T> vec3_t<T>::forward = vec3_t<T>(T(0), T(0), T(1));
template<typename T> const vec3_t<T> vec3_t<T>::backward = vec3_t<T>(T(0), T(0), T(-1));

#pragma endregion

#pragma region Comparison Operators

template<typename T> inline bool vec3_t<T>::operator==(const vec3 &rhs) const
{
	return ((this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z));
}

template<> inline bool fvec3::operator==(const fvec3 &rhs) const
{
	return (LINALG_FEQUAL(this->x, rhs.x) && LINALG_FEQUAL(this->y, rhs.y) && LINALG_FEQUAL(this->z, rhs.z));
}

template<> inline bool dvec3::operator==(const dvec3 &rhs) const
{
	return (LINALG_DEQUAL(this->x, rhs.x) && LINALG_DEQUAL(this->y, rhs.y) && LINALG_DEQUAL(this->z, rhs.z));
}

#pragma endregion

#pragma region Normalize

template<> inline fvec3 fvec3::normalize(const float &to) const
{
	float length = this->length();

	if (!LINALG_FEQUAL(length, 0.0f) && !LINALG_FEQUAL(length, to))
	{
		length = to / length;

		return fvec3(*this) * length;
	}

	return (*this);
}

template<> inline dvec3 dvec3::normalize(const double &to) const
{
	double length = this->length();

	if (!LINALG_DEQUAL(length, 0.0) && !LINALG_DEQUAL(length, to))
	{
		length = to / length;

		return dvec3(*this) * length;
	}

	return (*this);
}

#pragma endregion

#pragma region Check Vector Kind

template<typename T> bool vec3_t<T>::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return ((this->x == 0) && (this->y == 0) && (this->z == 0));
}

template<> bool fvec3::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return (LINALG_FEQUAL(this->x, 0.0f) && LINALG_FEQUAL(this->y, 0.0f) && LINALG_FEQUAL(this->z, 0.0f));
}

template<> bool dvec3::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return (LINALG_DEQUAL(this->x, 0.0) && LINALG_DEQUAL(this->y, 0.0) && LINALG_DEQUAL(this->z, 0.0));
}


template<> inline bool fvec3::isUnitVector() const
{
	return LINALG_FEQUAL(this->lengthSquared(), 1.0f);
}

template<> inline bool dvec3::isUnitVector() const
{
	return LINALG_DEQUAL(this->lengthSquared(), 1.0f);
}


template<> bool fvec3::isNormalized(const float &to) const
{
	const float length = this->length();

	return LINALG_FEQUAL(length, to);
}

template<> bool dvec3::isNormalized(const double &to) const
{
	const double length = this->length();

	return LINALG_DEQUAL(length, to);
}


template<typename T> bool vec3_t<T>::isOrthogonalTo(const vec3 &rhs) const
{
	return (this->dot(rhs) == 0);
}

template<> bool fvec3::isOrthogonalTo(const vec3 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 0.0f));
}

template<> bool dvec3::isOrthogonalTo(const vec3 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 0.0));
}


template<typename T> bool vec3_t<T>::isPerpendicularTo(const vec3 &rhs) const
{
	return (this->dot(rhs) == 0);
}

template<> bool fvec3::isPerpendicularTo(const vec3 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 0.0f));
}

template<> bool dvec3::isPerpendicularTo(const vec3 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 0.0));
}


template<typename T> bool vec3_t<T>::isParallelTo(const vec3 &rhs) const
{
	return (this->dot(rhs) == 1);
}

template<> bool fvec3::isParallelTo(const vec3 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 1.0f));
}

template<> bool dvec3::isParallelTo(const vec3 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 1.0));
}

#pragma endregion

#pragma region Validate sizeof Templated Objects

#ifdef DEBUG

#ifndef STATIC_ASSERT
#	define STATIC_ASSERT(bool_constexpr) static_assert(bool_constexpr, #bool_constexpr)
#endif

STATIC_ASSERT(sizeof(vec3_t<float>) == (sizeof(float) * 3));
STATIC_ASSERT(sizeof(vec3_t<double>) == (sizeof(double) * 3));

STATIC_ASSERT(sizeof(vec3_t<signed int>) == (sizeof(signed int) * 3));
STATIC_ASSERT(sizeof(vec3_t<unsigned int>) == (sizeof(unsigned int) * 3));

STATIC_ASSERT(sizeof(vec3_t<bool>) == (sizeof(bool) * 3));

STATIC_ASSERT(sizeof(vec3_t<signed long>) == (sizeof(signed long) * 3));
STATIC_ASSERT(sizeof(vec3_t<unsigned long>) == (sizeof(unsigned long) * 3));

STATIC_ASSERT(sizeof(vec3_t<signed long long>) == (sizeof(signed long long) * 3));
STATIC_ASSERT(sizeof(vec3_t<unsigned long long>) == (sizeof(unsigned long long) * 3));

#endif

#pragma endregion

#pragma endregion


#pragma region vec4

#pragma region Static Members

template<typename T> const vec4_t<T> vec4_t<T>::zero = vec4_t<T>(T(0), T(0), T(0), T(0));
template<typename T> const vec4_t<T> vec4_t<T>::one = vec4_t<T>(T(1), T(1), T(1), T(1));

#pragma endregion

#pragma region Comparison Operators

template<typename T> inline bool vec4_t<T>::operator==(const vec4 &rhs) const
{
	return ((this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z) && (this->w == rhs.w));
}

template<> inline bool fvec4::operator==(const fvec4 &rhs) const
{
	return (LINALG_FEQUAL(this->x, rhs.x) && LINALG_FEQUAL(this->y, rhs.y) && LINALG_FEQUAL(this->z, rhs.z) && LINALG_FEQUAL(this->w, rhs.w));
}

template<> inline bool dvec4::operator==(const dvec4 &rhs) const
{
	return (LINALG_DEQUAL(this->x, rhs.x) && LINALG_DEQUAL(this->y, rhs.y) && LINALG_DEQUAL(this->z, rhs.z) && LINALG_DEQUAL(this->w, rhs.w));
}

#pragma endregion

#pragma region Normalize

template<> inline fvec4 fvec4::normalize(const float &to) const
{
	float length = this->length();

	if (!LINALG_FEQUAL(length, 0.0f) && !LINALG_FEQUAL(length, to))
	{
		length = to / length;

		return fvec4(*this) * length;
	}

	return (*this);
}

template<> inline dvec4 dvec4::normalize(const double &to) const
{
	double length = this->length();

	if (!LINALG_DEQUAL(length, 0.0) && !LINALG_DEQUAL(length, to))
	{
		length = to / length;

		return dvec4(*this) * length;
	}

	return (*this);
}

#pragma endregion

#pragma region Check Vector Kind

template<typename T> bool vec4_t<T>::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return ((this->x == 0) && (this->y == 0) && (this->z == 0) && (this->w == 0));
}

template<> bool fvec4::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return (LINALG_FEQUAL(this->x, 0.0f) && LINALG_FEQUAL(this->y, 0.0f) && LINALG_FEQUAL(this->z, 0.0f) && LINALG_FEQUAL(this->w, 0.0f));
}

template<> bool dvec4::isNullVector(void) const
{
	// It's faster to just compare to 0, than to calculate the length
	return (LINALG_DEQUAL(this->x, 0.0) && LINALG_DEQUAL(this->y, 0.0) && LINALG_DEQUAL(this->z, 0.0) && LINALG_DEQUAL(this->w, 0.0));
}


template<> inline bool fvec4::isUnitVector() const
{
	return LINALG_FEQUAL(this->lengthSquared(), 1.0f);
}

template<> inline bool dvec4::isUnitVector() const
{
	return LINALG_DEQUAL(this->lengthSquared(), 1.0f);
}


template<> bool fvec4::isNormalized(const float &to) const
{
	const float length = this->length();

	return LINALG_FEQUAL(length, to);
}

template<> bool dvec4::isNormalized(const double &to) const
{
	const double length = this->length();

	return LINALG_DEQUAL(length, to);
}


template<typename T> bool vec4_t<T>::isOrthogonalTo(const vec4 &rhs) const
{
	return (this->dot(rhs) == 0);
}

template<> bool fvec4::isOrthogonalTo(const vec4 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 0.0f));
}

template<> bool dvec4::isOrthogonalTo(const vec4 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 0.0));
}


template<typename T> bool vec4_t<T>::isPerpendicularTo(const vec4 &rhs) const
{
	return (this->dot(rhs) == 0);
}

template<> bool fvec4::isPerpendicularTo(const vec4 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 0.0f));
}

template<> bool dvec4::isPerpendicularTo(const vec4 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 0.0));
}


template<typename T> bool vec4_t<T>::isParallelTo(const vec4 &rhs) const
{
	return (this->dot(rhs) == 1);
}

template<> bool fvec4::isParallelTo(const vec4 &rhs) const
{
	const float dot = this->dot(rhs);

	return (LINALG_FEQUAL(dot, 1.0f));
}

template<> bool dvec4::isParallelTo(const vec4 &rhs) const
{
	const double dot = this->dot(rhs);

	return (LINALG_DEQUAL(dot, 1.0));
}

#pragma endregion

#pragma region Validate sizeof Templated Objects

#ifdef DEBUG

#ifndef STATIC_ASSERT
#	define STATIC_ASSERT(bool_constexpr) static_assert(bool_constexpr, #bool_constexpr)
#endif

STATIC_ASSERT(sizeof(vec4_t<float>) == (sizeof(float) * 4));
STATIC_ASSERT(sizeof(vec4_t<double>) == (sizeof(double) * 4));

STATIC_ASSERT(sizeof(vec4_t<signed int>) == (sizeof(signed int) * 4));
STATIC_ASSERT(sizeof(vec4_t<unsigned int>) == (sizeof(unsigned int) * 4));

STATIC_ASSERT(sizeof(vec4_t<bool>) == (sizeof(bool) * 4));

STATIC_ASSERT(sizeof(vec4_t<signed long>) == (sizeof(signed long) * 4));
STATIC_ASSERT(sizeof(vec4_t<unsigned long>) == (sizeof(unsigned long) * 4));

STATIC_ASSERT(sizeof(vec4_t<signed long long>) == (sizeof(signed long long) * 4));
STATIC_ASSERT(sizeof(vec4_t<unsigned long long>) == (sizeof(unsigned long long) * 4));

#endif

#pragma endregion

#pragma endregion


#pragma region mat2

#pragma region Static Members

template<typename T> const mat2_t<T> mat2_t<T>::zero = mat2_t<T>(T(0));
template<typename T> const mat2_t<T> mat2_t<T>::identity = mat2_t<T>(T(1));

#pragma endregion

#pragma region Comparison Operators

template<typename T> inline bool mat2_t<T>::operator==(const mat2_t &rhs) const
{
	for (int i = 0; i < 2; i++)
		if ((*this)[i] != rhs[i])
			return false;

	return true;
}

template<> inline bool mat2_t<float>::operator==(const mat2_t<float> &rhs) const
{
	for (int i = 0; i < 2; i++)
		if (!LINALG_FEQUAL((*this)[i], rhs[i]))
			return false;

	return true;
}

template<> inline bool mat2_t<double>::operator==(const mat2_t<double> &rhs) const
{
	for (int i = 0; i < 2; i++)
		if (!LINALG_DEQUAL((*this)[i], rhs[i]))
			return false;

	return true;
}

#pragma endregion

#pragma endregion


#pragma region mat3

#pragma region Static Members

template<typename T> const mat3_t<T> mat3_t<T>::zero = mat3_t<T>(T(0));
template<typename T> const mat3_t<T> mat3_t<T>::identity = mat3_t<T>(T(1));

#pragma endregion

#pragma region Comparison Operators

template<typename T> inline bool mat3_t<T>::operator==(const mat3_t &rhs) const
{
	for (int i = 0; i < 3; i++)
		if ((*this)[i] != rhs[i])
			return false;

	return true;
}

template<> inline bool mat3_t<float>::operator==(const mat3_t<float> &rhs) const
{
	for (int i = 0; i < 3; i++)
		if (!LINALG_FEQUAL((*this)[i], rhs[i]))
			return false;

	return true;
}

template<> inline bool mat3_t<double>::operator==(const mat3_t<double> &rhs) const
{
	for (int i = 0; i < 3; i++)
		if (!LINALG_DEQUAL((*this)[i], rhs[i]))
			return false;

	return true;
}

#pragma endregion

#pragma endregion


#pragma region mat4

#pragma region Static Members

template<typename T> const mat4_t<T> mat4_t<T>::zero = mat4_t<T>(T(0));
template<typename T> const mat4_t<T> mat4_t<T>::identity = mat4_t<T>(T(1));

#pragma endregion

#pragma region Comparison Operators

template<typename T> inline bool mat4_t<T>::operator==(const mat4_t &rhs) const
{
	for (int i = 0; i < 4; i++)
		if ((*this)[i] != rhs[i])
			return false;

	return true;
}

template<> inline bool mat4_t<float>::operator==(const mat4_t<float> &rhs) const
{
	for (int i = 0; i < 4; i++)
		if (!LINALG_FEQUAL((*this)[i], rhs[i]))
			return false;

	return true;
}

template<> inline bool mat4_t<double>::operator==(const mat4_t<double> &rhs) const
{
	for (int i = 0; i < 4; i++)
		if (!LINALG_DEQUAL((*this)[i], rhs[i]))
			return false;

	return true;
}

#pragma endregion

#pragma endregion


// Enable structure padding
#pragma pack(pop)


#endif