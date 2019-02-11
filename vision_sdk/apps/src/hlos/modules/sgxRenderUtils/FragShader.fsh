uniform sampler2D  sTexture;

varying float  LightIntensity;
varying vec2   TexCoord;

void main()
{
    gl_FragColor.rgb = texture2D(sTexture, TexCoord).bbb;
    gl_FragColor.a = 1.0;
}
