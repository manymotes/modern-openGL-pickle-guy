#version 330 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec2 UV;
layout (location = 1) in vec3 Normal;

out vec2 uv_out;
out vec3 OutNormal;

uniform mat4 perspective;

void main()
{
   
    gl_Position =  perspective * vec4(position, 1.0);
    OutNormal = Normal;
}

