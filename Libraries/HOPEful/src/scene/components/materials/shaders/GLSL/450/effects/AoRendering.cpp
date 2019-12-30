// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/effects/AoRendering.hpp>

std::string AoRenderingSsaoFragmentCode =
"\
// Screen-space ambient occlusion.\n\
\n\
layout(location = UNIFORM_AO_USE_LOCATION) uniform int useSSAO ;\n\
layout(location = UNIFORM_AO_KERNEL_LOCATION) uniform vec3 kernel[AO_KERNEL_SIZE] ;\n\
layout(binding = 0) uniform sampler2D albedo ;\n\
layout(binding = 1) uniform sampler2D noise ;\n\
layout(binding = 2) uniform sampler2D normal ;\n\
layout(binding = 3) uniform sampler2D depth ;\n\
\n\
layout(location = 0) in vec2 inTexCoords ;\n\
\n\
layout(location = 0) out vec4 fragColor ;\n\
\n\
// Compute the world position of the current fragment.\n\
vec3 computeWorldPosition(vec2 texCoords) {\n\
    float depthValue = texture(depth, texCoords).r ;\n\
    return ComputeWorldSpacePosition(texCoords, depthValue).xyz ;\n\
}\n\
\n\
// Compute the view-space position of the current fragment.\n\
vec3 computeViewSpacePosition(vec2 texCoords) {\n\
    float depthValue = texture(depth, texCoords).r ;\n\
    return ComputeViewSpacePosition(texCoords, depthValue).xyz ;\n\
}\n\
\n\
// Texture coordinates of the noise texture for the current fragment.\n\
vec2 noiseTextureCoords() {\n\
    vec2 noiseTextureSize = textureSize(noise, 0) ;\n\
    vec2 coordScaling = viewportSize / noiseTextureSize.x ;\n\
    return inTexCoords * coordScaling ;\n\
}\n\
\n\
// Compute a TBN matrix with a random orientation.\n\
mat3 computeTBNMatrix() {\n\
    vec3 normal = DecodeSpheremapNormals(texture(normal, inTexCoords).xy) ;\n\
\n\
    vec2 noiseTexCoords = noiseTextureCoords() ;\n\
    vec3 random = normalize(texture(noise, noiseTexCoords).xyz) ;\n\
\n\
    vec3 tangent = normalize(random - normal * dot(random, normal)) ;\n\
    vec3 bitangent = cross(normal, tangent) ;\n\
    return mat3(tangent, bitangent, normal) ;\n\
}\n\
\n\
void main() {\n\
    float occlusion = 1.f ;\n\
\n\
    if (useSSAO == 1) {\n\
        vec3 worldPosition = computeViewSpacePosition(inTexCoords) ;\n\
        mat3 tbnMatrix = computeTBNMatrix() ;\n\
\n\
        occlusion = 0.f ;\n\
        for (int sampleIndex = 0 ; sampleIndex < AO_KERNEL_SIZE ; ++sampleIndex) {\n\
            // Sample position.\n\
            vec3 kernelSample = tbnMatrix * kernel[sampleIndex] ;\n\
            kernelSample = worldPosition + kernelSample * AO_RADIUS ;\n\
\n\
            // Project the sample onto the texture (screen-space position).\n\
            vec4 offset = vec4(kernelSample, 1.f) ;\n\
            offset = projectionMatrix * offset ;\n\
            offset.xyz /= offset.w ;\n\
            offset.xyz = offset.xyz * 0.5f + 0.5f ;\n\
\n\
            // Kernel sample depth.\n\
            float sampleDepth = computeViewSpacePosition(offset.xy).z ;\n\
\n\
            // Range check and accumulate.\n\
            float rangeCheck = smoothstep(0.f, 1.f, AO_RADIUS / abs(worldPosition.z - sampleDepth)) ;\n\
            occlusion += (sampleDepth >= kernelSample.z + AO_BIAS ? 1.f : 0.f) * rangeCheck ;\n\
        }\n\
\n\
        occlusion = 1.f - (occlusion / AO_KERNEL_SIZE) ;\n\
    }\n\
\n\
fragColor = vec4(texture(albedo, inTexCoords).rgb, occlusion) ;\n\
\n\
    // fragColor = vec4(texture(albedo, inTexCoords).rgb, occlusion) ;\n\
}\n\
" ;

std::string AoRenderingSsaoVertexCode =
"\
// Screen-space ambient occlusion.\n\
\n\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoords ;\n\
\n\
layout(location = 0) out vec2 outTexCoords ;\n\
\n\
void main() {\n\
    outTexCoords = texCoords ;\n\
    gl_Position = vec4(position, 1.f) ;\n\
}\n\
" ;

std::string AoRenderingBlurFragmentCode =
"\
// Screen-space ambient occlusion blur and copy.\n\
\n\
layout(binding = 0) uniform sampler2D ao ;\n\
\n\
layout(location = 0) in vec2 inTexCoords ;\n\
\n\
out vec4 fragColor ;\n\
\n\
void main() {\n\
    vec2 texelSize = 1.f / vec2(textureSize(ao, 0)) ;\n\
\n\
    float blurResult = 0.f ;\n\
    for (int x = -2 ; x < 2 ; ++x) {\n\
        for (int y = -2 ; y < 2 ; ++y) {\n\
            vec2 offset = vec2(float(x), float(y)) * texelSize ;\n\
            blurResult += texture(ao, inTexCoords + offset).a ;\n\
        }\n\
    }\n\
\n\
    blurResult = blurResult / (4.f * 4.f) ;\n\
    fragColor = vec4(texture(ao, inTexCoords).xyz, blurResult) ;\n\
}\n\
" ;

