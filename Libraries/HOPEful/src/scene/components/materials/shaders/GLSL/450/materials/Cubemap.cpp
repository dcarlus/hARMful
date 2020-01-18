// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/materials/Cubemap.hpp>

std::string CubemapForwardFragmentCode =
"\
layout(binding = 0) uniform samplerCube cubemap ;\n\
\n\
layout(location = 0) in vec3 inTexCoord ;\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    outColor = texture(cubemap, inTexCoord) ;\n\
}\n\
" ;

std::string CubemapDeferredFragmentCode =
"\
// Cubemap material shader.\n\
\n\
layout(binding = 0) uniform samplerCube cubemap ;\n\
\n\
layout(location = 0) in vec3 inTexCoord ;\n\
\n\
layout(location = 0) out vec4 gAlbedo ;\n\
layout(location = 1) out vec4 gSpecular ;\n\
layout(location = 2) out vec2 gNormal ;\n\
\n\
void main() {\n\
    const vec4 NoColor = vec4(0.f, 0.f, 0.f, 1.f) ;\n\
    gAlbedo = texture(cubemap, inTexCoord) ;\n\
    gNormal = NoColor.xy ;\n\
    gSpecular = NoColor ;\n\
}\n\
" ;

std::string CubemapForwardVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
\n\
layout(location = 0) out vec3 outTexCoord ;\n\
\n\
void main() {\n\
    outTexCoord = position ;\n\
    vec4 position4D = viewProjectionMatrix * vec4(position * farPlaneDistance, 1.f) ;\n\
    gl_Position = position4D.xyww ;\n\
}\n\
" ;

std::string CubemapDeferredVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
\n\
layout(location = 0) out vec3 outTexCoord ;\n\
\n\
void main() {\n\
    outTexCoord = position ;\n\
    vec4 position4D = viewProjectionMatrix * vec4(position * farPlaneDistance, 1.f) ;\n\
    gl_Position = position4D.xyww ;\n\
}\n\
" ;

