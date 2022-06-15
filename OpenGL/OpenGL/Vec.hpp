#pragma once

#include <initializer_list>
#include <cmath>

namespace gl {

template <typename derived, typename valueType, int dimension>
class VecBase {
	public:
		VecBase();
		VecBase(std::initializer_list<valueType> ls);
		derived& operator = (const derived& a);
		double Length();
};

template <typename T, int dim>
class Vec : public VecBase<Vec<T, dim>, T, dim> {
	public:
		using VecBase<Vec<T, dim>, T, dim>::VecBase;
		union {
			T dims[dim];
			struct {
				T x, y, z, w;
			};
		};
};

template <typename T>
class Vec<T, 2> : public VecBase<Vec<T, 2>, T, 2> {
	public:
		using VecBase<Vec<T, 2>, T, 2>::VecBase;
		union {
			T dims[2];
			struct {
				T x, y;
			};
		};
};

template <typename T>
class Vec<T, 3> : public VecBase<Vec<T, 3>, T, 3> {
	public:
		using VecBase<Vec<T, 3>, T, 3>::VecBase;
		union {
			T dims[3];
			struct {
				T x, y, z;
			};
		};
};

using Vec2i = Vec<int, 2>;
using Vec3i = Vec<int, 3>;
using Vec4i = Vec<int, 4>;
using Vec2f = Vec<float, 2>;
using Vec3f = Vec<float, 3>;
using Vec4f = Vec<float, 4>;

template <typename T, int dim>
bool operator < (const Vec<T, dim>& a, const Vec<T, dim>& b) {
	for (int i = 0; i < dim; ++i)
		if (a.dims[i] != b.dims[i])
			return a.dims[i] < b.dims[i];
	return false;
}

template <typename T, int dim>
bool operator == (const Vec<T, dim>& a, const Vec<T, dim>& b) {
	for (int i = 0; i < dim; ++i)
		if (a.dims[i] != b.dims[i])
			return false;
	return true;
}

template <typename T, int dim>
Vec<T, dim> operator + (const Vec<T, dim>& a, const Vec<T, dim>& b) {
	Vec<T, dim> temp;
	for (int i = 0; i < dim; ++i)
		temp.dims[i] = a.dims[i] + b.dims[i];
	return temp;
}

template <typename T, int dim>
Vec<T, dim> operator - (const Vec<T, dim>& a, const Vec<T, dim>& b) {
	Vec<T, dim> temp;
	for (int i = 0; i < dim; ++i)
		temp.dims[i] = a.dims[i] - b.dims[i];
	return temp;
}

template <typename T, int dim>
Vec<T, dim>& operator += (Vec<T, dim>& a, const Vec<T, dim>& b) {
	for (int i = 0; i < dim; ++i)
		a.dims[i] += b.dims[i];
	return a;
}

template <typename T, int dim>
Vec<T, dim>& operator -= (Vec<T, dim>& a, const Vec<T, dim>& b) {
	for (int i = 0; i < dim; ++i)
		a.dims[i] -= b.dims[i];
	return a;
}

template <typename T, int dim>
Vec<T, dim> operator / (const Vec<T, dim>& a, const T& b) {
	Vec<T, dim> temp;
	for (int i = 0; i < dim; ++i)
		temp.dims[i] = a.dims[i] / b;
	return temp;
}

template <typename derived, typename valueType, int dimension>
inline VecBase<derived, valueType, dimension>::VecBase() {
	for (auto& i : static_cast<derived*>(this)->dims)
		i = 0;
}

template <typename derived, typename valueType, int dimension>
inline VecBase<derived, valueType, dimension>::VecBase(std::initializer_list<valueType> ls) {
	for (auto& i : static_cast<derived*>(this)->dims)
		i = 0;
	for (auto i = ls.begin(); i != ls.end() && i - ls.begin() < dimension; ++i)
		static_cast<derived*>(this)->dims[i - ls.begin()] = *i;
}

template<typename derived, typename valueType, int dimension>
inline derived& VecBase<derived, valueType, dimension>::operator=(const derived& a) {
	for (int i = 0; i < dimension; ++i)
		static_cast<derived*>(this)->dims[i] = a.dims[i];
}

template<typename derived, typename valueType, int dimension>
inline double VecBase<derived, valueType, dimension>::Length() {
	double res = 0;
	for (int i = 0; i < dimension; ++i) {
		valueType temp = static_cast<derived*>(this)->dims[i];
		res += temp * temp;
	}
	return sqrt(res);
}

}