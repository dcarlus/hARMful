inline int32x4_t Vector4i::selection(
    const int32x4_t& selector,
    const int32x4_t& a,
    const int32x4_t& b
) {
    int32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        result[index] = selector[index] ? a[index] : b[index] ;
    }
    return result ;
}


                                              /** CONSTRUCTION / DESTRUCTION **/
Vector4i::Vector4i() {}

Vector4i::Vector4i(
    const int32_t& i1,
    const int32_t& i2,
    const int32_t& i3,
    const int32_t& i4
) {
    m_inner[0] = i1 ;
    m_inner[1] = i2 ;
    m_inner[2] = i3 ;
    m_inner[3] = i4 ;
}

Vector4i::Vector4i(const int32_t& value) {
    m_inner[0] = value ;
    m_inner[1] = value ;
    m_inner[2] = value ;
    m_inner[3] = value ;
}

Vector4i::Vector4i(const int32x4_t& vec) {
    std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
}

Vector4i::Vector4i(const float32x4_t& vec) {
    float32x4_t vecLocal = vec ;
    m_inner[0] = vecLocal[0] ;
    m_inner[1] = vecLocal[1] ;
    m_inner[2] = vecLocal[2] ;
    m_inner[3] = vecLocal[3] ;
}

Vector4i::~Vector4i() {}


                                                        /** STATIC FUNCTIONS **/
template <int32_t i0, int32_t i1, int32_t i2, int32_t i3>
inline int32x4_t Vector4i::constant() {
    int32x4_t vector;
    vector[0] = i0 ;
    vector[1] = i1 ;
    vector[2] = i2 ;
    vector[3] = i3 ;
    return vector ;
}

inline Vector4i Vector4i::min(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        result[index] = Math::min((*(int32x4_t*)a)[index], (*(int32x4_t*)b)[index]) ;
    }
    return result ;
}

inline Vector4i Vector4i::max(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        result[index] = Math::max((*(int32x4_t*)a)[index], (*(int32x4_t*)b)[index]) ;
    }
    return result ;
}

inline Vector4i Vector4i::abs(const Vector4i& vec) {
    int32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        result[index] = Math::abs((*(int32x4_t*)vec)[index]) ;
    }
    return result ;
}

inline void Vector4i::print() {
    int32_t* splitted = (int32_t*) &m_inner ;
    std::cout << "Vector4i @"
                            << std::hex << this << std::dec << "= { "
                                << m_inner[0] << ", "
                                << m_inner[1] << ", "
                                << m_inner[2] << ", "
                                << m_inner[3]
                            << " }"
                        << std::endl ;
}


                                                              /*** UTILITIES ***/
inline int32_t Vector4i::horizontalAdd() {
    return m_inner[0] + m_inner[1] + m_inner[2] + m_inner[3] ;
}


inline size_t Vector4i::length() const {
    return size() ;
}

inline size_t Vector4i::size() {
    return 4 ;
}


inline Vector4i::operator int32x4_t() const {
    return m_inner ;
}

inline Vector4i::operator int32x4_t*() const {
    return (int32x4_t*) &m_inner ;
}