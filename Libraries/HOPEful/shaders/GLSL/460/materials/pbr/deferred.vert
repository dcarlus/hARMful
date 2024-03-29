// Physics-based rendering material shader.

layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;
layout(location = 2) in vec3 normal ;
layout(location = 3) in vec3 tangent ;
layout(location = 4) in vec3 bitangent ;

layout(location = 0) out vec2 outTexCoord ;
layout(location = 1) out vec3 outNormal ;
layout(location = 2) out mat3 outTBNMatrix ;

void correctTBNMatrix() {
    outNormal = normalize(modelViewMatrix * vec4(normal, 0.f)).xyz ;
    vec3 correctedTangent = normalize(modelViewMatrix * vec4(tangent, 0.f)).xyz ;
    vec3 correctedBitangent = normalize(modelViewMatrix * vec4(bitangent, 0.f)).xyz ;
    vec3 correctedNormal = outNormal ;
    outTBNMatrix = mat3(correctedTangent, correctedBitangent, correctedNormal) ;
}

void main() {
    correctTBNMatrix() ;

    vec4 position4D = vec4(position, 1.f) ;
    gl_Position = mvpMatrix * position4D ;
    outTexCoord = texCoord ;
}
