#version 410 core

in vec2 TexCoord;

uniform sampler2D uText;
uniform vec3 uTextColor;

out vec4 FragColor;

void main() {
    float alpha = texture(uText, TexCoord).r;
    FragColor = vec4(uTextColor, alpha);
}
