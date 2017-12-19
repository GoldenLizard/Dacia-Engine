#pragma once

#include "../Definitions.hpp"

namespace dmath
{
	namespace color
	{
		enum class Format : byte
		{
			MONOCHROME,
			RGB332,
			RGB565,
			RGB888,
			YUV888,
			RGBA8888,
			CYMK8888,
		};

		struct Color
		{
			explicit Color(byte val);

			Color(uint32 color, Format, Endian endian = Endian::BIG);
			Color(byte val, byte A);
			Color(byte R, byte G, byte B, byte A);
			Color(byte R, byte G, byte B);

			byte	rgb332(Endian) const;
			uint16	rgb565(Endian) const;
			uint32  rgb888(Endian) const; 
			uint32  yuv888(Endian) const;

			uint32	rgba8888(Endian) const;
			uint32	cymk8888(Endian) const;

			inline float GetRedF() const
			{
				return R/255.f;
			}

			inline float GetBlueF() const
			{
				return B/255.f;
			}

			inline float GetGreenF() const
			{
				return G/255.f;
			}

			inline float GetAlphaF() const
			{
				return A/255.f;
			}

			inline void MakeOpaque()
			{
				A = 0xff;
			}

			inline bool IsOpaque() const
			{
				return A == 0xff;
			}

			inline bool IsGrayscale() const
			{
				return R == B == G;
			}

			inline float Brightness() const
			{
				return 0.2126f * R + 0.7152f * G + 0.0722f * B;
			}

			Color Grayscale();
			Color Inverse();

			union { byte R, C, Y; };
			union { byte G, Y, U; };
			union { byte B, M, V; };
			union { byte A, K; };
		};

	}
}
