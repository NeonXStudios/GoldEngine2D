#version 330 core
layout(location = 0) in vec3 inPosition;
out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = inPosition;
    gl_Position = projection * view * vec4(inPosition, 1.0);
}
