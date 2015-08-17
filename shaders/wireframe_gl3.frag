#version 150 core

uniform vec4 lightPosition;
uniform vec3 lightIntensity;

uniform vec4 diffuseColor; // Diffuse reflectivity

in vec3 position;
in vec3 normal;

out vec4 fragColor;

void main()
{
    vec3 s = normalize(vec3(lightPosition) - position);
    float diffuse = max( dot( s, normalize( normal)), 0.0);
    fragColor = vec4(lightIntensity, 1.0) * (diffuseColor * diffuse);
}
