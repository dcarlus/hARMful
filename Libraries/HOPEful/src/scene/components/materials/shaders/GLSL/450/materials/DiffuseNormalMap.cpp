// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/materials/DiffuseNormalMap.hpp>

std::string DiffuseNormalMapDeferredVertexCode =
"\
// Diffuse+normal maps material shader.\n\
\n\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoord ;\n\
layout(location = 2) in vec3 normal ;\n\
layout(location = 3) in vec3 tangent ;\n\
layout(location = 4) in vec3 bitangent ;\n\
\n\
layout(location = 0) out mat3 outTBNMatrix ;\n\
layout(location = 3) out vec2 outTexCoord ;\n\
\n\
void correctTBNMatrix() {\n\
    vec3 correctedTangent = normalize(vec3(normalMatrix * vec4(tangent, 0.f))) ;\n\
    vec3 correctedBitangent = normalize(vec3(normalMatrix * vec4(bitangent, 0.f))) ;\n\
    vec3 correctedNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
    outTBNMatrix = mat3(correctedTangent, correctedBitangent, correctedNormal) ;\n\
}\n\
\n\
void main() {\n\
    correctTBNMatrix() ;\n\
\n\
    vec4 position4D = vec4(position, 1.f) ;\n\
    gl_Position = mvpMatrix * position4D ;\n\
    outTexCoord = texCoord ;\n\
}\n\
" ;

std::string DiffuseNormalMapDeferredFragmentCode =
"\
// Diffuse+normal maps material shader.\n\
\n\
layout(binding = 0) uniform sampler2D diffuse ;\n\
layout(binding = 1) uniform sampler2D normal ;\n\
layout(location = 0) uniform vec3 ambient ;\n\
layout(location = 2) uniform vec3 specular ;\n\
layout(location = 3) uniform float shininess ;\n\
\n\
layout(location = 0) in mat3 inTBNMatrix ;\n\
layout(location = 3) in vec2 inTexCoord ;\n\
\n\
layout(location = 0) out vec4 gAlbedo ;\n\
layout(location = 1) out vec4 gSpecular ;\n\
layout(location = 2) out vec4 gNormal ;\n\
\n\
void main() {\n\
    gAlbedo = vec4(texture(diffuse, inTexCoord).rgb, 1.f) ;\n\
    gSpecular = vec4(specular, shininess) ;\n\
\n\
    vec3 normalVector = texture(normal, inTexCoord).rgb ;\n\
    normalVector = AdjustNormalVector(inTBNMatrix, normalVector) ;\n\
    gNormal = vec4(EncodeSpheremapNormals(normalVector), 0.f, 0.f) ;\n\
}\n\
" ;

std::string DiffuseNormalMapForwardVertexCode =
"\
// Diffuse+normal maps material shader.\n\
\n\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoord ;\n\
layout(location = 2) in vec3 normal ;\n\
layout(location = 3) in vec3 tangent ;\n\
layout(location = 4) in vec3 bitangent ;\n\
\n\
layout(location = 0) out vec3 outVertexWorldPosition ;\n\
layout(location = 1) out vec3 outNormal ;\n\
layout(location = 2) out mat3 outTBNMatrix ;\n\
layout(location = 5) out vec2 outTexCoord ;\n\
layout(location = 6) out vec3 outViewDirection ;\n\
\n\
void correctTBNMatrix() {\n\
    vec3 correctedTangent = normalize(vec3(normalMatrix * vec4(tangent, 0.f))) ;\n\
    vec3 correctedBitangent = normalize(vec3(normalMatrix * vec4(bitangent, 0.f))) ;\n\
    vec3 correctedNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
    outTBNMatrix = mat3(correctedTangent, correctedBitangent, correctedNormal) ;\n\
}\n\
\n\
void main() {\n\
    correctTBNMatrix() ;\n\
\n\
    vec4 position4D = vec4(position, 1.f) ;\n\
\n\
    gl_Position = mvpMatrix * position4D ;\n\
\n\
    vec4 vertexPosition4D = modelViewMatrix * vec4(position, 1.f) ;\n\
    outVertexWorldPosition = vec3(vertexPosition4D) / vertexPosition4D.w ;\n\
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
    outTexCoord = texCoord ;\n\
    outViewDirection = normalize(-outVertexWorldPosition) ;\n\
}\n\
" ;

std::string DiffuseNormalMapForwardFragmentCode =
"\
// Diffuse+normal maps material shader.\n\
\n\
layout(binding = 0) uniform sampler2D diffuse ;\n\
layout(binding = 1) uniform sampler2D normal ;\n\
layout(location = 0) uniform vec3 ambient ;\n\
layout(location = 2) uniform vec3 specular ;\n\
layout(location = 3) uniform float shininess ;\n\
\n\
layout(location = 0) in vec3 inVertexWorldPosition ;\n\
layout(location = 1) in vec3 inNormal ;\n\
layout(location = 2) in mat3 inTBNMatrix ;\n\
layout(location = 5) in vec2 inTexCoord ;\n\
layout(location = 6) in vec3 inViewDirection ;\n\
\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    FragmentData currentFragment ;\n\
    currentFragment.position = inVertexWorldPosition ;\n\
    currentFragment.diffuseValue = texture(diffuse, inTexCoord).rgb ;\n\
    currentFragment.specularValue = specular ;\n\
    vec3 normalVector = texture(normal, inTexCoord).rgb ;\n\
    currentFragment.normalValue = AdjustNormalVector(inTBNMatrix, normalVector) ;\n\
\n\
    vec3 colorLinear = ambient ;\n\
    colorLinear += ComputeLightsContribution(\n\
        inViewDirection,\n\
        currentFragment\n\
    ) ;\n\
\n\
    outColor = vec4(colorLinear, 1.f) ;\n\
}\n\
" ;

