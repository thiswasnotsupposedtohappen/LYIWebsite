#define pi 3.14159265358979323846264338327
#define PI 3.14159265358979323846264338327f
#define BUFFERSIZE 256

float32 Absolute(float32 input)
{
	if (input < 0)
		return -input;
	else
		return input;
}
float64 Absolute(float64 input)
{
	if (input < 0)
		return -input;
	else
		return input;
}
int32 Absolute(int32 input)
{
	if (input < 0)
		return -input;
	else
		return input;
}
float32 Sign(float32 input)
{
	if (input < 0)
		return -1.0f;
	else
		return +1.0f;
}
int8 Sign(int8 input)
{
	if (input < 0)
		return -1;
	else
		return +1;
}
int16 Sign(int16 input)
{
	if (input < 0)
		return -1;
	else
		return +1;
}
float32 Sign(int32 input)
{
	if (input < 0)
		return -1;
	else
		return +1;
}
float32 PositiveAnd(float32 input)
{
	if (input < 0)
		return 0;
	return input;
}
float64 PositiveAnd(float64 input)
{
	if (input < 0)
		return 0;
	return input;
}
float32 VectorAngle(float32 y2, float32 y1, float32 x2, float32 x1)
{
	float32 x = x2 - x1;
	float32 y = y2 - y1;
	float32 angle;

	angle = atan2f(y, x);
	if (angle < 0) angle = (angle)+(2 * PI);
	return angle;
}
float64 VectorAngle(float64 y2, float64 y1, float64 x2, float64 x1)
{
	float64 x = x2 - x1;
	float64 y = y2 - y1;
	float64 angle;

	angle = atan2(y, x);
	if (angle < 0) angle = (angle)+(2 * PI);
	return angle;
}
float64 VectorAngle(float64 x1, float64 y1, float64 z1, float64 x2, float64 y2, float64 z2)
{
	return acos(((x1 * x2) + (y1 * y2) + (z1 * z2)) / (sqrt((x1 * x1) + (y1 * y1) + (z1 * z1)) * sqrt((x2 * x2) + (y2 * y2) + (z2 * z2))));
}
float64 InterpolationForumula(float64 X, float64 x1, float64 x2, float64 y1, float64 y2)
{
	return ((X - x1) / (x2 - x1)) * (y2 - y1) + y1;
};
void QuadraticRegression(float64 x[], float64 y[], int n, float64* a, float64* b, float64* c)
{
	float64 sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
	float64 sum_y = 0, sum_xy = 0, sum_x2y = 0;

	for (int i = 0; i < n; i++)
	{
		float64 xi = x[i];
		float64 yi = y[i];

		sum_x += xi;
		sum_y += yi;
		sum_x2 += xi * xi;
		sum_x3 += xi * xi * xi;
		sum_x4 += xi * xi * xi * xi;
		sum_xy += xi * yi;
		sum_x2y += xi * xi * yi;
	}

	float64 sum_x_x = (sum_x2)-(((sum_x) * (sum_x)) / n);
	float64 sum_x_y = (sum_xy)-(((sum_x) * (sum_y)) / n);
	float64 sum_x_x2 = (sum_x3)-(((sum_x2) * (sum_x)) / n);
	float64 sum_x2_y = (sum_x2y)-(((sum_x2) * (sum_y)) / n);
	float64 sum_x2_x2 = (sum_x4)-(((sum_x2) * (sum_x2)) / n);

	*a = ((sum_x2_y * sum_x_x) - (sum_x_y * sum_x_x2)) / ((sum_x_x * sum_x2_x2) - ((sum_x_x2) * (sum_x_x2)));
	*b = ((sum_x_y * sum_x2_x2) - (sum_x2_y * sum_x_x2)) / ((sum_x_x * sum_x2_x2) - ((sum_x_x2) * (sum_x_x2)));
	*c = (sum_y / n) - (*b * sum_x / n) - (*a * sum_x2 / n);

	//*a = ((sum_x2_y * sum_x_x) - (sum_xy * sum_x_x2)) / ((sum_x_x * sum_x2_x2) - ((sum_x_x2) * (sum_x_x2)));
	//*b = ((sum_xy * sum_x2_x2) - (sum_x2y * sum_x_x2)) / ((sum_x_x * sum_x2_x2) - ((sum_x_x2) * (sum_x_x2)));
	//*c = (sum_y / n) - (*b * sum_x / n) - (*a * sum_x2 / n);
}

struct Matrix
{
	float32 e[4][4];
	uint8 rows;
	uint8 columns;
	Matrix()
	{
		ZeroMemory(this, sizeof(Matrix));
	}
	Matrix(uint8 _rows, uint8 _columns)
	{
		ZeroMemory(this, sizeof(Matrix));
		rows = _rows;
		columns = _columns;
	}
	Matrix(uint8 _rows, uint8 _columns, float32 _00, float32 _01, float32 _02, float32 _03, float32 _10, float32 _11, float32 _12, float32 _13, float32 _20, float32 _21, float32 _22, float32 _23, float32 _30, float32 _31, float32 _32, float32 _33)
	{
		ZeroMemory(this, sizeof(Matrix));
		rows = _rows;
		columns = _columns;
		if (columns > 0)e[0][0] = _00;
		if (columns > 1)e[0][1] = _01;
		if (columns > 2)e[0][2] = _02;
		if (columns > 3)e[0][3] = _03;
		if (columns > 0)e[1][0] = _10;
		if (columns > 1)e[1][1] = _11;
		if (columns > 2)e[1][2] = _12;
		if (columns > 3)e[1][3] = _13;
		if (columns > 0)e[2][0] = _20;
		if (columns > 1)e[2][1] = _21;
		if (columns > 2)e[2][2] = _22;
		if (columns > 3)e[2][3] = _23;
		if (columns > 0)e[3][0] = _30;
		if (columns > 1)e[3][1] = _31;
		if (columns > 2)e[3][2] = _32;
		if (columns > 3)e[3][3] = _33;
	}
	Matrix(const Matrix& m)
	{
		MemoryCopy(this, (void*)& m, sizeof(Matrix));
	}
	void R0(float32 _0, float32 _1, float32 _2, float32 _3)
	{
		if (columns > 0)e[0][0] = _0;
		if (columns > 1)e[0][1] = _1;
		if (columns > 2)e[0][2] = _2;
		if (columns > 3)e[0][3] = _3;
	}
	void R1(float32 _0, float32 _1, float32 _2, float32 _3)
	{
		if (columns > 0)e[1][0] = _0;
		if (columns > 1)e[1][1] = _1;
		if (columns > 2)e[1][2] = _2;
		if (columns > 3)e[1][3] = _3;
	}
	void R2(float32 _0, float32 _1, float32 _2, float32 _3)
	{
		if (columns > 0)e[2][0] = _0;
		if (columns > 1)e[2][1] = _1;
		if (columns > 2)e[2][2] = _2;
		if (columns > 3)e[2][3] = _3;
	}
	void R3(float32 _0, float32 _1, float32 _2, float32 _3)
	{
		if (columns > 0)e[3][0] = _0;
		if (columns > 1)e[3][1] = _1;
		if (columns > 2)e[3][2] = _2;
		if (columns > 3)e[3][3] = _3;
	}

	void operator=(const Matrix m)
	{
		MemoryCopy(this, (void*)&m, sizeof(Matrix));
	}
	Matrix operator!()
	{
		//Matrix  m(4,4);
		//float32 s0 = e[0][0] * e[1][1] - e[1][0] * e[0][1];
		//float32 s1 = e[0][0] * e[1][2] - e[1][0] * e[0][2];
		//float32 s2 = e[0][0] * e[1][3] - e[1][0] * e[0][3];
		//float32 s3 = e[0][1] * e[1][2] - e[1][1] * e[0][2];
		//float32 s4 = e[0][1] * e[1][3] - e[1][1] * e[0][3];
		//float32 s5 = e[0][2] * e[1][3] - e[1][2] * e[0][3];
		//float32 c5 = e[2][2] * e[3][3] - e[3][2] * e[2][3];
		//float32 c4 = e[2][1] * e[3][3] - e[3][1] * e[2][3];
		//float32 c3 = e[2][1] * e[3][2] - e[3][1] * e[2][2];
		//float32 c2 = e[2][0] * e[3][3] - e[3][0] * e[2][3];
		//float32 c1 = e[2][0] * e[3][2] - e[3][0] * e[2][2];
		//float32 c0 = e[2][0] * e[3][1] - e[3][0] * e[2][1];
		//float32 invdet = 1 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);
		//m.e[0][0] = (e[1][1] * c5 - e[1][2] * c4 + e[1][3] * c3) * invdet;
		//m.e[0][1] = (-e[0][1] * c5 + e[0][2] * c4 - e[0][3] * c3) * invdet;
		//m.e[0][2] = (e[3][1] * s5 - e[3][2] * s4 + e[3][3] * s3) * invdet;
		//m.e[0][3] = (-e[2][1] * s5 + e[2][2] * s4 - e[2][3] * s3) * invdet;
		//m.e[1][0] = (-e[1][0] * c5 + e[1][2] * c2 - e[1][3] * c1) * invdet;
		//m.e[1][1] = (e[0][0] * c5 - e[0][2] * c2 + e[0][3] * c1) * invdet;
		//m.e[1][2] = (-e[3][0] * s5 + e[3][2] * s2 - e[3][3] * s1) * invdet;
		//m.e[1][3] = (e[2][0] * s5 - e[2][2] * s2 + e[2][3] * s1) * invdet;
		//m.e[2][0] = (e[1][0] * c4 - e[1][1] * c2 + e[1][3] * c0) * invdet;
		//m.e[2][1] = (-e[0][0] * c4 + e[0][1] * c2 - e[0][3] * c0) * invdet;
		//m.e[2][2] = (e[3][0] * s4 - e[3][1] * s2 + e[3][3] * s0) * invdet;
		//m.e[2][3] = (-e[2][0] * s4 + e[2][1] * s2 - e[2][3] * s0) * invdet;
		//m.e[3][0] = (-e[1][0] * c3 + e[1][1] * c1 - e[1][2] * c0) * invdet;
		//m.e[3][1] = (e[0][0] * c3 - e[0][1] * c1 + e[0][2] * c0) * invdet;
		//m.e[3][2] = (-e[3][0] * s3 + e[3][1] * s1 - e[3][2] * s0) * invdet;
		//m.e[3][3] = (e[2][0] * s3 - e[2][1] * s1 + e[2][2] * s0) * invdet;
		//return m;
		Matrix result(4, 4);
		float32 det;

		result.e[0][0] = e[1][1] * e[2][2] * e[3][3] -
			e[1][1] * e[2][3] * e[3][2] -
			e[2][1] * e[1][2] * e[3][3] +
			e[2][1] * e[1][3] * e[3][2] +
			e[3][1] * e[1][2] * e[2][3] -
			e[3][1] * e[1][3] * e[2][2];

		result.e[1][0] = -e[1][0] * e[2][2] * e[3][3] +
			e[1][0] * e[2][3] * e[3][2] +
			e[2][0] * e[1][2] * e[3][3] -
			e[2][0] * e[1][3] * e[3][2] -
			e[3][0] * e[1][2] * e[2][3] +
			e[3][0] * e[1][3] * e[2][2];

		result.e[2][0] = e[1][0] * e[2][1] * e[3][3] -
			e[1][0] * e[2][3] * e[3][1] -
			e[2][0] * e[1][1] * e[3][3] +
			e[2][0] * e[1][3] * e[3][1] +
			e[3][0] * e[1][1] * e[2][3] -
			e[3][0] * e[1][3] * e[2][1];

		result.e[3][0] = -e[1][0] * e[2][1] * e[3][2] +
			e[1][0] * e[2][2] * e[3][1] +
			e[2][0] * e[1][1] * e[3][2] -
			e[2][0] * e[1][2] * e[3][1] -
			e[3][0] * e[1][1] * e[2][2] +
			e[3][0] * e[1][2] * e[2][1];

		result.e[0][1] = -e[0][1] * e[2][2] * e[3][3] +
			e[0][1] * e[2][3] * e[3][2] +
			e[2][1] * e[0][2] * e[3][3] -
			e[2][1] * e[0][3] * e[3][2] -
			e[3][1] * e[0][2] * e[2][3] +
			e[3][1] * e[0][3] * e[2][2];

		result.e[1][1] = e[0][0] * e[2][2] * e[3][3] -
			e[0][0] * e[2][3] * e[3][2] -
			e[2][0] * e[0][2] * e[3][3] +
			e[2][0] * e[0][3] * e[3][2] +
			e[3][0] * e[0][2] * e[2][3] -
			e[3][0] * e[0][3] * e[2][2];

		result.e[2][1] = -e[0][0] * e[2][1] * e[3][3] +
			e[0][0] * e[2][3] * e[3][1] +
			e[2][0] * e[0][1] * e[3][3] -
			e[2][0] * e[0][3] * e[3][1] -
			e[3][0] * e[0][1] * e[2][3] +
			e[3][0] * e[0][3] * e[2][1];

		result.e[3][1] = e[0][0] * e[2][1] * e[3][2] -
			e[0][0] * e[2][2] * e[3][1] -
			e[2][0] * e[0][1] * e[3][2] +
			e[2][0] * e[0][2] * e[3][1] +
			e[3][0] * e[0][1] * e[2][2] -
			e[3][0] * e[0][2] * e[2][1];

		result.e[0][2] = e[0][1] * e[1][2] * e[3][3] -
			e[0][1] * e[1][3] * e[3][2] -
			e[1][1] * e[0][2] * e[3][3] +
			e[1][1] * e[0][3] * e[3][2] +
			e[3][1] * e[0][2] * e[1][3] -
			e[3][1] * e[0][3] * e[1][2];

		result.e[1][2] = -e[0][0] * e[1][2] * e[3][3] +
			e[0][0] * e[1][3] * e[3][2] +
			e[1][0] * e[0][2] * e[3][3] -
			e[1][0] * e[0][3] * e[3][2] -
			e[3][0] * e[0][2] * e[1][3] +
			e[3][0] * e[0][3] * e[1][2];

		result.e[2][2] = e[0][0] * e[1][1] * e[3][3] -
			e[0][0] * e[1][3] * e[3][1] -
			e[1][0] * e[0][1] * e[3][3] +
			e[1][0] * e[0][3] * e[3][1] +
			e[3][0] * e[0][1] * e[1][3] -
			e[3][0] * e[0][3] * e[1][1];

		result.e[3][2] = -e[0][0] * e[1][1] * e[3][2] +
			e[0][0] * e[1][2] * e[3][1] +
			e[1][0] * e[0][1] * e[3][2] -
			e[1][0] * e[0][2] * e[3][1] -
			e[3][0] * e[0][1] * e[1][2] +
			e[3][0] * e[0][2] * e[1][1];

		result.e[0][3] = -e[0][1] * e[1][2] * e[2][3] +
			e[0][1] * e[1][3] * e[2][2] +
			e[1][1] * e[0][2] * e[2][3] -
			e[1][1] * e[0][3] * e[2][2] -
			e[2][1] * e[0][2] * e[1][3] +
			e[2][1] * e[0][3] * e[1][2];

		result.e[1][3] = e[0][0] * e[1][2] * e[2][3] -
			e[0][0] * e[1][3] * e[2][2] -
			e[1][0] * e[0][2] * e[2][3] +
			e[1][0] * e[0][3] * e[2][2] +
			e[2][0] * e[0][2] * e[1][3] -
			e[2][0] * e[0][3] * e[1][2];

		result.e[2][3] = -e[0][0] * e[1][1] * e[2][3] +
			e[0][0] * e[1][3] * e[2][1] +
			e[1][0] * e[0][1] * e[2][3] -
			e[1][0] * e[0][3] * e[2][1] -
			e[2][0] * e[0][1] * e[1][3] +
			e[2][0] * e[0][3] * e[1][1];

		result.e[3][3] = e[0][0] * e[1][1] * e[2][2] -
			e[0][0] * e[1][2] * e[2][1] -
			e[1][0] * e[0][1] * e[2][2] +
			e[1][0] * e[0][2] * e[2][1] +
			e[2][0] * e[0][1] * e[1][2] -
			e[2][0] * e[0][2] * e[1][1];

		det = e[0][0] * result.e[0][0] + e[0][1] * result.e[1][0] + e[0][2] * result.e[2][0] + e[0][3] * result.e[3][0];

		result.e[0][0] /= det;
		result.e[0][1] /= det;
		result.e[0][2] /= det;
		result.e[0][3] /= det;
		result.e[1][0] /= det;
		result.e[1][1] /= det;
		result.e[1][2] /= det;
		result.e[1][3] /= det;
		result.e[2][0] /= det;
		result.e[2][1] /= det;
		result.e[2][2] /= det;
		result.e[2][3] /= det;
		result.e[3][0] /= det;
		result.e[3][1] /= det;
		result.e[3][2] /= det;
		result.e[3][3] /= det;

		return result;
	}
	Matrix operator+(const Matrix m)
	{
		Matrix result(rows, columns);
		for (uint8 c = 0; c < columns; c++)
			for (uint8 r = 0; r < rows; r++)
				result.e[r][c] = e[r][c] + m.e[r][c];
		return result;
	}
	Matrix operator-(const Matrix m)
	{
		Matrix result(rows, columns);
		for (uint8 c = 0; c < columns; c++)
			for (uint8 r = 0; r < rows; r++)
				result.e[r][c] = e[r][c] - m.e[r][c];
		return result;
	}
	Matrix operator*(const Matrix m)
	{
		if (columns != m.rows)while (1);
		Matrix result(rows, m.columns);
		for (uint8 c = 0; c < m.columns; c++)
			for (uint8 r = 0; r < rows; r++)
				for (uint32 i = 0; i < columns; i++)
					result.e[r][c] += e[r][i] * m.e[i][c];
		return result;
	}

	void Identity()
	{
		R0(1, 0, 0, 0);
		R1(0, 1, 0, 0);
		R2(0, 0, 1, 0);
		R3(0, 0, 0, 1);
	}
	void Transpose()
	{
		Matrix result(*this);
		for (uint8 c = 0; c < columns; c++)
			for (uint8 r = 0; r < rows; r++)
				result.e[r][c] = e[c][r];
		*this = result;
	}
	void Translate(float32 x, float32 y, float32 z)
	{
		Matrix translate(4, 4);
		translate.R0(1, 0, 0, 0);
		translate.R1(0, 1, 0, 0);
		translate.R2(0, 0, 1, 0);
		translate.R3(x, y, z, 1);
		(*this) = (*this) * translate;
	}
	void Scale(float32 x, float32 y, float32 z)
	{
		Matrix scale(4, 4);
		scale.R0(x, 0, 0, 0);
		scale.R1(0, y, 0, 0);
		scale.R2(0, 0, z, 0);
		scale.R3(0, 0, 0, 1);
		(*this) = (*this) * scale;
	}
	void RotateX(float32 theta)
	{
		Matrix rotate(4, 4);
		rotate.R0(1, 0, 0, 0);
		rotate.R1(0, +cos(theta * PI / 180.0f), +sin(theta * PI / 180.0f), 0);
		rotate.R2(0, -sin(theta * PI / 180.0f), +cos(theta * PI / 180.0f), 0);
		rotate.R3(0, 0, 0, 1);
		(*this) = (*this) * rotate;
	}
	void RotateY(float32 theta)
	{
		Matrix rotate(4, 4);
		rotate.R0(+cos(theta * PI / 180.0f), 0, +sin(theta * PI / 180.0f), 0);
		rotate.R1(0, 1, 0, 0);
		rotate.R2(-sin(theta * PI / 180.0f), 0, +cos(theta * PI / 180.0f), 0);
		rotate.R3(0, 0, 0, 1);
		(*this) = (*this) * rotate;
	}
	void RotateZ(float32 theta)
	{
		Matrix rotate(4, 4);
		rotate.R0(+cos(theta * PI / 180.0f), +sin(theta * PI / 180.0f), 0, 0);
		rotate.R1(-sin(theta * PI / 180.0f), +cos(theta * PI / 180.0f), 0, 0);
		rotate.R2(0, 0, 1, 0);
		rotate.R3(0, 0, 0, 1);
		(*this) = (*this) * rotate;
	}
	void Rotate(float32 u, float32 v, float32 w, float32 theta)
	{
		theta = theta * PI / 180;
		Matrix rotate(4, 4);
		rotate.R0((u * u) + ((1 - (u * u)) * cosf(theta)), (u * v * (1 - cosf(theta))) - (w * sinf(theta)), (u * w * (1 - cosf(theta))) + (v * sinf(theta)), 0);
		rotate.R1((u * v * (1 - cosf(theta))) + (w * sinf(theta)), (v * v) + ((1 - (v * v)) * cosf(theta)), (v * w * (1 - cosf(theta))) - (u * sinf(theta)), 0);
		rotate.R2((u * w * (1 - cosf(theta))) - (v * sinf(theta)), (v * w * (1 - cosf(theta))) + (u * sinf(theta)), (w * w) + ((1 - (w * w)) * cosf(theta)), 0);
		rotate.R3(0, 0, 0, 1);
		(*this) = (*this) * rotate;

		//rotate.R0(
		//	((u*u) + ((v*v + w*w)*cosf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	((u*v*(1 - cosf(theta))) - (w*sqrt((u*u) + (v*v) + (w*w))*sinf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	((u*w*(1 - cosf(theta))) + (v*sqrt((u*u) + (v*v) + (w*w))*sinf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	0);
		//rotate.R1(
		//	((u*v*(1 - cosf(theta))) + (w*sqrt((u*u) + (v*v) + (w*w))*sinf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	((v*v) + ((u*u + w*w)*cosf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	((u*w*(1 - cosf(theta))) - (u*sqrt((u*u) + (v*v) + (w*w))*sinf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	0);
		//rotate.R2(
		//	((u*w*(1 - cosf(theta))) - (v*sqrt((u*u) + (v*v) + (w*w))*sinf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	((u*w*(1 - cosf(theta))) + (v*sqrt((u*u) + (v*v) + (w*w))*sinf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	((w*w) + ((u*u + v*v)*cosf(theta))) / ((u*u) + (v*v) + (w*w)),
		//	0);
	}
};
struct float4
{
	float32 x, y, z, w;
	float4()
	{
		ZeroMemory(this, sizeof(float4));
	}
	float4(const float4& f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
		w = f.w;
	}
	float4(float32 _x, float32 _y, float32 _z, float32 _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	float4(uint8 _x, uint8 _y, uint8 _z)
	{
		x = ((float32)_x) / 255.0f;
		y = ((float32)_y) / 255.0f;
		z = ((float32)_z) / 255.0f;
		w = 1.0;
	}

	void operator=(const float4 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
		w = f.w;
	}
	float4 operator+(const float4 f)
	{
		float4 result;
		result.x = x + f.x;
		result.y = y + f.y;
		result.z = z + f.z;
		result.w = w + f.w;
		return result;
	}
	float4 operator-(const float4 f)
	{
		float4 result;
		result.x = x - f.x;
		result.y = y - f.y;
		result.z = z - f.z;
		result.w = w - f.w;
		return result;
	}
	float4 operator*(const float32 f)
	{
		float4 result;
		result.x = x * f;
		result.y = y * f;
		result.z = z * f;
		result.w = w * f;
		return result;
	}
	float4 operator/(const float32 f)
	{
		float4 result;
		result.x = x / f;
		result.y = y / f;
		result.z = z / f;
		result.w = w / f;
		return result;
	}
	float32  operator*(const float4 f)
	{
		float32 result = 0;
		result += x * f.x;
		result += y * f.y;
		result += z * f.z;
		result += w * f.w;
		return result;
	}
	float4 operator*(const Matrix m)
	{
		if (m.rows != 4 || m.columns != 4)while (1);
		float4 result;
		result.x = x * m.e[0][0] + y * m.e[1][0] + z * m.e[2][0] + w * m.e[3][0];
		result.y = x * m.e[0][1] + y * m.e[1][1] + z * m.e[2][1] + w * m.e[3][1];
		result.z = x * m.e[0][2] + y * m.e[1][2] + z * m.e[2][2] + w * m.e[3][2];
		result.w = x * m.e[0][3] + y * m.e[1][3] + z * m.e[2][3] + w * m.e[3][3];
		return result;
	}
	void Normalize()
	{
		float32 factor = (float)sqrt((x * x) + (y * y) + (z * z) + (w * w));
		x /= factor;
		y /= factor;
		z /= factor;
		w /= factor;
	}
};
struct float3
{
	float32 x, y, z;
	float3()
	{
		ZeroMemory(this, sizeof(float3));
	}
	float3(const float3& f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}
	float3(float32 _x, float32 _y, float32 _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void operator=(const float3 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}
	void operator=(const float4 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}

	float3 operator+(const float3 f)
	{
		float3 result;
		result.x = x + f.x;
		result.y = y + f.y;
		result.z = z + f.z;
		return result;
	}
	float3 operator-(const float3 f)
	{
		float3 result;
		result.x = x - f.x;
		result.y = y - f.y;
		result.z = z - f.z;
		return result;
	}
	float3 operator*(const float32 f)
	{
		float3 result;
		result.x = x * f;
		result.y = y * f;
		result.z = z * f;
		return result;
	}
	float3 operator/(const float32 f)
	{
		float3 result;
		result.x = x / f;
		result.y = y / f;
		result.z = z / f;
		return result;
	}
	float32 operator*(const float3 f)
	{
		float32 result = 0;
		result += x * f.x;
		result += y * f.y;
		result += z * f.z;
		return result;
	}
	float3 operator^(const float3 f)
	{
		float3 result;
		result.x = (y * f.z) - (z * f.y);
		result.y = (z * f.x) - (x * f.z);
		result.z = (x * f.y) - (y * f.x);
		return result;
	}
	void Normalize()
	{
		float32 factor = (float)sqrt((x * x) + (y * y) + (z * z));
		x /= factor;
		y /= factor;
		z /= factor;
	}
};
struct float2
{
	float32 x, y;
	float2()
	{
		ZeroMemory(this, sizeof(float2));
	}
	float2(const float2& f)
	{
		x = f.x;
		y = f.y;
	}
	float2(float32 _x, float32 _y)
	{
		x = _x;
		y = _y;
	}

	void operator=(const float4 f)
	{
		x = f.x;
		y = f.y;
	}
	void operator=(const float3 f)
	{
		x = f.x;
		y = f.y;
	}
	void operator=(const float2 f)
	{
		x = f.x;
		y = f.y;
	}

	float2 operator+(const float2 f)
	{
		float2 result;
		result.x = x + f.x;
		result.y = y + f.y;
		return result;
	}
	float2 operator-(const float2 f)
	{
		float2 result;
		result.x = x - f.x;
		result.y = y - f.y;
		return result;
	}
	float2 operator*(const float32 f)
	{
		float2 result;
		result.x = x * f;
		result.y = y * f;
		return result;
	}
	float2 operator/(const float32 f)
	{
		float2 result;
		result.x = x / f;
		result.y = y / f;
		return result;
	}
	float32 operator*(const float2 f)
	{
		float32 result = 0;
		result += x * f.x;
		result += y * f.y;
		return result;
	}
	void Normalize()
	{
		float32 factor = (float)sqrt((x * x) + (y * y));
		x /= factor;
		y /= factor;
	}
};

struct float64x4
{
	float64 x, y, z, w;
	float64x4()
	{
		ZeroMemory(this, sizeof(float64x4));
	}
	float64x4(const float64x4& f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
		w = f.w;
	}
	float64x4(float64 _x, float64 _y, float64 _z, float64 _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void operator=(const float64x4 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
		w = f.w;
	}
	float64x4 operator+(const float64x4 f)
	{
		float64x4 result;
		result.x = x + f.x;
		result.y = y + f.y;
		result.z = z + f.z;
		result.w = w + f.w;
		return result;
	}
	float64x4 operator-(const float64x4 f)
	{
		float64x4 result;
		result.x = x - f.x;
		result.y = y - f.y;
		result.z = z - f.z;
		result.w = w - f.w;
		return result;
	}
	float64x4 operator*(const float64 f)
	{
		float64x4 result;
		result.x = x * f;
		result.y = y * f;
		result.z = z * f;
		result.w = w * f;
		return result;
	}
	float64x4 operator/(const float64 f)
	{
		float64x4 result;
		result.x = x / f;
		result.y = y / f;
		result.z = z / f;
		result.w = w / f;
		return result;
	}
	float64  operator*(const float64x4 f)
	{
		float64 result = 0;
		result += x * f.x;
		result += y * f.y;
		result += z * f.z;
		result += w * f.w;
		return result;
	}
	float64x4 operator*(const Matrix m)
	{
		if (m.rows != 4 || m.columns != 4)while (1);
		float64x4 result;
		result.x = x * m.e[0][0] + y * m.e[1][0] + z * m.e[2][0] + w * m.e[3][0];
		result.y = x * m.e[0][1] + y * m.e[1][1] + z * m.e[2][1] + w * m.e[3][1];
		result.z = x * m.e[0][2] + y * m.e[1][2] + z * m.e[2][2] + w * m.e[3][2];
		result.w = x * m.e[0][3] + y * m.e[1][3] + z * m.e[2][3] + w * m.e[3][3];
		return result;
	}
	void Normalize()
	{
		float64 factor = (float64)sqrt((x * x) + (y * y) + (z * z) + (w * w));
		x /= factor;
		y /= factor;
		z /= factor;
		w /= factor;
	}
};
struct float64x3
{
	float64 x, y, z;
	float64x3()
	{
		ZeroMemory(this, sizeof(float64x3));
	}
	float64x3(const float64x3& f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}
	float64x3(float64 _x, float64 _y, float64 _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void operator=(const float64x3 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}
	void operator=(const float64x4 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}
	bool operator==(const float64x3 f)
	{
		if (x != f.x)return false;
		if (y != f.y)return false;
		if (z != f.z)return false;
		return true;
	}

	float64x3 operator+(const float64x3 f)
	{
		float64x3 result;
		result.x = x + f.x;
		result.y = y + f.y;
		result.z = z + f.z;
		return result;
	}
	float64x3 operator-(const float64x3 f)
	{
		float64x3 result;
		result.x = x - f.x;
		result.y = y - f.y;
		result.z = z - f.z;
		return result;
	}
	float64x3 operator*(const float64 f)
	{
		float64x3 result;
		result.x = x * f;
		result.y = y * f;
		result.z = z * f;
		return result;
	}
	float64x3 operator/(const float64 f)
	{
		float64x3 result;
		result.x = x / f;
		result.y = y / f;
		result.z = z / f;
		return result;
	}
	float64 operator*(const float64x3 f)
	{
		float64 result = 0;
		result += x * f.x;
		result += y * f.y;
		result += z * f.z;
		return result;
	}
	float64x3 operator^(const float64x3 f)
	{
		float64x3 result;
		result.x = (y * f.z) - (z * f.y);
		result.y = (z * f.x) - (x * f.z);
		result.z = (x * f.y) - (y * f.x);
		return result;
	}
	float64 Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}
	void Normalize()
	{
		float64 factor = (float64)sqrt((x * x) + (y * y) + (z * z));
		x /= factor;
		y /= factor;
		z /= factor;
	}
};
struct float64x2
{
	float64 x, y;
	float64x2()
	{
		ZeroMemory(this, sizeof(float64x2));
	}
	float64x2(const float64x2& f)
	{
		x = f.x;
		y = f.y;
	}
	float64x2(float64 _x, float64 _y)
	{
		x = _x;
		y = _y;
	}

	void operator=(const float64x4 f)
	{
		x = f.x;
		y = f.y;
	}
	void operator=(const float64x3 f)
	{
		x = f.x;
		y = f.y;
	}
	void operator=(const float64x2 f)
	{
		x = f.x;
		y = f.y;
	}

	float64x2 operator+(const float64x2 f)
	{
		float64x2 result;
		result.x = x + f.x;
		result.y = y + f.y;
		return result;
	}
	float64x2 operator-(const float64x2 f)
	{
		float64x2 result;
		result.x = x - f.x;
		result.y = y - f.y;
		return result;
	}
	float64x2 operator*(const float64 f)
	{
		float64x2 result;
		result.x = x * f;
		result.y = y * f;
		return result;
	}
	float64x2 operator/(const float64 f)
	{
		float64x2 result;
		result.x = x / f;
		result.y = y / f;
		return result;
	}
	float64 operator*(const float64x2 f)
	{
		float64 result = 0;
		result += x * f.x;
		result += y * f.y;
		return result;
	}
	float64 Length()
	{
		return sqrt((x * x) + (y * y));
	}
	void Normalize()
	{
		float64 factor = (float64)sqrt((x * x) + (y * y));
		x /= factor;
		y /= factor;
	}
};

struct float32x4
{
	float32 x, y, z, w;
	float32x4()
	{
		ZeroMemory(this, sizeof(float32x4));
	}
	float32x4(const float32x4& f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
		w = f.w;
	}
	float32x4(float32 _x, float32 _y, float32 _z, float32 _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void operator=(const float32x4 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
		w = f.w;
	}
	float32x4 operator+(const float32x4 f)
	{
		float32x4 result;
		result.x = x + f.x;
		result.y = y + f.y;
		result.z = z + f.z;
		result.w = w + f.w;
		return result;
	}
	float32x4 operator-(const float32x4 f)
	{
		float32x4 result;
		result.x = x - f.x;
		result.y = y - f.y;
		result.z = z - f.z;
		result.w = w - f.w;
		return result;
	}
	float32x4 operator*(const float32 f)
	{
		float32x4 result;
		result.x = x * f;
		result.y = y * f;
		result.z = z * f;
		result.w = w * f;
		return result;
	}
	float32x4 operator/(const float32 f)
	{
		float32x4 result;
		result.x = x / f;
		result.y = y / f;
		result.z = z / f;
		result.w = w / f;
		return result;
	}
	float32  operator*(const float32x4 f)
	{
		float32 result = 0;
		result += x * f.x;
		result += y * f.y;
		result += z * f.z;
		result += w * f.w;
		return result;
	}
	float32x4 operator*(const Matrix m)
	{
		if (m.rows != 4 || m.columns != 4)while (1);
		float32x4 result;
		result.x = x * m.e[0][0] + y * m.e[1][0] + z * m.e[2][0] + w * m.e[3][0];
		result.y = x * m.e[0][1] + y * m.e[1][1] + z * m.e[2][1] + w * m.e[3][1];
		result.z = x * m.e[0][2] + y * m.e[1][2] + z * m.e[2][2] + w * m.e[3][2];
		result.w = x * m.e[0][3] + y * m.e[1][3] + z * m.e[2][3] + w * m.e[3][3];
		return result;
	}
	void Normalize()
	{
		float32 factor = (float32)sqrt((x * x) + (y * y) + (z * z) + (w * w));
		x /= factor;
		y /= factor;
		z /= factor;
		w /= factor;
	}
};
struct float32x3
{
	float32 x, y, z;
	float32x3()
	{
		ZeroMemory(this, sizeof(float32x3));
	}
	float32x3(const float32x3& f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}
	float32x3(float32 _x, float32 _y, float32 _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void operator=(const float32x3 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}
	void operator=(const float32x4 f)
	{
		x = f.x;
		y = f.y;
		z = f.z;
	}

	float32x3 operator+(const float32x3 f)
	{
		float32x3 result;
		result.x = x + f.x;
		result.y = y + f.y;
		result.z = z + f.z;
		return result;
	}
	float32x3 operator-(const float32x3 f)
	{
		float32x3 result;
		result.x = x - f.x;
		result.y = y - f.y;
		result.z = z - f.z;
		return result;
	}
	float32x3 operator*(const float32 f)
	{
		float32x3 result;
		result.x = x * f;
		result.y = y * f;
		result.z = z * f;
		return result;
	}
	float32x3 operator/(const float32 f)
	{
		float32x3 result;
		result.x = x / f;
		result.y = y / f;
		result.z = z / f;
		return result;
	}
	float32 operator*(const float32x3 f)
	{
		float32 result = 0;
		result += x * f.x;
		result += y * f.y;
		result += z * f.z;
		return result;
	}
	float32x3 operator^(const float32x3 f)
	{
		float32x3 result;
		result.x = (y * f.z) - (z * f.y);
		result.y = (z * f.x) - (x * f.z);
		result.z = (x * f.y) - (y * f.x);
		return result;
	}
	float32 Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}
	void Normalize()
	{
		float32 factor = (float32)sqrt((x * x) + (y * y) + (z * z));
		x /= factor;
		y /= factor;
		z /= factor;
	}
};
struct float32x2
{
	float32 x, y;
	float32x2()
	{
		ZeroMemory(this, sizeof(float32x2));
	}
	float32x2(const float32x2& f)
	{
		x = f.x;
		y = f.y;
	}
	float32x2(float32 _x, float32 _y)
	{
		x = _x;
		y = _y;
	}

	void operator=(const float32x4 f)
	{
		x = f.x;
		y = f.y;
	}
	void operator=(const float32x3 f)
	{
		x = f.x;
		y = f.y;
	}
	void operator=(const float32x2 f)
	{
		x = f.x;
		y = f.y;
	}

	float32x2 operator+(const float32x2 f)
	{
		float32x2 result;
		result.x = x + f.x;
		result.y = y + f.y;
		return result;
	}
	float32x2 operator-(const float32x2 f)
	{
		float32x2 result;
		result.x = x - f.x;
		result.y = y - f.y;
		return result;
	}
	float32x2 operator*(const float32 f)
	{
		float32x2 result;
		result.x = x * f;
		result.y = y * f;
		return result;
	}
	float32x2 operator/(const float32 f)
	{
		float32x2 result;
		result.x = x / f;
		result.y = y / f;
		return result;
	}
	float32 operator*(const float32x2 f)
	{
		float32 result = 0;
		result += x * f.x;
		result += y * f.y;
		return result;
	}
	float32 Length()
	{
		return sqrt((x * x) + (y * y));
	}
	void Normalize()
	{
		float32 factor = (float32)sqrt((x * x) + (y * y));
		x /= factor;
		y /= factor;
	}
};

float64 Dot(float64x3 v1, float64x3 v2)
{
	return v1.x*v2.x + v1.y * v2.y + v1.z * v2.z;
}
float64x3 Cross(float64x3 v1, float64x3 v2)
{
	return float64x3
	(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

Matrix __inline GenerateEyeMatrix(float32 posx, float32 posy, float32 posz, float32 lookx, float32 looky, float32 lookz, float32 upx, float32 upy, float32 upz)
{
	float3 eye = float3(posx, posy, posz);
	float3 at = float3(lookx, looky, lookz);
	float3 up = float3(upx, upy, upz);
	float3 zaxis = at - eye;
	zaxis.Normalize();
	float3 xaxis = up ^ zaxis;
	xaxis.Normalize();
	float3 yaxis = zaxis ^ xaxis;
	yaxis.Normalize();

	Matrix result(4, 4);
	result.R0(xaxis.x, yaxis.x, zaxis.x, 0);
	result.R1(xaxis.y, yaxis.y, zaxis.y, 0);
	result.R2(xaxis.z, yaxis.z, zaxis.z, 0);
	result.R3(-(xaxis * float3(posx, posy, posz)), -(yaxis * float3(posx, posy, posz)), -(zaxis * float3(posx, posy, posz)), 1);
	return result;
}
Matrix __inline GenerateProjectionMatrixPrespective(float32 _zoom, float32 _ratio, float32 _near, float32 _far)
{
	Matrix result(4, 4);
	result.R0(1 / (_ratio * tanf(_zoom / 2)), 0, 0, 0);
	result.R1(0, 1 / (tanf(_zoom / 2)), 0, 0);
	result.R2(0, 0, _far / (_far - _near), 1);
	result.R3(0, 0, -(_near * _far) / (_far - _near), 0);
	return result;
}
Matrix __inline GenerateProjectionMatrixOrthographic(float32 _width, float32 _height, float32 _near, float32 _far)
{
	Matrix result(4, 4);
	result.R0(2 / _width, 0, 0, 0);
	result.R1(0, 2 / _height, 0, 0);
	result.R2(0, 0, 1 / (_far - _near), 0);
	result.R3(0, 0, -_near / (_far - _near), 1);
	return result;
}
float32 DistanceSquared(float32* vector1, float32* vector2)
{
	return (*vector2 - *vector1) * (*vector2 - *vector1);
}
float32 DistanceSquared(float2* vector1, float2* vector2)
{
	return (((vector2->x - vector1->x) * (vector2->x - vector1->x)) + ((vector2->y - vector1->y) * (vector2->y - vector1->y)));
}
float32 DistanceSquared(float3* vector1, float3* vector2)
{
	return (((vector2->x - vector1->x) * (vector2->x - vector1->x)) + ((vector2->y - vector1->y) * (vector2->y - vector1->y)) + ((vector2->z - vector1->z) * (vector2->z - vector1->z)));
}
float32 DistanceSquared(float4* vector1, float4* vector2)
{
	return (((vector2->x - vector1->x) * (vector2->x - vector1->x)) + ((vector2->y - vector1->y) * (vector2->y - vector1->y)) + ((vector2->z - vector1->z) * (vector2->z - vector1->z)) + ((vector2->w - vector1->w) * (vector2->w - vector1->w)));
}
float32 Distance(float32 vector1, float32 vector2)
{
	return abs(vector2 - vector1);
}
float32 Distance(float2 vector1, float2 vector2)
{
	return sqrt(((vector2.x - vector1.x) * (vector2.x - vector1.x)) + ((vector2.y - vector1.y) * (vector2.y - vector1.y)));
}
float32 Distance(float3 vector1, float3 vector2)
{
	return sqrt(((vector2.x - vector1.x) * (vector2.x - vector1.x)) + ((vector2.y - vector1.y) * (vector2.y - vector1.y)) + ((vector2.z - vector1.z) * (vector2.z - vector1.z)));
}
float32 Distance(float4 vector1, float4 vector2)
{
	return sqrt(((vector2.x - vector1.x) * (vector2.x - vector1.x)) + ((vector2.y - vector1.y) * (vector2.y - vector1.y)) + ((vector2.z - vector1.z) * (vector2.z - vector1.z)) + ((vector2.w - vector1.w) * (vector2.w - vector1.w)));
}
float64 Distance(float64 vector1, float64 vector2)
{
	return abs(vector2 - vector1);
}
float64 Distance(float64x2 vector1, float64x2 vector2)
{
	return sqrt(((vector2.x - vector1.x) * (vector2.x - vector1.x)) + ((vector2.y - vector1.y) * (vector2.y - vector1.y)));
}
float64 Distance(float64x3 vector1, float64x3 vector2)
{
	return sqrt(((vector2.x - vector1.x) * (vector2.x - vector1.x)) + ((vector2.y - vector1.y) * (vector2.y - vector1.y)) + ((vector2.z - vector1.z) * (vector2.z - vector1.z)));
}
float64 Distance(float64x4 vector1, float64x4 vector2)
{
	return sqrt(((vector2.x - vector1.x) * (vector2.x - vector1.x)) + ((vector2.y - vector1.y) * (vector2.y - vector1.y)) + ((vector2.z - vector1.z) * (vector2.z - vector1.z)) + ((vector2.w - vector1.w) * (vector2.w - vector1.w)));
}

float64 DistanceOfaPointFromLine(float64x2 P, float64x2 L1, float64x2 L2)
{
	float64 A = -((L2.y - L1.y));
	float64 B = -((L2.x - L1.x));
	float64 C = -(L1.x * (L2.y - L1.y)) - (L1.y * (L2.x - L1.x));
	return abs((A * P.x + B * P.y + C) / sqrt(A * A + B * B));
}
float64 DistanceOfaPointFromLine(float64x3 P, float64x3 L1, float64x3 L2)
{
	return Distance(Cross(P - L1, P - L2), float64x3(0, 0, 0)) / Distance(L2 - L1, float64x3(0, 0, 0));
}

struct Kinematics
{
	float64 S(float64 u, float64 v, float64 a)
	{
		return ((v * v) - (u * u)) / (2.0 * a);
	}
	float64 U(float64 v, float64 a, float64 S)
	{
		return sqrt((v * v) - (2.0 * a * S));
	}
	float64 V(float64 u, float64 a, float64 S)
	{
		return sqrt((u * u) + (2.0 * a * S));
	}
	float64 T(float64 u, float64 v, float64 a)
	{
		return ((v - u) / a);
	}
	float64 T(float64 S, float64 V)
	{
		return (S / V);
	}
	float64 Tp(float64 u, float64 a, float64 s)
	{
		return ((-u + sqrt(u * u + 2 * a * s)) / a);
	}
	float64 Tn(float64 u, float64 a, float64 s)
	{
		return ((-u - sqrt(u * u + 2 * a * s)) / a);
	}
	float64 Intersection(float64 u, float64 v, float64 a, float64 d, float64 L)
	{
		return ((v * v) - (u * u) - (2.0 * d * L)) / ((2.0 * a) - (2.0 * d));
	}
};