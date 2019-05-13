// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GL/4.5/MaterialCubemap.hpp>

std::string MaterialCubemapVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
\n\
layout(location = 0) out vec3 outTexCoord ;\n\
\n\
void main() {\n\
    outTexCoord = position ;\n\
\n\
    vec4 position4D = viewProjectionMatrix * vec4(position * farPlaneDistance, 1.f) ;\n\
    gl_Position = position4D.xyww ;\n\
}\n\
" ;

std::string MaterialCubemapFragmentCode =
"\
uniform layout(binding = 0) samplerCube cubemap ;\n\
\n\
layout(location = 0) in vec3 inTexCoord ;\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    outColor = texture(cubemap, inTexCoord) ;\n\
}\n\
" ;
