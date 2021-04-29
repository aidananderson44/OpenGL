#shader vertex
#version 330 core
layout(location = 0)in vec4 position;
layout(location = 1)in vec3 normal;
layout(location = 2)in vec2 texCoord;
layout(location = 3)in float type;

out vec2 v_TexCoord;
out vec3 normalFrag;
out vec3 fragPos;
out float fragType;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
void main()
{
	gl_Position = projection * view * model * position;
	v_TexCoord = texCoord;
	fragPos = (model * position).xyz;
	normalFrag = vec3((model * vec4(normal, 0.0f)));
	fragType = type;
};


#shader fragment
#version 330 core
layout(location = 0)out vec4 color;

in vec2 v_TexCoord;
in vec3 normalFrag;
in vec3 fragPos;
in float fragType;
uniform vec4 u_Color;
uniform sampler2D u_Texture;
const vec3 lightPosition = vec3(-5.0f, 5.0f, 5.0f);
const vec3 lightColor = vec3(0.3f, 0.3f, 0.3f);
const float ambientStrength = 0.1f;


void main()
{
	vec3 ambientColor = vec3(fragType, fragType, fragType);
	vec3 ambient = ambientColor * ambientStrength;
	vec3 lightDirection = normalize(lightPosition - fragPos);
	vec3 norm = normalize(normalFrag);

	vec3 diffuse = max(dot(norm, lightDirection), 0.0f) * lightColor;
	color = vec4(diffuse + ambient, 1.0f);
	//color = vec4(fragType, fragType, fragType, 1.0f);
	
};