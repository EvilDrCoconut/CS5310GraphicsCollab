// ====================================================
#version 330 core

// ======================= uniform ====================
// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap; 

// ======================= IN =========================
in vec2 v_texCoord; // Import our texture coordinates from vertex shader

// ======================= out ========================
// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

const float offset = 1.0/300.0;

void main()
{

    vec2 offsets[9] = vec2[](
	vec2(-offset, offset),
	vec2(0.0f, offset),
	vec2(offset, offset),
	vec2(-offset, 0.0f),
	vec2(0.0f, 0.0f),
	vec2(offset, 0.0f),
	vec2(-offset, -offset),
	vec2(0.0f, -offset),
	vec2(offset, -offset)
    );

    float kernel[9] = float[](
		-1,-1,-1,
		-1, 9,-1,
		-1,-1,-1
	);

    int i; int j;
    vec3 sampleTex[9];
    for(i = 0; i < 9; i++){
	sampleTex[i] = vec3(texture(u_DiffuseMap, v_texCoord.st + offsets[i]));
    }

    vec3 color = vec3(0.0f);
    for(j = 0; j < 9; j++){
	color += sampleTex[j] * kernel[j];
    }

    // Store our final texture color
    vec3 diffuseColor;
    diffuseColor = texture(u_DiffuseMap, v_texCoord).rgb;
        
    FragColor = vec4(color,1.0);
}
// ==================================================================
