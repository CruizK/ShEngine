#include "Renderer2D.h"
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include <array>

namespace Shengine {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
	};

	struct Renderer2DData
	{

		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<IndexBuffer> QuadIndexBuffer;
		VertexBufferLayout QuadVertexLayout;

		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = White Texture

		glm::vec4 QuadVertexPositions[4];
	};

	static Renderer2DData s_Data;


	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = CreateRef<VertexArray>();
		s_Data.QuadVertexBuffer = CreateRef<VertexBuffer>();

		s_Data.QuadVertexBuffer->Create(nullptr, s_Data.MaxVertices * sizeof(QuadVertex));


		// Setup Vertex Layout
		s_Data.QuadVertexLayout.PushFloat(3); // Position
		s_Data.QuadVertexLayout.PushFloat(4); // Color
		s_Data.QuadVertexLayout.PushFloat(2); // TexCoords
		s_Data.QuadVertexLayout.PushFloat(1); // TexIndex

		s_Data.QuadVertexArray->AddBuffer(*s_Data.QuadVertexBuffer, s_Data.QuadVertexLayout);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];


		// Setup Index Buffer
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		// TODO: Maybe put index buffer in Vertex Array to couple all the buffer binding
		s_Data.QuadIndexBuffer = CreateRef<IndexBuffer>();
		s_Data.QuadIndexBuffer->Create(quadIndices, s_Data.MaxIndices * sizeof(uint32_t));
		delete[] quadIndices;


		// Create Texture
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture = CreateRef<Texture2D>();
		s_Data.WhiteTexture->LoadFromMemory(&whiteTextureData, 1, 1, 4);

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		// Create Shader
		s_Data.TextureShader = CreateRef<Shader>();
		s_Data.TextureShader->CreateFromFile("res/shaders/base.shader");
		s_Data.TextureShader->Use();
		s_Data.TextureShader->SetInt1v("u_Textures", s_Data.MaxTextureSlots, samplers);

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::Begin(const glm::mat4& camera)
	{
		s_Data.TextureShader->Use();
		s_Data.TextureShader->SetMat4("u_Proj", camera);

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const Renderable2D& renderable)
	{
		DrawQuad(renderable.GetTransform(), renderable.GetColor());
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		const size_t quadVertexCount = 4;
		const float textureIndex = 0.0f;
		const glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = texCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D> texture, const glm::vec4& tintColor)
	{
		const size_t quadVertexCount = 4;
		const glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		float textureIndex = 0.0f;

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				FlushAndReset();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = texCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
	}

	void Renderer2D::End()
	{

		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->UploadSubData(s_Data.QuadVertexBufferBase, dataSize, 0);

		Flush();
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount == 0)
			return;

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		s_Data.QuadVertexArray->Bind();
		s_Data.QuadIndexBuffer->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, s_Data.QuadIndexCount, GL_UNSIGNED_INT, 0));
	}


	// Only called when multiple draw calls are used
	void Renderer2D::FlushAndReset()
	{
		End();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}
}