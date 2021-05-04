#version 100

varying highp vec2 vTextureCoordinate;

uniform sampler2D uSampler;

void main() {
    highp vec4 color = texture2D(uSampler, vTextureCoordinate);
    gl_FragColor = vec4(color.a, color.a, color.a, color.a);
}