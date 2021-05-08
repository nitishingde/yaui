#version 100

varying highp vec2 vTextureCoordinate;
varying highp float vTextureIndex;

uniform sampler2D uSampler[8];

void main() {
    gl_FragColor = texture2D(uSampler[int(vTextureIndex)], vTextureCoordinate);
}