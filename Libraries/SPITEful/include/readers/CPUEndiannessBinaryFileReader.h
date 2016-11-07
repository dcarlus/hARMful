#ifndef __SPITE_CPU_ENDIANNESS_BINARY_FILE_READER__
#define __SPITE_CPU_ENDIANNESS_BINARY_FILE_READER__


#include <readers/BinaryFileReader.h>


namespace Spite {

    /**
     * @brief   A CPUEndiannessBinaryFileReader can read data from binary files
     *          written using the same endianness than the processor.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/23/2015
     */
    class CPUEndiannessBinaryFileReader : public BinaryFileReader {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Creation of a CPUEndiannessBinaryFileReader. */
            CPUEndiannessBinaryFileReader() ;

            /** @brief  Destruction of a CPUEndiannessBinaryFileReader. */
            ~CPUEndiannessBinaryFileReader() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Read a 8-bit integer value.
             * @return  The read value.
             */
            int8_t readChar() ;

            /**
             * @brief   Read a 16-bit integer value.
             * @return  The read value.
             */
            int16_t readShort() ;

            /**
             * @brief   Read a 32-bit integer value.
             * @return  The read value.
             */
            int32_t readInt32() ;

            /**
             * @brief   Read a 64-bit integer value.
             * @return  The read value.
             */
            int64_t readInt64() ;

            /**
             * @brief   Read a 32-bit float value.
             * @return  The read value.
             */
            float readFloat() ;

            /**
             * @brief   Read a 64-bit float value.
             * @return  The read value.
             */
            double readDouble() ;

            /**
             * @brief   Read a string byte by byte.
             * @param   string  Buffer to store the content of the string.
             * @param   length  Length of the string in byte.
             * @warning No null character inserted at the end of the string.
             */
            void readString(char string[], const unsigned int length) ;

            /**
             * @brief   Read a string byte by byte.
             * @param   buffer  Buffer to store the characters of the string.
             * @param   length  Length of the string in byte.
             */
            void readString(std::string& buffer, const unsigned int length) ;
    } ;

} ;


#endif
