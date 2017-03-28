#include <MINDOptions.hpp>
#ifdef USE_NO_SIMD

#include <cstring>
#include <simd/emulated/floats/SIMDVector4f.hpp>

namespace Mind {
    namespace EmulatedSIMD {
        float Vector4f::Mask::binaryConvert(const uint32_t value) {
            const float* tmpPtr = reinterpret_cast<const float*>(&value) ;
            return *tmpPtr ;
        }

        uint32_t Vector4f::Mask::binaryConvert(const float value) {
            const uint32_t* tmpPtr = reinterpret_cast<const uint32_t*>(&value) ;
            return *tmpPtr ;
        }


                                                /** CONSTRUCTION / DESTRUCTION **/
        Vector4f::Mask::Mask(
            const bool b0,
            const bool b1,
            const bool b2,
            const bool b3
        ) {
            m_inner[0] = binaryConvert(BoolToUInt32(b0)) ;
            m_inner[1] = binaryConvert(BoolToUInt32(b1)) ;
            m_inner[2] = binaryConvert(BoolToUInt32(b2)) ;
            m_inner[3] = binaryConvert(BoolToUInt32(b3)) ;
        }

        Vector4f::Mask::Mask(const bool value) {
            m_inner[0] = binaryConvert(BoolToUInt32(value)) ;
            m_inner[1] = binaryConvert(BoolToUInt32(value)) ;
            m_inner[2] = binaryConvert(BoolToUInt32(value)) ;
            m_inner[3] = binaryConvert(BoolToUInt32(value)) ;
        }

        Vector4f::Mask::Mask(const float32x4_t& vec) {
            std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
        }

        Vector4f::Mask::Mask(const Vector4i::Mask& mask) {
            int32x4_t maskInner = static_cast<int32x4_t>(mask) ;
            m_inner[0] = binaryConvert(BoolToUInt32(maskInner[0])) ;
            m_inner[1] = binaryConvert(BoolToUInt32(maskInner[1])) ;
            m_inner[2] = binaryConvert(BoolToUInt32(maskInner[2])) ;
            m_inner[3] = binaryConvert(BoolToUInt32(maskInner[3])) ;
        }

        Vector4f::Mask::Mask(const Vector4ui::Mask& mask) {
            uint32x4_t maskInner = static_cast<uint32x4_t>(mask) ;
            m_inner[0] = binaryConvert(BoolToUInt32(maskInner[0])) ;
            m_inner[1] = binaryConvert(BoolToUInt32(maskInner[1])) ;
            m_inner[2] = binaryConvert(BoolToUInt32(maskInner[2])) ;
            m_inner[3] = binaryConvert(BoolToUInt32(maskInner[3])) ;
        }

        Vector4f::Mask::~Mask() {}


                                                              /*** UTILITIES ***/
        bool Vector4f::Mask::get(const unsigned int index) {
            return (m_inner[index] != 0.f) ;
        }

        size_t Vector4f::Mask::length() const {
            return size() ;
        }

        size_t Vector4f::Mask::size() {
            return Vector4f::size() ;
        }

        void Vector4f::Mask::print() {
            std::cout << "Vector4f::Mask @"
                                    << std::hex << this << std::dec << "= { "
                                        << m_inner[0] << ", "
                                        << m_inner[1] << ", "
                                        << m_inner[2] << ", "
                                        << m_inner[3]
                                    << " }"
                                << std::endl ;
        }


                                                              /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
        Vector4f::Mask& Vector4f::Mask::operator=(const Mask& mask) {
            auto other = mask.m_inner ;
            std::copy(other.begin(), other.end(), m_inner.begin()) ;
            return *this ;
        }

        Vector4f::Mask& Vector4f::Mask::operator=(const bool value) {
            m_inner[0] = binaryConvert(BoolToUInt32(value)) ;
            m_inner[1] = binaryConvert(BoolToUInt32(value)) ;
            m_inner[2] = binaryConvert(BoolToUInt32(value)) ;
            m_inner[3] = binaryConvert(BoolToUInt32(value)) ;
            return *this ;
        }

        Vector4f::Mask& Vector4f::Mask::operator=(const int32x4_t& vec) {
            std::memcpy(m_inner.data(), vec.data(), sizeof(vec)) ;
            return *this ;
        }

        Vector4f::Mask& Vector4f::Mask::operator=(const float32x4_t& vec) {
            std::memcpy(m_inner.data(), vec.data(), sizeof(vec)) ;
            return *this ;
        }

        Vector4f::Mask& Vector4f::Mask::operator=(const Vector4i::Mask& mask) {
            auto other = (int32x4_t) mask ;
            std::memcpy(m_inner.data(), other.data(), sizeof(other)) ;
            return *this ;
        }

                                                            /** CAST OPERATORS **/
        Vector4f::Mask::operator int32x4_t() const {
            int32x4_t result ;
            std::memcpy(result.data(), m_inner.data(), sizeof(m_inner)) ;
            return result ;
        }

        Vector4f::Mask::operator float32x4_t() const {
            float32x4_t result ;
            std::copy(m_inner.begin(), m_inner.end(), result.begin()) ;
            return result ;
        }

        Vector4f::Mask::operator float32x4_t*() const {
            return (float32x4_t*) &m_inner ;
        }

        Vector4f::Mask::operator Vector4i::Mask() const {
            int32x4_t result ;
            std::memcpy(result.data(), m_inner.data(), sizeof(m_inner)) ;
            return result ;
        }

        Vector4f::Mask::operator Vector4ui::Mask() const {
            uint32x4_t result ;
            std::memcpy(result.data(), m_inner.data(), sizeof(m_inner)) ;
            return result ;
        }
    } ;
} ;

#endif
