#version 100

attribute vec4 colour;
attribute vec4 position;
varying vec4 vertexColour;

uniform mat4 uMVP;

void main() {
    gl_Position = uMVP * vec4(position.xyz, 1.0f);
    vertexColour = colour;
}
