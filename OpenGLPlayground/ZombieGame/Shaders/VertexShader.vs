#version 330
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 proj;

void main() {
    //Set the x,y position on the screen

	//vec2 offset = offsets[gl_InstanceID];

    gl_Position.xy = (proj * vec4(vertexPosition,0.0,1.0)).xy;
    //the z position is zero since we are in 2D
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;

	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
	fragmentPosition = vertexPosition;
	fragmentColor = vertexColor;
   
}