#version 100

attribute vec4 colour;
attribute vec4 position;
varying vec4 vertexColour;

void main() {
    gl_Position = vec4(position.xyz, 1.0f);
    vertexColour = colour;
}
