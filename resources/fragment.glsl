#version 100

//precision mediump float;
//attribute vec4 position;
varying highp vec4 vertexColour;

void main() {
    gl_FragColor = vertexColour;
}
