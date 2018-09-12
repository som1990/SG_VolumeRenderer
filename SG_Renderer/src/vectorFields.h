#ifndef vectorFields_h__
#define vectorFields_h__

#include "VolumeField.h"
#include <cmath>
namespace vol
{
	class VectorFieldAdd : public VolumeField<lux::Vector>
	{
	public:
		VectorFieldAdd(VolumeVectorPtr f, VolumeVectorPtr g) :
			elem1(f), elem2(g) {}

		const lux::Vector eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) + elem2->eval(p);
		}

	private:
		VolumeVectorPtr elem1;
		VolumeVectorPtr elem2;

	};

	class VectorFieldSub: public VolumeField<lux::Vector>
	{
	public:
		VectorFieldSub(VolumeVectorPtr f, VolumeVectorPtr g) :
			elem1(f), elem2(g) {}
		const lux::Vector eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) - elem2->eval(p);
		}
	private:
		VolumeVectorPtr elem1;
		VolumeVectorPtr elem2;
	};

	class VectorFieldMinus : public VolumeField<lux::Vector>
	{
	public:
		VectorFieldMinus(VolumeVectorPtr f) :
			elem1(f) {}
		const lux::Vector eval(const lux::Vector& p) const override
		{
			return -elem1->eval(p);
		}
	private:
		VolumeVectorPtr elem1;
	};

	class VectorFieldScalarMult : public VolumeField<lux::Vector>
	{
	public:
		VectorFieldScalarMult(VolumeVectorPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}
		const lux::Vector eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) * elem2->eval(p);
		}
	private:
		VolumeVectorPtr elem1;
		VolumeFloatPtr elem2;
	};

	class VectorFieldScalarDiv : public VolumeField<lux::Vector>
	{
	public:
		VectorFieldScalarDiv(VolumeVectorPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}
		const lux::Vector eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) / elem2->eval(p);
		}
	private:
		VolumeVectorPtr elem1;
		VolumeFloatPtr elem2;
	};

	class VectorFieldDot : public VolumeField<float>
	{
	public:
		VectorFieldDot(VolumeVectorPtr f, VolumeVectorPtr g) :
			elem1(f), elem2(g) {}
		const float eval(const lux::Vector& p) const override
		{
			return elem1->eval(p)*elem2->eval(p);
		}

	private:
		VolumeVectorPtr elem1;
		VolumeVectorPtr elem2;
	};

	class VectorFieldCross : public VolumeField<lux::Vector>
	{
	public:
		VectorFieldCross(VolumeVectorPtr f, VolumeVectorPtr g) :
			elem1(f), elem2(g) {}
		const lux::Vector eval(const lux::Vector& p) const override
		{
			return elem1->eval(p)^elem2->eval(p);
		}
	private:
		VolumeVectorPtr elem1;
		VolumeVectorPtr elem2;
	};
	
	class VectorFieldOuterProd : public VolumeField<lux::Matrix>
	{
	public:
		VectorFieldOuterProd(VolumeVectorPtr f, VolumeVectorPtr g) :
			elem1(f), elem2(g) {}
		const lux::Matrix eval(const lux::Vector& p)const override
		{
			return elem1->eval(p) & elem2->eval(p);

		}

	private:
		VolumeVectorPtr elem1;
		VolumeVectorPtr elem2;
	};

	//Inline Operator Overloads

	inline const VectorFieldAdd operator+(VolumeField<lux::Vector> &f, VolumeField<lux::Vector> &g)
	{
		return VectorFieldAdd(&f, &g);
	}

	inline const VectorFieldSub operator- (VolumeField<lux::Vector> &f, VolumeField<lux::Vector> &g)
	{
		return VectorFieldSub(&f, &g);
	}
	inline const VectorFieldMinus operator- (VolumeField <lux::Vector> &f)
	{
		return VectorFieldMinus(&f);
	}

	inline const VectorFieldScalarMult operator* (VolumeField<lux::Vector> &f, VolumeField<float> &g)
	{
		return VectorFieldScalarMult(&f, &g);
	}

	inline const VectorFieldScalarDiv operator/ (VolumeField<lux::Vector> &f, VolumeField<float> &g)
	{
		return VectorFieldScalarDiv(&f, &g);
	}

	inline const VectorFieldDot operator* (VolumeField<lux::Vector> &f, VolumeField<lux::Vector>&g)
	{
		return VectorFieldDot(&f, &g);
	}

	inline const VectorFieldCross operator^ (VolumeField<lux::Vector> &f, VolumeField<lux::Vector>&g)
	{
		return VectorFieldCross(&f, &g);
	}

	inline const VectorFieldOuterProd operator& (VolumeField<lux::Vector> &f, VolumeField<lux::Vector>&g)
	{
		return VectorFieldOuterProd(&f, &g);
	}
}
#endif // vectorFields_h__
