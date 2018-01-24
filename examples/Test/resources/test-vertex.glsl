#version 330 core

in vec3 position;
in vec3 color;
in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vsColor;
out vec2 vsTexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vsColor = color;
	vsTexCoord = texCoord;
}
