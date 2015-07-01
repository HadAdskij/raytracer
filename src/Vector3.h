#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3
{
	public:
		float x, y, z;

		Vector3() {};
		Vector3(float x, float y, float z);
		Vector3 operator + (const Vector3 &v) const;
		Vector3 operator - (const Vector3 &v) const;
		Vector3 operator * (const float t) const;
		float operator * (const Vector3 &v) const;
		bool operator == (const Vector3 &v) const;
		Vector3 Cross(const Vector3 &v) const;

		static Vector3 Zero() { return Vector3(0,0,0); }

		float SquareNorm() const;
		float Norm() const;
		void Normalize();
};

#endif
