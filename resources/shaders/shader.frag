#version 410 core

in vec3 FragPos;
out vec4 FragColour;

void main() {
    FragColour = vec4(FragPos.x, FragPos.y - FragPos.x, -FragPos.y, 1.0);
}