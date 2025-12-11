#version 450

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 cameraPos;
layout(location = 4) in vec3 lightPos;
layout(location = 5) in vec3 lightColor;
layout(location = 6) in float time;

layout(location = 0) out vec4 outColor;

struct Ray {
    vec3 origin;
    vec3 direction;
};

struct Sphere {
    vec3 center;
    float radius;
    vec3 color;
    float metallic;
    float roughness;
};

struct Plane {
    vec3 point;
    vec3 normal;
    vec3 color;
    float metallic;
    float roughness;
};

struct HitRecord {
    bool hit;
    float t;
    vec3 point;
    vec3 normal;
    vec3 color;
    float metallic;
    float roughness;
};

float intersectSphere(const Ray ray, const Sphere sphere, inout vec3 normal) {
    vec3 oc = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return -1.0;
    }

    float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    float t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    float t = t1;
    if (t1 < 0.0) {
        t = t2;
    }

    if (t < 0.0) {
        return -1.0;
    }

    vec3 hitPoint = ray.origin + t * ray.direction;
    normal = normalize(hitPoint - sphere.center);

    return t;
}

float intersectPlane(const Ray ray, const Plane plane, inout vec3 normal) {
    float denom = dot(ray.direction, plane.normal);
    if (abs(denom) < 0.0001) {
        return -1.0;
    }

    float t = dot(plane.point - ray.origin, plane.normal) / denom;
    if (t < 0.0) {
        return -1.0;
    }

    normal = plane.normal;
    return t;
}

HitRecord closestHit(const Ray ray, const Sphere spheres[4], const Plane plane) {
    HitRecord closest;
    closest.hit = false;
    closest.t = 1000000.0;

    // Check spheres
    for (int i = 0; i < 4; i++) {
        vec3 normal;
        float t = intersectSphere(ray, spheres[i], normal);
        if (t > 0.0 && t < closest.t) {
            closest.hit = true;
            closest.t = t;
            closest.point = ray.origin + t * ray.direction;
            closest.normal = normal;
            closest.color = spheres[i].color;
            closest.metallic = spheres[i].metallic;
            closest.roughness = spheres[i].roughness;
        }
    }

    // Check plane
    vec3 planeNormal;
    float t = intersectPlane(ray, plane, planeNormal);
    if (t > 0.0 && t < closest.t) {
        closest.hit = true;
        closest.t = t;
        closest.point = ray.origin + t * ray.direction;
        closest.normal = planeNormal;
        
        // Checkerboard pattern for plane
        vec3 pos = closest.point;
        bool isEven = mod(floor(pos.x) + floor(pos.z), 2.0) == 0.0;
        closest.color = isEven ? vec3(0.2, 0.2, 0.2) : vec3(0.8, 0.8, 0.8);
        closest.metallic = 0.0;
        closest.roughness = 0.8;
    }

    return closest;
}

vec3 calculateLighting(const HitRecord hit, const vec3 lightPos, const vec3 lightColor, const vec3 cameraPos, const Sphere spheres[4], const Plane plane) {
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 lightDir = normalize(lightPos - hit.point);
    float diff = max(dot(hit.normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting (with roughness)
    vec3 viewDir = normalize(cameraPos - hit.point);
    vec3 reflectDir = reflect(-lightDir, hit.normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0 / hit.roughness);
    vec3 specular = hit.metallic * spec * lightColor;

    // Check for shadows
    Ray shadowRay;
    shadowRay.origin = hit.point + 0.001 * hit.normal;
    shadowRay.direction = lightDir;
    
    HitRecord shadowHit = closestHit(shadowRay, spheres, plane);
    float shadowFactor = 1.0;
    if (shadowHit.hit) {
        float distanceToLight = length(lightPos - hit.point);
        if (shadowHit.t < distanceToLight) {
            shadowFactor = 0.3;
        }
    }

    // Combine lighting components
    vec3 result = (ambient + shadowFactor * (diffuse + specular)) * hit.color;
    return result;
}

vec3 traceRay(const Ray ray, const Sphere spheres[4], const Plane plane, const vec3 lightPos, const vec3 lightColor, const vec3 cameraPos) {
    HitRecord hit = closestHit(ray, spheres, plane);

    if (!hit.hit) {
        // Sky color gradient
        vec3 unitDir = normalize(ray.direction);
        float t = 0.5 * (unitDir.y + 1.0);
        return mix(vec3(0.8, 0.9, 1.0), vec3(1.0, 1.0, 1.0), t);
    }

    // Calculate lighting
    vec3 color = calculateLighting(hit, lightPos, lightColor, cameraPos, spheres, plane);

    return color;
}

void main() {
    // Create spheres
    Sphere spheres[4];
    spheres[0] = Sphere(vec3(0.0, 1.0, -5.0), 1.0, vec3(0.8, 0.2, 0.2), 0.0, 0.3);
    spheres[1] = Sphere(vec3(2.0, 1.0, -5.0), 1.0, vec3(0.2, 0.8, 0.2), 0.5, 0.5);
    spheres[2] = Sphere(vec3(-2.0, 1.0, -5.0), 1.0, vec3(0.2, 0.2, 0.8), 0.8, 0.2);
    spheres[3] = Sphere(vec3(0.0, 1.5, -3.0), 0.5, vec3(0.8, 0.8, 0.2), 0.2, 0.7);

    // Create plane (floor)
    Plane plane = Plane(vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.5), 0.0, 0.8);

    // Create ray from camera through current pixel
    vec2 uv = (gl_FragCoord.xy / vec2(800.0, 600.0)) * 2.0 - 1.0;
    uv.x *= 800.0 / 600.0; // Aspect ratio correction

    Ray ray;
    ray.origin = cameraPos;
    ray.direction = normalize(vec3(uv.x, uv.y, -1.0));

    // Trace the ray
    vec3 color = traceRay(ray, spheres, plane, lightPos, lightColor, cameraPos);

    // Apply gamma correction
    color = pow(color, vec3(1.0 / 2.2));

    outColor = vec4(color, 1.0);
}
