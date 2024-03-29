#ifndef __HOPE__GL_TESSELATIONCONTROLSHADER__
#define __HOPE__GL_TESSELATIONCONTROLSHADER__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/glsl/shaders/Shader.hpp>

namespace Hope::GL {
    /**
     * Represent a tesselation control shader, that can be combined with other
     * shader types into a shader program. It is reusable for other programs as
     * well.
     */
    class TesselationControlShader final : public Shader {
        public:
            /**
             * Create a new TesselationControlShader.
             */
            exported TesselationControlShader() : Shader(GL_TESS_CONTROL_SHADER) {}
    } ;
}

#endif
