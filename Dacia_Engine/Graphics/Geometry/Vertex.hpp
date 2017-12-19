#pragma once
#include <Graphics\DaciaGraphics.hpp>
#include <Dacia.Math\Definitions.hpp>
#include <Dacia.Math\Vectorial\VectorUtil.hpp>
#include <Graphics\GpuBuffer.hpp>


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

			inline dmath::Vector3 bitangents();
		};

		inline dmath::Vector3 Dacia::Graphics::Vertex::bitangents()
		{
			return dmath::Cross(normals, tangents);
		}


		struct VertexBuffer : 
			public GpuBuffer
		{
			template<size_t size>
			VertexBuffer(float (&content)[size]);

			virtual void Init()		override;
			virtual void Destroy()	override;
			virtual void Bind()		override;
			virtual void Unbind()	override;

			VertexBufferFormat const content;
		};
	}
}