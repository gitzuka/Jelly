#pragma once
#include "Mesh.h"

class CubeFrame : public Mesh
{
public:
	CubeFrame();
	~CubeFrame();

	void generateVertices() override;
private:
};