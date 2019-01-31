#ifndef __HOPE__GL_CAPABILITY_DEPTH_MASK__
#define __HOPE__GL_CAPABILITY_DEPTH_MASK__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Enable depth mask GL capability.
     */
    class DepthMask final : public Capability {
        private:
            /**
             * To know if the depth mask is used or not for rendering.
             */
            GLboolean m_isEnabled = GL_TRUE ;

            /**
             * Store the depth mask state for restore.
             */
            GLboolean m_oldIsEnabled = GL_TRUE ;

        public:
            /**
             * Enable depth mask.
             */
            void enable() {
                m_isEnabled = true ;
            }

            /**
             * Disable depth mask.
             */
            void disable() {
                m_isEnabled = false ;
            }

        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                glGetBooleanv(GL_DEPTH_WRITEMASK, &m_oldIsEnabled) ;

                if (m_isEnabled != m_oldIsEnabled) {
                    glDepthMask(m_isEnabled) ;
                }
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                if (m_isEnabled != m_oldIsEnabled) {
                    glDepthMask(m_oldIsEnabled) ;
                }
            }
    } ;
}

#endif