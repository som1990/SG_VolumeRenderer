#ifndef matrixField_h__
#define matrixField_h__

#include "VolumeField.h"

namespace vol
{
	class MatrixFieldAdd : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldAdd(VolumeMatrixPtr f, VolumeMatrixPtr g) :
			elem1(f), elem2(g) {}

		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) + elem2->eval(p);
		}

	private:
		VolumeMatrixPtr elem1;
		VolumeMatrixPtr elem2;
	};

	class MatrixFieldSub : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldSub(VolumeMatrixPtr f, VolumeMatrixPtr g) :
			elem1(f), elem2(g) {}

		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) - elem2->eval(p);
		}

	private:
		VolumeMatrixPtr elem1;
		VolumeMatrixPtr elem2;
	};

	class MatrixFieldMinus : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldMinus(VolumeMatrixPtr f) :
			elem1(f) {}
		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return -elem1->eval(p);
		}
	private:
		VolumeMatrixPtr elem1;
	};

	class MatrixFieldMult : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldMult(VolumeMatrixPtr f, VolumeMatrixPtr g) :
			elem1(f), elem2(g) {}

		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) * elem2->eval(p);
		}

	private:
		VolumeMatrixPtr elem1;
		VolumeMatrixPtr elem2;
	};





	class MatrixFieldVectorRMult : public VolumeField<lux::Vector>
	{
	public:
		MatrixFieldVectorRMult(VolumeMatrixPtr f, VolumeVectorPtr g) :
			elem1(f), elem2(g) {}

		const lux::Vector eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) * elem2->eval(p);
		}

	private:
		VolumeMatrixPtr elem1;
		VolumeVectorPtr elem2;
	};

	class MatrixFieldVectorLMult : public VolumeField<lux::Vector>
	{
	public:
		MatrixFieldVectorLMult(VolumeVectorPtr f, VolumeMatrixPtr g) :
			elem1(f), elem2(g) {}

		const lux::Vector eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) * elem2->eval(p);
		}

	private:
		VolumeVectorPtr elem1;
		VolumeMatrixPtr elem2;
		
	};

	class MatrixFieldScalarRMult : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldScalarRMult(VolumeMatrixPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}
		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) * elem2->eval(p);
		}
	private:
		VolumeMatrixPtr elem1;
		VolumeFloatPtr elem2;
	};

	class MatrixFieldScalarLMult : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldScalarLMult(VolumeFloatPtr f, VolumeMatrixPtr g) :
			elem1(f), elem2(g) {}
		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) * elem2->eval(p);
		}
	private:
		VolumeFloatPtr elem1;
		VolumeMatrixPtr elem2;
	};

	class MatrixFieldScalarDiv : public VolumeField<lux::Matrix>
	{
	public:
		MatrixFieldScalarDiv(VolumeMatrixPtr f, VolumeFloatPtr g) :
			elem1(f), elem2(g) {}
		const lux::Matrix eval(const lux::Vector& p) const override
		{
			return elem1->eval(p) / elem2->eval(p);
		}
	private:
		VolumeMatrixPtr elem1;
		VolumeFloatPtr elem2;
	};

	inline const MatrixFieldAdd operator+ (VolumeField<lux::Matrix> &f, VolumeField<lux::Matrix> &g)
	{
		return MatrixFieldAdd(&f, &g);
	}

	inline const MatrixFieldSub operator- (VolumeField<lux::Matrix> &f, VolumeField<lux::Matrix> &g)
	{
		return MatrixFieldSub(&f, &g);
	}

	inline const MatrixFieldMinus operator- (VolumeField <lux::Matrix> &f)
	{
		return MatrixFieldMinus(&f);
	}

	inline const MatrixFieldMult operator* (VolumeField<lux::Matrix> &f, VolumeField<lux::Matrix> &g)
	{
		return MatrixFieldMult(&f, &g);
	}

	inline const MatrixFieldVectorRMult operator* (VolumeField<lux::Matrix> &f, VolumeField<lux::Vector> &g)
	{
		return MatrixFieldVectorRMult(&f, &g);
	}

	inline const MatrixFieldVectorLMult operator* (VolumeField<lux::Vector> &f, VolumeField<lux::Matrix> &g)
	{
		return MatrixFieldVectorLMult(&f, &g);
	}

	inline const MatrixFieldScalarRMult operator* (VolumeField<lux::Matrix> &f, VolumeField<float> &g)
	{
		return MatrixFieldScalarRMult(&f, &g);
	}

	inline const MatrixFieldScalarLMult operator* (VolumeField<float> &f, VolumeField<lux::Matrix> &g)
	{
		return MatrixFieldScalarLMult(&f, &g);
	}

	inline const MatrixFieldScalarDiv operator/ (VolumeField<lux::Matrix> &f, VolumeField<float> &g)
	{
		return MatrixFieldScalarDiv(&f, &g);
	}
}
#endif // matrixField_h__
