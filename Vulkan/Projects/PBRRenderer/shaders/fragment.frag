#version 450

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragLightPos;
layout(location = 4) in vec3 fragViewPos;

layout(location = 0) out vec4 outColor;

// PBR材质参数
const float metallic = 0.5;
const float roughness = 0.3;

// 环境光
const vec3 ambientColor = vec3(0.03);

// 光源颜色
const vec3 lightColor = vec3(1.0, 1.0, 1.0);

// 物体颜色
const vec3 albedo = vec3(0.8, 0.8, 0.8);

// 法线分布函数 - Trowbridge-Reitz GGX
float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = 3.14159265359 * denom * denom;

    return num / denom;
}

// 几何遮蔽函数 - Schlick-GGX
float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

// 几何遮蔽函数 - Smith
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

// 菲涅尔方程 - Schlick近似
vec3 FresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main() {
    // 标准化法向量
    vec3 N = normalize(fragNormal);
    // 视线方向
    vec3 V = normalize(fragViewPos - fragPos);
    // 光照方向
    vec3 L = normalize(fragLightPos - fragPos);
    // 半程向量
    vec3 H = normalize(V + L);

    // 计算反射率
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    // 计算光源与法线的夹角
    float NdotL = max(dot(N, L), 0.0);
    // 计算视线与法线的夹角
    float NdotV = max(dot(N, V), 0.0);

    // BRDF项
    float D = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = FresnelSchlick(max(dot(H, V), 0.0), F0);

    // 镜面反射项
    vec3 numerator = D * G * F;
    float denominator = 4.0 * NdotV * NdotL + 0.0001;
    vec3 specular = numerator / denominator;

    // 漫反射项
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    // 环境光
    vec3 ambient = ambientColor * albedo;

    // 直接光照
    vec3 radiance = lightColor * NdotL;
    vec3 diffuse = albedo / 3.14159265359;

    // 总光照
    vec3 lighting = (kD * diffuse + specular) * radiance;
    lighting += ambient;

    // 简单的曝光调整
    lighting = lighting / (lighting + vec3(1.0));
    // Gamma校正
    lighting = pow(lighting, vec3(1.0 / 2.2));

    outColor = vec4(lighting, 1.0);
}
