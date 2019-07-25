#ifndef __HOPE__SSAO_COMPUTE_DATA__
#define __HOPE__SSAO_COMPUTE_DATA__

#include <scene/framegraph/deferred/effects/EffectData.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/components/materials/external/SSAOComputeUniformSetter.hpp>

namespace Hope {
    /**
     * Data required for screen-space ambient occlusion.
     */
    class SSAOComputeData final : public EffectData {
        private:
            /**
             * Send SSAO data to shaders.
             */
            SSAOComputeUniformSetter m_ssaoSetter ;

        public:
            /**
             * Set the node containing SSAO data.
             */
            void setSSAO(Hope::SSAORenderNode* node) {
                m_ssaoSetter.setSSAONode(node) ;
            }

            /**
             * Update the uniform values for directional light shadow mapping.
             */
            void updateUniformValues() override {
                m_ssaoSetter.updateUniforms() ;
            }

            /**
             * Get the shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> uniforms() const override {
                return m_ssaoSetter.shaderUniforms() ;
            }
    } ;
}

#endif
