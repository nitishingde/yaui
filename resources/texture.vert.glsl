#version 100

attribute vec3 aPosition;
attribute vec2 aTextureCoordinate;

varying vec2 vTextureCoordinate;

void main() {
    gl_Position = vec4(aPosition, 1.0);
    vTextureCoordinate = aTextureCoordinate;
}
