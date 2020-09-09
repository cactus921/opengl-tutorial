#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 v_fragPos;
out vec3 v_normal;
out vec2 v_texCoord;

uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform float u_Time;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    //v_fragPos = vec3(u_Model * vec4(position, 1.0));
    //v_normal = vec3(u_Model * vec4(normal, 1.0)); //normal;
    //v_texCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//in vec3 v_fragPos;
//in vec3 v_normal;
//in vec2 v_texCoord;

//uniform vec4 u_Color;
//uniform vec3 u_LightPos;
//uniform vec3 u_ViewPos;
//uniform sampler2D u_Texture;

//uniform float u_Time;

void main()
{
    gl_FragColor = vec4(1.0);
};
