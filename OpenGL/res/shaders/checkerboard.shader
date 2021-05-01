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
uniform vec3 cameraPosition;
uniform sampler2D u_Texture;
const vec3 lightPosition = vec3(-5.0f, 10.0f, 5.0f);
const vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
const vec3 ambientColor = vec3(0.0f, 1.0f, 0.0f);
const float ambientStrength = 0.1f;
const float specularPower = 0.1;
const float diffusePower = 0.1;

void main()
{
	vec3 ambientColor = vec3(fragType, fragType, fragType);
	vec3 ambient = ambientColor * ambientStrength;
	vec3 lightDirection = normalize(lightPosition - fragPos);
	float distanceFromLight = length(lightPosition - fragPos) / 20;

	vec3 cameraDirection = normalize(cameraPosition - fragPos);
	vec3 norm = normalize(normalFrag);
	vec3 reflection = reflect(-lightDirection, norm);
	vec3 specular = clamp(dot(cameraDirection, reflection), 0, 1) * lightColor * specularPower / (distanceFromLight * distanceFromLight);

	vec3 diffuse = max(dot(norm, lightDirection), 0.0f) * lightColor * diffusePower / (distanceFromLight * distanceFromLight);
	color = vec4(diffuse + ambient + specular, 1.0f);


	/*
	vec3 ambient = ambientColor * ambientStrength;
	vec3 lightDirection = normalize(lightPosition - fragPos);
	vec3 norm = normalize(normalFrag);

	vec3 diffuse = max(dot(norm, lightDirection), 0.0f) * lightColor;
	color = vec4(diffuse + ambient, 1.0f);
	//color = vec4(fragType, fragType, fragType, 1.0f);
	*/
};