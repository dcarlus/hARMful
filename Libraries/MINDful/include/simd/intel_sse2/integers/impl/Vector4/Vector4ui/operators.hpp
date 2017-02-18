                                                                /** ADDITION **/
/**
 * Add two Vector4ui, each element of a Vector4ui to its corresponding one in
 * the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4ui operator+(const Vector4ui& a, const Vector4ui& b) {
    return _mm_add_epi32(a, b) ;
}

/**
 * Add a Vector4ui to a float. The float is converted to a Vector4ui where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4ui operator+(const Vector4ui& a, const float& b) {
    return a + Vector4ui(b) ;
}

/**
 * Add a Vector4ui to a float. The float is converted to a Vector4ui where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4ui operator+(const float& a, const Vector4ui& b) {
    return Vector4ui(a) + b ;
}

/**
 * Add a Vector4ui to a float. The float is converted to a Vector4ui where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4ui& operator+=(Vector4ui& a, const Vector4ui& b) {
    a = a + b ;
    return a ;
}

/**
 * Add two Vector4ui, each element of a Vector4ui to its corresponding one in
 * the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4ui& operator+=(Vector4ui& a, const float& b) {
    a = a + Vector4ui(b) ;
    return a ;
}


                                                               /** INCREMENT **/
/**
 * Postfix incrementation.
 * @param   a   Vector4ui for which each component is increased of +1.
 * @warning Quite slower than prefix incrementation.
 */
static inline Vector4ui operator++(Vector4ui& a, int) {
    Vector4ui previous = a ;
    a = a + 1.f ;
    return previous ;
}

/**
 * Prefix incrementation.
 * @param   a   Vector4ui for which each component is increased of +1.
 */
static inline Vector4ui& operator++(Vector4ui& a) {
    a = a + 1.f ;
    return a ;
}


                                                              /** DIFFERENCE **/
/**
 * Substract two Vector4ui, each element of a Vector4ui to its corresponding one
 * in the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4ui operator-(const Vector4ui& a, const Vector4ui& b) {
    return _mm_sub_epi32(a, b) ;
}

/**
 * Substract a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4ui operator-(const Vector4ui& a, const float& b) {
    return a - Vector4ui(b) ;
}

/**
 * Substract a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4ui operator-(const float& a, const Vector4ui& b) {
    return Vector4ui(a) - b ;
}

/**
 * Substract two Vector4ui, each element of a Vector4ui to its corresponding one
 * in the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4ui& operator-=(Vector4ui& a, const Vector4ui& b) {
    a = a - b ;
    return a ;
}

/**
 * Substract a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4ui& operator-=(Vector4ui& a, const float& b) {
    a = a - Vector4ui(b) ;
    return a ;
}


                                                                  /** NEGATE **/
/**
 * Negate a Vector4.
 * @param   a   The Vector4 to negate.
 * @return  The negated Vector4.
 */
static inline Vector4ui operator-(const Vector4ui& a) {
    const int MaskNegateBit = 0x80000000 ;
    return _mm_xor_si128(a, _mm_set1_epi32(MaskNegateBit)) ;
}


                                                               /** DECREMENT **/
/**
 * Postfix decrementation.
 * @param   a   Vector4ui for which each component is decreased of -1.
 * @warning Quite slower than prefix decrementation.
 */
static inline Vector4ui operator--(Vector4ui& a, int) {
    Vector4ui previous = a ;
    a = a - 1.f ;
    return previous ;
}

/**
 * Prefix decrementation.
 * @param   a   Vector4ui for which each component is decreased of -1.
 */
static inline Vector4ui& operator--(Vector4ui& a) {
    a = a - 1.f ;
    return a ;
}


                                                                /** MULTIPLY **/
/**
 * Multiply two Vector4ui, each element of a Vector4ui to its corresponding one
 * in the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4ui operator*(const Vector4ui& a, const Vector4ui& b) {
    #if defined USE_INTEL_SSE4_1
        return _mm_mullo_epi32(a, b) ;
    #else
        // As for SSE4.1 built-in function :
        // Multiply the packed 32-bit integers in a and b, producing
        // intermediate 64-bit integers, and store the low 32 bits of the
        // intermediate integers in dst.
        int32x4_t a13 = _mm_shuffle_epi32(a, 0xF5) ;                            // Keep values (-,a3,-,a1)
        int32x4_t b13 = _mm_shuffle_epi32(b, 0xF5) ;                            // Keep values (-,b3,-,b1)
        int32x4_t prod02 = _mm_mul_epu32(a, b) ;                                // (-,a2*b2,-,a0*b0)
        int32x4_t prod13 = _mm_mul_epu32(a13, b13) ;                            // (-,a3*b3,-,a1*b1)
        // Unpack and interleave 32-bit integers from the low half of a and b
        int32x4_t prod01 = _mm_unpacklo_epi32(prod02, prod13) ;                 // (-,-,a1*b1,a0*b0)
        // Unpack and interleave 32-bit integers from the high half of a and b
        int32x4_t prod23 = _mm_unpackhi_epi32(prod02, prod13) ;                 // (-,-,a3*b3,a2*b2)
        // Unpack and interleave 64-bit integers from the low half of a and b   // (ab3,ab2,ab1,ab0)
        return _mm_unpacklo_epi64(prod01, prod23) ;
    #endif
}

/**
 * Multiply a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4ui operator*(const Vector4ui& a, const float& b) {
    return a * Vector4ui(b) ;
}

/**
 * Multiply a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4ui operator*(const float& a, const Vector4ui& b) {
    return Vector4ui(a) * b ;
}

/**
 * Multiply two Vector4ui, each element of a Vector4ui to its corresponding one
 * in the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4ui& operator*=(Vector4ui& a, const Vector4ui& b) {
    a = a * b ;
    return a ;
}

/**
 * Multiply a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4ui& operator*=(Vector4ui& a, const float& b) {
    a = a * Vector4ui(b) ;
    return a ;
}


                                                  /*** COMPARISON OPERATORS ***/
/**
 * Check if two Vector4ui objects contain the same values.
 * The positions for which the values are equal are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values are
 *          equal, FALSE for different values in the Vector4ui parameters.
 */
static inline Vector4ui::Mask operator==(const Vector4ui& a, const Vector4ui& b) {
    return _mm_cmpeq_epi32(a, b) ;
}

/**
 * Check if two Vector4ui objects contain different values.
 * The positions for which the values are different are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values
 *          are different, FALSE for different values in the Vector4ui
 *          parameters.
 */
static inline Vector4ui::Mask operator!=(const Vector4ui& a, const Vector4ui& b) {
    Vector4ui::Mask compVec = (a == b) ;
    Vector4ui::Mask reversedCompVec = operator~<uint32_t>(compVec) ;
    return reversedCompVec ;
}

/**
 * Check positions <i>p</i> in Vector4ui objects at which
 * @a a[<i>p</i>] < @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values of
 *          @a a are lower than values of @a b.
 */
static inline Vector4ui::Mask operator<(const Vector4ui& a, const Vector4ui& b) {
    return _mm_cmplt_epi32(a, b) ;
}

/**
 * Check positions <i>p</i> in Vector4ui objects at which
 * @a a[<i>p</i>] > @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values of
 *          @a a are greater than values of @a b.
 */
static inline Vector4ui::Mask operator>(const Vector4ui& a, const Vector4ui& b) {
    return b < a ;
}

/**
 * Check positions <i>p</i> in Vector4ui objects at which
 * @a a[<i>p</i>] >= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values of
 *          @a a are greater or equal to values of @a b.
 */
static inline Vector4ui::Mask operator>=(const Vector4ui& a, const Vector4ui& b) {
    Vector4ui::Mask compVec = (b > a) ;
    Vector4ui::Mask reversedCompVec = operator~<uint32_t>(compVec) ;
    return reversedCompVec ;
}

/**
 * Check positions <i>p</i> in Vector4ui objects at which
 * @a a[<i>p</i>] <= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values of
 *          @a a are lower or equal to values of @a b.
 */
static inline Vector4ui::Mask operator<=(const Vector4ui& a, const Vector4ui& b) {
    return b >= a ;
}

                                             /*** BITWISE LOGICAL OPERATORS ***/
/**
 * Reverse bits of a Vector4ui.
 * @param   a   Vector for which the bits have to be reversed.
 * @return  A Vector4ui corresponding the the @a a reversed at bit level.
 */
static inline Vector4ui operator~(const Vector4ui& a) {
    return _mm_xor_si128(a, _mm_set1_epi32(-1)) ;
}

                                                                     /** AND **/
/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4ui operator&(const Vector4ui& a, const Vector4ui& b) {
    return _mm_and_si128(a, b) ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4ui& operator&=(Vector4ui& a, const Vector4ui& b) {
    a = a & b ;
    return a ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4ui operator&(const Vector4ui& a, const Vector4ui::Mask& b) {
    return _mm_and_si128(a, b) ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4ui& operator&=(Vector4ui& a, const Vector4ui::Mask& b) {
    a = a & b ;
    return a ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4ui operator&(const Vector4ui::Mask& a, const Vector4ui& b) {
    return _mm_and_si128(a, b) ;
}


                                                                      /** OR **/
/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4ui operator|(const Vector4ui& a, const Vector4ui& b) {
    return _mm_or_si128(a, b) ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4ui& operator|=(Vector4ui& a, const Vector4ui& b) {
    a = a | b ;
    return a ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4ui operator|(const Vector4ui& a, const Vector4ui::Mask& b) {
    return _mm_or_si128(a, b) ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4ui& operator|=(Vector4ui& a, const Vector4ui::Mask& b) {
    a = a | b ;
    return a ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4ui operator|(const Vector4ui::Mask& a, const Vector4ui& b) {
    return _mm_or_si128(a, b) ;
}


                                                                     /** XOR **/
/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4ui operator^(const Vector4ui& a, const Vector4ui& b) {
    return _mm_xor_si128(a, b) ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4ui& operator^=(Vector4ui& a, const Vector4ui& b) {
    a = a ^ b ;
    return a ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4ui operator^(const Vector4ui& a, const Vector4ui::Mask& b) {
    return _mm_xor_si128(a, b) ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4ui& operator^=(Vector4ui& a, const Vector4ui::Mask& b) {
    a = a ^ b ;
    return a ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4ui operator^(const Vector4ui::Mask& a, const Vector4ui& b) {
    return _mm_xor_si128(a, b) ;
}


                                                                   /** SHIFT **/
/**
 * Shift left values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4ui operator<<(const Vector4ui& vec, const int32_t& bits) {
    return _mm_sll_epi32(vec,_mm_cvtsi32_si128(bits)) ;
}

/**
 * Shift left values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4ui& operator<<=(Vector4ui& vec, const int32_t& bits) {
    vec = vec << bits ;
    return vec ;
}


/**
 * Shift right values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4ui operator>>(const Vector4ui& vec, const int32_t& bits) {
    return _mm_sra_epi32(vec,_mm_cvtsi32_si128(bits)) ;
}

/**
 * Shift right values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4ui& operator>>=(Vector4ui& vec, const int32_t& bits) {
    vec = vec << bits ;
    return vec ;
}