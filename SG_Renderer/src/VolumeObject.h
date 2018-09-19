#ifndef Header_h__
#define Header_h__
#include "Fields.h"

namespace obj
{
	class VolumeObject
	{
	public:
		VolumeObject(vol::VolumeFloatPtr scalarField, vol::VolumeColorPtr colorField, vol::VolumeVectorPtr vectorField, vol::VolumeMatrixPtr matrixField) :
			sField(scalarField), cField(colorField), vField(vectorField), mField(matrixField) {}

		const vol::VolumeFloatPtr getScalarField() const { return sField; }
		const vol::VolumeColorPtr getColorField() const { return cField; }
	private:
		vol::VolumeFloatPtr sField;
		vol::VolumeColorPtr cField;
		vol::VolumeVectorPtr vField;
		vol::VolumeMatrixPtr mField;
	};


}



#endif // Header_h__