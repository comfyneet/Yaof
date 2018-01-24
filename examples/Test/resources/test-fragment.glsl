#version 330 core

in vec3 vsColor;
in vec2 vsTexCoord;

uniform sampler2D containerTexture;
uniform sampler2D awesomeFaceTexture;

out vec4 color;

void main()
{
	color = mix(texture(awesomeFaceTexture, vsTexCoord), texture(containerTexture, vsTexCoord), 0.2) /** vec4(vsColor, 1.0)*/;
}
