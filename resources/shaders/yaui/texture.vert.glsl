#version 100

attribute vec2 aPosition;
attribute vec4 aColour;
attribute vec2 aTextureCoordinate;
attribute float aTextureIndex;

varying vec2 vTextureCoordinate;
varying float vTextureIndex;

uniform mat4 uMVP;

void main() {
    gl_Position = uMVP * vec4(aPosition, 1.f, 1.f);
    vTextureCoordinate = aTextureCoordinate;
    vTextureIndex = aTextureIndex;
}
