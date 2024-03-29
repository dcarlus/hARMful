#ifndef __HOPE__GL_RENDER_PASS__
#define __HOPE__GL_RENDER_PASS__

#include <utils/Platform.hpp>

#include <scene/SceneTypes.hpp>
#include <scene/framegraph/shading/FilterOption.hpp>
#include <scene/framegraph/shading/ShaderValue.hpp>
#include <scene/framegraph/shading/UniformCache.hpp>
#include <scene/ogl/rendering/glsl/ShaderProgram.hpp>
#include <scene/ogl/rendering/capabilities/Capability.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <map>
#include <memory>
#include <set>
#include <vector>

namespace Hope {
    class MaterialComponent;
}

namespace Hope::GL {
    /**
     * Represents a shader program execution as a single render pass.
     */
    class RenderPass final {
        friend class Hope::MaterialComponent ;

        private:
            /**
             * For direct access to capabilities pointers.
             */
            struct CapabilityIndex {
                unsigned int index ;
                std::unique_ptr<Capability> capability ;
            } ;

            /**
             * ID of the pass.
             */
            RenderPassID m_id = ForwardPassID ;

            /**
             * List of the options.
             */
            std::set<std::shared_ptr<Hope::FilterOption>> m_options ;

            /**
             * List of graphics API capabilities.
             */
            std::map<CapabilityType, CapabilityIndex> m_capabilities ;

            /**
             * Cache pointers on capabilities for easy sharing without
             * ownership.
             */
            std::vector<Capability*> m_capabilitiesPointers ;

            /**
             * The shader program that is executed in the current render pass.
             */
            std::unique_ptr<ShaderProgram> m_shaderProgram ;

            /**
             * Uniforms cache.
             */
            UniformCache m_uniforms ;

        public:
            /**
             * Create a render pass.
             */
            exported RenderPass(const Hope::RenderPassID id = ForwardPassID) ;

            /**
             * Add a filter option.
             * If a FilterOption is set in the framegraph branch and that at
             * least one of them matches in the current render pass, the entity
             * may be rendered. If no option matches in the current render pass,
             * the entity cannot be rendered (neither its children).
             *
             * If there is a FilterOption in the framegraph but no one in the
             * current render pass, the entity is discarded from rendering (and
             * its children as well).
             */
            exported void addFilterOption(const std::shared_ptr<Hope::FilterOption> option) ;

            /**
             * Remove a filter option.
             */
            exported void removeFilterOption(const std::shared_ptr<Hope::FilterOption> option) ;

            /**
             * Get the filter options.
             */
            exported std::set<std::shared_ptr<Hope::FilterOption>> filterOptions() const {
                return m_options ;
            }

            /**
             * Add a graphics API capability.
             * @return  true if the Capability can be added; false if a
             *          Capability of same type is already in use.
             */
            exported bool addCapability(std::unique_ptr<Capability> capability) ;

            /**
             * Remove a graphics API capability.
             */
            exported void removeCapability(const CapabilityType type) ;

            /**
             * Get the capability of wanted type.
             */
            exported const Capability* capability(const CapabilityType type) const ;

            /**
             * Get the capabilities of the current render pass.
             */
            exported const std::vector<Capability*>& capabilities() const {
                return m_capabilitiesPointers ;
            }

            /**
             * Get the shader program.
             */
            exported ShaderProgram* shaderProgram() const {
                return m_shaderProgram.get() ;
            }

            /**
             * Get the render pass ID.
             */
            exported Hope::RenderPassID id() const {
                return m_id ;
            }

            /**
             * Get the shader uniforms.
             */
            exported const std::vector<Hope::ShaderUniform*>& shaderUniforms() const {
                return m_uniforms.pointers() ;
            }

        protected:
            /**
             * Get the uniform cache.
             */
            UniformCache& uniformCache() {
                return m_uniforms ;
            }
    } ;
}

#endif
