#version 100

varying highp vec2 vTextureCoordinate;

uniform sampler2D uSampler;

void main() {
    gl_FragColor = texture2D(uSampler, vTextureCoordinate);
}