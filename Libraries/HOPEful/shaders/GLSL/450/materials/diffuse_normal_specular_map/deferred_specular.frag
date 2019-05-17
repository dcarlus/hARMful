// Blinn-Phong material shader.

struct Material {
    vec3 ambient ;
    vec3 diffuse ;
    vec3 specular ;
    float shininess ;
} ;

uniform Material material ;

out vec4 outColor ;

void main() {
    outColor = vec4(material.specular, material.shininess) ;
}