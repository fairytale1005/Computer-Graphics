
#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;


void Test()
{
	//矩阵用法
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = 2.3;   m(1, 2) = 0.99;
	m(2, 1) = 1.1;   m(2, 2) = 0;
	cout << "Matrix:" << endl;
	cout << m << endl;

	//向量用法
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	//v[4] = 1.0;
	v.normalize();//归一化

	//输出矩阵与向量相乘的结果
	cout << "result:" << endl;
	cout << m * v << endl;
}

vector<Eigen::Vector3f> VertexTransform(vector<Eigen::Vector3f> vertices)
{
	vector<Eigen::Vector3f> rlt(vertices.size());
	Eigen::Vector4f v;

	Eigen::Matrix4f M = mViewPort * mProjection * mModelView;

	for (int i = 0; i < vertices.size(); ++i)
	{
		v[3] = 1.0;
		v.head<3>() = vertices[i];

		v = M * v;
		rlt[i][0] = v[0] / v[3];
		rlt[i][1] = v[1] / v[3];
		rlt[i][2] = v[2] / v[3];
	}
	return rlt;
}

Eigen::Matrix4f myLookAt(float ex, float ey, float ez, float atx, float aty, float atz, float upx, float upy, float upz)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数

	Eigen::Vector3f e(ex, ey, ez);
	Eigen::Vector3f g(atx-ex, aty-ey, atz-ez);
	Eigen::Vector3f t(upx, upy, upz);

	Eigen::Vector3f w = -g / g.norm();
	Eigen::Vector3f u = t.cross(w) / t.cross(w).norm();
	Eigen::Vector3f v = w.cross(u);//差积
	m << u, v, w, e,
		0, 0, 0, 1;//设置矩阵元素
	m = m.inverse().eval();//矩阵转置

	//请在上面空白处完成此函数

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = costheta;   m(1, 2) = -sintheta;
	m(2, 1) = sintheta;   m(2, 2) = costheta;

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(1, 1) = 1;
	m(3, 3) = 1;
	m(0, 0) = costheta;   m(0, 2) = sintheta;
	m(2, 0) = -sintheta;   m(2, 2) = costheta;

	mModelView *= m;
	//cout << m << endl;
	return m;
}

Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(2, 2) = 1;
	m(3, 3) = 1;
	m(0, 0) = costheta;   m(0, 1) = -sintheta;
	m(1, 0) = sintheta;   m(1, 1) = costheta;

	mModelView *= m;
	//cout << m << endl;
	return m;
}


Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(1, 1) = 1;
	m(2, 2) = 1;
	m(3, 3) = 1;

	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;

	mModelView *= m;

	//cout << m << endl;
	return m;
}

Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;

	m.setIdentity();//To be modified

	mModelView *= m;

	return m;
}

Eigen::Matrix4f myFrustum(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数

	m(0, 0) = 2 * n / (r - l); m(0, 2) = (r + l) / (r - l);
	m(1, 1) = 2 * n / (t - b); m(1, 2) = -(t + b) / (t - b);
	m(2, 2) = -(f + n) / (f - n); m(2, 3) = -2 * f * n / (f - n);
	m(3, 2) = -1;

	//请在上面空白处完成此函数

	mProjection *= m;
	return m;
}

Eigen::Matrix4f myOrtho(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数
	
	//设置m
	m(0, 0) = 2 / (r - l); m(0, 3) = -(r + l) / (r - l);
	m(1, 1) = 2 / (t - b); m(1, 3) = -(t + b) / (t - b);
	m(2, 2) = -2 / (f - n); m(2, 3) = -(f + n) / (f - n);
	m(3, 3) = 1;

	//请在上面空白处完成此函数

	mProjection *= m;

	return m;
}

Eigen::Matrix4f myViewPort(float x, float y, float w, float h)
{
	Eigen::Matrix4f m;
	m.setZero();
	//请在下面空白处完成此函数
	//glOrtho(GLdouble left, GLdouble right, Gldouble bottom, GLdouble top, GLdouble near, GLdouble far);
	//		 (-1.0,				1.0,			 -1.0,			1.0,			-1.0,			 1.0)
	/*
	* WinX = Ox + (x+1)/2*width
	* WinY = Oy + (y+1)/2*height
	* WinZ = (z+1)/2 (规范化到[0,1]之间)
	* */
	m(0, 0) = h / 2.0f;
	m(0, 3) = x + w / 2.0f;
	m(1, 1) = h / 2.0f;//注意此处y是负值,不知道为什么又不用了
	m(1, 3) = y + h / 2.0f;
	m(2, 2) = 1 / 2.0f;	
	m(2, 3) = 1 / 2.0f;
	m(3, 3) = 1;
	//请在上面空白处完成此函数

	mViewPort = m;

	return m;
}