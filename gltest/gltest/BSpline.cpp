#include "BSpline.h"


BSpline::BSpline(std::vector<glm::vec3> uniformControlPoints, int degree) : n(uniformControlPoints.size()), degree(degree), controlPoints(uniformControlPoints)
{
	memoN = new float*[degree+1];
	for (int i = 0; i < degree+1; ++i)
	{
		memoN[i] = new float[n+2]{-1};
	}
}

void BSpline::resetMemo()
{
	for (int i = 0; i < degree+1; ++i)
		for (int j = 0; j < n+2; ++j)
			memoN[i][j] = -1;
}

BSpline::~BSpline()
{
	for (int i = 0; i < degree+1; ++i)
	{
		delete[] memoN[i];
	}
	delete memoN;
}

float BSpline::T(int i)
{
	if (i <= degree) return 0;
	if (degree < i && i < n) return (i - degree) / (float)(n - degree);
	else return 1;
}

float BSpline::N(float t, int p, int i)
{
	if (p == 0)
	{
		if (t >= T(i) && t < T(i + 1)) return 1;
		else return 0;
	}
	else
	{
		if (memoN[p][i] == -1)
		{
            if (T(i+p) == T(i)) memoN[p][i] = 0.0f;
            else memoN[p][i] = (t - T(i)) / (T(i + p) - T(i))*N(t, p - 1, i);
            if (T(i + p + 1) != T(i + 1))
                memoN[p][i] += (T(i + p + 1) - t) / (T(i + p + 1) - T(i + 1))*N(t, p - 1, i + 1);
		}
		return memoN[p][i];
	}
}

glm::vec3 BSpline::Value(float t)
{
	resetMemo();
	glm::vec3 result(0.0f);
	for (int i = 0; i < n; ++i)
	{
		result += N(t, degree, i)*controlPoints[i];
	}
	return result;
}