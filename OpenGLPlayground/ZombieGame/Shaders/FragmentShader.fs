#version 330
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;
uniform sampler2D playerTexture;

void main() {

    vec4 texColor= texture(playerTexture,fragmentUV );
    //Make crazy colors using time and position!
    color = fragmentColor * texColor;
}