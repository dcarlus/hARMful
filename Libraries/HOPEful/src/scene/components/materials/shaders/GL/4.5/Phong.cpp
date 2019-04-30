// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GL/4.5/Phong.hpp>

std::string PhongVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoord ;\n\
layout(location = 2) in vec3 normal ;\n\
\n\
layout(location = 0) out vec3 outVertexWorldPosition ;\n\
layout(location = 1) out vec3 outNormal ;\n\
layout(location = 2) out vec2 outTexCoord ;\n\
layout(location = 3) out vec3 outViewDirection ;\n\
\n\
void main() {\n\
    vec4 position4D = vec4(position, 1.f) ;\n\
\n\
    gl_Position = mvpMatrix * position4D ;\n\
\n\
    vec4 vertexPosition4D = modelViewMatrix * vec4(position, 1.f) ;\n\
    outVertexWorldPosition = vec3(vertexPosition4D) / vertexPosition4D.w ;\n\
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
    outTexCoord = texCoord ;\n\
    outViewDirection = normalize(-outVertexWorldPosition) ;\n\
}\n\
" ;

std::string PhongFragmentCode =
"\
// Phong material shader.\n\
\n\
struct Material {\n\
    vec3 ambientColor ;\n\
    vec3 diffuseColor ;\n\
    vec3 specularColor ;\n\
    float shininess ;\n\
} ;\n\
\n\
uniform Material phong ;\n\
\n\
const float ScreenGamma = 2.2f ;\n\
\n\
layout(location = 0) in vec3 inVertexWorldPosition ;\n\
layout(location = 1) in vec3 inNormal ;\n\
layout(location = 2) in vec2 inTexCoord ;\n\
layout(location = 3) in vec3 inViewDirection ;\n\
\n\
out vec4 outColor ;\n\
\n\
vec3 ComputeDirectionalLight(\n\
    DirectionalLight light,\n\
    vec3 viewDirection,\n\
    vec3 normal\n\
) {\n\
    vec3 returnedLighting = vec3(0.f) ;\n\
\n\
    vec4 lightWorldDirection = normalMatrix * vec4(light.direction,1) ;\n\
    vec3 lightDirection = normalize(-vec3(lightWorldDirection)) ;\n\
    float lambertian = max(dot(lightDirection, normal), 0.0) ;\n\
    vec3 reflectDirection = reflect(-lightDirection, normal) ;\n\
\n\
    vec3 halfwayDirection = normalize(lightDirection + viewDirection) ;\n\
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;\n\
    specularAngle *= pow(specularAngle, phong.shininess) ;\n\
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;\n\
\n\
    vec3 lightPowerColor = light.color * light.power ;\n\
    returnedLighting = (phong.diffuseColor * lambertian * lightPowerColor) ;\n\
    returnedLighting += (phong.specularColor * specularColor * lightPowerColor) ;\n\
\n\
    return returnedLighting ;\n\
}\n\
\n\
vec3 ComputePointLight(\n\
    PointLight light,\n\
    vec3 viewDirection,\n\
    vec3 normal\n\
) {\n\
    vec3 returnedLighting = vec3(0.f) ;\n\
\n\
    vec3 lightWorldPosition = vec3(modelViewMatrix * vec4(light.position, 1)) ;\n\
    vec3 lightDirection = normalize(lightWorldPosition - inVertexWorldPosition) ;\n\
    float lambertian = max(dot(lightDirection, normal), 0.0) ;\n\
    vec3 reflectDirection = reflect(-lightDirection, normal) ;\n\
\n\
    vec3 halfwayDirection = normalize(lightDirection + viewDirection) ;\n\
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;\n\
    specularAngle *= pow(specularAngle, phong.shininess) ;\n\
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;\n\
\n\
    float lightDistance = length(inVertexWorldPosition - light.position) ;\n\
    float sqrLightDistance = lightDistance * lightDistance ;\n\
    float sqrFalloffDistance = light.falloffDistance * light.falloffDistance ;\n\
\n\
    float lightLinearIntensity = light.falloffDistance / (light.falloffDistance + (light.linearAttenuation * lightDistance)) ;\n\
    float lightQuadIntensity = sqrFalloffDistance / (sqrFalloffDistance + (light.quadraticAttenuation * sqrLightDistance)) ;\n\
    float lightIntensity = light.power * lightLinearIntensity * lightQuadIntensity ;\n\
\n\
    vec3 lightPowerColor = light.color * lightIntensity ;\n\
    returnedLighting = (phong.diffuseColor * lambertian * lightPowerColor) ;\n\
    returnedLighting += (phong.specularColor * specularColor * lightPowerColor) ;\n\
\n\
    return returnedLighting ;\n\
}\n\
\n\
void main() {\n\
    vec3 colorLinear = phong.ambientColor ;\n\
\n\
    {\n\
        // Contribution of directional lights.\n\
        int validAmountOfDirLights = min(MAX_DIRECTIONAL_LIGHTS, amountDirectionalLights) ;\n\
        for (int lightIndex = 0 ; lightIndex < validAmountOfDirLights ; lightIndex++) {\n\
            colorLinear = colorLinear +\n\
                ComputeDirectionalLight(\n\
                    dirLights[lightIndex],\n\
                    inViewDirection,\n\
                    inNormal\n\
                ) ;\n\
        }\n\
    }\n\
\n\
    {\n\
        // Contribution of point lights.\n\
        int validAmountOfPointLights = min(MAX_POINT_LIGHTS, amountPointLights) ;\n\
        for (int lightIndex = 0 ; lightIndex < validAmountOfPointLights ; lightIndex++) {\n\
            colorLinear = colorLinear +\n\
                ComputePointLight(\n\
                    pointLights[lightIndex],\n\
                    inViewDirection,\n\
                    inNormal\n\
                ) ;\n\
        }\n\
    }\n\
\n\
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.f / ScreenGamma)) ;\n\
    outColor = vec4(colorGammaCorrected, 1.f) ;\n\
}\n\
" ;

