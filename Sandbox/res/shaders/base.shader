#vertex
#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iColor;
layout (location = 2) in vec2 iTexCoords;

out vec3 oPos;
out vec4 oColor;
out vec2 oTexCoords;

void main()
{
    gl_Position = vec4(iPos.xyz, 1);
    oPos = iPos;
    oColor = iColor;
    oTexCoords = iTexCoords;
}

#fragment
#version 330 core

in vec3 oPos;
in vec4 oColor;
in vec2 oTexCoords;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture2D(uTexture, oTexCoords) * oColor;
}