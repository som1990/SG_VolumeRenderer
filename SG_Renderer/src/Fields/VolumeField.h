#ifndef VolumeField_h__
#define VolumeField_h__

#include "luxMath.h"

namespace vol {

	template <typename U>
	struct GradType
	{
		typedef int GType;
	};

	template<>
	struct GradType<float>
	{
		typedef lux::Vector GType;
	};
	template <>
	struct GradType<lux::Vector>
	{
		typedef lux::Matrix GType;
	};


	template<typename U>
	class VolumeField
	{
	public:
		VolumeField(){}
		virtual ~VolumeField() {}

		typedef U volumeDataType;
		typedef typename GradType<U>::GType volumeGradType;

		virtual const volumeDataType eval(const lux::Vector& P) const { volumeDataType base{}; return base; }
		virtual const volumeGradType grad(const lux::Vector& P) const { volumeGradType base{}; return base; }

		//virtual const volumeDataType operator+(volumeDataType) const{ volumeDataType base{}; return base; }
	};
	
	typedef VolumeField<float>* VolumeFloatPtr;
	typedef VolumeField<lux::Color>* VolumeColorPtr;
	typedef VolumeField<lux::Vector>* VolumeVectorPtr;
	typedef VolumeField<lux::Matrix>* VolumeMatrixPtr;
}
#endif // VolumeField_h__
