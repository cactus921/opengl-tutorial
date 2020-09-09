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
    v_fragPos = vec3(u_Model * vec4(position, 1.0));
    v_normal = vec3(u_Model * vec4(normal, 1.0)); //normal;
    v_texCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_texCoord;

uniform vec4 u_Color;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform sampler2D u_Texture;

uniform float u_Time;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    //vec3 objectColor = vec3(0.8, 0.4, 0.2);

    vec4 texColor = texture(u_Texture, v_texCoord);

    // Ambient Light
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse Light
    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(u_LightPos - v_fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular Light
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    //vec3 result = (ambient + diffuse + specular) * objectColor;
    //gl_FragColor = vec4(result, 1.0);
    vec4 result = vec4((ambient + diffuse + specular), 1.0) * texColor;
    gl_FragColor = result;
};
