#version 330 core

in vec3 vert_color;

out vec3 frag_color;

#define GAMMA (1.0)


void main()
{
	frag_color = vert_color;

	// gamma½ÃÕý
	frag_color = pow(frag_color, vec3(1.0 / GAMMA));
}