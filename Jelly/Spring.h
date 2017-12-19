#pragma once
class Vertex;

class Spring
{
public:
	Spring(Vertex p1, Vertex p2);
	Spring();
	~Spring();

private:
	float m_initialLength;

};
