attribute vec3  inVertex;
attribute vec3  inNormal;
attribute vec2  inTexCoord;

uniform mat4  MVPMatrix;
uniform vec3  LightDirection;

varying float  LightIntensity;
varying vec2   TexCoord;

void main()
{
	// Transform position
	gl_Position = MVPMatrix * vec4(inVertex, 1.0);

	// Pass through texcoords
	TexCoord = inTexCoord;
	
	// Simple diffuse lighting in model space
	LightIntensity = dot(inNormal, -LightDirection);
}
