#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Shader;

namespace trans
{
	// ģ�ͱ任���ֲ�����->�������꣩
	namespace model
	{
		// ��λ��
		void identity();
		// ��ջ
		void push();
		// ��ջ
		void pop();
		// �ύ�任
		void apply(Shader& shader);

		// ƽ��
		void translate(const vec3& v);
		// ��ת
		void rotate(float rad, const vec3& axis);
		// ����
		void scale(const vec3& v);
		// ����
		void look_at(const vec3& eye_pos, const vec3& center_pos, const vec3& head_v);
	}

	// ��ͼ�任����������->�۲����꣩
	namespace view
	{
		// ��λ��
		void identity();
		// ��ջ
		void push();
		// ��ջ
		void pop();
		// �ύ�任
		void apply(Shader& shader);

		// ƽ��
		void translate(const vec3& v);
		// ��ת
		void rotate(float rad, const vec3& axis);
		// ����
		void scale(const vec3& v);
		// ����
		void look_at(const vec3& eye_pos, const vec3& center_pos, const vec3& head_v);
	}

	// ͶӰ�任���۲�����->�ü����꣩
	namespace projection
	{
		// ��λ��
		void identity();
		// ��ջ
		void push();
		// ��ջ
		void pop();

		// ����ͶӰ
		void ortho(float left, float right, float top, float buttom, float z_near, float z_far);
		// ͸��ͶӰ
		void perspective(float fovy, float aspect, float z_near, float z_far);
		// �ύ�任
		void apply(Shader& shader);
	}

	// ����ĳ����Ϊ��λ����
	void identity(mat4& m);
	// ��ĳ�������ƽ��
	void translate(mat4& m, const vec3& v);
	// ��ĳ���������ת
	void rotate(mat4& m, float rad, const vec3& axis);
	// ��ĳ�����������
	void scale(mat4& m, const vec3& v);
	// ��ĳ������п���
	void look_at(mat4& m, const vec3& eye_pos, const vec3& center_pos, const vec3& head_v);
}