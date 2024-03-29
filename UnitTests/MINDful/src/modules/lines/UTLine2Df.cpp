#include <modules/lines/UTLine2Df.hpp>
#include <string>
#include <iostream>
#include <cmath>

using namespace Mind ;

namespace UTMind {
    void UTLine2Df::allocation() {
        Line2Df l1 ;
        check(l1.startX() == 0.f) ;
        check(l1.startY() == 0.f) ;
        check(l1.endX() == 0.f) ;
        check(l1.endY() == 0.f) ;

        Scalar pStartX = 5.75f ;
        Scalar pStartY = 0.574f ;
        Point2Df pStart(pStartX, pStartY) ;

        Scalar pEndX = 54.12f ;
        Scalar pEndY = -452.4f ;
        Point2Df pEnd(pEndX, pEndY) ;

        Line2Df l2(pStart, pEnd) ;
        check(l2.startX() == pStartX) ;
        check(l2.startY() == pStartY) ;
        check(l2.endX() == pEndX) ;
        check(l2.endY() == pEndY) ;
        check(l2 != l1) ;

        Line2Df l3(l2) ;
        check(l3.startX() == l2.startX()) ;
        check(l3.startY() == l2.startY()) ;
        check(l3.endX() == l2.endX()) ;
        check(l3.endY() == l2.endY()) ;
        check(l3 == l2) ;
    }

    void UTLine2Df::utilities() {
        // Line 1
        Scalar p1StartX = 9.785f ;
        Scalar p1StartY = 15.41f ;
        Point2Df p1Start(p1StartX, p1StartY) ;

        Scalar p1EndX = -458.04f ;
        Scalar p1EndY = 15.112f ;
        Point2Df p1End(p1EndX, p1EndY) ;

        Line2Df l1(p1Start, p1End) ;

        // Line 2
        Scalar p2StartX = -0.024f ;
        Scalar p2StartY = -87.254f ;
        Point2Df p2Start(p2StartX, p2StartY) ;

        Scalar p2EndX = 78.1f ;
        Scalar p2EndY = -0.145f ;
        Point2Df p2End(p2EndX, p2EndY) ;

        Line2Df l2(p2Start, p2End) ;

        // Line 3
        Scalar p3EndX = -97.1f ;
        Scalar p3EndY = 80.f ;
        Point2Df p3End(p3EndX, p3EndY) ;

        Line2Df l3(p3End, p1Start) ;

        // Line 4
        Line2Df l4(p1End, p1Start) ;

        // Line 5
        Line2Df l5(l1) ;


        // Lengths
        double expectedL1SquaredLength = 218860.319429 ;
        double computedL1SquaredLength = pow(p1EndX - p1StartX, 2) + pow(p1EndY - p1StartY, 2) ;
        check(compare(expectedL1SquaredLength, expectedL1SquaredLength)) ;
        double expectedL1Length = 467.82509491154918163612 ;
        double computedL1Length = sqrt(computedL1SquaredLength) ;
        check(compare(expectedL1Length, computedL1Length)) ;

        check(compare(l1.length(), computedL1Length)) ;
        check(compare(l1.lengthSquared(), computedL1SquaredLength)) ;

        // Contiguous lines
        check(!l1.isContiguousTo(l2)) ;
        check(l1.isContiguousTo(l3)) ;
        check(l1.isContiguousTo(l4)) ;
        check(!l1.isContiguousTo(l5)) ;

        // Relative CCW
        check(Line2Df::CCW(l1, Point2Df(0.f, 500.f)) == 1) ;
        check(Line2Df::CCW(l1, Point2Df(0.f, 0.f)) == -1) ;

        // Relative line to plan origin
        Line2Df relativeL1 = Line2Df::relative(l1) ;
        check(relativeL1.startX() == 0.f) ;
        check(relativeL1.startY() == 0.f) ;
        check(relativeL1.endX() == (p1EndX - p1StartX)) ;
        check(relativeL1.endY() == (p1EndY - p1StartY)) ;
    }

    void UTLine2Df::intersections() {
        // Line 1 (horizontal)
        Scalar p1StartX = -50.105f ;
        Scalar p1StartY = 10.f ;
        Point2Df p1Start(p1StartX, p1StartY) ;

        Scalar p1EndX = 480.12f ;
        Scalar p1EndY = 10.f ;
        Point2Df p1End(p1EndX, p1EndY) ;

        Line2Df l1(p1Start, p1End) ;

        // Line 2 (vertical)
        Scalar p2StartX = 2.3f ;
        Scalar p2StartY = -945.154f ;
        Point2Df p2Start(p2StartX, p2StartY) ;

        Scalar p2EndX = 2.3f ;
        Scalar p2EndY = 210.98785f ;
        Point2Df p2End(p2EndX, p2EndY) ;

        Line2Df l2(p2Start, p2End) ;

        // Line 3 (to up right)
        Scalar p3StartX = -32.321f ;
        Scalar p3StartY = -5.154f ;
        Point2Df p3Start(p3StartX, p3StartY) ;

        Scalar p3EndX = 95.21f ;
        Scalar p3EndY = 15.35f ;
        Point2Df p3End(p3EndX, p3EndY) ;

        Line2Df l3(p3Start, p3End) ;

        // Line 4 (to down right)
        Scalar p4StartX = -164.105f ;
        Scalar p4StartY = 485.152f ;
        Point2Df p4Start(p4StartX, p4StartY) ;

        Scalar p4EndX = 158.458f ;
        Scalar p4EndY = -156.11f ;
        Point2Df p4End(p4EndX, p4EndY) ;

        Line2Df l4(p4Start, p4End) ;

        // Line 5 (little)
        Scalar p5StartX = 65.45f ;
        Scalar p5StartY = 23.458f ;
        Point2Df p5Start(p5StartX, p5StartY) ;

        Scalar p5EndX = 66.12f ;
        Scalar p5EndY = 22.3451f ;
        Point2Df p5End(p5EndX, p5EndY) ;

        Line2Df l5(p5Start, p5End) ;

        // Line 6 (as Line 1)
        Line2Df l6(l1) ;


        check(l1.intersects(l2)) ;
        check(l1.intersects(l3)) ;
        check(l1.intersects(l4)) ;
        check(not l1.intersects(l5)) ;
        check(l1.intersects(l6)) ;

        check(l2.intersects(l1)) ;
        check(l2.intersects(l2)) ;
        check(l2.intersects(l3)) ;
        check(l2.intersects(l4)) ;
        check(not l2.intersects(l5)) ;
        check(l2.intersects(l6)) ;

        check(l3.intersects(l4)) ;
        check(not l3.intersects(l5)) ;
        check(l3.intersects(l6)) ;
    }

    void UTLine2Df::distance() {
        // Line 1
        Scalar p1StartX = -32.5f ;
        Scalar p1StartY = 25.f ;
        Point2Df p1Start(p1StartX, p1StartY) ;

        Scalar p1EndX = 8.f ;
        Scalar p1EndY = 28.5f ;
        Point2Df p1End(p1EndX, p1EndY) ;

        Line2Df l1(p1Start, p1End) ;


        // Distance to Point A
        Point2Df pointA(4.f, -9.f) ;
        float computedDistanceA = l1.distanceTo(pointA) ;
        float expectedDistanceA = 37.016353607178f ;
        check(compare(computedDistanceA, expectedDistanceA)) ;

        Point2Df pointB(3.f, 5.f) ;
        float computedDistanceB = l1.distanceTo(pointB) ;
        float expectedDistanceB = 22.982242584229f ;
        check(compare(computedDistanceB, expectedDistanceB)) ;
    }
}
