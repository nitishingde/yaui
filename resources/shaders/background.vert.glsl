#version 100

attribute vec2 aPosition;
attribute vec4 aColour;

varying vec4 vColour;

uniform mat4 uMVP;

void main() {
    gl_Position = uMVP * vec4(aPosition.xy, 1.0f, 1.0f);
    vColour = aColour;
}
