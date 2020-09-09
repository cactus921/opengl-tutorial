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

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

//const int c_PointLight       = 0;
//const int c_DirectionalLight = 1;

layout(location = 0) out vec4 color;

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_texCoord;

uniform vec4 u_Color;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform vec3 u_LightColor;
uniform vec3 u_LightDir;
uniform int u_LightType;
uniform sampler2D u_Texture;
uniform Material u_Material;

uniform float u_Time;

vec3 calcLightDir()
{
    if(u_LightType == 0)    // Point Light
        return normalize(u_LightPos - v_fragPos);
    else if (u_LightType == 1)  // Directional Light
        return normalize(-u_LightDir);
    else
        return vec3(0.0);
}

void main()
{
    //vec4 texColor = texture(u_Texture, v_texCoord);

    // Ambient Light
    vec3 m_Ambient = u_Material.ambient * u_LightColor;

    // Diffuse Light
    vec3 norm = normalize(v_normal);
    vec3 lightDir = calcLightDir();
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 m_Diffuse = u_LightColor * diff * u_Material.diffuse;

    // Specular Light
    vec3 viewDir = normalize(u_ViewPos - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 m_Specular = u_LightColor * spec * u_Material.specular;

    //vec3 result = (ambient + diffuse + specular) * objectColor;
    //gl_FragColor = vec4(result, 1.0);
    vec4 result = vec4((m_Ambient + m_Diffuse + m_Specular), 1.0);// * texColor;
    gl_FragColor = result;

    //gl_FragColor = vec4(1.0);
};
