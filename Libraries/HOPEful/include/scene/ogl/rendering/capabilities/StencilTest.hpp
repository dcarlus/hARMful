#ifndef __HOPE__GL_CAPABILITY_STENCIL_TEST__
#define __HOPE__GL_CAPABILITY_STENCIL_TEST__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Set front and/or back function and reference value for stencil testing.
     */
    class StencilTest final : public Capability {
        public:
            struct Parameters final {
                /**
                 * All possible face modes.
                 */
                enum FaceMode : GLenum {
                    Front =  GL_FRONT,
                    Back =  GL_BACK,
                    FrontAndBack =  GL_FRONT_AND_BACK
                } ;

                /**
                 * Possible alpha test function to apply.
                 */
                enum StencilFunction : GLenum {
                    Never = GL_NEVER,
                    Less = GL_LESS,
                    Equal = GL_EQUAL,
                    LessOrEqual = GL_LEQUAL,
                    Greater = GL_GREATER,
                    GreaterOrEqual = GL_GEQUAL,
                    NotEqual = GL_NOTEQUAL,
                    Always = GL_ALWAYS
                } ;

                /**
                 * Specify whether front and/or back stencil state is updated.
                 */
                FaceMode face ;

                /**
                 * Stencil test function to apply.
                 */
                StencilFunction function = Always ;

                /**
                 * Specify the reference value for the stencil test.
                 */
                GLint reference = 0 ;

                /**
                 * Specify a mask that is ANDed with both the reference value
                 * and the stored stencil value when the test is done.
                 */
                GLuint mask = 0xFFFFFFFF ;
            } ;

            /**
             * Create a new StencilTest instance.
             */
            exported StencilTest() : Capability(CapabilityType::StencilTest) {}

        private:
            /**
             * Front faces parameters.
             */
            Parameters m_frontFaces ;

            /**
             * Store parameters for restore.
             */
            Parameters m_oldFrontFaces ;

            /**
             * Back faces parameters.
             */
            Parameters m_backFaces ;

            /**
             * Store parameters for restore.
             */
            Parameters m_oldBackFaces ;

        public:
            /**
             * Set parameters for front-facing faces.
             */
            exported void setFrontParameters(const Parameters& params) {
                m_frontFaces = params ;
                m_frontFaces.face = Parameters::FaceMode::Front ;
            }

            /**
             * Set parameters for back-facing faces.
             */
            exported void setBackParameters(const Parameters& params) {
                m_backFaces = params ;
                m_frontFaces.face = Parameters::FaceMode::Back ;
            }

        protected:
            /**
             * Apply the capability.
             */
            exported void apply() override ;

            /**
             * Remove the capability.
             */
            exported void remove() override ;
    } ;
}

#endif
