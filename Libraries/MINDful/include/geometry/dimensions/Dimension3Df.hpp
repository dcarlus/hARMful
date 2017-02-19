#ifndef __MIND__GEOMETRY_DIMENSION3DF__
#define __MIND__GEOMETRY_DIMENSION3DF__

#include <iostream>

#include <MINDTypes.hpp>
#include <geometry/points/Point3Df.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>

namespace Mind {
    class Dimension2Df ;
    class Point3Df ;

    /**
     * A Dimension is used to get the size of an element, and so get the area of
     * the element as a rectangle bounding shape.
     */
    class Dimension3Df final {
        private:
            /** Width of the Dimension2Df. */
            Scalar m_width ;

            /** Height of the Dimension2Df. */
            Scalar m_height ;

            /** Depth of the Dimension2Df. */
            Scalar m_depth ;


        public:
            /** Create a Dimension of zero by zero. */
            Dimension3Df() ;

            /**
             * Copy a Dimension object.
             * @param   copied  The Dimension to copy.
             */
            Dimension3Df(const Dimension3Df& copied) ;

            /**
             * Create a Dimension with the given sizes.
             * @param   width   Width to set the size of the element.
             * @param   height  Height to set the size of the element.
             * @param   depth   Depth to set the size of the element.
             */
            Dimension3Df(const Scalar& width, const Scalar& height, const Scalar& depth) ;

            /** Destroy the Dimension. */
            virtual ~Dimension3Df() ;


            /** Set the Dimension as absolute values. */
            void absolute() ;

            /**
             * Get the width of the dimension.
             * @return  The width.
             */
            Scalar getWidth() const ;

            /**
             * Get the height of the dimension.
             * @return  The height.
             */
            Scalar getHeight() const ;

            /**
             * Get the depth of the dimension.
             * @return  The depth.
             */
            Scalar getDepth() const ;

            /**
             * Set the width of the dimension.
             * @param   width   Width of the dimension.
             */
            void setWidth(const Scalar& width) ;

            /**
             * Set the height of the dimension.
             * @param   height  Height of the dimension.
             */
            void setHeight(const Scalar& height) ;

            /**
             * Set the depth of the dimension.
             * @param   depth   Depth of the dimension.
             */
            void setDepth(const Scalar& depth) ;

            /**
             * Set the depth of the dimension.
             * @param   width   Width of the dimension.
             * @param   height  Height of the dimension.
             * @param   depth   Depth of the dimension.
             */
            void set(const Scalar& width, const Scalar& height, const Scalar& depth) ;

            /** Conversion from Dimension3D to Point3D. */
            operator Point3Df() ;

            /** Conversion from Dimension3D to Dimension2D. */
            operator Dimension2Df() ;

            /**
             * Add a Dimension and affect the result.
             * @param   other   The other Dimension to add.
             * @return  The sum of the two Dimensions.
             */
            Dimension3Df& operator+=(Dimension3Df& other) ;

            /**
             * Substract a Dimension and affect the result.
             * @param   other   The other Dimension to substract.
             * @return  The substract of the two Dimensions.
             */
            Dimension3Df& operator-=(Dimension3Df& other) ;

            /**
             * Multiply a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to multiply the Dimension coordinates by.
             * @return  The result of the multiplication.
             */
            Dimension3Df& operator*=(const Scalar& coeff) ;

            /**
             * Divide a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to divide the Dimension coordinates by.
             * @return  The result of the division.
             */
            Dimension3Df& operator/=(const Scalar& coeff) ;

            /**
             * Assignment operator to copy a Dimension.
             * @return  The current Dimension with the copied values.
             */
            Dimension3Df& operator=(const Dimension3Df& other) ;

            /**
             * Test if two Dimension have the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have the same size, FALSE else.
             */
            bool operator==(const Dimension3Df& other) const ;

            /**
             * Test if two Dimension have not the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have two different size, FALSE else.
             */
            bool operator!=(const Dimension3Df& other) const ;

            /**
             * Add a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Point at (a.w + b.w, a.h + b.h).
             */
            friend Dimension3Df operator+(const Dimension3Df& a, const Dimension3Df& b) ;

            /**
             * Substract a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Point at (a.w - b.w, a.h - b.h).
             */
            friend Dimension3Df operator-(const Dimension3Df& a, const Dimension3Df& b) ;

            /**
             * Multiply a Dimension by a scalar value (scale).
             * @param   p       Dimension to be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (d.w * coeff, d.h * coeff).
             */
            friend Dimension3Df operator*(const Dimension3Df& d, const Scalar& coeff) ;

            /**
             * Divide a Dimension by a scalar value (scale).
             * @param   a       Dimension to be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (d.w / coeff, d.h / coeff).
             */
            friend Dimension3Df operator/(const Dimension3Df& d, const Scalar& coeff) ;

            /**
             * Echo the Dimension size on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   p   The Dimension to print.
             * @return  The stream with the printed Dimension size.
             */
            friend std::ostream& operator<<(std::ostream& s, const Dimension3Df& p) ;
    } ;
} ;

#endif
