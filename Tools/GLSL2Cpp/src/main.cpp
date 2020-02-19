#include <FileUtils.hpp>
#include <StringUtils.hpp>
#include <iostream>
#include <filesystem>
#include <system_error>
#include <Paths.hpp>

void createSymLink() {
    const std::string PathSeparatorStr = std::string(PathSeparator) ;

    fs::path currentDir = fs::current_path() ;
    fs::path harmfulDir = currentDir ;

    const std::string WantedDirName(ProjectDirName) ;
    std::string stem = harmfulDir.stem().generic_string() ;
    while (harmfulDir.has_parent_path() && (stem != WantedDirName)) {
        harmfulDir = harmfulDir.parent_path() ;
        stem = harmfulDir.stem().generic_string() ;
    }

	fs::path libDirectoryPath(harmfulDir.generic_string() + PathSeparator + LibDirectory) ;
	libDirectoryPath = libDirectoryPath ;

	fs::path symlibDirectoryPath(SimLinkDirectory) ;
	symlibDirectoryPath = symlibDirectoryPath ;

	if (fs::exists(symlibDirectoryPath)) {
	    return ;
    }

    // Create the local symlink to the HOPEful library folder.
	std::error_code error ;
	fs::create_directory_symlink(libDirectoryPath, symlibDirectoryPath, error) ;

	if (error) {
		auto errorMsg = error.message() ;
		std::cerr << "ERROR: " << error << errorMsg << std::endl ;
	}
}

int main() {
    createSymLink() ;

    const std::string PathSeparatorStr = std::string(PathSeparator) ;

    // Get the shader files.
    auto shaderFiles = FileUtils::GetShaderFiles(ShadersDirectory) ;

    // Copy GLSL includes into GLSL modules/includes...
    {
        std::string fullDestinationPath = std::string(ShadersDirectory) + PathSeparatorStr +
                                            GLSL4xModulesDirectory + PathSeparatorStr +
                                            IncludesDirectory ;

        FileUtils::CopyIncludeModules(
            ShadersDirectory,
            shaderFiles[GLSLIncludesDirectory],
            fullDestinationPath
        ) ;
    }

    {
        const bool RemoveUnderscoreChars = true ;
        std::string fullDestinationPath = std::string(GLSLCppHeadersDirectory) +
                                            PathSeparatorStr +
                                            std::string(IncludesDirectory) ;

        // Copy GLSL includes into CPP headers (in "shaders" folder)...
        FileUtils::CopyIncludeModules(
            ShadersDirectory,
            shaderFiles[GLSLIncludesDirectory],
            fullDestinationPath,
            CppHeaderExtension,
            RemoveUnderscoreChars
        ) ;
    }

    // Remove GLSL/includes from the map.
    shaderFiles.erase(GLSLIncludesDirectory) ;

    // Convert GLSL source code to C++ HPP/CPP files.
    for (auto& [dir, files]: shaderFiles) {
        files.storeIntoCppFiles(
            ShadersDirectory,
            ShadersCppHeadersDirectory,
            ShadersCppSourcesDirectory
        ) ;
    }
}
