#ifndef __MIND__SQUARE_MATRIXF__
#define __MIND__SQUARE_MATRIXF__

#include <cstddef>
#include <iostream>
#include <iomanip>

#include <simd/SIMDVector.hpp>
#include <geometry/points/Point2Df.hpp>
#include <geometry/points/Point3Df.hpp>

namespace Mind {
    // Pre-declare operator overloadings
    class SquareMatrixf ;
    std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) ;

    /**
     * Square matrix base class with a fixed size.
     * The maximal size of the matrix is four elements on row and columns.
     */
    class SquareMatrixf {
        protected:
            /**
             * Maximal amount of data in a direction.
             */
            static const size_t MaximalDataSize ;

            /**
             * Size of the SquareMatrix (one side).
             */
            size_t m_size ;

            /**
             * Default value of the cleared SquareMatrix.
             */
            Scalar m_defaultValue ;

            #ifdef USE_NO_SIMD
                /**
                 * SquareMatrix content values.
                 */
                std::array<std::array<float, 4>, 4> m_data ;
            #else
                /**
                 * SquareMatrix content values.
                 */
                SIMD::Vector4f m_data[4] ;
            #endif

        public:
            /**
             * Create a SquareMatrix with its size.
             * @param	size 	Size of the SquareMatrix. This will produce a
             *					"size x size" matrix.
             * @param	value 	Initial value in the SquareMatrix.
             */
            SquareMatrixf(const size_t size, const Scalar value = 0) ;

            /**
             * Copy a SquareMatrixf.
             */
            SquareMatrixf(const SquareMatrixf& mat) = default ;

            /**
             * Move a SquareMatrixf.
             */
            SquareMatrixf(SquareMatrixf&& mat) = default ;

            /**
             * Destruction of the SquareMatrix.
             */
            virtual ~SquareMatrixf() = default ;

            /**
             * Fill the SquareMatrix with its default value.
             */
            void clear() ;

            /**
             * Fill the SquareMatrix with zero values and put one on
             * matrix diagonal (left to right, top to bottom).
             */
            void identity() ;

            /**
             * Compute the trace of the SquareMatrix, that is to say add all its
             * diagonal components.
             * @return Value of the trace of the SquareMatrix.
             */
            Scalar trace() const ;

            /**
             * Set the values of a column from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(
                const size_t column,
                const Point2Df& values
            ) = 0 ;

            /**
             * Set the values of a column from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(
                const size_t column,
                const Point3Df& values
            ) = 0 ;

            /**
             * Set the values of a row from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(
                const size_t row,
                const Point2Df& values
            ) = 0 ;

            /**
             * Set the values of a row from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(
                const size_t row,
                const Point3Df& values
            ) = 0 ;

            /**
             * Get the element a the specified position.
             * @param   row     Index of the wanted row.
             * @param   col     Index of the wanted column.
             * @return	Reference to the element at the wanted column and row
             *			indices.
             */
            Scalar at(
                const unsigned int row,
                const unsigned int col
            ) const ;

            /**
             * Get the element a the specified position.
             * @param   row     Index of the wanted row.
             * @param   col     Index of the wanted column.
             * @return	Reference to the element at the wanted column and row
             *			indices.
             */
            Scalar& at(
                const unsigned int row,
                const unsigned int col
            ) ;

            /**
             * Set the element a the specified position.
             * @param   col     Index of the wanted column.
             * @param   row     Index of the wanted row.
             * @param   value   Value to set at the given position.
             */
            void at(
                const unsigned int row,
                const unsigned int col,
                const Scalar value
            ) ;

            #ifdef USE_NO_SIMD
                /**
                 * Set or get the element a the specified position.
                 * @param   index   Index of the wanted row.
                 */
                std::array<float, 4>& operator[](int index) ;
            #else
                /**
                 * Set or get the element a the specified position.
                 * @param   index   Index of the wanted row.
                 */
                SIMD::Vector4f& operator[](int index) ;
            #endif

            /**
             * Get the size of the SquareMatrix.
             * @return	Size of the SquareMatrix (amount of both columns and
             *			rows).
             */
            unsigned int size() const ;

            /**
             * Assignment operator to copy a SquareMatrixf.
             * @return  The current SquareMatrixf with the copied values.
             */
            SquareMatrixf& operator=(const SquareMatrixf& other) = default ;

            /**
             * Assignment operator to move a SquareMatrixf.
             * @return  The current SquareMatrixf with the moved values.
             */
            SquareMatrixf& operator=(SquareMatrixf&& other) = default ;

            /**
            * Echo the SquareMatrix values on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   p   The SquareMatrix to print.
            * @return  The stream with the printed Point coordinates.
            */
            friend std::ostream& operator<<(
                std::ostream& s,
                const SquareMatrixf& p
            ) ;

        protected:
            /**
             * Get the total size of the SquareMatrix.
             * @return  Total amount of elements in the SquareMatrix.
             */
            unsigned int totalSize() const ;

            /**
             * Clear the matrix with the given value.
             * @param   value   Value to fill the matrix with.
             */
            void clearWith(const Scalar value) ;

            /**
             * Get the inner data of the SquareMatrix.
             * @param   output  Storage of the inner data.
             * @warning Output must have the right size as a single array.
             */
            void getData(Scalar* output) ;
    } ;

    inline void SquareMatrixf::clear() {
        clearWith(m_defaultValue) ;
    }

    inline Scalar SquareMatrixf::at(
        const unsigned int row,
        const unsigned int col
    ) const {
        return m_data[row][col] ;
    }

    inline Scalar& SquareMatrixf::at(
        const unsigned int row,
        const unsigned int col
    ) {
        return m_data[row][col] ;
    }

    inline void SquareMatrixf::at(
        const unsigned int row,
        const unsigned int col,
        const Scalar value
    ) {
        m_data[row][col] = value ;
    }

    #ifdef USE_NO_SIMD
        inline std::array<float, 4>& SquareMatrixf::operator[](int index) {
            return m_data[index] ;
        }
    #else
        inline SIMD::Vector4f& SquareMatrixf::operator[](int index) {
            return m_data[index] ;
        }
    #endif
} ;

#endif
