#ifndef colorField_h__
#define colorField_h__
#include "VolumeField.h"

static float mask(const float &a)
{
	if (a > 0.0)
		return 1;
	else
		return 0;
}

static float clamp(const float &a)
{
	if (a < 0.0)
		return 0.0f;
	else if (a > 1.0)
		return 1.0f;
	else
		return a;
}

namespace vol
{
	class SolidColorField : public VolumeField<lux::Color>
	{
	public:
		SolidColorField(lux::Color* c) :
			elem1(c) {}
		const lux::Color eval(const lux::Vector &p) const override
		{
			return *elem1;
		}
	private:
		lux::Color* elem1;
	};

	class MaskColorFields : public VolumeField<lux::Color>
	{
	public:
		MaskColorFields(VolumeColorPtr color1, VolumeFloatPtr f, VolumeColorPtr color2, VolumeFloatPtr g) :
			elem1(color1), f1(f), elem2(color2), f2(g) {}

		
		const lux::Color eval(const lux::Vector &p) const override
		{
			return elem1->eval(p)*mask(f1->eval(p)) + elem2->eval(p)*mask(f2->eval(p));
		}
	private:
		VolumeColorPtr elem1;
		VolumeColorPtr elem2;
		VolumeFloatPtr f1;
		VolumeFloatPtr f2;
	};

	class ClampColorFields : public VolumeField<lux::Color>
	{
	public:
		ClampColorFields(VolumeColorPtr c1, VolumeFloatPtr f, VolumeColorPtr c2, VolumeFloatPtr g) :
			elem1(c1), f1(f), elem2(c2), f2(g) {}


		const lux::Color eval(const lux::Vector &p) const override
		{
			return elem1->eval(p)*clamp(f1->eval(p)) + elem2->eval(p)*clamp(f2->eval(p));
		}
	private:
		VolumeColorPtr elem1;
		VolumeColorPtr elem2;
		VolumeFloatPtr f1;
		VolumeFloatPtr f2;
	};

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