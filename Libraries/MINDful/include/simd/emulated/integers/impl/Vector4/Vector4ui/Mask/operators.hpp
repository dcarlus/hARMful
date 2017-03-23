                                                                     /** AND **/
/**
 * Bitwise AND operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE if they are TRUE if both parameters.
 *          They are FALSE if at least one operand has FALSE at that position.
 */
static inline typename Vector4ui::Mask operator&(
    const typename Vector4ui::Mask& a,
    const typename Vector4ui::Mask& b
) {
    uint32x4_t result ;
    uint32x4_t* aLocal = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bLocal = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4ui::Mask::size() ; ++index) {
        result[index] = (*aLocal)[index] & (*bLocal)[index] ;
    }
    return result ;
}

/**
 * Bitwise AND operator on two Masks. The result is affected to the
 * first operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE if they are TRUE if both parameters.
 *          They are FALSE if at least one operand has FALSE at that position.
 */
static inline typename Vector4ui::Mask& operator&=(
    typename Vector4ui::Mask& a,
    const typename Vector4ui::Mask& b
) {
    a = a & b ;
    return a ;
}


                                                                      /** OR **/
/**
 * Bitwise OR operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are FALSE if they are FALSE if both
 *          parameters. They are TRUE if at least one operand has TRUE at that
 * position.
 */
static inline typename Vector4ui::Mask operator|(
    const typename Vector4ui::Mask& a,
    const typename Vector4ui::Mask& b
) {
    uint32x4_t result ;
    uint32x4_t* aLocal = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bLocal = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4ui::Mask::size() ; ++index) {
        result[index] = (*aLocal)[index] | (*bLocal)[index] ;
    }
    return result ;
}

/**
 * Bitwise OR operator on two Masks. The result is affected to the
 * first operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are FALSE if they are FALSE if both
 *          parameters. They are TRUE if at least one operand has TRUE at that
 * position.
 */
static inline typename Vector4ui::Mask& operator|=(
    typename Vector4ui::Mask& a,
    const typename Vector4ui::Mask& b
) {
    a = a | b ;
    return a ;
}


                                                                     /** XOR **/
/**
 * Bitwise XOR operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE only when the two operands have
 *          different values at a same given position.
 */
static inline typename Vector4ui::Mask operator^(
    const typename Vector4ui::Mask& a,
    const typename Vector4ui::Mask& b
) {
    uint32x4_t result ;
    uint32x4_t* aLocal = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bLocal = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4ui::Mask::size() ; ++index) {
        result[index] = (*aLocal)[index] ^ (*bLocal)[index] ;
    }
    return result ;
}

/**
 * Bitwise XOR operator on two Masks. The result is affected to the
 * first operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE only when the two operands have
 *          different values at a same given position.
 */
static inline typename Vector4ui::Mask& operator^=(
    typename Vector4ui::Mask& a,
    const typename Vector4ui::Mask& b
) {
    a = a ^ b ;
    return a ;
}


                                                                     /** NOT **/
/**
 * Reverse each boolean value.
 * @param   a   The Mask for which bits must be reversed.
 * @return  The result Mask, for which bit are reversed compared to input.
 */
static inline typename Vector4ui::Mask operator~(const typename Vector4ui::Mask& a) {
    uint32x4_t result ;
    uint32x4_t* aLocal = static_cast<uint32x4_t*>(a) ;
    for (unsigned int index = 0 ; index < Vector4ui::Mask::size() ; ++index) {
        result[index] = ~(*aLocal)[index] ;
    }
    return result ;
}
