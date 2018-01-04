#version 330 core
// shadertype=<glsl>
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 color;
uniform mat4 MVP;
uniform vec3 points[64];
out vec4 vColor;
//uniform vec3 position[64]


vec3 deCasteljau(float t, vec3 a, vec3 b, vec3 c, vec3 d)
{
	float paramT = (1-t);
	
	a = a * paramT + b*t;
	b = b * paramT + c*t;
	c = c * paramT + d*t;

	a = a * paramT + b*t;
	b = b * paramT + c*t;
	
	a = a * paramT + b*t;

	return a;
}



vec3 surfaceCalc(vec3 positionUVW)
{
	vec3 sum1 = deCasteljau(positionUVW.z, points[0], points[16], points[32], points[48]);
	vec3 sum2 = deCasteljau(positionUVW.z, points[1], points[17], points[33], points[49]);
	vec3 sum3 = deCasteljau(positionUVW.z, points[2], points[18], points[34], points[50]);
	vec3 sum4 = deCasteljau(positionUVW.z, points[3], points[19], points[35], points[51]);
	vec3 sum5 = deCasteljau(positionUVW.z, points[4], points[20], points[36], points[52]);
	vec3 sum6 = deCasteljau(positionUVW.z, points[5], points[21], points[37], points[53]);
	vec3 sum7 = deCasteljau(positionUVW.z, points[6], points[22], points[38], points[54]);
	vec3 sum8 = deCasteljau(positionUVW.z, points[7], points[23], points[39], points[55]);
	vec3 sum9 = deCasteljau(positionUVW.z, points[8], points[24], points[40], points[56]);
	vec3 sum10 = deCasteljau(positionUVW.z, points[9], points[25], points[41], points[57]);
	vec3 sum11 = deCasteljau(positionUVW.z, points[10], points[26], points[42], points[58]);
	vec3 sum12 = deCasteljau(positionUVW.z, points[11], points[27], points[43], points[59]);
	vec3 sum13 = deCasteljau(positionUVW.z, points[12], points[28], points[44], points[60]);
	vec3 sum14 = deCasteljau(positionUVW.z, points[13], points[29], points[45], points[61]);
	vec3 sum15 = deCasteljau(positionUVW.z, points[14], points[30], points[46], points[62]);
	vec3 sum16 = deCasteljau(positionUVW.z, points[15], points[31], points[47], points[63]);

	vec3 sumP1 = deCasteljau(positionUVW.y, sum1, sum5, sum9, sum13);
	vec3 sumP2 = deCasteljau(positionUVW.y, sum2, sum6, sum10, sum14);
	vec3 sumP3 = deCasteljau(positionUVW.y, sum3, sum7, sum11, sum15);
	vec3 sumP4 = deCasteljau(positionUVW.y, sum4, sum8, sum12, sum16);

	vec3 sumTotal = deCasteljau(positionUVW.x, sumP1, sumP2, sumP3, sumP4);
	
	return sumTotal;
}

void main()
{
    //gl_PointSize = 4;
    gl_Position = MVP * vec4(surfaceCalc(position), 1.0);
    //gl_Position = vec4(position, 1.0);
	vColor = vec4(color, 1.0);
}
