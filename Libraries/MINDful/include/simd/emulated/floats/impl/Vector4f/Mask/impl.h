inline float Vector4f::Mask::binaryConvert(uint32_t value) {
    return (*((float*) &value)) ;
}

inline uint32_t Vector4f::Mask::binaryConvert(float value) {
    return (*((uint32_t*) &value)) ;
}


                              				  /** CONSTRUCTION / DESTRUCTION **/
inline Vector4f::Mask::Mask(
                            const bool& b0,
                            const bool& b1,
                            const bool& b2,
                            const bool& b3
                           ) {
    m_inner[0] = binaryConvert(-uint32_t(b0)) ;
    m_inner[1] = binaryConvert(-uint32_t(b1)) ;
    m_inner[2] = binaryConvert(-uint32_t(b2)) ;
    m_inner[3] = binaryConvert(-uint32_t(b3)) ;
}

inline Vector4f::Mask::Mask(const bool& value) {
    m_inner[0] = binaryConvert(-uint32_t(value)) ;
    m_inner[1] = binaryConvert(-uint32_t(value)) ;
    m_inner[2] = binaryConvert(-uint32_t(value)) ;
    m_inner[3] = binaryConvert(-uint32_t(value)) ;
}

inline Vector4f::Mask::Mask(const float32x4_t& vec) {
    memcpy(&m_inner, &vec, sizeof(float32x4_t)) ;
}

inline Vector4f::Mask::Mask(const Vector4i::Mask& mask) {
    int32x4_t maskInner = mask ;
    m_inner[0] = binaryConvert(-uint32_t(maskInner[0])) ;
    m_inner[1] = binaryConvert(-uint32_t(maskInner[1])) ;
    m_inner[2] = binaryConvert(-uint32_t(maskInner[2])) ;
    m_inner[3] = binaryConvert(-uint32_t(maskInner[3])) ;
}

inline Vector4f::Mask::Mask(const Vector4ui::Mask& mask) {
    uint32x4_t maskInner = mask ;
    m_inner[0] = binaryConvert(-uint32_t(maskInner[0])) ;
    m_inner[1] = binaryConvert(-uint32_t(maskInner[1])) ;
    m_inner[2] = binaryConvert(-uint32_t(maskInner[2])) ;
    m_inner[3] = binaryConvert(-uint32_t(maskInner[3])) ;
}

inline Vector4f::Mask::~Mask() {}


                                             				 /*** UTILITIES ***/
inline bool Vector4f::Mask::get(const unsigned int& index) {
    return (m_inner[index] != 0.f) ;
}

inline size_t Vector4f::Mask::length() const {
    return size() ;
}

inline size_t Vector4f::Mask::size() {
    return Vector4f::size() ;
}

inline void Vector4f::Mask::print() {
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
inline Vector4f::Mask& Vector4f::Mask::operator=(const Mask& mask) {
    memcpy(&m_inner, &mask.m_inner, sizeof(float32x4_t)) ;
    return *this ;
}

inline Vector4f::Mask& Vector4f::Mask::operator=(const bool& value) {
    m_inner[0] = binaryConvert(-uint32_t(value)) ;
    m_inner[1] = binaryConvert(-uint32_t(value)) ;
    m_inner[2] = binaryConvert(-uint32_t(value)) ;
    m_inner[3] = binaryConvert(-uint32_t(value)) ;
    return *this ;
}

inline Vector4f::Mask& Vector4f::Mask::operator=(const int32x4_t& vec) {
    memcpy(&m_inner, &vec, sizeof(float32x4_t)) ;
    return *this ;
}

inline Vector4f::Mask& Vector4f::Mask::operator=(const float32x4_t& vec) {
    memcpy(&m_inner, &vec, sizeof(float32x4_t)) ;
    return *this ;
}

inline Vector4f::Mask& Vector4f::Mask::operator=(const Vector4i::Mask& mask) {
    int32x4_t tmp = mask ;
    memcpy(&m_inner, &tmp, sizeof(float32x4_t)) ;
    return *this ;
}

                                          				  /** CAST OPERATORS **/
inline Vector4f::Mask::operator int32x4_t() const {
    int32x4_t result ;
    memcpy(&result, &m_inner, sizeof(float32x4_t)) ;
    return result ;
}

inline Vector4f::Mask::operator float32x4_t() const {
    float32x4_t result ;
    memcpy(&result, &m_inner, sizeof(float32x4_t)) ;
    return result ;
}

inline Vector4f::Mask::operator float32x4_t*() const {
    return (float32x4_t*) &m_inner ;
}

inline Vector4f::Mask::operator Vector4i::Mask() const {
    int32x4_t result ;
    memcpy(&result, &m_inner, sizeof(int32x4_t)) ;
    return result ;
}

inline Vector4f::Mask::operator Vector4ui::Mask() const {
    uint32x4_t result ;
    memcpy(&result, &m_inner, sizeof(uint32x4_t)) ;
    return result ;
}
