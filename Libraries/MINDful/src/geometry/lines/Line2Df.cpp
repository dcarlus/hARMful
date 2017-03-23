#include <geometry/lines/Line2Df.hpp>
#include <FastMath.hpp>
#include <Math.hpp>

namespace Mind {
    Line2Df::Line2Df() {
        m_length = 0.f ;
    }

    Line2Df::Line2Df(
        const Point2Df& start,
        const Point2Df& end
    ) : m_start(start),
        m_end(end) {
        m_length = Point2Df::distance(m_start, m_end) ;
    }

    Scalar Line2Df::length() {
        if (m_isChanged) {
            m_length = Point2Df::distance(m_start, m_end) ;
        }
        return m_length ;
    }

    Scalar Line2Df::lengthSquared() {
        if (m_isChanged) {
            m_length = Point2Df::distance(m_start, m_end) ;
        }
        return m_length * m_length ;
    }

    bool Line2Df::isContiguousTo(const Line2Df& other) {
        return ((m_start == other.m_end) || (m_end == other.m_start)) ;
    }

    char Line2Df::CCW(const Line2Df& l, const Point2Df& p) {
        // Relative expression of S and P to the start point of S.
        Line2Df l2 = relative(l) ;
        Point2Df p2 = p - l.m_start ;

        Scalar ccw = (p2.getX() * l2.m_end.getY()) - (p2.getY() * l2.m_end.getX()) ;
        if (ccw == 0) {
            ccw = (p2.getX() * l2.m_end.getX()) + (p2.getY() * l2.m_end.getY()) ;
            if (ccw > 0) {
                // Make P relative to the end point of S
                p2 = p - l.m_end ;
                ccw = (p2.getX() * l.m_end.getX()) + (p2.getY() * l.m_end.getY()) ;
                if (ccw < 0) {
                    ccw = 0 ;
                }
            }
        }

        if (ccw < 0) {
            return -1 ;
        }
        else if (ccw > 0) {
            return 1 ;
        }
        else {
            return 0 ;
        }
    }

    Line2Df Line2Df::relative(const Line2Df& l) {
        return Line2Df(Point2Df(0,0), l.m_end - l.m_start) ;
    }

    bool Line2Df::intersects(const Line2Df& line) {
        if (isContiguousTo(line)) {
            return false ;
        }

        bool intersection ;
        intersection = ((CCW(*this, line.m_start) * CCW(*this, line.m_end)) < 1)
                            && ((CCW(line, m_start) * CCW(line, m_end)) < 1) ;
        return intersection ;
    }

    Scalar Line2Df::distanceTo(const Point2Df& point) {
        return FastMath::sqrt(distanceSquaredTo(point)) ;
    }

    Scalar Line2Df::distanceTo(const Scalar x, const Scalar y) {
        return distanceTo(Point2Df(x, y)) ;
    }

    Scalar Line2Df::distanceSquaredTo(const Point2Df& point) {
        Point2Df relativeLine = m_end - m_start ;
        // Make the point relative to start.
        Point2Df relativePointToStart = point - m_start ;

        Scalar dotProduct = relativePointToStart.dot(relativeLine) ;
        Scalar projectedLengthSquared = dotProduct * dotProduct / relativeLine.dot(relativeLine) ;
        Scalar lengthSquared = relativePointToStart.dot(relativePointToStart) - projectedLengthSquared ;

        if (lengthSquared < 0.f) {
            return 0.f ;
        }
        return lengthSquared ;
    }

    Scalar Line2Df::distanceSquaredTo(const Scalar x, const Scalar y) {
        return distanceSquaredTo(Point2Df(x, y)) ;
    }

    const Rectangle2Df Line2Df::getBounds() const {
        return Rectangle2Df(m_start, m_end) ;
    }

    const Point2Df& Line2Df::getStartPoint() const {
        return m_start ;
    }

    const Point2Df& Line2Df::getEndPoint() const {
        return m_end ;
    }

    Scalar Line2Df::getStartX() const {
        return m_start.getX() ;
    }

    Scalar Line2Df::getStartY() const {
        return m_start.getY() ;
    }

    Scalar Line2Df::getEndX() const {
        return m_end.getX() ;
    }

    Scalar Line2Df::getEndY() const {
        return m_end.getY() ;
    }

    bool Line2Df::isEmpty() const {
        return ((m_start.getX() - m_end.getX() == 0)
                    && (m_start.getY() - m_end.getY() == 0)) ;
    }

    Line2Df& Line2Df::operator=(const Line2Df& other) {
        if (this != &other) {
            m_start = other.m_start ;
            m_end = other.m_end ;
            m_isChanged = true ;
        }

        return *this ;
    }

    bool Line2Df::operator==(const Line2Df& other) const {
        return ((this == &other)
                    || ((m_start == other.m_start) && (m_end == other.m_end))) ;
    }

    bool Line2Df::operator!=(const Line2Df& other) const {
        return !(*this == other) ;
    }

    std::ostream& operator<<(std::ostream& s, const Line2Df& l) {
        s << "Line2Df ("
                         << l.getStartPoint()
                         << " | "
                         << l.getEndPoint()
                         << ")" << std::endl ;
        return s ;
    }
} ;
