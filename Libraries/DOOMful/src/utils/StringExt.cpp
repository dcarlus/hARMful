#include <utils/StringExt.hpp>
#include <utils/Random.hpp>
#include <cmath>
#include <cctype>

namespace Doom {
    namespace StringExt {
        void CaseChar(std::string& stringCap, size_t position, CharacterCase charCase) {
            if (position > stringCap.length()) {
                return ;
            }

            char character = stringCap[position] ;
            switch(charCase) {
                case CharacterCase::Upper:
                    if (character >= 'a' && character <= 'z') {
                        stringCap[position] += (int8_t)(CharacterCase::Upper) ;
                    }
                    break ;

                case CharacterCase::Lower:
                    if (character >= 'A' && character <= 'Z') {
                        stringCap[position] += (int8_t)(CharacterCase::Lower) ;
                    }
                    break ;
            }
        }

        void CaseFirst(std::string& stringCap, CharacterCase charCase) {
            CaseChar(stringCap, 0, charCase) ;
        }

        void CaseWords(std::string& stringCap, CharacterCase charCase) {
            size_t characterPosition = 0 ;
            bool insideWord = false ;
            for (char& character : stringCap) {
                bool isWhiteSpace = isspace(character) ;

                if (!insideWord && !isWhiteSpace) {
                    insideWord = true ;
                    CaseChar(stringCap, characterPosition, charCase) ;
                }
                else if (isWhiteSpace) {
                    insideWord = false ;
                }
                characterPosition++ ;
            }
        }

        void TextCase(std::string& stringCap, CharacterCase charCase) {
            size_t characterPosition = 0 ;
            for (char& character : stringCap) {
                CaseChar(stringCap, characterPosition, charCase) ;
                characterPosition++ ;
            }
        }

        /**
         * Trim the beginning of a string.
         * @param   stringToTrim The string to trim.
         */
        static void TrimFront(std::string& stringToTrim) {
            size_t strLength = stringToTrim.length() - 1 ;
            size_t index = 0 ;

            bool continueToTrim = true ;
            while(continueToTrim) {
                bool isSpace = isspace(stringToTrim[index]) ;
                if (isSpace) {
                    // Move the index to remove the character to delete.
                    index = index + 1 ;
                    continueToTrim = (index < strLength) ;
                }
                else {
                    // Stop trimming and substring with the index.
                    continueToTrim = false ;
                    stringToTrim = stringToTrim.substr(index) ;
                }
            }
        }

        /**
         * Trim the ending of a string.
         * @param   stringToTrim The string to trim.
         */
        static void TrimBack(std::string& stringToTrim) {
            size_t strLength = stringToTrim.length() - 1 ;
            size_t index = strLength ;

            bool continueToTrim = true ;
            while(continueToTrim) {
                bool isSpace = isspace(stringToTrim[index]) ;
                if (isSpace) {
                    // Move the index to remove the character to delete.
                    index = index - 1 ;
                    continueToTrim = (index > 0) ;
                }
                else {
                    // Stop trimming and substring with the index.
                    continueToTrim = false ;
                    stringToTrim = stringToTrim.substr(0, index + 1) ;
                }
            }
        }

        void Trim(std::string& stringToTrim) {
            if (stringToTrim.empty()) {
                return ;
            }

            TrimFront(stringToTrim) ;
            TrimBack(stringToTrim) ;
        }

        std::vector<std::string> Split(const std::string& toSplit, const std::string& characters) {
            std::vector<std::string> result ;

            std::size_t previousPosition = 0 ;
            std::size_t foundPosition = toSplit.find_first_of(characters) ;
            while (foundPosition != std::string::npos) {
                std::size_t length = foundPosition - previousPosition ;
                std::string part = toSplit.substr(previousPosition, length) ;
                if (!part.empty()) {
                    result.push_back(part) ;
                }

                previousPosition = foundPosition + 1 ;
                foundPosition = toSplit.find_first_of(characters, previousPosition) ;
            }
            std::string remaining = toSplit.substr(previousPosition) ;
            if (!remaining.empty()) {
                result.push_back(remaining) ;
            }

            return result ;
        }

        std::string ToStringi(int32_t value, unsigned char base) {
            const char ASCIINumberStart = '0' ;
            const char BufferSize = 32 ;
            std::string buffer(BufferSize, '\0') ;

            unsigned short offset = BufferSize - 1 ;
            bool isNegative = value < 0 ;
            while ((value != 0) && (offset > 0)) {
                int32_t tmp = value ;
                value = value / base ;
                buffer[offset] = std::abs(tmp - (value * base)) + ASCIINumberStart ;
                if (buffer[offset] > '9') {
                    // Add difference between 9 and A in the ASCII table.
                    buffer[offset] += 8 ;
                }
                offset-- ;
            }

            if (isNegative) {
                buffer[offset] = '-' ;
            }
            return buffer.substr(offset + 1, BufferSize - offset) ;
        }

        std::string ToStringf(float value, unsigned char precision) {
            int32_t integer = (int32_t) value ;
            float fractional = value - integer ;

            // Convert the integer part.
            std::string representation(ToStringi(integer)) ;

            // Get the fractional part with the wanted precision.
            if (precision == 0) {
                return representation ;
            }

            unsigned int power_fractional = 1 ;
            for (unsigned char power = 0 ; power < precision ; power++) {
                power_fractional *= 10 ;
            }
            long fractional_integer = (fractional * (double) power_fractional) ;
            representation += "." ;
            representation += ToStringi(fractional_integer) ;

            return representation ;
        }

        std::string Random(unsigned int length) {
            const std::string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" ;
            return Random(length, alphanum) ;
        }

        std::string Random(unsigned int length, const std::string& characters) {
            Random::Initialize() ;

            std::string output(length, '\0') ;
            size_t charactersListLength = characters.length() ;
            for (size_t index = 0 ; index < length ; ++index) {
                int characterPosition = Random::GetInteger(0, charactersListLength) ;
                char pickedCharacter = characters[characterPosition] ;
                output[index] = pickedCharacter ;
            }
            return output ;
        }
    }
}
