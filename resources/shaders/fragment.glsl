#version 100

varying highp vec4 vertexColour;

void main() {
    gl_FragColor = vertexColour;
}
