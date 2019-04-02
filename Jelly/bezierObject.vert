#version 330 core
// shadertype=<glsl>

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
//layout(location = 2) in vec3 positionNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 MVP;
uniform vec3 lightPos;
uniform bool isModel;
out vec3 vFragPos;
out vec3 vNormal;
out vec3 vLightPos;
uniform vec3 points[64];
uniform vec3 pointsNormals[64];
uniform mat4 rotation;

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

vec3 surfaceCalc(vec3 positionUVW, vec3 bezierPoints[64])
{
    vec3 sum1 = deCasteljau(positionUVW.x, bezierPoints[0], bezierPoints[16], bezierPoints[32], bezierPoints[48]);
    vec3 sum2 = deCasteljau(positionUVW.x, bezierPoints[1], bezierPoints[17], bezierPoints[33], bezierPoints[49]);
    vec3 sum3 = deCasteljau(positionUVW.x, bezierPoints[2], bezierPoints[18], bezierPoints[34], bezierPoints[50]);
    vec3 sum4 = deCasteljau(positionUVW.x, bezierPoints[3], bezierPoints[19], bezierPoints[35], bezierPoints[51]);
    vec3 sum5 = deCasteljau(positionUVW.x, bezierPoints[4], bezierPoints[20], bezierPoints[36], bezierPoints[52]);
    vec3 sum6 = deCasteljau(positionUVW.x, bezierPoints[5], bezierPoints[21], bezierPoints[37], bezierPoints[53]);
    vec3 sum7 = deCasteljau(positionUVW.x, bezierPoints[6], bezierPoints[22], bezierPoints[38], bezierPoints[54]);
    vec3 sum8 = deCasteljau(positionUVW.x, bezierPoints[7], bezierPoints[23], bezierPoints[39], bezierPoints[55]);
    vec3 sum9 = deCasteljau(positionUVW.x, bezierPoints[8], bezierPoints[24], bezierPoints[40], bezierPoints[56]);
    vec3 sum10 = deCasteljau(positionUVW.x, bezierPoints[9], bezierPoints[25], bezierPoints[41], bezierPoints[57]);
    vec3 sum11 = deCasteljau(positionUVW.x, bezierPoints[10], bezierPoints[26], bezierPoints[42], bezierPoints[58]);
    vec3 sum12 = deCasteljau(positionUVW.x, bezierPoints[11], bezierPoints[27], bezierPoints[43], bezierPoints[59]);
    vec3 sum13 = deCasteljau(positionUVW.x, bezierPoints[12], bezierPoints[28], bezierPoints[44], bezierPoints[60]);
    vec3 sum14 = deCasteljau(positionUVW.x, bezierPoints[13], bezierPoints[29], bezierPoints[45], bezierPoints[61]);
    vec3 sum15 = deCasteljau(positionUVW.x, bezierPoints[14], bezierPoints[30], bezierPoints[46], bezierPoints[62]);
    vec3 sum16 = deCasteljau(positionUVW.x, bezierPoints[15], bezierPoints[31], bezierPoints[47], bezierPoints[63]);
    vec3 sumP1 = deCasteljau(positionUVW.y, sum1, sum5, sum9, sum13);
    vec3 sumP2 = deCasteljau(positionUVW.y, sum2, sum6, sum10, sum14);
    vec3 sumP3 = deCasteljau(positionUVW.y, sum3, sum7, sum11, sum15);
    vec3 sumP4 = deCasteljau(positionUVW.y, sum4, sum8, sum12, sum16);
    vec3 sumTotal = deCasteljau(positionUVW.z, sumP1, sumP2, sumP3, sumP4);
    return sumTotal;
}

void main()
{
    vec3 surfPoint = surfaceCalc(position, points);
    vec3 surfPointNorm = surfaceCalc(position * 2.0, pointsNormals);
    gl_Position = MVP * vec4(surfPoint, 1.0);
    vFragPos = vec3(view * model * vec4(surfPoint, 1.0));
    if (isModel)
	{
        vNormal =  mat3(rotation) * -normal;
    }
	else
	{
        vNormal =  (surfPointNorm-surfPoint);
    }

    vLightPos = vec3(view * vec4(lightPos, 1.0));
}
