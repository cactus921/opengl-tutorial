#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
const vec2 quadVertices[4] = vec2[4](vec2(-1.0, -1.0), vec2(1.0, -1.0), vec2(-1.0, 1.0), vec2(1.0, 1.0));
//out vec3 v_fragPos;
//out vec3 v_normal;
//out vec2 v_texCoord;
out vec2 v_sourceCoord;

uniform mat4 u_MVP;
//uniform mat4 u_Model;
//uniform float u_Time;

void main()
{
    //gl_Position = u_MVP * vec4(position, 1.0);
    gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);
    vec4 pos = u_MVP * vec4(0.0, 0.0, 0.0, 1.0);
    vec2 sourceCoord = pos.xy / pos.w;
    //v_fragPos = u_MVP * vec4(0.0, 0.0, 0.0, 1.0);
    //v_normal = vec3(u_Model * vec4(normal, 1.0)); //normal;
    //v_texCoord = texCoord;
};


#shader fragment
#version 330 core

//layout(location = 0) out vec4 color;

//in vec3 v_fragPos;
//in vec3 v_normal;
//in vec2 v_texCoord;
//in vec2 v_sourceCoord;

uniform mat4 u_MVP;
uniform vec2 u_resolution;
//uniform vec4 u_Color;
//uniform vec3 u_LightPos;
//uniform vec3 u_ViewPos;
//uniform sampler2D u_Texture;

//uniform float u_Time;

void main()
{
    
    vec2 coord = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);
    //float color = 0.0;
    //color += 0.1 * (0.1) / length(coord-sourceCoord.xy);
    vec3 uColor = vec3(length(coord));
    gl_FragColor = vec4(uColor, 1.0);
};
