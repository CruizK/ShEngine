#vertex
#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iColor;

out vec3 oPos;
out vec4 oColor;

void main()
{
    gl_Position = vec4(iPos.xyz, 1);
    oPos = iPos;
    oColor = iColor;
}

#fragment
#version 330 core

in vec3 oPos;
in vec4 oColor;

out vec4 FragColor;

void main()
{
    FragColor = oColor;
}