#ifndef __SPITE__COLOR_FORMAT__
#define __SPITE__COLOR_FORMAT__

#include <string>
#include <vector>

namespace Spite {

    /**
     * Class to contain informations on color format used by pictures.
     */
    class ColorFormat final {
        public:
            /**
             * IDs to identity the supported color formats.
             */
            enum ID {
                RGB = 0,
                BGR,
                RGBA,
                ARGB,
                YUV,
                AmountOfIDs
            } ;

        private:
            /**
             * All the available ColorFormat to describe the organization of
             * data inside the raw images.
             */
            static std::vector<ColorFormat> ColorFormats ;

            /**
             * Name of the ColorFormat.
             */
            std::string m_name ;

            /**
             * Mask of the components.
             */
            std::vector<unsigned int> m_componentMasks ;

            /**
             * Size of each component in bytes.
             */
            unsigned char m_componentSize ;

            /**
             * Total size of each pixel information in bytes.
             */
            unsigned char m_pixelSize ;

            /**
             * Color depth of the ColorFormat.
             */
            unsigned char m_colorDepth ;

            /**
             * To check if a ColorFormat has been initialized.
             */
            bool m_isInitialized = false ;


        public:
            /**
             * Empty constructor, just for optimization.
             */
            ColorFormat() = default ;

            /**
             * Create a new ColorFormat.
             * @param   name                Name of the ColorFormat.
             * @param   components          Components in the ColorFormat.
             * @param   componentSize       Size of each component in bytes.
             */
            ColorFormat(
                const std::string& name,
                const std::vector<unsigned int>& components,
                const unsigned char& componentSize
            ) ;

            /**
             * Initialize the class for standard color formats.
             */
            static void Initialize() ;

            /**
             * Create a ColorFormat.
             * @param   id  ID of the ColorFormat.
             */
            static void Create(const ColorFormat::ID& id) ;

            /**
             * Clear all ColorFormat instances.
             */
            static void Clear() ;

            /**
             * Get the wanted ColorFormat.
             * @param   id  ID of the ColorFormat to get.
             * @return  The wanted ColorFormat.
             */
            static ColorFormat& Get(const ColorFormat::ID& id) ;

            /**
             * Get the name of the ColorFormat.
             * @return  Name of the ColorFormat.
             */
            const std::string& name() const ;

            /**
             * Get the amount of components used in the ColorFormat.
             * @return  Amount of components in the ColorFormat.
             */
            unsigned char amountOfComponents() const ;

            /**
             * Get the total size in bytes of each pixel information.
             * @return  Amount of bytes used to represent each pixel of an image.
             */
            unsigned char pixelSizeInBytes() const ;

            /**
             * Get the color depth of the ColorFormat.
             * @return  Color depth in bits.
             */
            unsigned char colorDepth() const ;

            /**
             * Get the size of each component in bytes.
             * @return  Size of a component in bytes.
             */
            unsigned char componentSize() const ;

            /**
             * Get the mask of the wanted component.
             * @param   componentID ID of the component for which the mask is
             *                      wanted.
             * @return  The mask for the given @a componentID.
             */
            unsigned int mask(const unsigned int& componentID) const ;

        private:
            /**
             * Check if a ColorFormat has been initialized.
             * @return  TRUE if initialized, FALSE else.
             */
            bool isInitialized() const ;

            /**
             * Set the data for the given ID of color format.
             * @param   id                  ID of the ColorFormat.
             * @param   name                Name of the ColorFormat.
             * @param   components          Components in the ColorFormat.
             * @param   componentSize       Size of each component in bytes.
             */
            static void SetDataForFormat(
                const ColorFormat::ID& id,
                std::string& name,
                std::vector<unsigned int>& components,
                unsigned char& componentSize
            ) ;
    } ;
}

#endif