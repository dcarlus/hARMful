#ifndef __HOPE__FRAME_RENDER_CACHE__
#define __HOPE__FRAME_RENDER_CACHE__

#include <utils/Platform.hpp>

#include <scene/components/materials/PBRMaterialComponent.hpp>
#include <scene/framegraph/cache/GeometryData.hpp>
#include <scene/framegraph/cache/PointLightData.hpp>
#include <map>
#include <set>
#include <vector>

namespace Hope {
    class Entity ;
    class LightComponent ;
    class DirectionalLightComponent ;
    class PointLightComponent ;

    /**
     * Cache some elements of the scene to access them faster while rendering
     * the current frame.
     */
    class FrameRenderCache final {
        private:
            /**
             * Default material.
             */
            PBRMaterialComponent m_defaultMaterial ;

            /**
             * Cache of all meshes to render.
             */
            std::vector<GeometryData> m_meshes ;

            /**
             * Cache of all directional lights to use for the render.
             */
            std::vector<DirectionalLightComponent*> m_directionalLights ;

            /**
             * Cache of all points lights to use for the render.
             */
            std::vector<PointLightData> m_pointLights ;

        public:
            /**
             * Create a new FrameRenderCache instance.
             */
            exported FrameRenderCache() ;

            /**
             * Put the components of the entity that need to be in the cache.
             * @param   entity              Entity to get components.
             * @param   worldTransformation World transformation of the entity.
             */
            exported void cacheEntity(
                const Entity* entity,
                const Mind::Matrix4x4f& worldTransformation
            ) ;

            /**
             * Clear the cache data.
             */
            exported void clear() {
                m_meshes.clear() ;
                m_directionalLights.clear() ;
                m_pointLights.clear() ;
            }

            /**
             * To know if the cache is empty.
             */
            exported bool empty() const {
                return m_meshes.empty() ||
                        m_directionalLights.empty() ||
                        m_pointLights.empty() ;
            }

            /**
             * Get the cache of all meshes to render.
             */
            exported std::vector<GeometryData>& meshes() {
                return m_meshes ;
            }

            /**
             * Gache of all directional lights to use for the render.
             */
            exported const std::vector<DirectionalLightComponent*>& directionalLights() const {
                return m_directionalLights ;
            }

            /**
             * Get the cache of all points lights to use for the render.
             */
            exported const std::vector<PointLightData>& pointLights() const {
                return m_pointLights ;
            }

        private:
            /**
             * Put a light in cache.
             */
            exported void cacheLight(
                LightComponent* light,
                const Mind::Matrix4x4f& worldTransformation
            ) ;

            /**
             * Put a mesh in cache.
             */
            exported void cacheGeometry(
                const Entity* entity,
                const Mind::Matrix4x4f& worldTransformation
            ) ;
    } ;
}

#endif
