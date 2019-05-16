// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/materials/BlinnPhong.hpp>

std::string BlinnPhongDeferredSpecularFragmentCode =
"\
// Blinn-Phong material shader.\n\
\n\
struct Material {\n\
    vec3 ambient ;\n\
    vec3 diffuse ;\n\
    vec3 specular ;\n\
    float shininess ;\n\
} ;\n\
\n\
uniform Material material ;\n\
\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    outColor = vec4(material.specular, material.shininess) ;\n\
}\n\
" ;

std::string BlinnPhongForwardFragmentCode =
"\
// Blinn-Phong material shader.\n\
\n\
struct Material {\n\
    vec3 ambient ;\n\
    vec3 diffuse ;\n\
    vec3 specular ;\n\
    float shininess ;\n\
} ;\n\
\n\
uniform Material material ;\n\
\n\
const float ScreenGamma = 2.2f ;\n\
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
    currentFragment.diffuseValue = material.diffuse ;\n\
    currentFragment.specularValue = material.specular ;\n\
    currentFragment.normalValue = inNormal ;\n\
\n\
    vec3 colorLinear = material.ambient + ComputeLightsContribution(inViewDirection, currentFragment) ;\n\
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.f / ScreenGamma)) ;\n\
    outColor = vec4(colorGammaCorrected, 1.f) ;\n\
}\n\
" ;

std::string BlinnPhongDeferredVertexNormalVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
layout(location = 2) in vec3 normal ;\n\
\n\
layout(location = 0) out vec3 outNormal ;\n\
\n\
void main() {\n\
    gl_Position = mvpMatrix * vec4(position, 1.f) ;\n\
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
}\n\
" ;

std::string BlinnPhongDeferredNormalFragmentCode =
"\
// Blinn-Phong material shader.\n\
layout(location = 0) in vec3 normal ;\n\
\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    outColor = vec4(normal, 1.f) ;\n\
}\n\
" ;

std::string BlinnPhongDeferredPositionFragmentCode =
"\
// Blinn-Phong material shader.\n\
layout(location = 0) in vec4 vertexWorldPosition ;\n\
\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    outColor = vertexWorldPosition ;\n\
}\n\
" ;

std::string BlinnPhongForwardVertexCode =
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
    vec4 vertexPosition4D = modelViewMatrix * position4D ;\n\
    outVertexWorldPosition = vec3(vertexPosition4D) / vertexPosition4D.w ;\n\
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
    outTexCoord = texCoord ;\n\
    outViewDirection = normalize(-outVertexWorldPosition) ;\n\
}\n\
" ;

std::string BlinnPhongDeferredAlbedoFragmentCode =
"\
// Blinn-Phong material shader.\n\
\n\
struct Material {\n\
    vec3 ambient ;\n\
    vec3 diffuse ;\n\
    vec3 specular ;\n\
    float shininess ;\n\
} ;\n\
\n\
uniform Material material ;\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    outColor = vec4(material.diffuse, 1.f) ;\n\
}\n\
" ;

std::string BlinnPhongDeferredVertexPositionVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
\n\
layout(location = 0) out vec4 vertexWorldPosition ;\n\
\n\
void main() {\n\
    vec4 position4D = vec4(position, 1.f) ;\n\
    gl_Position = mvpMatrix * position4D ;\n\
\n\
    vec4 vertexPosition4D = modelViewMatrix * position4D ;\n\
    vertexWorldPosition = vec4(vertexPosition4D) / vertexPosition4D.w ;\n\
}\n\
" ;

