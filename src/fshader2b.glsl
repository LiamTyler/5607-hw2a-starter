#version 330

out vec4 finalColor;

uniform vec3 Kd;

in vec3 worldSpacePos;
in vec3 worldSpaceNormal;

const vec3 worldSpaceLightDir = vec3( 0, 0, -1 );
const vec3 lightColor = vec3( 1, 1, 1 );

void main() 
{
    // note: should be doing ambient, diffuse, and specular. Just diffuse so far
    vec3 fragColor = vec3( 0, 0, 0 );
    
    // diffuse component
    fragColor += Kd * lightColor * max( 0, dot( worldSpaceNormal, -worldSpaceLightDir ) );
	
    finalColor = vec4( fragColor, 1 );
}