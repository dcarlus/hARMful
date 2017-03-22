#include <geometry/dimensions/Dimension3Df.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <cmath>

namespace Mind {
    Dimension3Df::Dimension3Df() : m_width(0), m_height(0), m_depth(0) {}

    Dimension3Df::Dimension3Df(
        Scalar width,
        Scalar height,
        Scalar depth
    ) : m_width(width),
        m_height(height),
        m_depth(depth) {}

    void Dimension3Df::absolute() {
        m_width = std::fabs(m_width) ;
        m_height = std::fabs(m_height) ;
        m_depth = std::fabs(m_depth) ;
    }

    Scalar Dimension3Df::getWidth() const {
        return m_width ;
    }

    Scalar Dimension3Df::getHeight() const {
        return m_height ;
    }

    Scalar Dimension3Df::getDepth() const {
        return m_depth ;
    }

    void Dimension3Df::setWidth(Scalar width) {
        m_width = std::fabs(width) ;
    }

    void Dimension3Df::setHeight(Scalar height) {
        m_height = std::fabs(height) ;
    }

    void Dimension3Df::setDepth(Scalar depth) {
        m_depth = std::fabs(depth) ;
    }

    void Dimension3Df::set(
        Scalar width,
        Scalar height,
        Scalar depth
    ) {
        m_width = std::fabs(width) ;
        m_height = std::fabs(height) ;
        m_depth = std::fabs(depth) ;
    }

    Dimension3Df::operator Point3Df() {
        return Point3Df(m_width, m_height, m_depth) ;
    }

    Dimension3Df::operator Dimension2Df() {
        return Dimension2Df(m_width, m_height) ;
    }


    Dimension3Df& Dimension3Df::operator+=(Dimension3Df& other) {
        m_width += other.m_width ;
        m_height += other.m_height ;
        m_depth += other.m_depth ;
        return *this ;
    }

    Dimension3Df& Dimension3Df::operator-=(Dimension3Df& other) {
        m_width = (other.m_width > m_width) ? 0 : m_width - other.m_width ;
        m_height = (other.m_height > m_height) ? 0 : m_height - other.m_height ;
        m_depth = (other.m_depth > m_depth) ? 0 : m_depth - other.m_depth ;

        return *this ;
    }

    Dimension3Df& Dimension3Df::operator*=(Scalar coeff) {
        m_width *= coeff ;
        m_height *= coeff ;
        m_depth *= coeff ;
        return *this ;
    }

    Dimension3Df& Dimension3Df::operator/=(Scalar coeff) {
        m_width /= coeff ;
        m_height /= coeff ;
        m_depth /= coeff ;
        return *this ;
    }

    bool Dimension3Df::operator==(const Dimension3Df& other) const {
        return ((this == &other) ||
                        ((m_width == other.m_width)
                            && (m_height == other.m_height)
                            && (m_depth == other.m_depth))) ;
    }

    bool Dimension3Df::operator!=(const Dimension3Df& other) const {
        return !(*this == other) ;
    }

    Dimension3Df operator+(const Dimension3Df& a, const Dimension3Df& b) {
        return Dimension3Df(
            a.getWidth() + b.getWidth(),
            a.getHeight() + b.getHeight(),
            a.getDepth() + b.getDepth()
        ) ;
    }

    Dimension3Df operator-(const Dimension3Df& a, const Dimension3Df& b) {
        return Dimension3Df(
            a.getWidth() - b.getWidth(),
            a.getHeight() - b.getHeight(),
            a.getDepth() - b.getDepth()
        ) ;
    }

    Dimension3Df operator*(const Dimension3Df& d, Scalar coeff) {
        return Dimension3Df(
            d.getWidth() * coeff,
            d.getHeight() * coeff,
            d.getDepth() * coeff
        ) ;
    }

    Dimension3Df operator/(const Dimension3Df& d, Scalar coeff) {
        return Dimension3Df(
            d.getWidth() / coeff,
            d.getHeight() / coeff,
            d.getDepth() / coeff
        ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Dimension3Df& p) {
        s << "Dimension3Df {" <<
                                 p.getWidth() << "," <<
                                 p.getHeight() << "," <<
                                 p.getDepth() <<
                           "}" ;
        return s ;
    }
} ;
