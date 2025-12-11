#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in float aSize;

out vec3 Color;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    Color = aColor;
    gl_Position = projection * view * vec4(aPos, 1.0);
    gl_PointSize = aSize * 200.0; // 调整点大小，考虑屏幕距离
}
