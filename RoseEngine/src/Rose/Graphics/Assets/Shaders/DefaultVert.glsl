#version 410 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in mat4 aInstanceTransform; // location 2-5

out vec2 UV;

uniform mat4 uProjection;
uniform mat4 uView;

void main() {
    UV = aUV;
    gl_Position = uProjection * uView * aInstanceTransform * vec4(aPos, 0.0, 1.0);
}
