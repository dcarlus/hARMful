// Material for deferred rendering. Applied on a simple quad on the whole
// viewport area.

layout(binding = 0) uniform sampler2DMS albedo ;
layout(binding = 1) uniform sampler2DMS specular ;
layout(binding = 2) uniform sampler2DMS normal ;
layout(binding = 3) uniform sampler2DMS depth ;
layout(location = 10) uniform int msaaQuality ;

layout(location = 0) in vec2 inTexCoords ;

out vec3 outColor ;

// Apply fog.
void applyFog(in float distance, inout vec3 shadedColor) {
    float fogFactor = (distance - fog.minDistance) / (fog.maxDistance - fog.minDistance) ;
    fogFactor = fog.color.a * clamp(fogFactor, 0.f, 1.f) ;

    shadedColor = mix(
        shadedColor,
        fog.color.rgb,
        fogFactor
    ) ;
}

void main() {
    const ivec2 FragCoords = ivec2(gl_FragCoord.xy) ;

    FragmentData currentFragment ;

    for (int sampleIndex = 0; sampleIndex < msaaQuality; ++sampleIndex) {
        // Note: The lighting computations are performed in view-space.
        // Get the view-space positions of the 3D objects from the pixel coordinates
        // and the depth buffer.
        float depthValue = texelFetch(depth, FragCoords, sampleIndex).r ;
        vec4 viewSpacePosition = ComputeViewSpacePosition(inTexCoords, depthValue) ;

        // Put values to perform the lighting pass for the current fragment.
        currentFragment.diffuseValue = texelFetch(albedo, FragCoords, sampleIndex).rgb ;
        currentFragment.normalValue = DecodeSpheremapNormals(texelFetch(normal, FragCoords, sampleIndex).xy) ;
        currentFragment.specularValue = texelFetch(specular, FragCoords, sampleIndex).rgb ;
        currentFragment.shininess = texelFetch(specular, FragCoords, sampleIndex).a ;
        currentFragment.position = viewSpacePosition ;
        currentFragment.depth = depthValue ;

        // Compute ligh shading.
        vec3 viewDirection = normalize(-currentFragment.position.xyz) ;
        vec3 shadedColor = ComputeLightsContribution(
            viewDirection,
            currentFragment
        ) ;

        applyFog(abs(currentFragment.position.z), shadedColor) ;

        // Compute the skybox mask to include it in the final render.
        // 1. Get the normal mask based on the length of the normal vector (the
        //    skybox material gives [0,0,0,0] during the off-screen pass).
        // 2. Revsere the values of the normal mask to get the sky mask.
        // 3. Extract the diffuse color of the sky by multiplying by the mask.
        // 4. Merge shading color and sky diffuse color.
        float normalMask = clamp(ceil(length(texelFetch(normal, FragCoords, sampleIndex).rgb)), 0.f, 1f) ;
        shadedColor *= normalMask ; // remove fog from the skymap!
        float skyMask = 1.f - normalMask ;
        vec3 skyDiffuse = currentFragment.diffuseValue * skyMask ;

        outColor += shadedColor + skyDiffuse ;


        //#define DEBUG_CSM
        #ifdef DEBUG_CSM
            const vec3 CascadeColors[] = {
                vec3(1.f, 0.3f, 0.3f),
                vec3(0.3f, 1.f, 0.3f),
                vec3(0.3f, 0.3f, 1.f)
            } ;

           float distanceCamera = distanceFromCamera(currentFragment.position) ;

           int selectedCascade = 0 ;
            for (int cascadeIndex = amountCascades - 1 ; cascadeIndex >= 0 ; cascadeIndex--) {
                if (distanceCamera < cascadedSplits[cascadeIndex]) {
                    selectedCascade = cascadeIndex ;
                    break ;
                }
            }

            outColor += vec3(CascadeColors[selectedCascade]) ;
            normalize(outColor) ;
        #endif
    }

    outColor /= msaaQuality ;
}