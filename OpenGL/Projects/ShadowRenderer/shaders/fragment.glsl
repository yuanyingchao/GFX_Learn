#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform sampler2D shadowMap;

// 计算阴影
float ShadowCalculation(vec4 fragPosLightSpace) {
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    
    // 将坐标转换到 [0,1] 范围
    projCoords = projCoords * 0.5 + 0.5;
    
    // 从阴影贴图中获取最近的深度
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    
    // 获取当前片段在光源空间中的深度
    float currentDepth = projCoords.z;
    
    // 计算阴影偏移，减少阴影失真
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    
    // 计算PCF（百分比更近过滤）以获得更柔和的阴影
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    // 如果投影坐标超出范围，不应用阴影
    if(projCoords.z > 1.0) {
        shadow = 0.0;
    }
    
    return shadow;
}

void main() {
    // 材质颜色
    vec3 objectColor = vec3(0.8, 0.3, 0.3);
    
    // 环境光
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // 镜面反射
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    // 计算阴影
    float shadow = ShadowCalculation(FragPosLightSpace);
    
    // 最终颜色
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) * objectColor;
    
    FragColor = vec4(result, 1.0);
}
