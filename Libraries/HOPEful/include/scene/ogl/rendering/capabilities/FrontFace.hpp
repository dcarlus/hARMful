#ifndef __HOPE__GL_CAPABILITY_FRONT_FACE__
#define __HOPE__GL_CAPABILITY_FRONT_FACE__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the front face GL capability.
     * Default orientation is counter clock-wise.
     */
    class FrontFace final : public Capability {
        public:
            /**
             * Possible face orientations.
             */
            enum Orientation : GLenum {
                ClockWise = GL_CW,
                CounterClockWise = GL_CCW
            } ;

        private:
            /**
             * Orientation of front-facing polygons.
             */
            Orientation m_orientation = Orientation::CounterClockWise ;

            /**
             * Store the previous orientation before changing it. Allows
             * restoration when the capability is removed.
             */
            Orientation m_oldOrientation ;

        public:
            /**
             * Create a new FrontFace instance.
             */
            exported FrontFace() : Capability(CapabilityType::FrontFace) {}

            /**
             * Set the buffer index.
             */
            exported void setOrientation(const Orientation orientation) {
                m_orientation = orientation ;
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
