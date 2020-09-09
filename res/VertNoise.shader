#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_MVP;
uniform float u_Time;

float noise1d(float value){
    return cos(value + cos(value * 90.0) * 100.0) * 0.5 + 0.5;
}

float random2d(vec2 coord){
    return fract(sin(dot(coord.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    gl_Position = u_MVP * position;
    float factor = abs(sin(u_Time / 500.0));
    gl_Position.x += factor * random2d(position.xy);
    gl_Position.y += factor * random2d(position.yz);
    gl_Position.z += factor * random2d(position.zx);
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
    color = vec4(vec3(0.5), 1.0);
};
