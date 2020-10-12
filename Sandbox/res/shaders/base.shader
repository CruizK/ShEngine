#vertex
#version 330 core

layout (location = 0) in vec4 iPos;
layout (location = 1) in vec4 iColor;
layout (location = 2) in vec2 iTexCoords;
layout (location = 3) in float iTexIndex;

out vec4 oPos;
out vec4 oColor;
out vec2 oTexCoords;
out float oTexIndex;

uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * iPos;
    oPos = iPos;
    oColor = iColor;
    oTexCoords = iTexCoords;
    oTexIndex = iTexIndex;
}

#fragment
#version 330 core

in vec4 oPos;
in vec4 oColor;
in vec2 oTexCoords;
in float oTexIndex;

out vec4 FragColor;

uniform sampler2D u_Textures[32];

void main()
{
    int texIndex = int(oTexIndex);
    vec4 texColor = oColor;
    //FragColor = texture2D(u_Textures[texIndex], oTexCoords) * oColor;
    
    switch(texIndex) {
        case 0: texColor *= texture2D(u_Textures[0], oTexCoords); break;
        case 1: texColor *= texture2D(u_Textures[1], oTexCoords); break;
        case 2: texColor *= texture2D(u_Textures[2], oTexCoords); break;
        case 3: texColor *= texture2D(u_Textures[3], oTexCoords); break;
        case 4: texColor *= texture2D(u_Textures[4], oTexCoords); break;
        case 5: texColor *= texture2D(u_Textures[5], oTexCoords); break;
        case 6: texColor *= texture2D(u_Textures[6], oTexCoords); break;
        case 7: texColor *= texture2D(u_Textures[7], oTexCoords); break;
        case 8: texColor *= texture2D(u_Textures[8], oTexCoords); break;
        case 9: texColor *= texture2D(u_Textures[9], oTexCoords); break;
        case 10: texColor *= texture2D(u_Textures[10], oTexCoords); break;
        case 11: texColor *= texture2D(u_Textures[11], oTexCoords); break;
        case 12: texColor *= texture2D(u_Textures[12], oTexCoords); break;
        case 13: texColor *= texture2D(u_Textures[13], oTexCoords); break;
        case 14: texColor *= texture2D(u_Textures[14], oTexCoords); break;
        case 15: texColor *= texture2D(u_Textures[15], oTexCoords); break;
        case 16: texColor *= texture2D(u_Textures[16], oTexCoords); break;
        case 17: texColor *= texture2D(u_Textures[17], oTexCoords); break;
        case 18: texColor *= texture2D(u_Textures[18], oTexCoords); break;
        case 19: texColor *= texture2D(u_Textures[19], oTexCoords); break;
        case 20: texColor *= texture2D(u_Textures[20], oTexCoords); break;
        case 21: texColor *= texture2D(u_Textures[21], oTexCoords); break;
        case 22: texColor *= texture2D(u_Textures[22], oTexCoords); break;
        case 23: texColor *= texture2D(u_Textures[23], oTexCoords); break;
        case 24: texColor *= texture2D(u_Textures[24], oTexCoords); break;
        case 25: texColor *= texture2D(u_Textures[25], oTexCoords); break;
        case 26: texColor *= texture2D(u_Textures[26], oTexCoords); break;
        case 27: texColor *= texture2D(u_Textures[27], oTexCoords); break;
        case 28: texColor *= texture2D(u_Textures[29], oTexCoords); break;
        case 29: texColor *= texture2D(u_Textures[29], oTexCoords); break;
        case 30: texColor *= texture2D(u_Textures[30], oTexCoords); break;
        case 31: texColor *= texture2D(u_Textures[31], oTexCoords); break;

    }
    FragColor = texColor;
}
