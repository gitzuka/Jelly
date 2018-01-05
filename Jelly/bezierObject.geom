#version 430 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 gPVM; //perspective view model matrix

in vec3 v2gPixelNormal[];

out vec3 g2fPixelNormal;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = gPVM * gl_in[i].gl_Position;
		g2fPixelNormal = v2gPixelNormal[i];
		EmitVertex();
	}
	EndPrimitive();
}



//layout ( triangles ) in;
//layout ( triangle_strip, max_vertices = 3 ) out;
//varying vec3 eyeSpaceNormal;
////output normal for frag shader

//void main( void )
//{
//    eyeSpaceNormal = gl_NormalMatrix * normalize(cross(gl_PositionIn[1].xyz - gl_PositionIn[0].xyz, gl_PositionIn[2].xyz - gl_PositionIn[0].xyz));
//    //calculate normal for this face

// for (int i = 0;i<gl_VerticesIn;i++)
// {
//        gl_Position =gl_ModelViewProjectionMatrix * gl_PositionIn[i];
//        //multiply position by MVP matrix;
//  EmitVertex();
//    }

// EndPrimitive();
//}


//out vec3 normal_out;
//uniform mat4 MVP;
//uniform mat4 modelViewMatrix;


//void main(void)
//{
//    // Please ignore my modelMatrix and NormalMatrix calculation here
//    mat4 modelMatrix = modelTranslationMatrix * modelScaleMatrix * modelRotationXMatrix * modelRotationYMatrix * modelRotationZMatrix;
//    mat4 modelViewMatrix = viewMatrix * modelMatrix;
//    mat4 mvp = projectionMatrix * modelViewMatrix;
//    vec3 A = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
//    vec3 B = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
//    mat4 normalMatrix = transpose(inverse(modelViewMatrix));
//    normal_out = mat3(normalMatrix) * normalize(cross(A,B));
//    gl_Position = mvp * gl_in[0].gl_Position;
//    EmitVertex();
//    gl_Position = mvp * gl_in[1].gl_Position;
//    EmitVertex();
//    gl_Position = mvp * gl_in[2].gl_Position;
//    EmitVertex();
//    EndPrimitive();
//}