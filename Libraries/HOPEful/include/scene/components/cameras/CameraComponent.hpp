#ifndef __HOPE__CAMERA_COMPONENT__
#define __HOPE__CAMERA_COMPONENT__

#include <scene/components/Component.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <scene/common/Color.hpp>

namespace Hope {
    /**
     * Component that represents a camera.
     * Useless as is, use a PerspectiveCameraComponent or an
     * OrthographicCameraComponent.
     */
    class CameraComponent : public Component {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = CameraComponentType ;

        private:
            /**
             * Default clear color.
             */
            static const Color DefaultClearColor ;

            /**
             * Up vector of the world.
             */
            static const Mind::Vector3f WorldUpVector ;

            /**
             * Near plane distance of the camera frustum.
             */
            float m_nearPlaneDistance ;

            /**
             * Far plane distance of the camera frustum.
             */
            float m_farPlaneDistance ;

            /**
             * Point in the 3D space the camera is targetting.
             */
            Mind::Vector3f m_target ;

            /**
             * Direction of the camera view.
             */
            Mind::Vector3f m_viewDirection ;

            /**
             * Right axis of the camera.
             */
            Mind::Vector3f m_rightAxis ;

            /**
             * up vector of the camera.
             */
            Mind::Vector3f m_up ;

            /**
             * View matrix.
             */
            Mind::Matrix4x4f m_viewMatrix ;

            /**
             * Projection matrix.
             */
            Mind::Matrix4x4f m_projectionMatrix ;

            /**
             * Clear color when using the current camera.
             */
            Color m_clearColor ;

            /**
             * To know if the projection matrix needs to be updated.
             */
            bool m_projectionChanged = true ;

        public:
            /**
             * Create a new CameraComponent.
             */
            CameraComponent() ;

            /**
             * Update the camera.
             */
            void update() {
                lookAt(m_target) ;
            }

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the CameraComponent cannot be shared.
             */
            bool isShareable() const override {
                return false ;
            }

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  true, the component can be removed.
             */
            bool isRemovable() const override {
                return true ;
            }

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  false, an entity can only bear one CameraComponent.
             */
            bool isStackable() const override {
                return false ;
            }

            /**
             * Set the near plane distance of the camera frustum.
             */
            void setNearPlaneDistance(const float distance) {
                if (m_nearPlaneDistance != distance) {
                    m_projectionChanged = true ;
                    m_nearPlaneDistance = distance ;
                }
            }

            /**
             * Set the far plane distance of the camera frustum.
             */
            void setFarPlaneDistance(const float distance) {
                if (m_farPlaneDistance != distance) {
                    m_projectionChanged = true ;
                    m_farPlaneDistance = distance ;
                }
            }

            /**
             * Set the up vector of the camera. The up vector is normalized.
             * Default is Y-up.
             */
            void setUpVector(const Mind::Vector3f& up) ;

            /**
             * Generate the view matrix.
             * @param   target      Center of the camera view.
             */
            void lookAt(const Mind::Vector3f& target) ;

            /**
             * Get the near plane distance of the camera frustum.
             */
            float nearPlaneDistance() const {
                return m_nearPlaneDistance ;
            }

            /**
             * Get the far plane distance of the camera frustum.
             */
            float farPlaneDistance() const {
                return m_farPlaneDistance ;
            }

            /**
             * Get the target of the camera.
             */
            const Mind::Vector3f& target() const {
                return m_target ;
            }

            /**
             * Get the view direction of the camera.
             */
            const Mind::Vector3f& viewDirection() const {
                return m_viewDirection ;
            }

            /**
             * Get the right axis of the camera.
             */
            const Mind::Vector3f& rightAxis() const {
                return m_rightAxis ;
            }

            /**
             * Get the up vector of the camera.
             */
            const Mind::Vector3f& up() const {
                return m_up ;
            }

            /**
             * Set the clear color of the camera.
             */
            void setClearColor(const Color& color) {
                m_clearColor = color ;
            }

            /**
             * Get the clear color of the camera.
             */
            const Color& clearColor() const {
                return m_clearColor ;
            }

            /**
             * Get the view matrix.
             */
            const Mind::Matrix4x4f& viewMatrix() const {
                return m_viewMatrix ;
            }

            /**
             * Get the projection matrix.
             * @param   projection  Projection matrix to get back.
             * @param   aspectRatio Aspect ratio of the window in which the
             *                      camera is used to render the scene.
             * @return  The computed projection, same result as the given
             *          parameter value for a convenient use.
             * @warning Clear any change in the projection matrix value.
             */
            Mind::Matrix4x4f& projectionMatrix(
                Mind::Matrix4x4f& projection,
                const float aspectRatio
            ) ;

            /**
             * To know if the projection matrix needs to be updated.
             */
            bool projectionChanged() const {
                return m_projectionChanged ;
            }

        protected:
            /**
             * Action to performed when the component is attached to an
             * entity.
             * @param   entity  Entity to attach the component to.
             */
            void onAttach(Entity* entity) override ;

            /**
             * Compute the projection matrix.
             * @param   projection  Projection matrix to get back.
             * @param   aspectRatio Aspect ratio of the window in which the
             *                      camera is used to render the scene.
             * @return  The computed projection, same result as the given
             *          parameter value for a convenient use.
             */
            virtual void computeProjectionMatrix(
                Mind::Matrix4x4f& projection,
                const float aspectRatio
            ) const = 0 ;

            /**
             * Notify when a value has been updated and the projection matrix
             * needs to be computed again.
             */
            void notifyProjectionChange() {
                m_projectionChanged = true ;
            }
    } ;
}

#endif