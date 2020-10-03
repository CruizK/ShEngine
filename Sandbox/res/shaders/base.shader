#vertex
#version 330 core

layout (location = 0) in vec4 iPos;
layout (location = 1) in vec4 iColor;
layout (location = 2) in vec2 iTexCoords;
layout (location = 3) in float iTexIndex;

out vec4 oPos;
out vec4 oColor;
out vec2 oTexCoords;

uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * iPos;
    oPos = iPos;
    oColor = iColor;
    oTexCoords = iTexCoords;
}

#fragment
#version 330 core

in vec4 oPos;
in vec4 oColor;
in vec2 oTexCoords;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture2D(uTexture, oTexCoords) * oColor;
}