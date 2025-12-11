#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 cameraPos;
    vec3 lightPos;
    vec3 lightColor;
    float time;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 cameraPos;
layout(location = 4) out vec3 lightPos;
layout(location = 5) out vec3 lightColor;
layout(location = 6) out float time;

void main() {
    fragPos = vec3(ubo.model * vec4(inPosition, 1.0));
    fragNormal = mat3(transpose(inverse(ubo.model))) * inNormal;
    fragTexCoord = inTexCoord;
    cameraPos = ubo.cameraPos;
    lightPos = ubo.lightPos;
    lightColor = ubo.lightColor;
    time = ubo.time;

    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
}
