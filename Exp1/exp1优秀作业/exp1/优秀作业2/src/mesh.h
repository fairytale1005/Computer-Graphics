#pragma once
#include "shader.h"
#include <vector>

// ������������
struct Vertex
{
	vec3 position;
	vec3 color;
};

// ����������
struct Triangle
{
	Vertex p1;
	Vertex p2;
	Vertex p3;
};

// ������������
class Mesh
{
	unsigned vao;
	unsigned vbo;

	// �����ζ�������
	std::vector<Triangle> triangles;

public:
	
	// ���һ��������
	void add(const Triangle& triangle);

	// ���
	void clear();

	// ��ʼ������
	void init();

	// ����
	void draw(Shader& shader);

	~Mesh();

};