// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/460/effects/AoRendering.hpp>

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
layout(binding = 0) uniform sampler2DMS ao ;\n\
\n\
layout(location = 0) in vec2 inTexCoords ;\n\
\n\
out vec4 fragColor ;\n\
\n\
void main() {\n\
    ivec2 texSize = textureSize(ao) ;\n\
    vec2 texelSize = 1.f / viewportSize ;\n\
\n\
    float blurResult = 0.f ;\n\
    for (int x = -1 ; x <= 1 ; ++x) {\n\
        for (int y = -1 ; y <= 1 ; ++y) {\n\
            vec2 offset = vec2(float(x), float(y)) * texelSize ;\n\
            vec2 normalizedCoords = inTexCoords + offset ;\n\
            blurResult += texelFetch(ao, ivec2(normalizedCoords * texSize), 0).a ;\n\
        }\n\
    }\n\
\n\
    blurResult = blurResult / 9.f ;\n\
    fragColor = vec4(texelFetch(ao, ivec2(gl_FragCoord), 0).xyz, blurResult) ;\n\
}\n\
" ;

std::string AoRenderingSsaoFragmentCode =
"\
// Screen-space ambient occlusion.\n\
\n\
layout(location = UNIFORM_AO_USE_LOCATION) uniform int useSSAO ;\n\
layout(location = UNIFORM_AO_KERNEL_LOCATION) uniform vec3 kernel[AO_KERNEL_SIZE] ;\n\
layout(binding = 0) uniform sampler2DMS albedo ;\n\
layout(binding = 1) uniform sampler2D noise ;\n\
layout(binding = 2) uniform sampler2DMS normal ;\n\
layout(binding = 3) uniform sampler2DMS depth ;\n\
\n\
layout(location = 0) in vec2 inTexCoords ;\n\
\n\
layout(location = 0) out vec4 fragColor ;\n\
\n\
const float Epsilon = 0.0001f ;\n\
\n\
// Compute the world position of the current fragment.\n\
vec3 computeWorldPosition(vec2 texCoords) {\n\
    ivec2 texSize = textureSize(depth) ;\n\
    float depthValue = texelFetch(depth, ivec2(texCoords * texSize), 0).r ;\n\
    return ComputeWorldSpacePosition(inTexCoords, depthValue).xyz ;\n\
}\n\
\n\
// Compute the view-space position of the current fragment.\n\
vec3 computeViewSpacePosition(vec2 texCoords) {\n\
    ivec2 texSize = textureSize(depth) ;\n\
    float depthValue = texelFetch(depth, ivec2(texCoords * texSize), 0).r ;\n\
    return ComputeViewSpacePosition(inTexCoords, depthValue).xyz ;\n\
}\n\
\n\
// Texture coordinates of the noise texture for the current fragment.\n\
vec2 noiseTextureCoords() {\n\
    vec2 coordScaling = viewportSize / AO_NOISE_TEXTURE_SIZE ;\n\
    return inTexCoords * coordScaling ;\n\
}\n\
\n\
// Compute a TBN matrix with a random orientation.\n\
mat3 computeTBNMatrix() {\n\
    vec3 randDirection = normalize(texture(noise, noiseTextureCoords()).xyz) ;\n\
    vec3 normal = DecodeSpheremapNormals(texelFetch(normal, ivec2(gl_FragCoord), 0).xy) ;\n\
    vec3 bitangent = cross(normal, randDirection) ;\n\
\n\
    if (length(bitangent) < Epsilon) {\n\
        bitangent = cross(normal, vec3(0,0,1)) ;\n\
    }\n\
\n\
    bitangent = normalize(bitangent) ;\n\
    vec3 tangent = cross(bitangent, normal) ;\n\
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
            kernelSample = worldPosition + AO_RADIUS * kernelSample ;\n\
\n\
            // Project the sample onto the texture (screen-space position).\n\
            vec4 offset = vec4(kernelSample, 1.f) ;\n\
            offset = projectionMatrix * offset ;\n\
            offset.xyz /= offset.w ;\n\
            offset.xyz = offset.xyz * 0.5f + 0.5f ;\n\
\n\
            // Kernel sample depth.\n\
            float sampleDepth = computeViewSpacePosition(offset.xy).z ;\n\
            float EpsilonZ = sampleDepth - worldPosition.z ;\n\
\n\
            // Range check and accumulate points that are occluded.\n\
            float rangeCheck = smoothstep(0.f, 1.f, AO_RADIUS / EpsilonZ) ;\n\
            occlusion += (sampleDepth >= (kernelSample.z + AO_BIAS) ? 1.f : 0.f) * rangeCheck ;\n\
        }\n\
\n\
        occlusion = 1.f - (occlusion / AO_KERNEL_SIZE) ;\n\
    }\n\
\n\
    fragColor = vec4(texelFetch(albedo, ivec2(gl_FragCoord), 0).rgb, occlusion) ;\n\
}\n\
" ;

