#pragma once
#include "transform.h"
#include <string>

// 着色器程序类型
class Shader
{
	unsigned int program = 0;

public:

	unsigned int id() const;

	~Shader();

	// 从文件中读取顶点和片段着色器并链接，返回是否成功
	bool load_from_file(const std::string& vert_filename, const std::string& frag_filename);

	// 从内存中读取顶点和片段着色器并链接，返回是否成功
	bool load_from_str(const std::string& vert, const std::string& frag);

	// 是否已经加载
	bool ready() const;

	// 释放着色器程序
	void release();

	// 使用着色器程序
	void use();


	// 获取uniform变量id
	unsigned int get_uniform_loc(const std::string& name);

	// 设置int型uniform
	void set_uniform_i(const std::string& name, int v);
	// 设置float型uniform
	void set_uniform_f(const std::string& name, float v);
	// 设置vec3型uniform
	void set_uniform_vec3(const std::string& name, const vec3& v);
	// 设置vec4型uniform
	void set_uniform_vec4(const std::string& name, const vec4& v);
	// 设置mat4型uniform
	void set_uniform_mat4(const std::string& name, const mat4& v);


	// 绑定空着色器
	static void unuse();

};