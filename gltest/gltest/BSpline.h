#pragma once
#include "gl.h"
#include <vector>

class BSpline
{
public:
	BSpline(std::vector<glm::vec3> uniformControlPoints, int degree);
	~BSpline();
	glm::vec3 Value(float t);

private:
	int n;
	int degree;
	std::vector<glm::vec3> controlPoints;
	float T(int i);
	float N(float t, int p, int i);
	void resetMemo();

	float** memoN;
};

