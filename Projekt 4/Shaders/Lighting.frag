static const char* SimpleFragmentShader = STRINGIFY(

in varying vec3 EyespaceNormal;

uniform vec3 LightPosition;
uniform vec3 AmbientMaterial;
uniform vec3 DiffuseMaterial;
uniform vec3 SpecularMaterial;
uniform float Shininess;

void main(void)
{
    vec3 N = normalize(EyespaceNormal);
    vec3 L = normalize(LightPosition);
    vec3 E = vec3(0, 0, 1);
    vec3 H = normalize(L + E);
    
    float df = max(0.0, dot(N, L));
    float sf = max(0.0, dot(N, H));
    sf = pow(sf, Shininess);

    vec3 color = AmbientMaterial + df * DiffuseMaterial + sf * SpecularMaterial;

    gl_FragColor = vec4(color, 1);
}
);
