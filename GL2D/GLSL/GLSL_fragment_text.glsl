#version 330 core

in vec3 fragPos;
in vec2 TexCoord;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 viewPos;

uniform float transparency;

void main() {

    fragColor = vec4(objectColor.rgb, transparency);
}