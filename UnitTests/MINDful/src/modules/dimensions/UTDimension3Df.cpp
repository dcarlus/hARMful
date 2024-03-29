#include <modules/dimensions/UTDimension3Df.hpp>
#include <geometry/dimensions/Dimension3Df.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <geometry/points/Point3Df.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    void UTDimension3Df::allocation() {
        Dimension3Df dim3d1 ;
        check(dim3d1.width() == 0.f) ;
        check(dim3d1.height() == 0.f) ;
        check(dim3d1.depth() == 0.f) ;

        Dimension3Df dim3d2(5.2f, 3.9f, 9.5f) ;
        check(dim3d2.width() == 5.2f) ;
        check(dim3d2.height() == 3.9f) ;
        check(dim3d2.depth() == 9.5f) ;

        Dimension3Df dim3d3(dim3d2) ;
        check(dim3d3.width() == 5.2f) ;
        check(dim3d3.height() == 3.9f) ;
        check(dim3d3.depth() == 9.5f) ;
    }

    void UTDimension3Df::scalarOperations() {
        const float Width = 6.8975f ;
        const float Height = 2.47441f ;
        const float Depth = 452.4459f ;
        const float Divisor = 3.77487f ;
        const float Factor = 5.97f ;
        Dimension3Df dim3d1(Width, Height, Depth) ;

        /* Divisions */
        Dimension3Df dim3d2 = dim3d1 / Divisor ;
        check(compare(dim3d2.width(), Width / Divisor)) ;
        check(compare(dim3d2.height(), Height / Divisor)) ;
        check(compare(dim3d2.depth(), Depth / Divisor)) ;

        dim3d2 /= Divisor ;
        check(compare(dim3d2.width(), Width / Divisor / Divisor)) ;
        check(compare(dim3d2.height(), Height / Divisor / Divisor)) ;
        check(compare(dim3d2.depth(), Depth / Divisor / Divisor)) ;

        /* Products */
        Dimension3Df dim3d3 = dim3d1 * Factor ;
        check(compare(dim3d3.width(), Width * Factor)) ;
        check(compare(dim3d3.height(), Height * Factor)) ;
        check(compare(dim3d3.depth(), Depth * Factor)) ;

        dim3d3 *= Factor ;
        check(compare(dim3d3.width(), Width * Factor * Factor)) ;
        check(compare(dim3d3.height(), Height * Factor * Factor)) ;
        check(compare(dim3d3.depth(), Depth * Factor * Factor)) ;
    }

    void UTDimension3Df::dimensionsOperations() {
        const float Width1 = 5478.45f ;
        const float Height1 = 4855.48114748786f ;
        const float Depth1 = 75.4f ;
        Dimension3Df dim3d1(Width1, Height1, Depth1) ;

        const float Width2 = 48781.4454544f ;
        const float Height2 = 45778.145f ;
        const float Depth2 = 9765.214f ;
        Dimension3Df dim3d2(Width2, Height2, Depth2) ;

        const float Width3 = 0.34545447995f ;
        const float Height3 = 0.3875487f ;
        const float Depth3 = 0.0471f ;
        Dimension3Df dim3d3(Width3, Height3, Depth3) ;

        /* Addition */
        Dimension3Df dim3d1PLUSd2 = dim3d1 + dim3d2 ;
        check(compare(dim3d1PLUSd2.width(), Width1 + Width2)) ;
        check(compare(dim3d1PLUSd2.height(), Height1 + Height2)) ;
        check(compare(dim3d1PLUSd2.depth(), Depth1 + Depth2)) ;

        Dimension3Df dim3d1PLUSd3 = dim3d1 + dim3d3 ;
        check(compare(dim3d1PLUSd3.width(), Width1 + Width3)) ;
        check(compare(dim3d1PLUSd3.height(), Height1 + Height3)) ;
        check(compare(dim3d1PLUSd3.depth(), Depth1 + Depth3)) ;

        Dimension3Df dim3d2PLUSd3 = dim3d2 + dim3d3 ;
        check(compare(dim3d2PLUSd3.width(), Width2 + Width3)) ;
        check(compare(dim3d2PLUSd3.height(), Height2 + Height3)) ;
        check(compare(dim3d2PLUSd3.depth(), Depth2 + Depth3)) ;

        dim3d2PLUSd3 += dim3d1 ;
        check(compare(dim3d2PLUSd3.width(), Width2 + Width3 + Width1)) ;
        check(compare(dim3d2PLUSd3.height(), Height2 + Height3 + Height1)) ;
        check(compare(dim3d2PLUSd3.depth(), Depth2 + Depth3 + Depth1)) ;


        /* Difference */
        Dimension3Df dim3d1MINUSd2 = dim3d1 - dim3d2 ;
        check(compare(dim3d1MINUSd2.width(), Width1 - Width2)) ;
        check(compare(dim3d1MINUSd2.height(), Height1 - Height2)) ;
        check(compare(dim3d1MINUSd2.depth(), Depth1 - Depth2)) ;

        Dimension3Df dim3d1MINUSd3 = dim3d1 - dim3d3 ;
        check(compare(dim3d1MINUSd3.width(), Width1 - Width3)) ;
        check(compare(dim3d1MINUSd3.height(), Height1 - Height3)) ;
        check(compare(dim3d1MINUSd3.depth(), Depth1 - Depth3)) ;

        Dimension3Df dim3d2MINUSd3 = dim3d2 - dim3d3 ;
        check(compare(dim3d2MINUSd3.width(), Width2 - Width3)) ;
        check(compare(dim3d2MINUSd3.height(), Height2 - Height3)) ;
        check(compare(dim3d2MINUSd3.depth(), Depth2 - Depth3)) ;

        dim3d2MINUSd3 -= dim3d1 ;
        check(compare(dim3d2MINUSd3.width(), Width2 - Width3 - Width1)) ;
        check(compare(dim3d2MINUSd3.height(), Height2 - Height3 - Height1)) ;
        check(compare(dim3d2MINUSd3.depth(), Depth2 - Depth3 - Depth1)) ;
    }

    void UTDimension3Df::equality() {
        const float Width1 = 4575.975f ;
        const float Height1 = 751.445f ;
        const float Depth1 = 975.1746f ;
        Dimension3Df dim3d1 = Dimension3Df(Width1, Height1, Depth1) ;
        Dimension3Df dim3d2 = Dimension3Df(Width1, Height1, Depth1) ;
        Dimension3Df dim3d3 = Dimension3Df(dim3d1) ;
        Dimension3Df dim3d4 = Dimension3Df(dim3d2) ;

        check(dim3d1 == dim3d1) ;
        check(dim3d1 == dim3d2) ;
        check(dim3d2 == dim3d1) ;
        check(dim3d1 == dim3d3) ;
        check(dim3d3 == dim3d1) ;
        check(dim3d1 == dim3d4) ;
        check(dim3d4 == dim3d1) ;

        check(dim3d2 == dim3d2) ;
        check(dim3d2 == dim3d3) ;
        check(dim3d3 == dim3d2) ;
        check(dim3d2 == dim3d4) ;
        check(dim3d4 == dim3d2) ;

        check(dim3d3 == dim3d3) ;
        check(dim3d3 == dim3d4) ;
        check(dim3d4 == dim3d3) ;
    }

    void UTDimension3Df::inequality() {
        const float Width1 = 4575.975f ;
        const float Height1 = 751.445f ;
        const float Depth1 = 975.1746f ;
        Dimension3Df dim3d1 = Dimension3Df(Width1, Height1, Depth1) ;

        const float Width2 = 4575.975f ;
        const float Height2 = 777.445f ;
        const float Depth2 = 975.1746f ;
        Dimension3Df dim3d2 = Dimension3Df(Width2, Height2, Depth2) ;

        const float Width3 = 455.975f ;
        const float Height3 = 777.445f ;
        const float Depth3 = 975.1746f ;
        Dimension3Df dim3d3 = Dimension3Df(Width3, Height3, Depth3) ;

        const float Width4 = 4575.975f ;
        const float Height4 = 751.445f ;
        const float Depth4 = 975.174f ;
        Dimension3Df dim3d4 = Dimension3Df(Width4, Height4, Depth4) ;

        const float Width5 = 987.f ;
        const float Height5 = 17.5f ;
        const float Depth5 = 975.1746f ;
        Dimension3Df dim3d5 = Dimension3Df(Width5, Height5, Depth5) ;

        check(dim3d1 != dim3d2) ;
        check(dim3d2 != dim3d1) ;
        check(dim3d1 != dim3d3) ;
        check(dim3d3 != dim3d1) ;
        check(dim3d1 != dim3d4) ;
        check(dim3d4 != dim3d1) ;
        check(dim3d1 != dim3d5) ;
        check(dim3d5 != dim3d1) ;

        check(dim3d2 != dim3d3) ;
        check(dim3d3 != dim3d2) ;
        check(dim3d2 != dim3d4) ;
        check(dim3d4 != dim3d2) ;
        check(dim3d5 != dim3d2) ;
        check(dim3d2 != dim3d5) ;

        check(dim3d3 != dim3d4) ;
        check(dim3d4 != dim3d3) ;
        check(dim3d5 != dim3d3) ;
        check(dim3d3 != dim3d5) ;

        check(dim3d4 != dim3d5) ;
        check(dim3d5 != dim3d4) ;
    }

    void UTDimension3Df::setter() {
        Dimension3Df dim3d ;

        float width = 7.874f ;
        float height = 14.132f ;
        float depth = 3.14f ;
        dim3d.set(width, height, depth) ;
        check(dim3d.width() == width) ;
        check(dim3d.height() == height) ;
        check(dim3d.depth() == depth) ;

        width = 9.465f ;
        dim3d.setWidth(width) ;
        check(dim3d.width() == width) ;
        check(dim3d.height() == height) ;
        check(dim3d.depth() == depth) ;

        height = 87.517f ;
        dim3d.setHeight(height) ;
        check(dim3d.width() == width) ;
        check(dim3d.height() == height) ;
        check(dim3d.depth() == depth) ;

        depth = 2.698f ;
        dim3d.setDepth(depth) ;
        check(dim3d.width() == width) ;
        check(dim3d.height() == height) ;
        check(dim3d.depth() == depth) ;
    }

    void UTDimension3Df::cast() {
        // To Dimension2Df.
        {
            const float Width = 897.45f ;
            const float Height = 5452.f ;
            const float Depth = 487.4f ;
            Dimension3Df dim3d(Width, Height, Depth) ;
            Dimension2Df dim2d = (Dimension2Df) dim3d ;
            check(dim2d.width() == dim3d.width()) ;
            check(dim2d.height() == dim3d.height()) ;
        }
        // To Point3Df.
        {
            const float Width = 7.45f ;
            const float Height = 469.198f ;
            const float Depth = 7487.8785f ;
            Dimension3Df dim3d(Width, Height, Depth) ;
            Point3Df p3d = (Point3Df) dim3d ;
            check(p3d.get(Point3Df::Axis::X) == dim3d.width()) ;
            check(p3d.get(Point3Df::Axis::Y) == dim3d.height()) ;
            check(p3d.get(Point3Df::Axis::Z) == dim3d.depth()) ;
        }
    }
}
