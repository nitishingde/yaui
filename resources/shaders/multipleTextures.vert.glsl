#version 100

attribute vec3 aPosition;
attribute vec2 aTextureCoordinate;
attribute float aTextureIndex;

uniform mat4 uMVP;

varying vec2 vTextureCoordinate;
varying float vTextureIndex;

void main() {
    gl_Position = uMVP * vec4(aPosition, 1.0);
    vTextureCoordinate = aTextureCoordinate;
    vTextureIndex = aTextureIndex;
}
