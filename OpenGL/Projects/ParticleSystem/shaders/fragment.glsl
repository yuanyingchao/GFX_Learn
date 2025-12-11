#version 330 core

in vec3 Color;
out vec4 FragColor;

void main()
{
    // 创建圆形粒子
    vec2 p = gl_PointCoord * 2.0 - 1.0;
    float radius = length(p);
    if (radius > 1.0) {
        discard;
    }
    
    // 计算透明度，边缘更透明
    float alpha = 1.0 - radius;
    
    FragColor = vec4(Color, alpha);
}
