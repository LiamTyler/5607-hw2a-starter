#version 330

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;

uniform mat4 M;
uniform mat4 VP;

out vec3 worldSpacePos;
out vec3 worldSpaceNormal;

void main()
{
    worldSpacePos = (M * vec4( position, 1 )).xyz;
    
    // dont forget that the model space to world space matrix for normals
    // is the inverse transpose of M, otherwise the normals can be skewed!
    worldSpaceNormal = (inverse(transpose(M)) * vec4( normal, 0 )).xyz;
	
    // final position of vertex
    gl_Position = VP * M * vec4( position, 1);
}
