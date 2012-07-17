const char* SimpleFragmentShader = STRINGIFY(

varying vec4 DestinationColor;

void main(void)
{
    gl_FragColor = DestinationColor;
}
);
