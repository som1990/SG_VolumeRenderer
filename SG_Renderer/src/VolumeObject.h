#ifndef VolumeObject_h__
#define VolumeObject_h__
#include "Fields.h"
#include "AABBox.h"

namespace obj
{
	class VolumeObject
	{
	public:
		VolumeObject(vol::VolumeFloatPtr scalarField, vol::VolumeColorPtr colorField, vol::VolumeVectorPtr vectorField, vol::VolumeMatrixPtr matrixField) :
			sField(scalarField), cField(colorField), vField(vectorField), mField(matrixField) {}

		const vol::VolumeFloatPtr &getScalarField() const { return sField; }
		const vol::VolumeColorPtr &getColorField() const { return cField; }
		const bool getHit() const { return hit; }
		void updateObject(vol::VolumeFloatPtr scalarField, vol::VolumeColorPtr colorField, vol::VolumeVectorPtr vectorField, vol::VolumeMatrixPtr matrixField)
		{
			sField = scalarField;  
			cField = colorField; 
			vField = vectorField; 
			mField = matrixField;
		}
		void setHit(bool _hit) { hit = _hit; }
		void setBBox(const lux::Vector &llc, const lux::Vector &urc) {
			box = AABBox(llc, urc);
			has_bbox = true;
		}

	private:
		vol::VolumeFloatPtr sField;
		vol::VolumeColorPtr cField;
		vol::VolumeVectorPtr vField;
		vol::VolumeMatrixPtr mField;
		AABBox box;
		bool hit = true;
		bool has_bbox = false;
	};

}

#endif // VolumeObject_h__