#version 410 core

in vec2 UV;

out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
    FragColor = texture(uTexture, UV);
}
