#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_MVP;
uniform float u_Time;

void main()
{
    gl_Position = u_MVP * position;
    gl_Position.x *= abs(1/(sin(u_Time / 500) + 1.5));
    v_texCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

//uniform vec2 u_resolution;
uniform float u_Time;

void main()
{
    vec4 texColor = texture(u_Texture, v_texCoord);
    //color = texColor;
    //color = u_Color;
    //vec3 ucolor = vec3(0.0);
    //ucolor.r = sin(u_Time / 1000);
    //ucolor.b = v_texCoord.y;
    //color = vec4(ucolor, 1.0);

    float time = u_Time / 500;

    vec2 coord = v_texCoord * 20;

    for (int n = 1; n < 16; n++){
        float i = float(n);
        coord += vec2(0.7 / i * sin(i*coord.y + time + 0.3 * i) + 0.8, 0.4 /i* sin(i*coord.x + time + 0.3*i) + 1.6);
    }
    vec3 ucolor = vec3(0.5 * sin(coord.x) + 0.5, 0.5 * sin(coord.y) + 0.5, sin(coord.x + coord.y));

    // make it cartoonish
    float size = 12.0;
    float alpha = sin(floor(coord.y * size) + time * 4.0) + 1.0 / 2.0;

    color = vec4(ucolor, 1.0);
};
