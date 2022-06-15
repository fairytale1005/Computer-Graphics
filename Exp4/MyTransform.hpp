#pragma once

#include <Eigen/Core>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;

//�˺���������Ķ�
void Test()
{
	//����eigen���÷����ɲο���
	//http://eigen.tuxfamily.org/dox/group__QuickRefPage.html
	
	//�����÷�
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = 2.3;   m(1, 2) = 0.99;
	m(2, 1) = 1.1;   m(2, 2) = 0;
	cout << "Matrix:" << endl;
	cout << m << endl;

	//�����÷�
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	v.normalize();//��һ��

	//���������������˵Ľ��
	cout << "result:" << endl;
	cout << m * v << endl;
}

//�˺�������Ķ�
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

//��x����תangle�Ƕ�
Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//��������հ״���ɴ˺���

	m(0, 0) = 1;
	m(1, 1) = cos(theta);
	m(1, 2) = -sin(theta);
	m(2, 1) = sin(theta);
	m(2, 2) = cos(theta);
	m(3, 3) = 1;

	//��������հ״���ɴ˺���

	mModelView *= m;
	return m;
}

//��y����תangle�Ƕ�
Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//��������հ״���ɴ˺���

	m(0, 0) = cos(theta);
	m(0, 2) = sin(theta);
	m(1, 1) = 1;
	m(2, 0) = -sin(theta);
	m(2, 2) = cos(theta);
	m(3, 3) = 1;

	//��������հ״���ɴ˺���

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//��z����תangle�Ƕ�
Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//��������հ״���ɴ˺���

	m(0, 0) = cos(theta);
	m(0, 1) = -sin(theta);
	m(1, 0) = sin(theta);
	m(1, 1) = cos(theta);
	m(2, 2) = 1;
	m(3, 3) = 1;

	//��������հ״���ɴ˺���

	mModelView *= m;
	//cout << m << endl;
	return m;
}


//ƽ��x��y��z
Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();
	
	//��������հ״���ɴ˺���
	
	m(0, 0) = 1;
	m(1, 1) = 1;
	m(2, 2) = 1;
	m(3, 3) = 1;
	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;

	//��������հ״���ɴ˺���

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//����(x,y,z)(ע��:����δ��һ���� ��תangle�Ƕ�
Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;
	
	//��������հ״���ɴ˺���

	Eigen::Vector3f r;
	//����������һ��
	r[0] = x;
	r[1] = y;
	r[2] = z;
	r.normalize();
	m.setZero();
	m(0, 0) = cos(theta) + (1 - cos(theta)) * r[0] * r[0];
	m(0, 1) = (1 - cos(theta)) * r[0] * r[1] - r[2] * sin(theta);
	m(0, 2) = (1 - cos(theta)) * r[0] * r[2] + r[1] * sin(theta);
	m(1, 0) = (1 - cos(theta)) * r[1] * r[0] + r[2] * sin(theta);
	m(1, 1) = cos(theta) + (1 - cos(theta)) * r[1] * r[1];
	m(1, 2) = (1 - cos(theta)) * r[2] * r[1] - r[0] * sin(theta);
	m(2, 0) = (1 - cos(theta)) * r[0] * r[2] - r[1] * sin(theta);
	m(2, 1) = (1 - cos(theta)) * r[1] * r[2] + r[0] * sin(theta);
	m(2, 2) = cos(theta) + (1 - cos(theta)) * r[2] * r[2];
	m(3, 3) = 1;

	//��������հ״���ɴ˺���

	mModelView *= m;

	return m;
}