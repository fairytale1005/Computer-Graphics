#include <glad/gl.h>
#include <fstream>
#include <iostream>
#include <string>
#include "shader.h"

bool Shader::load_from_file(const std::string& vert_filename, const std::string& frag_filename)
{
	std::string vert_src;
	std::string frag_src;

	// ���ļ��ж�ȡ������ɫ��
	{
		std::ifstream in(vert_filename);
		if (!in)
		{
			std::cout << "��ȡ�ļ�ʧ��: " << vert_filename << std::endl;
			return false;
		}

		std::string line;
		while (getline(in, line))
			vert_src += line, vert_src.push_back('\n');
	}

	// ���ļ��ж�ȡƬ����ɫ��
	{
		std::ifstream in(frag_filename);
		if (!in)
		{
			std::cout << "��ȡ�ļ�ʧ��: " << frag_filename << std::endl;
			return false;
		}

		std::string line;
		while (getline(in, line))
			frag_src += line, frag_src.push_back('\n');
	}

	return load_from_str(vert_src, frag_src);
}

bool Shader::load_from_str(const std::string& vert_src, const std::string& frag_src)
{
	// ����Ѿ����������ͷ�
	if (program)
		release();

	unsigned int vert_shader;
	unsigned int frag_shader;

	// ���붥����ɫ��
	{
		vert_shader = glCreateShader(GL_VERTEX_SHADER);

		auto vert_src_str = vert_src.c_str();
		glShaderSource(vert_shader, 1, &vert_src_str, NULL);
		glCompileShader(vert_shader);

		int  success;
		char infoLog[512];
		glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vert_shader, 512, NULL, infoLog);
			std::cout << "���붥����ɫ��ʱ��������: " << ":\n" << infoLog << std::endl;
			glDeleteShader(vert_shader);
			return false;
		}
	}

	// ����Ƭ����ɫ��
	{
		frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

		auto frag_src_str = frag_src.c_str();
		glShaderSource(frag_shader, 1, &frag_src_str, NULL);
		glCompileShader(frag_shader);

		int  success;
		char infoLog[512];
		glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
			std::cout << "����ƬԪ��ɫ��ʱ��������: " << ":\n" << infoLog << std::endl;
			glDeleteShader(vert_shader);
			glDeleteShader(frag_shader);
			return false;
		}
	}

	// ������ɫ������
	program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	int  success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "������ɫ������ʱ��������: \n" << infoLog << std::endl;
		release();
		return false;
	}

	return true;
}

bool Shader::ready() const
{
	return program;
}

void Shader::release()
{
	if (program)
	{
		glDeleteProgram(program);
		program = 0;
	}
}

unsigned int Shader::id() const
{
	return program;
}

Shader::~Shader()
{
	release();
}

void Shader::use()
{
	if (!program)
		std::cout << "ERROR: ʹ��δ���ص���ɫ��" << std::endl;
	else
		glUseProgram(program);
}

unsigned int Shader::get_uniform_loc(const std::string& name)
{
	return glGetUniformLocation(program, name.c_str());
}

void Shader::set_uniform_i(const std::string& name, int v)
{
	auto loc = glGetUniformLocation(program, name.c_str());
	glUniform1i(loc, v);
}

void Shader::set_uniform_f(const std::string& name, float v)
{
	auto loc = glGetUniformLocation(program, name.c_str());
	glUniform1f(loc, v);
}

void Shader::set_uniform_vec3(const std::string& name, const vec3& v)
{
	auto loc = glGetUniformLocation(program, name.c_str());
	glUniform3f(loc, v.x, v.y, v.z);
}

void Shader::set_uniform_vec4(const std::string& name, const vec4& v)
{
	auto loc = glGetUniformLocation(program, name.c_str());
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void Shader::set_uniform_mat4(const std::string& name, const mat4& v)
{
	auto loc = glGetUniformLocation(program, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::unuse()
{
	glUseProgram(0);
}
