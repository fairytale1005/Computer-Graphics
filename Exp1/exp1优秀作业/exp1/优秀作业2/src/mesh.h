#pragma once
#include "shader.h"
#include <vector>

// 顶点数据类型
struct Vertex
{
	vec3 position;
	vec3 color;
};

// 三角形类型
struct Triangle
{
	Vertex p1;
	Vertex p2;
	Vertex p3;
};

// 三角网格类型
class Mesh
{
	unsigned vao;
	unsigned vbo;

	// 三角形顶点数据
	std::vector<Triangle> triangles;

public:
	
	// 添加一个三角形
	void add(const Triangle& triangle);

	// 清空
	void clear();

	// 初始化绘制
	void init();

	// 绘制
	void draw(Shader& shader);

	~Mesh();

};