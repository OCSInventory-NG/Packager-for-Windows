#pragma once

class Flate
{
public:
	Flate()
	{
	}

	void Inflate(ISequentialStream* pOutput, ISequentialStream* pInput);
	void Deflate(ISequentialStream* pOutput, ISequentialStream* pInput);

	void Inflate(CFile* pOutput, CFile* pInput);
	void Deflate(CFile* pOutput, CFile* pInput);

	BOOL	Compress(CByteArray& dst, const CByteArray& src)
	{
		return Compress(dst, src.GetData(), src.GetSize());
	}

	BOOL	Compress(CByteArray& dst, const BYTE* src, UINT srcLen);

	BOOL	Uncompress(CByteArray& dst, const CByteArray& src)
	{
		return Uncompress(dst, src.GetData(), src.GetSize());
	}

	BOOL	Uncompress(CByteArray& dst, const BYTE* src, UINT srcLen);
};

