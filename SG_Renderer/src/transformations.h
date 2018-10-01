#ifndef transformations_h__
#define transformations_h__

#include "Fields.h"
#include <cmath>

namespace vol
{

	inline lux::Vector calcFieldRotation(const lux::Vector &point, const lux::Vector &rotationVec)
	{
		float angle = rotationVec.magnitude();
		lux::Vector axis = rotationVec.unitvector();
		float A = std::cos(angle);
		float B = (axis*point)*(1 - std::cos(angle));
		float C = std::sin(angle);

		lux::Vector pRotated = point*A + axis*B + (axis^point)*C;
		return pRotated;

	}

	/*
	template <typename V, typename U>
	class Translate :VolumeField<U>
	{	
	public:
		typedef U volumeDataType;
		typedef V volumePtrType;
		Translate( volumePtrType field, lux::Vector val) :
			elem(field), x(val) {}
		const volumeDataType eval(const lux::Vector& p) const override
		{
			return elem->eval(p - x);
		}

	private:
		volumePtrType elem;
		lux::Vector x;
	};
	*/

	class ScalarFieldTranslate : public VolumeField<float>
	{
	public:
		ScalarFieldTranslate(VolumeFloatPtr field, lux::Vector val) :
			elem(field), x(val) {}
		const float eval(const lux::Vector& p) const override
		{
			return elem->eval(p - x);
		}
	private:
		VolumeFloatPtr elem;
		lux::Vector x;
	};

	class VectorFieldTranslate : public VolumeField<lux::Vector>
	{
	public:
		VectorFieldTranslate(VolumeVectorPtr field, lux::Vector val) :
			elem(field), x(val) {}
		const lux::Vector eval(const lux::Vector& p) const override
		{
			return elem->eval(p - x);
		}
	private:
		VolumeVectorPtr elem;
		lux::Vector x;
	};

	class MatrixFieldTranslate : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldTranslate(VolumeMatrixPtr field, lux::Vector val) :
			elem(field), x(val) {}
		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return elem->eval(p - x);
		}
	private:
		VolumeMatrixPtr elem;
		lux::Vector x;
	};


	class ScalarFieldScale : public VolumeField<float>
	{
	public:
		ScalarFieldScale(VolumeFloatPtr field, float scale) :
			elem(field), s(scale) {}
		const float eval(const lux::Vector& p) const override
		{
			return elem->eval(p / s);
		}
	private:
		VolumeFloatPtr elem;
		float s;
	};

	class ColorFieldScale : VolumeField<lux::Color>
	{
	public:
		ColorFieldScale(VolumeColorPtr field, float scale) :
			elem(field), s(scale) {}
		const lux::Color eval(const lux::Vector& p) const override
		{
			return elem->eval(p / s);
		}
	private:
		VolumeColorPtr elem;
		float s;
	};

	class VectorFieldScale : VolumeField<lux::Vector>
	{
	public:
		VectorFieldScale(VolumeVectorPtr field, float scale) :
			elem(field), s(scale) {}
		const lux::Vector eval(const lux::Vector& p) const override
		{
			return (elem->eval(p / s))*s;
		}
	private:
		VolumeVectorPtr elem;
		float s;
	};

	class MatrixFieldScale : VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldScale(VolumeMatrixPtr field, float scale):
			elem(field), s(scale){}
		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return (elem->eval(p / s))*(s*s);
		}
	private:
		VolumeMatrixPtr elem;
		float s;
	};

	class ScalarFieldRotate : public VolumeField<float>
	{
	public:
		ScalarFieldRotate(VolumeFloatPtr field, lux::Vector alphaVec) :
			elem(field), aVec(alphaVec) {}
		const float eval(const lux::Vector& p) const override
		{
			lux::Vector pInvRotated = calcFieldRotation(p, -aVec);
			return elem->eval(pInvRotated);
		}
	private:
		VolumeFloatPtr elem;
		lux::Vector aVec;
	};

	class ColorFieldRotate : public VolumeField<lux::Color>
	{
	public:
		ColorFieldRotate(VolumeColorPtr field, lux::Vector alphaVec) :
			elem(field), aVec(alphaVec) {}
		const lux::Color eval(const lux::Vector& p) const override
		{
			lux::Vector pInvRotated = calcFieldRotation(p, -aVec);
			return elem->eval(pInvRotated);
		}
	private:
		VolumeColorPtr elem;
		lux::Vector aVec;
	};

	class VectorFieldRotate : public VolumeField<lux::Vector>
	{
	public:
		VectorFieldRotate(VolumeVectorPtr field, lux::Vector alphaVec) :
			elem(field), aVec(alphaVec) {}
		const lux::Vector eval(const lux::Vector& p) const override
		{
			lux::Vector pInvRotated = calcFieldRotation(p, -aVec);
			lux::Vector v_prime = elem->eval(pInvRotated);
			return calcFieldRotation(v_prime, aVec);
		}
	private:
		VolumeVectorPtr elem;
		lux::Vector aVec;
	};

	class MatrixFieldRotate : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldRotate(VolumeMatrixPtr field, lux::Vector alphaVec) :
			elem(field), aVec(alphaVec) {}
		const lux::Matrix eval(const lux::Vector& p) const override
		{
			lux::Vector pInvRotated = calcFieldRotation(p, -aVec);
			lux::Matrix m_prime = elem->eval(pInvRotated);
			lux::Matrix R = lux::rotation(aVec.unitvector(), aVec.magnitude());
			lux::Matrix R_T = R.transpose();
			return R * m_prime * R_T;
		}
	private:
		VolumeMatrixPtr elem;
		lux::Vector aVec;
	};
}


#endif // transformations_h__