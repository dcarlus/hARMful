#ifndef __SPITE__REVERSED_CPU_ENDIANNESS_BINARY_FILE_WRITER__
#define __SPITE__REVERSED_CPU_ENDIANNESS_BINARY_FILE_WRITER__

#include <utils/Platform.hpp>
#include <writers/BinaryFileWriter.hpp>

namespace Spite {

    /**
     * A ReversedCPUEndiannessBinaryFileWriter can write data in binary files
     * using the other known endianness from the processor.
     * For example, use a ReversedCPUEndiannessBinaryFileWriter to write a Big
     * Endian file on a Little Endian CPU.
     */
    class ReversedCPUEndiannessBinaryFileWriter : public BinaryFileWriter {
        public:
            /**
             * Write a 8-bit integer value.
             * @param   value   The value to write.
             */
            exported void writeChar(int8_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 16-bit integer value.
             * @param   value   The value to write.
             */
            exported void writeShort(int16_t value) {
                value = ((value << 8) | (value >> 8)) ;
                m_stream -> read((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 32-bit integer value.
             * @param   value   The value to write.
             */
            exported void writeInt32(int32_t value) {
                value = swapInt32(value) ;
                m_stream -> read((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 64-bit integer value.
             * @param   value   The value to write.
             */
            exported void writeInt64(int64_t value) {
                value = swapInt64(value) ;
                m_stream -> read((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 32-bit float value.
             * @param   value   The value to write.
             */
            exported void writeFloat(float value) {
                // Union used to swap the float value bytes.
                union SwapEndianness {
                    float fValue ;
                    int32_t iValue ;
                } swapper ;

                swapper.fValue = value ;
                // Swap its bytes.
                swapper.iValue = swapInt32(swapper.iValue) ;

                m_stream -> read((char*) &swapper.iValue, sizeof(swapper.iValue)) ;
            }

            /**
             * Write a 64-bit float value.
             * @param   value   The value to write.
             */
            exported void writeDouble(double value) {
                // Union used to swap the float value bytes.
                union SwapEndianness {
                    double dValue ;
                    int64_t lValue ;
                } swapper ;

                swapper.dValue = value ;
                // Swap its bytes.
                swapper.lValue = swapInt64(swapper.lValue) ;

                m_stream -> read((char*) &swapper.lValue, sizeof(swapper.lValue)) ;
            }

            /**
             * Write a string byte by byte.
             * @param   text    Text to write in the File.
             * @param   length  Length of the string in byte.
             */
            exported void writeString(
                const char* text,
                const unsigned int length
            ) {
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> write((char*) &text[index], sizeof(char)) ;
                }
            }

            /**
             * Write a string byte by byte.
             * @param   text    Text to write in the File.
             */
            exported void writeString(const std::string& text) {
                size_t length = text.size() ;
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> write((char*) &text[index], sizeof(char)) ;
                }
            }


        private:
            /**
             * Swap the bytes of a 32-bit integer value.
             * @param   value   The value to swap.
             * @return  The swapped value.
             */
            int32_t swapInt32(int32_t value) {
                // Switch bytes for good endianness:
                // [ 1 | 2 | 3 | 4 ] --> [ 4 | 3 | 2 | 1 ]
                return ((value & 0x000000FF) << 24
                            | (value & 0x0000FF00) << 8
                            | (value & 0x00FF0000) >> 8
                            | (value & 0xFF000000) >> 24) ;
            }

            /**
             * Swap the bytes of a 64-bit integer value.
             * @param   value   The value to swap.
             * @return  The swapped value.
             */
            int64_t swapInt64(int64_t value) {
                // Switch bytes for good endianness
                // [ 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 ] --> [ 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 ]
                return ((value & 0x00000000000000FF) << 56
                            | (value & 0x000000000000FF00) << 40
                            | (value & 0x0000000000FF0000) << 24
                            | (value & 0x00000000FF000000) << 8
                            | (value & 0x000000FF00000000) >> 8
                            | (value & 0x0000FF0000000000) >> 24
                            | (value & 0x00FF000000000000) >> 40
                            | (value & 0xFF00000000000000) >> 56) ;
            }
    } ;
}

#endif
