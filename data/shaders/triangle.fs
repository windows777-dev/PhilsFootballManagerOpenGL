#version 330 core
out vec4 FragColor;
  
//in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D overlay;

void main()
{
    vec4 bg = texture(ourTexture, TexCoord);
    vec4 fg = texture(overlay, TexCoord);

    vec3 blended = bg.rgb * (1.0 - fg.a) + fg.rgb * fg.a;

    FragColor = vec4(blended, 1.0);

}