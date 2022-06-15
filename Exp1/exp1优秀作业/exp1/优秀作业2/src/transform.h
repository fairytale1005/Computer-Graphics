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
	// 模型变换（局部坐标->世界坐标）
	namespace model
	{
		// 单位化
		void identity();
		// 入栈
		void push();
		// 出栈
		void pop();
		// 提交变换
		void apply(Shader& shader);

		// 平移
		void translate(const vec3& v);
		// 旋转
		void rotate(float rad, const vec3& axis);
		// 缩放
		void scale(const vec3& v);
		// 看向
		void look_at(const vec3& eye_pos, const vec3& center_pos, const vec3& head_v);
	}

	// 视图变换（世界坐标->观察坐标）
	namespace view
	{
		// 单位化
		void identity();
		// 入栈
		void push();
		// 出栈
		void pop();
		// 提交变换
		void apply(Shader& shader);

		// 平移
		void translate(const vec3& v);
		// 旋转
		void rotate(float rad, const vec3& axis);
		// 缩放
		void scale(const vec3& v);
		// 看向
		void look_at(const vec3& eye_pos, const vec3& center_pos, const vec3& head_v);
	}

	// 投影变换（观察坐标->裁剪坐标）
	namespace projection
	{
		// 单位化
		void identity();
		// 入栈
		void push();
		// 出栈
		void pop();

		// 正交投影
		void ortho(float left, float right, float top, float buttom, float z_near, float z_far);
		// 透视投影
		void perspective(float fovy, float aspect, float z_near, float z_far);
		// 提交变换
		void apply(Shader& shader);
	}

	// 重置某矩阵为单位矩阵
	void identity(mat4& m);
	// 对某矩阵进行平移
	void translate(mat4& m, const vec3& v);
	// 对某矩阵进行旋转
	void rotate(mat4& m, float rad, const vec3& axis);
	// 对某矩阵进行缩放
	void scale(mat4& m, const vec3& v);
	// 对某矩阵进行看向
	void look_at(mat4& m, const vec3& eye_pos, const vec3& center_pos, const vec3& head_v);
}