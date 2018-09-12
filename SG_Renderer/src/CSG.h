#ifndef CSG_h__
#define CSG_h__
#include <algorithm>



namespace vol
{
	class ScalarFieldUnion: public VolumeField<float>
	{
	public:
		ScalarFieldUnion(VolumeFloatPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}
		
		const float eval(const lux::Vector& p) const override
		{
			float val{};
			val = std::max(elem1->eval(p), elem2->eval(p));
			return val;
		}

	private:
		VolumeFloatPtr elem1;
		VolumeFloatPtr elem2;

	};

	class ScalarFieldIntersection : public VolumeField<float>
	{
	public:
		ScalarFieldIntersection(VolumeFloatPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}

		const float eval(const lux::Vector& p) const override
		{
			float val{};
			val = std::min(elem1->eval(p), elem2->eval(p));
			return val;
		}

	private:
		VolumeFloatPtr elem1;
		VolumeFloatPtr elem2;

	};

	class ScalarFieldCutout : public VolumeField<float>
	{
	public:
		ScalarFieldCutout(VolumeField<float>* f, VolumeField<float>* g) :
			elem1(f), elem2(g) {}

		const float eval(const lux::Vector& p) const override
		{
			float val{};
			val = std::min(elem1->eval(p), -elem2->eval(p));
			return val;
		}

	private:
		VolumeField<float>* elem1;
		VolumeField<float>* elem2;

	};

	class ScalarFieldShell : public VolumeField<float>
	{
	public:
		ScalarFieldShell(VolumeFloatPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}

		const float eval(const lux::Vector& p) const override
		{
			float val{};
			VolumeField<float> v1 = *elem1 + *elem2;
			VolumeField<float> v2 = *elem1 - *elem2;
			VolumeField<float> test = ScalarFieldCutout(&v1, &v2);
			val = test.eval(p);
			return val;
		}

	private:
		VolumeFloatPtr elem1;
		VolumeFloatPtr elem2;

	};
}


#endif // CSG_h__