#version 150

uniform sampler2D waterTexture;
uniform sampler2D reflectionTexture;
in vec2 vTexCoord;
out vec4 fragColor;

void main() {
    vec2 reflectTexCoords = vec2(vTexCoord.x, 1.0 - vTexCoord.y); 
    vec4 waterColor = texture(waterTexture, vTexCoord);
    vec4 reflectionColor = texture(reflectionTexture, reflectTexCoords);
    
    float reflectivity = 0.3;  // Adjust to control reflectivity

    fragColor = mix(waterColor, reflectionColor, reflectivity);
}
