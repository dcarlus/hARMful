// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/materials/DiffuseMap.hpp>

std::string DiffuseMapForwardVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoord ;\n\
layout(location = 2) in vec3 normal ;\n\
\n\
layout(location = 0) out vec3 outVertexWorldPosition ;\n\
layout(location = 1) out vec3 outNormal ;\n\
layout(location = 2) out vec2 outTexCoord ;\n\
layout(location = 3) out vec3 outViewDirection ;\n\
\n\
void main() {\n\
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

std::string DiffuseMapForwardFragmentCode =
"\
// Blinn-Phong material shader using a diffuse map.\n\
\n\
struct Material {\n\
    vec3 ambient ;\n\
    layout(binding = 0) sampler2D diffuse ;\n\
    vec3 specular ;\n\
    float shininess ;\n\
} ;\n\
\n\
uniform Material material ;\n\
\n\
layout(location = 0) in vec3 inVertexWorldPosition ;\n\
layout(location = 1) in vec3 inNormal ;\n\
layout(location = 2) in vec2 inTexCoord ;\n\
layout(location = 3) in vec3 inViewDirection ;\n\
\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    FragmentData currentFragment ;\n\
    currentFragment.worldPosition = inVertexWorldPosition ;\n\
    currentFragment.diffuseValue = texture(material.diffuse, inTexCoord).rgb ;\n\
    currentFragment.specularValue = material.specular ;\n\
    currentFragment.normalValue = inNormal ;\n\
\n\
    vec3 colorLinear = material.ambient ;\n\
    colorLinear += ComputeLightsContribution(\n\
        inViewDirection,\n\
        currentFragment\n\
    ) ;\n\
\n\
    outColor = vec4(colorLinear, 1.f) ;\n\
}\n\
" ;

