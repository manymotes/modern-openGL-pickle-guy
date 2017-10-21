#version 330 core
out vec4 ColorOut;

uniform sampler2D myTexture;

//in vec2 uv_out;

in vec3 OutNormal;

vec3 green;




void main()
{
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightPos  = vec3(-20.0f, 40.0f, 0.0f);
    vec3 FragPos = vec3(3.00f, 0.0f, -50.0f);
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(OutNormal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

     green = vec3(0.0, 1.0, 0.4);
     vec3 result = (ambient + diffuse) * green;
     ColorOut = vec4(result, 1.0);

   
   
}
