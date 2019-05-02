// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GL/4.5/modules/BaseDataBlock.hpp>

std::string BaseDataBlockVertexCode =
"\
layout (std140, binding = BASE_DATA_UBO_BINDING_INDEX) uniform BaseData\n\
{\n\
    mat4 viewMatrix ;\n\
    mat4 projectionMatrix ;\n\
    mat4 viewProjectionMatrix ;\n\
    mat4 inverseViewMatrix ;\n\
    mat4 inverseProjectionMatrix ;\n\
    mat4 inverseViewProjectionMatrix ;\n\
    mat3 viewportMatrix ;\n\
    mat3 inverseViewportMatrix ;\n\
    float aspectRatio ;\n\
    float time ;\n\
    vec3 eyePosition ;\n\
} ;\n\
" ;
