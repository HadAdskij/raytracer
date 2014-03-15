#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3
{
	public:
		float x, y, z;

		Vector3() {};
		Vector3(float x, float y, float z);
		Vector3 operator + (const Vector3 &v);
		Vector3 operator - (const Vector3 &v);
		Vector3 operator * (const float t);
		float operator * (const Vector3 &v);
		bool operator == (const Vector3 &v);
		Vector3 Cross(const Vector3 &v);

		static Vector3 Zero() { return Vector3(0,0,0); }

		float SquareNorm();
		float Norm();
		void Normalize();
};

#endif
