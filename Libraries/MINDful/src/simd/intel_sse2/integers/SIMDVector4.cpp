#include <MINDOptions.hpp>
#ifdef USE_INTEL_SSE2

#include <simd/intel_sse2/integers/SIMDVector4.hpp>

namespace Mind {
	namespace SSE2 {
		template <typename Type>
		int32x4_t Vector4<Type>::selection(
										    const int32x4_t& selector,
										    const int32x4_t& a,
										    const int32x4_t& b
										   ) {
			#if defined(USE_INTEL_SSE4_1)
			    return _mm_blendv_epi8 (b, a, selector) ;
			#else
			    return _mm_or_si128(
							        _mm_and_si128(selector, a),
							        _mm_andnot_si128(selector, b)
								   ) ;
			#endif
		}

		                                              /** CONSTRUCTION / DESTRUCTION **/
		template <typename Type>
		Vector4<Type>::Vector4() {}

		template <typename Type>
		Vector4<Type>::Vector4(const Type& i1, const Type& i2, const Type& i3, const Type& i4) {
		    m_inner = _mm_setr_epi32(i1, i2, i3, i4) ;
		}

		template <typename Type>
		Vector4<Type>::Vector4(const Type& value) {
		    m_inner = _mm_set1_epi32(value) ;
		}

		template <typename Type>
		Vector4<Type>::Vector4(const int32x4_t& vec) {
			m_inner = vec ;
		}

		template <typename Type>
		Vector4<Type>::Vector4(const float32x4_t& vec) {
		    m_inner = _mm_castps_si128(vec) ;
		}

		template <typename Type>
		Vector4<Type>::~Vector4() {}


		                                             				 /*** UTILITIES ***/
		template <typename Type>
		Type Vector4<Type>::horizontalAdd() {
		    // The goal of this function is to put the sum of vector elements in the
		    // lower element (ie. first position) of the result, and finally return the
		    // contained value in this lower element.
		    #if defined (USE_INTEL_SSSE3)
		        // Compute sum of all elements in vector.
		        // Notice that _mm_hadd_ps() function only sum adjacent positions
		        // (indices 0+1 ; 2+3). It is so necessary to sum twice the vector to
		        // sum the four positions.
		        int32x4_t sum1 = _mm_hadd_epi32(m_inner, m_inner) ;
		        // Sum twice.
		        int32x4_t sum2 = _mm_hadd_epi32(sum1, sum1) ;
		        // Get the lower element from the inner vector, containing the sum of
		        // all elements.
		        return _mm_cvtsi128_si32(sum2) ;
		    #else
		        // Shuffle highest elements.
		        int32x4_t tmp1 = _mm_shuffle_epi32(m_inner, 0x0E) ;
		        // Then, sum inner to tmp1.
		        int32x4_t tmp2 = _mm_add_epi32(m_inner, tmp1) ;
		        int32x4_t tmp3 = _mm_shuffle_epi32(tmp2, 0x01) ;
		        int32x4_t tmp4 = _mm_add_epi32(tmp2, tmp3) ;
		        return _mm_cvtsi128_si32(tmp4) ;
		    #endif
		}


		template <typename Type>
		size_t Vector4<Type>::length() const {
			return size() ;
		}

		template <typename Type>
		size_t Vector4<Type>::size() {
			return 4 ;
		}


		template <typename Type>
		Vector4<Type>::operator int32x4_t() const {
			return m_inner ;
		}


	    template class Vector4<int> ;
	    template class Vector4<unsigned int> ;

	} ;

} ;

#endif