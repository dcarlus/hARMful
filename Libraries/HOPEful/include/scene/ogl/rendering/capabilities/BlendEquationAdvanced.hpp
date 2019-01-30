#ifndef __HOPE__GL_CAPABILITY_BLEND_EQUATION__
#define __HOPE__GL_CAPABILITY_BLEND_EQUATION__

#include <scene/ogl/rendering/capabilities/Capability.hpp>
#include <scene/common/Color.hpp>
#include <array>

namespace Hope::GL {
    /**
     * Encapsulate the blend equation GL capability.
     */
    class BlendEquation final : public Capability {
        public:
            /**
             * Possible blend parameters.
             */
            enum class BlendParameter : GLenum {
                Zero =  GL_ZERO,
                One = GL_ONE,
                SourceColor = GL_SRC_COLOR,
                OneMinusSourceColor =  GL_ONE_MINUS_SRC_COLOR,
                DestinationColor = GL_DST_COLOR,
                OneMinusDestinationColor =  GL_ONE_MINUS_DST_COLOR,
                SourceAlpha = GL_SRC_ALPHA,
                OneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
                DestinationAlpha = GL_DST_ALPHA,
                OneMineDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
                ConstantColor = GL_CONSTANT_COLOR,
                OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
                ConstantAlpha = GL_CONSTANT_ALPHA,
                OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
                SourceSaturateAlpha = GL_SRC_ALPHA_SATURATE,
                Source1Color = GL_SRC1_COLOR,
                OneMinusSource1Color = GL_ONE_MINUS_SRC1_COLOR,
                Source1Alpha = GL_SRC1_ALPHA,
                OneMinusSource1Alpha = GL_ONE_MINUS_SRC1_ALPHA
            } ;

        private:
            /**
             * Index of the draw buffer for which to set the blend function.
             */
            GLuint m_bufferIndex ;

            /**
             * To know how the red, green, blue, and alpha source blending factors are computed.
             */
            std::array<BlendParameter, Color::Channels::AmountChannels> m_sourceParams{ One, One, One, One } ;

            /**
             * To know how the red, green, blue, and alpha destination blending
             * factors are computed.
             */
            std::array<BlendParameter, Color::Channels::AmountChannels> m_destinationParams{ Zero, Zero, Zero, Zero } ;

        public:
            /**
             * Set the buffer index.
             */
            void setBufferIndex(const GLuint index) {
                m_bufferIndex = index ;
            }

            /**
             * Set the blend parameter for the RGB channels of the source.
             */
            void setSourceRGBParameter(const BlendParameter param) {
                m_sourceParams[Color::Channels::Red] = param ;
                m_sourceParams[Color::Channels::Green] = param ;
                m_sourceParams[Color::Channels::Blue] = param ;
            }

            /**
             * Set the blend parameter for the alpha channel of the source.
             */
            void setSourceAlphaParameter(const BlendParameter param) {
                m_sourceParams[Color::Channels::Alpha] = param ;
            }

            /**
             * Set the blend parameter for the RGBA channels of the source.
             */
            void setSourceRGBAParameter(const BlendParameter param) {
                setSourceRGBParameter(param) ;
                setSourceAlphaParameter(param) ;
            }

            /**
             * Set the blend parameter for the RGB channels of the destination.
             */
            void setDestinationRGBParameter(const BlendParameter param) {
                m_destinationParams[Color::Channels::Red] = param ;
                m_destinationParams[Color::Channels::Green] = param ;
                m_destinationParams[Color::Channels::Blue] = param ;
            }

            /**
             * Set the blend parameter for the alpha channel of the destination.
             */
            void setDestinationAlphaParameter(const BlendParameter param) {
                m_destinationParams[Color::Channels::Alpha] = param ;
            }

            /**
             * Set the blend parameter for the RGBA channels of the destination.
             */
            void setDestinationRGBAParameter(const BlendParameter param) {
                setDestinationRGBParameter(param) ;
                setDestinationAlphaParameter(param) ;
            }

        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() {
                glEnable(GL_BLEND) ;

                for (
                    Color::Channels channel = Color::Channels::Red;
                    channel < Color::Channels::AmountChannels;
                    ++channel
                ) {
                    glBlendFunc(
                        m_bufferIndex,
                        m_sourceParams[channel],
                        m_destinationParams[channel]
                    ) ;
                }
            }

            /**
             * Remove the capability.
             */
            virtual void remove() {
                glDisable(GL_BLEND) ;
            }
    } ;
}

#endif