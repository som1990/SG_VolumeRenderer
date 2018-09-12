#ifndef colorField_h__
#define colorField_h__
#include "VolumeField.h"

namespace vol
{
	class ColorFieldAdd : public VolumeField<lux::Color>
	{
	public:
		ColorFieldAdd(VolumeColorPtr f, VolumeColorPtr g) :
			elem1(f), elem2(g) {}
		const lux::Color eval(const lux::Vector &p) const override
		{
			return elem1->eval(p) + elem2->eval(p);
		}
	private:
		VolumeColorPtr elem1;
		VolumeColorPtr elem2;

	};
	class ColorFieldMult : public VolumeField<lux::Color>
	{
	public:
		ColorFieldMult(VolumeColorPtr f, VolumeColorPtr g) :
			elem1(f), elem2(g) {}
		const lux::Color eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) * elem2->eval(p);
		}
	private:
		VolumeColorPtr elem1;
		VolumeColorPtr elem2;
	};

	class ColorFieldScalarMult : public VolumeField<lux::Color>
	{
	public:
		ColorFieldScalarMult(VolumeColorPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}
		const lux::Color eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) * elem2->eval(p);
		}
	private:
		VolumeColorPtr elem1;
		VolumeFloatPtr elem2;
	};
	
	class ColorFieldScalarDiv : public VolumeField<lux::Color>
	{
	public:
		ColorFieldScalarDiv(VolumeColorPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}
		const lux::Color eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) / elem2->eval(p);
		}
	private:
		VolumeColorPtr elem1;
		VolumeFloatPtr elem2;
	};

	class ColorFieldSub : public VolumeField<lux::Color>
	{
	public:
		ColorFieldSub(VolumeColorPtr f, VolumeColorPtr g) :
			elem1(f), elem2(g) {}
		const lux::Color eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) - elem2->eval(p);
		}
	private:
		VolumeColorPtr elem1;
		VolumeColorPtr elem2;
	};
	class ColorFieldMinus : public VolumeField<lux::Color>
	{
	public:
		ColorFieldMinus(VolumeColorPtr f) :
			elem1(f) {}
		const lux::Color eval(const lux::Vector& p) const override
		{
			return -elem1->eval(p);
		}
	private:
		VolumeColorPtr elem1;

	};
	 
	inline const ColorFieldAdd operator+ (VolumeField<lux::Color> &f, VolumeField<lux::Color> &g)
	{
		return ColorFieldAdd(&f, &g);
	}

	inline const ColorFieldSub operator- (VolumeField <lux::Color> &f, VolumeField<lux::Color> &g)
	{
		return ColorFieldSub(&f, &g);
	}
	inline const ColorFieldMinus operator- (VolumeField<lux::Color> &f)
	{
		return ColorFieldMinus(&f);
	}

	inline const ColorFieldMult operator* (VolumeField<lux::Color> &f, VolumeField<lux::Color> &g)
	{
		return ColorFieldMult(&f, &g);
	}
	inline const ColorFieldScalarMult operator* (VolumeField<lux::Color> &f, VolumeField<float> &g)
	{
		return ColorFieldScalarMult(&f, &g);
	}
	inline const ColorFieldScalarDiv operator/ (VolumeField<lux::Color> &f, VolumeField<float> &g)
	{
		return ColorFieldScalarDiv(&f, &g);
	}
}



#endif // colorField_h__