#version 330 core
in vec3 ourColor;
out vec4 FragColor;
uniform vec4 ourColor_old;
void main()
{
        FragColor = vec4(ourColor,1.0f);
}
