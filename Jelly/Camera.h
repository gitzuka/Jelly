#pragma once
#include <QMatrix4x4>
#include <QVector3D>
#define CAM_NEAR 0.01f
#define CAM_FAR 50.0f
#define FOV 60.0f
#define SPEED 0.12f
#define MOUSE_SENSITIVITY 0.005f
#define TRANSLATION_STEP 0.4f

class Camera
{
public:
	Camera();

	float m_pitch;
	float m_yaw;
	QPoint m_mousePos;
	QVector3D m_eyeVector;
	QMatrix4x4 m_viewMatrix;
	QMatrix4x4 m_projectionMatrix;
	QMatrix4x4 m_projView;
	//QMatrix4x4 m_projViewInv;

	void updateView();
	void keyPressed(const unsigned char key);
	void mouseMoved(float x, float y);

	static QMatrix4x4 createLookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	static QMatrix4x4 createLookAt(const QVector3D &eye, const QVector3D &target, const QVector3D &up);
	static QVector4D transform(const QVector4D &point, const QMatrix4x4 &matrix);
	static QMatrix4x4 createTranslation(float x, float y, float z);
	static QMatrix4x4 createTranslation(const QVector3D &vec);
	static QMatrix4x4 createProjection(float width, float heigth, float near = CAM_NEAR, float far = CAM_FAR, float angle = FOV);
	static QMatrix4x4 createScaling(float factor);
	static QMatrix4x4 createRotationX(float angle);
	static QMatrix4x4 createRotationY(float angle);
	static QMatrix4x4 createRotationZ(float angle);
	static QMatrix4x4 createIdentity();
	static QVector4D multiplyByMatrix(const QMatrix4x4 &mat, const QVector4D &vec);
	static QVector3D convertToScreenSpace(float mouseX, float mouseY, float mouseZ, float width, float heigth, const QMatrix4x4 &view, float pitch, float yaw);
	static float convertToRadians(float angle);
};
