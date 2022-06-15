#include "transform.h"
#include "shader.h"
#include <glad/gl.h>
#include <vector>

namespace trans
{
	namespace model
	{
		glm::mat4 m(1.0f);
		std::vector<glm::mat4> stack;
		void identity()
		{
			m = glm::mat4(1.0f);
		}
		void push()
		{
			stack.push_back(m);
		}
		void pop()
		{
			m = stack.front();
			stack.pop_back();
		}
		void apply(Shader& shader)
		{
			shader.use();
			shader.set_uniform_mat4("model", m);
		}

		void translate(const vec3& v)
		{
			m = glm::translate(m, v);
		}
		void rotate(float rad, const vec3& axis)
		{
			m = glm::rotate(m, rad, axis);
		}
		void scale(const vec3& v)
		{
			m = glm::scale(m, v);
		}
		void look_at(const vec3& eye_pos, const vec3& center_pos, const vec3& head_v)
		{
			m = glm::lookAt(eye_pos, center_pos, head_v);
		}
	}

	namespace view
	{
		glm::mat4 m(1.0f);
		std::vector<glm::mat4> stack;
		void identity()
		{
			m = glm::mat4(1.0f);
		}
		void push()
		{
			stack.push_back(m);
		}
		void pop()
		{
			m = stack.front();
			stack.pop_back();
		}
		void apply(Shader& shader)
		{
			shader.use();
			shader.set_uniform_mat4("view", m);
		}

		void translate(const vec3& v)
		{
			m = glm::translate(m, v);
		}
		void rotate(float rad, const vec3& axis)
		{
			m = glm::rotate(m, rad, axis);
		}
		void scale(const vec3& v)
		{
			m = glm::scale(m, v);
		}
		void look_at(const vec3& eye_pos, const vec3& center_pos, const vec3& head_v)
		{
			m = glm::lookAt(eye_pos, center_pos, head_v);
		}
	}

	namespace projection
	{
		glm::mat4 m(1.0f);
		std::vector<glm::mat4> stack;
		void identity()
		{
			m = glm::mat4(1.0f);
		}
		void push()
		{
			stack.push_back(m);
		}
		void pop()
		{
			m = stack.front();
			stack.pop_back();
		}
		void apply(Shader& shader)
		{
			shader.use();
			shader.set_uniform_mat4("projection", m);
		}

		void ortho(float left, float right, float top, float buttom, float z_near, float z_far)
		{
			m = glm::ortho(left, right, buttom, top, z_near, z_far);
		}
		void perspective(float fovy, float aspect, float z_near, float z_far)
		{
			m = glm::perspective(fovy, aspect, z_near, z_far);
		}
	}

	void identity(mat4& m)
	{
		m = mat4(1.0f);
	}
	void translate(mat4& m, const vec3& v)
	{
		m = glm::translate(m, v);
	}
	void rotate(mat4& m, float rad, const vec3& axis)
	{
		m = glm::rotate(m, rad, axis);
	}
	void scale(mat4& m, const vec3& v)
	{
		m = glm::scale(m, v);
	}
	void look_at(mat4& m, const vec3& eye_pos, const vec3& center_pos, const vec3& head_v)
	{
		m = glm::lookAt(eye_pos, center_pos, head_v);
	}
}