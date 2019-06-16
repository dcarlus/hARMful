// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>

std::string FunctionsUtilityModuleCode =
"\
/**\n\
 * Adjust a normal vector with a Tangent-Bitangent-Normal matrix.\n\
 */\n\
vec3 AdjustNormalVector(mat3 tbnMatrix, vec3 normalValue) {\n\
    vec3 adjustedNormalVector = normalize((normalValue * 2.f) - 1.f) ;\n\
    adjustedNormalVector = normalize(tbnMatrix * adjustedNormalVector) ;\n\
    return adjustedNormalVector ;\n\
}\n\
\n\
/**\n\
 * Retrieve a view space position from texture coordinates and depth.\n\
 */\n\
vec4 ComputeViewSpacePosition(vec2 texCoords, float depth) {\n\
    vec2 adjustedTexCoords = texCoords * 2.f - 1.f ;\n\
	float x = adjustedTexCoords.x ;\n\
	float y = adjustedTexCoords.y ;\n\
	float z = depth * 2.f - 1.f ;\n\
\n\
	vec4 positionProjection = vec4(x, y, z, 1.f) ;\n\
	vec4 positionView = inverseProjectionMatrix * positionProjection ;\n\
    positionView /= positionView.w ;\n\
	return positionView ;\n\
}\n\
\n\
/**\n\
 * Encode normals using the Lambert azimuthal equal-area projection.\n\
 * See http://aras-p.info/texts/CompactNormalStorage.html\n\
 */\n\
vec2 EncodeSpheremapNormals(vec3 normal) {\n\
    vec3 normalizedNormal = normalize(normal) ;\n\
    float zEncoding = sqrt(normalizedNormal.z * 8.f + 8.f) ;\n\
    return (normalizedNormal.xy / zEncoding) + 0.5f ;\n\
}\n\
\n\
/**\n\
 * Decode normals using the Lambert azimuthal equal-area projection.\n\
 * See http://aras-p.info/texts/CompactNormalStorage.html\n\
 */\n\
vec3 DecodeSpheremapNormals(vec2 sphereNormal) {\n\
    vec2 adjustedSphereNormal = sphereNormal * 4.f - 2.f ;\n\
    float dotResult = dot(adjustedSphereNormal, adjustedSphereNormal) ;\n\
    float zInverseDecoding = sqrt(1.f - dotResult / 4.f) ;\n\
\n\
    vec3 decodedNormal = vec3(0.f) ;\n\
    decodedNormal.xy = adjustedSphereNormal * zInverseDecoding ;\n\
    decodedNormal.z = 1.f - dotResult / 2.f ;\n\
    return decodedNormal ;\n\
}\n\
" ;

std::string FunctionsLightComputeModuleCode =
"\
/*** Data ***/\n\
struct DirectionalLight {\n\
    // Direction of the light.\n\
    vec3 direction ;\n\
\n\
    // Color of the light.\n\
    vec3 color ;\n\
\n\
    // Power of the light.\n\
    float power ;\n\
\n\
    // Does the light produce a specular?\n\
    float generateSpecular ;\n\
} ;\n\
\n\
struct PointLight {\n\
    // Position of the light in the 3D space.\n\
    vec3 position ;\n\
\n\
    // Color of the light.\n\
    vec3 color ;\n\
\n\
    // Distance of the light effect.\n\
    float falloffDistance ;\n\
\n\
    // Linear attenuation of the light.\n\
    float linearAttenuation ;\n\
\n\
    // Quadratic attenuation of the light.\n\
    float quadraticAttenuation ;\n\
\n\
    // Power of the light.\n\
    float power ;\n\
\n\
    // Does the light produce a specular?\n\
    float generateSpecular ;\n\
} ;\n\
\n\
layout (std140, binding = LIGHTS_DATA_UBO_BINDING_INDEX) uniform LightsData\n\
{\n\
    DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHTS] ;\n\
    PointLight pointLights[MAX_POINT_LIGHTS] ;\n\
    int amountDirectionalLights ;\n\
    int amountPointLights ;\n\
} ;\n\
\n\
\n\
struct FragmentData {\n\
    // Position of the fragment.\n\
    vec4 position ;\n\
\n\
    // Diffuse color value.\n\
    vec3 diffuseValue ;\n\
\n\
    // Normal value.\n\
    vec3 normalValue ;\n\
\n\
    // Specular color value.\n\
    vec3 specularValue ;\n\
\n\
    // Shininess value.\n\
    float shininess ;\n\
\n\
    // Depth of the fragment.\n\
    float depth ;\n\
} ;\n\
\n\
/*** Functions ***/\n\
/**\n\
 * Compute the directional light contribution in a fragment shader.\n\
 * @param   light           Data of the directional light.\n\
 * @param   viewDirection   Direction of the view.\n\
 * @param   fragment        Data on the processed fragment.\n\
 * @return  Light contribution color.\n\
 */\n\
vec3 ComputeDirectionalLight(\n\
    DirectionalLight light,\n\
    vec3 viewDirection,\n\
    FragmentData fragment\n\
) {\n\
    vec3 lightDirection = -light.direction ;\n\
    lightDirection = normalize((viewMatrix * vec4(lightDirection, 0.f))).xyz ;\n\
    float lambertian = max(dot(lightDirection, fragment.normalValue), 0.0) ;\n\
    vec3 reflectDirection = reflect(-lightDirection, fragment.normalValue) ;\n\
\n\
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;\n\
    specularAngle *= pow(specularAngle, fragment.shininess) ;\n\
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;\n\
\n\
    float litFragment = ShadowCompute(\n\
        lightDirection,\n\
        fragment.position,\n\
        fragment.normalValue,\n\
        fragment.depth\n\
    ) ;\n\
\n\
    vec3 lightPowerColor = litFragment * light.color * light.power ;\n\
    vec3 returnedLighting = fragment.diffuseValue * lambertian * lightPowerColor ;\n\
    returnedLighting += fragment.specularValue * specularColor * lightPowerColor ;\n\
\n\
    return returnedLighting ;\n\
}\n\
\n\
/**\n\
 * Compute the point light contribution in a fragment shader.\n\
 * @param   light           Data of the point light.\n\
 * @param   viewDirection   Direction of the view.\n\
 * @param   fragment        Data on the processed fragment.\n\
 * @return  Light contribution color.\n\
 */\n\
vec3 ComputePointLight(\n\
    PointLight light,\n\
    vec3 viewDirection,\n\
    FragmentData fragment\n\
) {\n\
    vec3 lightDirection = normalize(light.position - fragment.position.xyz) ;\n\
    float lambertian = max(dot(lightDirection, fragment.normalValue), 0.0) ;\n\
    vec3 reflectDirection = reflect(-lightDirection, fragment.normalValue) ;\n\
\n\
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;\n\
    specularAngle *= pow(specularAngle, fragment.shininess) ;\n\
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;\n\
\n\
    float lightDistance = length(fragment.position.xyz - light.position) ;\n\
    float sqrLightDistance = lightDistance * lightDistance ;\n\
    float sqrFalloffDistance = light.falloffDistance * light.falloffDistance ;\n\
\n\
    float lightLinearIntensity = light.falloffDistance / (light.falloffDistance + (light.linearAttenuation * lightDistance)) ;\n\
    float lightQuadIntensity = sqrFalloffDistance / (sqrFalloffDistance + (light.quadraticAttenuation * sqrLightDistance)) ;\n\
    float lightIntensity = light.power * lightLinearIntensity * lightQuadIntensity ;\n\
\n\
    vec3 lightPowerColor = light.color * lightIntensity ;\n\
    vec3 returnedLighting = fragment.diffuseValue * lambertian * lightPowerColor ;\n\
    returnedLighting += fragment.specularValue * specularColor * lightPowerColor ;\n\
\n\
    return returnedLighting ;\n\
}\n\
\n\
/**\n\
 * Compute the lights contribution in a fragment shader.\n\
 * @param   viewDirection   Direction of the view.\n\
 * @param   fragment        Data on the processed fragment.\n\
 * @return  Color of the whole scene lights contribution.\n\
 */\n\
vec3 ComputeLightsContribution(\n\
    vec3 viewDirection,\n\
    FragmentData fragment\n\
) {\n\
    // Contribution of the directional light.\n\
    vec3 colorLinear = ComputeDirectionalLight(\n\
        dirLights[0],\n\
        viewDirection,\n\
        fragment\n\
    ) ;\n\
\n\
    // Contribution of point lights.\n\
    int validAmountOfPointLights = min(MAX_POINT_LIGHTS, amountPointLights) ;\n\
    for (int lightIndex = 0 ; lightIndex < validAmountOfPointLights ; lightIndex++) {\n\
        colorLinear = colorLinear +\n\
            ComputePointLight(\n\
                pointLights[lightIndex],\n\
                viewDirection,\n\
                fragment\n\
            ) ;\n\
    }\n\
\n\
    return colorLinear ;\n\
}\n\
" ;

