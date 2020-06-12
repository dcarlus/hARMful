#ifndef __HOPE__DEFERRED_RENDERING_SCREEN_QUAD_MATERIAL_COMPONENT__
#define __HOPE__DEFERRED_RENDERING_SCREEN_QUAD_MATERIAL_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/textures/environment/EnvironmentMap.hpp>
    #include <scene/ogl/textures/TextureImage2D.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * Material used on a quad having taking the whole viewport area to display
     * the content of the G-Buffer (deferred rendering).
     */
    class GBufferQuadMaterialComponent final : public MaterialComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

        private:
            /**
             * Location of the uniform for the MSAA quality.
             */
            static const int MSAAQualityUniformLocation = 5 ;

            /**
             * Binding of the BRDF look-up table.
             */
            static const int BrdfLUTBinding = 6 ;

            /**
             * Binding of the environment irradiance map.
             */
            static const int IrradianceBinding = 20 ;

            /**
             * Binding of the environment specular map.
             */
            static const int SpecularBinding = 30 ;

            /**
             * BRDF look-up table.
             */
            static std::unique_ptr<API::TextureImage2D> BrdfLUT ;

            /**
             * G-Buffer contening all the required data to perform the deferred
             * shading step.
             */
            const GBufferRenderNode* m_gBuffer = nullptr ;

            /**
             * Specular cubemap texture.
             */
            std::shared_ptr<API::EnvironmentMapTexture> m_specularMap = nullptr ;

            /**
             * Irradiance cubemap texture.
             */
            std::shared_ptr<API::EnvironmentMapTexture> m_irradianceMap = nullptr ;

        public:
            /**
             * Create a GBufferQuadMaterialComponent.
             * @param gBuffer   G-Buffer contening all the required data to
             *                  perform the deferred shading step.
             * @param envMap    Environment map for taking specular and
             *                  irradiance textures.
             */
            exported GBufferQuadMaterialComponent(
                const GBufferRenderNode* gBuffer,
                const API::EnvironmentMap* envMap = nullptr
            ) ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            exported void updateUniformValues() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            exported void setupUniforms() ;

        protected:
            /**
             * Setup the shader for the forward rendering pass.
             */
            exported void setupForwardShader() override ;

            /**
             * Setup the shader for the deferred rendering pass.
             * No deferred shading here!
             */
            exported void setupDeferredShader() override {}
    } ;
}

#endif
