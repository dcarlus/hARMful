#include <MINDOptions.h>
#ifdef USE_INTEL_SSE2

#include <simd/intel_sse2/integers/SIMDVector4i.h>

namespace Mind {

	namespace SSE2 {

                                              /** CONSTRUCTION / DESTRUCTION **/
        Vector4i::Vector4i() : Vector4int32() {}

        Vector4i::Vector4i(
                           const int32_t& i1,
                           const int32_t& i2,
                           const int32_t& i3,
                           const int32_t& i4
                          ) : Vector4int32(i1, i2, i3, i4) {}

        Vector4i::Vector4i(const int32_t& value) : Vector4int32(value) {}

        Vector4i::Vector4i(const int32x4_t& vec) : Vector4int32(vec) {}

        Vector4i::Vector4i(const float32x4_t& vec) : Vector4int32(vec) {}

        Vector4i::~Vector4i() {}


                                                        /** STATIC FUNCTIONS **/
        // template <int32_t i0, int32_t i1, int32_t i2, int32_t i3>
        // int32x4_t Vector4i::constant() {
        //     static const union {
        //         int integer[4] ;
        //         int32x4_t vector ;
        //     } u = {{i0, i1, i2, i3}} ;
        //     return u.vector ;
        // }

        Vector4i Vector4i::min(const Vector4i& a, const Vector4i& b) {
            #if defined(USE_INTEL_SSE4_1)
                return _mm_min_epi32(a, b) ;
            #else
                int32x4_t greater = _mm_cmpgt_epi32(a, b) ;
                return Vector4::selection(greater, b, a) ;
            #endif
        }

        Vector4i Vector4i::max(const Vector4i& a, const Vector4i& b) {
            #if defined(USE_INTEL_SSE4_1)
                return _mm_max_epi32(a, b) ;
            #else
                int32x4_t greater = _mm_cmpgt_epi32(a, b) ;
                return Vector4::selection(greater, a, b) ;
            #endif
        }

        Vector4i Vector4i::abs(const Vector4i& vec) {
            #if defined(USE_INTEL_SSSE3)
                return _mm_sign_epi32(vec, vec) ;
            #else
                // Get the sign of vector values.
                int32x4_t sign = _mm_srai_epi32(vec, 31) ;
                // Invert bits for negative values.
                int32x4_t inv  = _mm_xor_si128(vec, sign) ;
                // Add one to the inverted values (through shifted sign) to retrieve
                // absolute values of vec.
                return _mm_sub_epi32(inv, sign) ;
            #endif
        }

        void Vector4i::print() {
            int32_t* splitted = (int32_t*) &m_inner ;
            std::cout << "Vector4i @"
                                    << std::hex << this << std::dec << "= { "
                                        << splitted[0] << ", "
                                        << splitted[1] << ", "
                                        << splitted[2] << ", "
                                        << splitted[3]
                                    << " }"
                                << std::endl ;
        }


                                                             /*** OPERATORS ***/
                                                                   /** SHIFT **/
        //static Vector4i operator<<(const Vector4i& vec, int32_t bits) {
        //    return _mm_sll_epi32(vec,_mm_cvtsi32_si128(bits)) ;
        //}

        //static Vector4i& operator<<=(Vector4i& vec, int32_t bits) {
        //    vec = vec << bits ;
        //    return vec ;
        //}

        //static Vector4i operator>>(const Vector4i& vec, int32_t bits) {
        //    return _mm_sra_epi32(vec,_mm_cvtsi32_si128(bits)) ;
        //}

        //static Vector4i& operator>>=(Vector4i& vec, int32_t bits) {
        //    vec = vec << bits ;
        //    return vec ;
        //}

                                                              /** COMPARISON **/
        //static Vector4i operator==(const Vector4i& a, const Vector4i&b) {
        //    return _mm_cmpeq_epi32(a, b) ;
        //}

        //static Vector4i operator!=(const Vector4i& a, const Vector4i&b) {
        //    return !(a == b) ;
        //}

    } ;

} ;

#endif
