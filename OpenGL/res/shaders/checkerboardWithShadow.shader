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
out vec4 lightSpace;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightViewProj;
void main()
{
	gl_Position = projection * view * model * position;
	v_TexCoord = texCoord;
	fragPos = (model * position).xyz;
	normalFrag = vec3((model * vec4(normal, 0.0f)));
	fragType = type;
	lightSpace = (lightViewProj * model * position);
};


#shader fragment
#version 330 core
layout(location = 0)out vec4 color;

in vec4 lightSpace;
in vec2 v_TexCoord;
in vec3 normalFrag;
in vec3 fragPos;
in float fragType;
uniform vec4 u_Color;
uniform vec3 cameraPosition;
uniform sampler2D shadowMap;
uniform vec3 lightPosition;// = vec3(-25.0f, 30.0f, 25.0f);
uniform vec3 lightColor;// = vec3(1.0f, 1.0f, 1.0f);
const vec3 ambientColor = vec3(0.0f, 1.0f, 0.0f);
const float ambientStrength = 0.1f;
const float specularPower = 75;
const float diffusePower = 75;


void main()
{

	vec3 shadowMapCoord = lightSpace.xyz / lightSpace.w;
	shadowMapCoord = shadowMapCoord * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, shadowMapCoord.xy).x;
	float currentDepth = shadowMapCoord.z;
	vec3 lightDirection = normalize(lightPosition - fragPos);
	float bias = 0.00005f;// max(0.001f * (1.0f - dot(normalFrag, -lightDirection)), 0.0001f);
	float shadow = currentDepth - bias > closestDepth? 1.0 : 0.0;

	vec3 ambientColor = vec3(fragType, fragType, fragType);
	vec3 ambient = ambientColor * ambientStrength;
	
	float distanceFromLight = length(lightPosition - fragPos);

	vec3 cameraDirection = normalize(cameraPosition - fragPos);
	vec3 norm = normalize(normalFrag);
	vec3 reflection = reflect(-lightDirection, norm);
	vec3 specular = clamp(dot(cameraDirection, reflection), 0, 1) * lightColor * specularPower / (distanceFromLight * distanceFromLight);

	vec3 diffuse = max(dot(norm, lightDirection), 0.0f) * lightColor * diffusePower / (distanceFromLight * distanceFromLight);
	color = vec4(ambient + (diffuse + specular) * (1 - shadow), 1.0f);


	/*
	vec3 ambient = ambientColor * ambientStrength;
	vec3 lightDirection = normalize(lightPosition - fragPos);
	vec3 norm = normalize(normalFrag);

	vec3 diffuse = max(dot(norm, lightDirection), 0.0f) * lightColor;
	color = vec4(diffuse + ambient, 1.0f);
	//color = vec4(fragType, fragType, fragType, 1.0f);
	*/
};