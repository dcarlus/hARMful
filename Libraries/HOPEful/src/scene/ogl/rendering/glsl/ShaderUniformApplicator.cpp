#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>

using namespace Hope ;
using namespace Hope::GL ;

void ShaderUniformApplicator::ApplyUniform(
    const GLuint programID,
    Hope::ShaderUniform* uniform
) {
    ShaderUniform::ValueType type = uniform -> type() ;

    switch(type) {
        case ShaderUniform::Boolean:
        case ShaderUniform::Integer:
            Integer(programID, uniform) ;
            return ;
        case ShaderUniform::UInteger:
            UnsignedInteger(programID, uniform) ;
            return ;
        case ShaderUniform::Floating:
            Floating(programID, uniform) ;
            return ;

        case ShaderUniform::BVec2:
        case ShaderUniform::IVec2:
            IVec2(programID, uniform) ;
            return ;
        case ShaderUniform::BVec3:
        case ShaderUniform::IVec3:
            IVec3(programID, uniform) ;
            return ;
        case ShaderUniform::BVec4:
        case ShaderUniform::IVec4:
            IVec4(programID, uniform) ;
            return ;

        case ShaderUniform::UIVec2:
            UnsignedIVec2(programID, uniform) ;
            return ;
        case ShaderUniform::UIVec3:
            UnsignedIVec3(programID, uniform) ;
            return ;
        case ShaderUniform::UIVec4:
            UnsignedIVec4(programID, uniform) ;
            return ;

        case ShaderUniform::Vec2:
            Vec2(programID, uniform) ;
            return ;
        case ShaderUniform::Vec3:
            Vec3(programID, uniform) ;
            return ;
        case ShaderUniform::Vec4:
            Vec4(programID, uniform) ;
            return ;

        case ShaderUniform::Mat2:
            Mat2(programID, uniform) ;
            return ;
        case ShaderUniform::Mat3:
            Mat3(programID, uniform) ;
            return ;
        case ShaderUniform::Mat4:
            Mat4(programID, uniform) ;
            return ;

        case ShaderUniform::Mat2x3:
            Mat2x3(programID, uniform) ;
            return ;
        case ShaderUniform::Mat3x2:
            Mat3x2(programID, uniform) ;
            return ;
        case ShaderUniform::Mat2x4:
            Mat2x4(programID, uniform) ;
            return ;
        case ShaderUniform::Mat4x2:
            Mat4x2(programID, uniform) ;
            return ;
        case ShaderUniform::Mat3x4:
            Mat3x4(programID, uniform) ;
            return ;
        case ShaderUniform::Mat4x3:
            Mat4x3(programID, uniform) ;
            return ;

        case ShaderUniform::Sampler2D:
            Sampler2D(programID, uniform) ;
            return ;
        case ShaderUniform::SamplerCube:
            SamplerCube(programID, uniform) ;
            return ;

        default:
            return ;
    }
}

bool ShaderUniformApplicator::LocateUniform(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    const char* uniformName = (uniform -> name()).c_str() ;
    uniform -> setLocation(glGetUniformLocation(programID, uniformName)) ;

    GLenum error = glGetError() ;
    return error == GL_NO_ERROR ;
}

void ShaderUniformApplicator::Integer(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        glUniform1i(uniform -> location(), uniform -> integer()) ;
    }
}

void ShaderUniformApplicator::IVec2(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const int* values = uniform -> ivec2() ;
        glUniform2i(uniform -> location(), values[0], values[1]) ;
    }
}

void ShaderUniformApplicator::IVec3(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const int* values = uniform -> ivec3() ;
        glUniform3i(uniform -> location(), values[0], values[1], values[2]) ;
    }
}

void ShaderUniformApplicator::IVec4(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const int* values = uniform -> ivec4() ;
        glUniform4i(uniform -> location(), values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderUniformApplicator::UnsignedInteger(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        glUniform1ui(uniform -> location(), uniform -> uinteger()) ;
    }
}

void ShaderUniformApplicator::UnsignedIVec2(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const unsigned int* values = uniform -> uivec2() ;
        glUniform2ui(uniform -> location(), values[0], values[1]) ;
    }
}

void ShaderUniformApplicator::UnsignedIVec3(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const unsigned int* values = uniform -> uivec3() ;
        glUniform3ui(uniform -> location(), values[0], values[1], values[2]) ;
    }
}

void ShaderUniformApplicator::UnsignedIVec4(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const unsigned int* values = uniform -> uivec4() ;
        glUniform4ui(uniform -> location(), values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderUniformApplicator::Floating(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        glUniform1f(uniform -> location(), uniform -> floating()) ;
    }
}

void ShaderUniformApplicator::Vec2(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const float* values = uniform -> vec2() ;
        glUniform2f(uniform -> location(), values[0], values[1]) ;
    }
}

void ShaderUniformApplicator::Vec3(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const float* values = uniform -> vec3() ;
        glUniform3f(uniform -> location(), values[0], values[1], values[2]) ;
    }
}

void ShaderUniformApplicator::Vec4(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        const float* values = uniform -> vec4() ;
        glUniform4f(uniform -> location(), values[0], values[1], values[2], values[3]) ;
    }
}

void ShaderUniformApplicator::Mat2(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat2() ;
        glUniformMatrix2fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Mat3(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat3() ;
        glUniformMatrix3fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Mat4(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat4() ;
        glUniformMatrix4fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Mat2x3(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat2x3() ;
        glUniformMatrix2x3fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Mat3x2(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat3x2() ;
        glUniformMatrix3x2fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Mat2x4(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat2x4() ;
        glUniformMatrix2x4fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Mat4x2(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat4x2() ;
        glUniformMatrix4x2fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Mat3x4(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat3x4() ;
        glUniformMatrix3x4fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Mat4x3(
    GLuint programID,
    Hope::ShaderUniform* uniform
) {
    bool success = true ;
    if (uniform -> location() == -2) {
        success = LocateUniform(programID, uniform) ;
    }

    if (success) {
        static const GLsizei AmountUpdatedMatrices = 1 ;
        static const GLboolean Transpose = false ;
        const float* values = uniform -> mat4x3() ;
        glUniformMatrix4x3fv(uniform -> location(), AmountUpdatedMatrices, Transpose, values) ;
    }
}

void ShaderUniformApplicator::Sampler2D(
    GLuint /*programID*/,
    Hope::ShaderUniform* /*uniform*/
) {
}

void ShaderUniformApplicator::SamplerCube(
    GLuint /*programID*/,
    Hope::ShaderUniform* /*uniform*/
) {
}
