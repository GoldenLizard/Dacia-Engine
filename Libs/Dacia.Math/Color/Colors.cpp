#include "Colors.hpp"

namespace dmath
{
	color::Color::Color(uint32 color, Format format, Endian endian)
	{
		switch (format)
		{
			case Format::MONOCHROME:
			{
				R = B = G = color & 0x000000ff;
				A = 0xff;
				break;
			}
			case Format::RGB332:
			{
				if (endian == Endian::BIG)
				{
					R = uint8(color) & 0b11100000 >> 5;
					G = uint8(color) & 0b00011100 >> 2;
					B = uint8(color) & 0b00000011;
					A = 0xff;
				}
				else
				{
					B = uint8(color) & (0b11000000 >> 6);
					G = uint8(color) & (0b00111000 >> 3);
					R = uint8(color) & 0b00000111;
					A = 0xff;
				}

			} break;

			case Format::RGB565:
			case Format::RGB888:
			case Format::RGBA8888:
			case Format::CYMK8888:
			default:
				return;
		}
	}

	color::Color::Color(byte val):
		A(0xff)
	{
		R = G = B = val;
	}

	color::Color::Color(byte val, byte A):
		A(A)
	{
		R = G = B = val;
	}

	color::Color::Color(byte R, byte G, byte B, byte A):
		R(R), G(G), B(B), A(A)
	{
	}

	color::Color::Color(byte R, byte G, byte B):
		R(R), G(G), B(B), A(0xff)
	{
	}

	byte color::Color::rgb332(Endian endian) const
	{
		switch (endian)
		{
			case Endian::LITTLE:
			{
				byte rgb332 = 0;
				rgb332 |= B & 0b11000000;
				rgb332 |= (G >> 3) & 0b00011100;
				rgb332 |= (R >> 5) & 0b00000111;

				return rgb332;
			}

			case Endian::BIG:
			{
				byte rgb332 = 0;
				rgb332 |= R & 0b11100000;
				rgb332 |= (G >> 3) & 0b00011100;
				rgb332 |= (B >> 6) & 0b00000011;

				return rgb332;
			}
		}
	}

	uint16 color::Color::rgb565(Endian endian) const
	{
		switch (endian)
		{
			case Endian::LITTLE:
			{
				uint16 rgb565 = 0;
				rgb565 |= (B << 11) & 0b1111100000000000;
				rgb565 |= (G << 6)  & 0b0000011111100000;
				rgb565 |=  R		& 0b0000000000011111;

				return rgb565;
			}

			case Endian::BIG:
			{
				uint16 rgb565 = 0;
				rgb565 |= (R << 11) & 0b1111100000000000;
				rgb565 |= (G << 6)	& 0b0000011111100000;
				rgb565 |=  B		& 0b0000000000011111;

				return rgb565;
			}
		}
	}
	uint32 color::Color::rgb888(Endian endian) const
	{
		switch (endian)
		{
			case Endian::LITTLE:
			{
				uint16 rgb888 = 0;
				rgb888 |= (B << 16) & 0x00ff0000;
				rgb888 |= (G << 8)	& 0x0000ff00;
				rgb888 |= (R)		& 0x000000ff;

				return rgb888;
			}

			case Endian::BIG:
			{
				uint16 rgb888 = 0;
				rgb888 |= (R << 16) & 0x00ff0000;
				rgb888 |= (G << 8)  & 0x0000ff00;
				rgb888 |= (B)		& 0x000000ff;

				return rgb888;
			}
		}
	}
	uint32 color::Color::rgba8888(Endian endian) const
	{
		switch (endian)
		{
			case Endian::LITTLE:
			{
				uint32 rgb8888 = 0;
				rgb8888 |= (B << 24)	& 0xff000000;
				rgb8888 |= (G << 16)	& 0x00ff0000;
				rgb8888 |= (R << 8)		& 0x0000ff00;
				rgb8888 |=  A			& 0x000000ff;

				return rgb8888;
			}

			case Endian::BIG:
			{
				uint32 rgb8888 = 0;
				rgb8888 |= (A << 24)	& 0xff000000;
				rgb8888 |= (R << 16)	& 0x00ff0000;
				rgb8888 |= (G << 8)		& 0x0000ff00;
				rgb8888 |= (B)			& 0x000000ff;

				return rgb8888;
			}
		}
	}

	uint32 color::Color::cymk8888(Endian endian) const
	{
		return rgba8888(endian);
	}

	color::Color color::Color::Grayscale()
	{
		return Color(byte(0xff * Brightness()),A);
	}

	color::Color color::Color::Inverse()
	{
		return Color(0xff - R, 0xff - G, 0xff - B);
	}
}
