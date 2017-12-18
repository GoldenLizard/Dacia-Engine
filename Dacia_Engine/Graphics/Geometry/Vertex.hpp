#pragma once
#include <Graphics\DaciaGraphics.hpp>
#include <Dacia.Math\Definitions.hpp>


namespace Dacia
{
	namespace Graphics
	{

		enum class VertexBufferFormat :
			byte
		{
			POS_TX,
			POS_TX_NRM,
			POS_TX_NRM_TG,
			POS_TX_NRM_TG_BTG,
			POS_NRM_TX,
			POS_NRM_TG_TX,
			POS_NRM_TG_TX_BTG
		};

		struct Vertex
		{
			dmath::Vector3 position;
			dmath::Vector3 normals;
			dmath::Vector3 tangents;
			dmath::Vector3 uvw;

			dmath::Vector3 bitangents();
		};

		struct VertexBuffer
		{
			GPU_Handle					handle;
			VertexBufferFormat	const	content;

		};
	}
}