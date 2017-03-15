#include <modules/quaternions/UTQuaternion.hpp>
#include <geometry/quaternions/Quaternion.hpp>
#include <Math.hpp>
#include <string>
#include <iostream>

#include <utils/Chrono.hpp>

using namespace Mind ;

namespace UTMind {
    UTQuaternion::UTQuaternion() {}

    UTQuaternion::~UTQuaternion() {}

    void UTQuaternion::runTests() {
        allocation() ;
        utilities() ;
        operators() ;
    }

    void UTQuaternion::allocation() {
        // Default.
        {
            Quaternion q1 ;
            Scalar roll, pitch, yaw ;
            q1.to(roll, pitch, yaw) ;
            check(roll == 0.f) ;
            check(pitch == 0.f) ;
            check(yaw == 0.f) ;
        }

        // Values.
        {
            Scalar x = 0.478f ;
            Scalar y = -0.3784f ;
            Scalar z = 0.92f ;
            Scalar w = -0.004f ;
            Quaternion q2(x, y, z, w) ;
            check(q2[Quaternion::Axis::X] == x) ;
            check(q2[Quaternion::Axis::Y] == y) ;
            check(q2[Quaternion::Axis::Z] == z) ;
            check(q2[Quaternion::Axis::W] == w) ;
        }

        // Rotation matrix.
        {
            Matrix3x3f matrix ;
            matrix.at(0,0, +0.8f) ;
            matrix.at(0,1, +0.1f) ;
            matrix.at(0,2, -0.5f) ;
            matrix.at(1,0, +0.7f) ;
            matrix.at(1,1, -1.0f) ;
            matrix.at(1,2, +0.6f) ;
            matrix.at(2,0, +0.0f) ;
            matrix.at(2,1, -0.1f) ;
            matrix.at(2,2, +0.7f) ;

            /*
            Octave result:
            q2 = 0.6124 - 0.2858i - 0.2041j + 0.2449k
            */
            Scalar expectedX = -0.285773803324704 ;
            Scalar expectedY = -0.204124145231932 ;
            Scalar expectedZ =  0.244948974278318 ;
            Scalar expectedW =  0.612372435695794 ;

            Quaternion q3(matrix) ;
            check(compare(q3[Quaternion::Axis::X], expectedX)) ;
            check(compare(q3[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q3[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q3[Quaternion::Axis::W], expectedW)) ;

            Quaternion q4(q3) ;
            check(compare(q4[Quaternion::Axis::X], expectedX)) ;
            check(compare(q4[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q4[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q4[Quaternion::Axis::W], expectedW)) ;
        }

        // Axis and rotation.
        {
            Vector3f axis(0.f, 0.5f, 0.78f) ;
            axis.normalize() ;
            Scalar angle = Math::Pi / 4.f ;

            /*
            Octave result:
            q5 = 0.9239 + 0i + 0.2065j + 0.3222k
            */
            Scalar expectedX =  0.f ;
            Scalar expectedY =  0.206521281112347 ;
            Scalar expectedZ =  0.322173198535262 ;
            Scalar expectedW =  0.923879532511287 ;

            Quaternion q5(axis, angle) ;
            check(compare(q5[Quaternion::Axis::X], expectedX)) ;
            check(compare(q5[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q5[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q5[Quaternion::Axis::W], expectedW)) ;
        }

        // @TODO: Check constructor from 3 axes.
    }

    void UTQuaternion::utilities() {
        // Dot product and norm.
        {
            Quaternion q1(0.24f, 0.9f, -0.47f, 0.17f) ;
            Quaternion q2(-0.21f, 0.78f, 0.01f, 0.98f) ;
            Scalar dot = q1.dot(q2) ;

            Scalar expectedDot = 0.8135f ;
            check(compare(dot, expectedDot)) ;

            Scalar normQ1 = q1.norm() ;
            Scalar expectedNorm = 1.05707142615814f ;
            check(compare(normQ1, expectedNorm)) ;
        }

        // Normalize.
        {
            Quaternion q3(0.2f, 0.9f, 0.4f, 0.5f) ;
            q3.normalize() ;

            /*
            Octave result:
            >> q3n = unit(q3)
            q3n = 0.4454 + 0.1782i + 0.8018j + 0.3563k
            */
            Scalar expectedX = 0.178174161274950f ;
            Scalar expectedY = 0.801783725737273f ;
            Scalar expectedZ = 0.356348322549899f ;
            Scalar expectedW = 0.445435403187374f ;

            check(compare(q3[Quaternion::Axis::X], expectedX)) ;
            check(compare(q3[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q3[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q3[Quaternion::Axis::W], expectedW)) ;
        }

        // Inverse.
        {
            Quaternion q4(0.96f, -0.7f, 0.39f, 0.f) ;
            Quaternion q4inv = q4.inverse() ;

            /*
             Octave result:
             >> q4inv = inv(q4)
             q4inv = 0 - 0.6139i + 0.4477j - 0.2494k
            */
            Scalar expectedX = -0.613928502909765f ;
            Scalar expectedY =  0.447656200038371f ;
            Scalar expectedZ = -0.249408454307092f ;
            Scalar expectedW =  0.f ;

            check(compare(q4inv[Quaternion::Axis::X], expectedX)) ;
            check(compare(q4inv[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q4inv[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q4inv[Quaternion::Axis::W], expectedW)) ;
        }

        // Exponential.
        {
            Quaternion q5(-0.01f, 0.97f, 0.144f, -0.987f) ;
            Quaternion q5exp = q5.exp() ;

            /*
            Octave result:
            >> q5exp = exp(q5)
            q5exp = 0.2074 - 0.003158i + 0.3063j + 0.04547k
            */
            Scalar expectedX = -0.00315762103232588f ;
            Scalar expectedY =  0.306289240135610f ;
            Scalar expectedZ =  0.0454697428654927f ;
            Scalar expectedW =  0.207387502635283f ;

            check(compare(q5exp[Quaternion::Axis::X], expectedX)) ;
            check(compare(q5exp[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q5exp[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q5exp[Quaternion::Axis::W], expectedW)) ;
        }

        // Logarithmus naturalis.
        {
            Quaternion q6(-0.014f, -0.17f, 0.874f, 0.24f) ;
            Quaternion q6ln = q6.ln() ;

            /*
             Octave result:
             >> q6ln = log(q6)
             q6ln = -0.08092 - 0.02056i - 0.2496j + 1.283k
             But, according to Neil Dantam, W is simplified to 0.
             http://www.neil.dantam.name/note/dantam-quaternion.pdf

             The same result on the W component is seen on the Matlab
             documentation:
             for q=[cos(theta),sin(theta)v], with log(q)=[0,thetav].
             https://fr.mathworks.com/help/aerotbx/ug/quatlog.html
             */
             Scalar expectedX = -0.0205566850320550f ;
             Scalar expectedY = -0.249616889674954f ;
             Scalar expectedZ =  1.28332447985829f ;
             Scalar expectedW =  0.f ;

             check(compare(q6ln[Quaternion::Axis::X], expectedX)) ;
             check(compare(q6ln[Quaternion::Axis::Y], expectedY)) ;
             check(compare(q6ln[Quaternion::Axis::Z], expectedZ)) ;
             check(compare(q6ln[Quaternion::Axis::W], expectedW)) ;
        }
    }

    void UTQuaternion::operators() {
        // Product.
        {
            Quaternion q1(-0.47f, 0.1474f, 0.657f, 0.24f) ;
            Quaternion q2(-0.24f, 0.3f, -0.176f, -0.709f) ;
            Quaternion qr = q1 * q2 ;

            /*
            Octave result:
            >> q1 .* q2
            ans = -0.2115 + 0.05259i - 0.2729j - 0.6137k
            */
            Scalar expectedX =  0.0525876f ;
            Scalar expectedY = -0.2729066 ;
            Scalar expectedZ = -0.613677 ;
            Scalar expectedW = -0.211548 ;

            check(compare(qr[Quaternion::Axis::X], expectedX)) ;
            check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
            check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(qr[Quaternion::Axis::W], expectedW)) ;
        }
    }
}
