#pragma once
#include "transform.h"
#include <string>

// ��ɫ����������
class Shader
{
	unsigned int program = 0;

public:

	unsigned int id() const;

	~Shader();

	// ���ļ��ж�ȡ�����Ƭ����ɫ�������ӣ������Ƿ�ɹ�
	bool load_from_file(const std::string& vert_filename, const std::string& frag_filename);

	// ���ڴ��ж�ȡ�����Ƭ����ɫ�������ӣ������Ƿ�ɹ�
	bool load_from_str(const std::string& vert, const std::string& frag);

	// �Ƿ��Ѿ�����
	bool ready() const;

	// �ͷ���ɫ������
	void release();

	// ʹ����ɫ������
	void use();


	// ��ȡuniform����id
	unsigned int get_uniform_loc(const std::string& name);

	// ����int��uniform
	void set_uniform_i(const std::string& name, int v);
	// ����float��uniform
	void set_uniform_f(const std::string& name, float v);
	// ����vec3��uniform
	void set_uniform_vec3(const std::string& name, const vec3& v);
	// ����vec4��uniform
	void set_uniform_vec4(const std::string& name, const vec4& v);
	// ����mat4��uniform
	void set_uniform_mat4(const std::string& name, const mat4& v);


	// �󶨿���ɫ��
	static void unuse();

};