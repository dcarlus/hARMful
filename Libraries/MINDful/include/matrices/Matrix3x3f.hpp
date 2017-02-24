#ifndef __MIND__MATRIX_3X3F__
#define __MIND__MATRIX_3X3F__

#include <matrices/SquareMatrixf.hpp>

namespace Mind {
    /**
     * 3x3 square matrix.
     */
    class Matrix3x3f final : public SquareMatrixf {
        public:
            /**
             * Create a square matrix of size equal to 3.
             * @param   value   Value of the matrix when created or cleared.
             *                  The default value is zero.
             */
            Matrix3x3f(const Scalar& value = 0.f) ;

            /**
             * Copy a Matrix3x3f.
             */
            Matrix3x3f(const Matrix3x3f& mat) ;

            /**
             * Destruction of the matrix.
             */
            virtual ~Matrix3x3f() ;

            /**
             * Multiplay the current Matrix3x3 by another one.
             * The result is set in the current Matrix3x3.
             * @param   other   The other Matrix3x3 used in the product.
             */
            void multiply(const Matrix3x3f& other) ;

            /**
             * Set the values of a column from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(const size_t& column, const Point2Df& values) final ;

            /**
             * Set the values of a column from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(const size_t& column, const Point3Df& values) final ;

            /**
             * Set the values of a row from a Point2D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(const size_t& row, const Point2Df& values) final ;

            /**
             * Set the values of a row from a Point3D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(const size_t& row, const Point3Df& values) final ;

            /**
             * Multiply the current matrix by a scalar value.
             * The result is put into the current matrix.
             * @param   scalar  The scalar value to multiply each component of
             *                  the matrix with.
             * @return  The result of the multiplication.
             */
            Matrix3x3f& operator*=(const Scalar& scalar) ;

            /**
             * Multiply the current matrix by a scalar value.
             * The result is put into a new matrix.
             * @param   mat     The matrix to multiply.
             * @param   scalar  The scalar value to multiply each component of
             *                  the matrix with.
             * @return  The result of the multiplication.
             */
            Matrix3x3f operator*(const Scalar& scalar) ;

            /**
             * Multiply the current matrix by another matrix.
             * The result is put into the current matrix.
             * @param   other   The other matrix to multiply with the current
             *                  one.
             * @return  The result of the multiplication.
             */
            Matrix3x3f& operator*=(Matrix3x3f& other) ;

            /**
             * Multiply the current matrix by another value.
             * The result is put into a new matrix.
             * @param   mat     The matrix to multiply.
             * @param   other   The other matrix to multiply with the current
             *                  one.
             * @return  The result of the multiplication.
             */
            Matrix3x3f operator*(Matrix3x3f& other) ;

            /**
             * Addition of the current matrix with another one.
             * The result is put into the current matrix.
             * @param   other   The other matrix to add to the current one.
             * @return  The result of the addition.
             */
            Matrix3x3f& operator+=(Matrix3x3f& other) ;

            /**
             * Addition of the current matrix with another one.
             * The result is put into a new matrix.
             * @param   mat     The matrix to add.
             * @param   other   The other matrix to add to the current one.
             * @return  The result of the addition.
             */
            Matrix3x3f operator+(Matrix3x3f& other) ;

           /**
            * Assignment operator to copy a Matrix3x3.
            * @return  The current Matrix3x3 with the copied values.
            */
            Matrix3x3f& operator=(const Matrix3x3f& other) ;
    } ;
} ;

#endif
