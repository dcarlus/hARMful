// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>

std::string IncludesBlockBindingsModuleCode =
"\
#ifndef HOPE__SHADER_BLOCK_BINDINGS\n\
#define HOPE__SHADER_BLOCK_BINDINGS\n\
\n\
#define BASE_DATA_UBO_BINDING_INDEX 0\n\
#define MODEL_DATA_UBO_BINDING_INDEX 1\n\
#define LIGHTS_DATA_UBO_BINDING_INDEX 2\n\
\n\
#endif\n\
" ;

std::string IncludesAmountLightsModuleCode =
"\
#ifndef HOPE__SHADER_AMOUNT_LIGHTS\n\
#define HOPE__SHADER_AMOUNT_LIGHTS\n\
\n\
#define MAX_DIRECTIONAL_LIGHTS  1\n\
#define MAX_POINT_LIGHTS        32\n\
#define MAX_SPOT_LIGHTS         8\n\
\n\
#endif\n\
" ;

std::string IncludesTextureUnitsModuleCode =
"\
#ifndef HOPE__TEXTURE_UNIT_BINDINGS\n\
#define HOPE__TEXTURE_UNIT_BINDINGS\n\
\n\
#define MAX_AMOUNT_SHADOW_CASCADES 4\n\
#define SHADOW_DEPTH_MAP_BINDING_UNIT 7\n\
#define UNIFORM_SHADOW_USE_LOCATION 12\n\
#define UNIFORM_SHADOW_AMOUNT_CASCADE_LOCATION UNIFORM_SHADOW_USE_LOCATION + 1\n\
#define UNIFORM_SHADOW_CASCADED_SPLITS_LOCATION UNIFORM_SHADOW_AMOUNT_CASCADE_LOCATION + 1\n\
#define UNIFORM_SHADOW_CASCADE_MATRICES_LOCATION UNIFORM_SHADOW_CASCADED_SPLITS_LOCATION + MAX_AMOUNT_SHADOW_CASCADES\n\
\n\
#endif\n\
" ;

