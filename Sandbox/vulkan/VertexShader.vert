#version 450

layout(binding = 0) uniform FE_UniformBufferObject
{
    mat4 mvp;
	vec4 ambientLightColor;
    vec3 lightPosition;
	vec4 lightColor;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in mat4 inTransform;

layout(location = 0) out vec4 fragColor;

void main() {
    vec4 vertexPosition =  vec4(inPosition, 1) * inTransform;
    gl_Position = ubo.mvp * vertexPosition;

    vec3 lightDirection = ubo.lightPosition - vertexPosition.xyz;
    vec4 normal = inTransform * vec4(inNormal, 1);

    vec3 lightColor = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w;
    vec3 ambientLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w;


    vec3 diffuseLight = lightColor * max(dot(normal.xyz, normalize(lightDirection)), 0);

    diffuseLight.z = 1;

    fragColor = vec4(diffuseLight * ambientLight, 1) * inColor;
}
