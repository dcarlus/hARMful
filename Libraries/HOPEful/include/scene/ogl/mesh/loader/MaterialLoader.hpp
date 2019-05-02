#ifndef __HOPE__GL_MATERIAL_LOADER__
#define __HOPE__GL_MATERIAL_LOADER__

#include <filesystem>

namespace fs = std::filesystem ;

struct aiMaterial ;

namespace Hope {
    class MaterialComponent ;
}

namespace Hope::GL {
    /**
     * Load the right material from the Assimp data.
     */
    class MaterialLoader final {
        public:
            /**
             * Convert the Assimp material structure to a material component
             * that can be attached to an entity.
             * @param   meshPath    Path of the mesh that is currently loaded.
             *                      It is useful to retreive the absolute path
             *                      to the textures in case it is relative to
             *                      the file.
             * @param   material    Material to convert as a component.
             */
            static MaterialComponent* ConvertMaterial(
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;

            // Copy/move operations.
            MaterialLoader() = delete ;
            MaterialLoader(const MaterialLoader& copied) = delete ;
            MaterialLoader(MaterialLoader&& moved) = delete ;
            MaterialLoader& operator=(const MaterialLoader& copied) = delete ;
            MaterialLoader& operator=(MaterialLoader&& moved) = delete ;

        private:
            /**
             * Create a Blinn-Phong material.
             * @param   material    Material to convert as a component.
             */
            static MaterialComponent* BlinnPhongMaterial(const aiMaterial* material) ;

            /**
             * Create a Blinn-Phong material with a diffuse texture.
             * @param   meshPath    Path of the mesh that is currently loaded.
             *                      It is useful to retreive the absolute path
             *                      to the textures in case it is relative to
             *                      the file.
             * @param   material    Material to convert as a component.
             */
            static MaterialComponent* DiffuseMaterial(
                const fs::path& meshPath,
                const aiMaterial* material
            ) ;
    } ;
} ;

#endif