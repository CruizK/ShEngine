#include "Renderer2D.h"
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include <array>
#include <memory>

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

	std::unique_ptr<VertexArray> QuadVertexArray;
	std::unique_ptr<VertexBuffer> QuadVertexBuffer;
	std::unique_ptr<IndexBuffer> QuadIndexBuffer;
	VertexBufferLayout QuadVertexLayout;

	std::unique_ptr<Shader> TextureShader;
	std::unique_ptr<Texture2D> WhiteTexture;

	uint32_t QuadIndexCount = 0;
	QuadVertex* QuadVertexBufferBase = nullptr;
	QuadVertex* QuadVertexBufferPtr = nullptr;

	std::array<Texture2D, MaxTextureSlots> TextureSlots;
	uint32_t TextureSlotIndex = 1; // 0 = White Texture

	glm::vec4 QuadVertexPositions[4];
};

static Renderer2DData s_Data;


void Renderer2D::Init()
{
	s_Data.QuadVertexArray = std::make_unique<VertexArray>();
	s_Data.QuadVertexBuffer = std::make_unique<VertexBuffer>();

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
	s_Data.QuadIndexBuffer = std::make_unique<IndexBuffer>();
	s_Data.QuadIndexBuffer->Create(quadIndices, s_Data.MaxIndices * sizeof(uint32_t));
	delete[] quadIndices;


	// Create Texture
	uint32_t whiteTextureData = 0xffffffff;
	s_Data.WhiteTexture = std::make_unique<Texture2D>();
	s_Data.WhiteTexture->LoadFromMemory(&whiteTextureData, 1, 1, 4);

	// Create Shader
	s_Data.TextureShader = std::make_unique<Shader>();
	s_Data.TextureShader->CreateFromFile("res/shaders/base.shader");

	s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
	s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
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

void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	const size_t quadVertexCount = 4;
	const float textureIndex = 0.0f;
	const glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
	
	if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		CORE_ERROR("QUAD INDEX COUNT EXCEEDED!!!");

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

void Renderer2D::End()
{
	if (s_Data.QuadIndexCount == 0)
		return;

	uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
	s_Data.QuadVertexBuffer->UploadSubData(s_Data.QuadVertexBufferBase, dataSize, 0);

	s_Data.WhiteTexture->Bind(0);

	s_Data.QuadVertexArray->Bind();
	s_Data.QuadIndexBuffer->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, s_Data.QuadIndexCount, GL_UNSIGNED_INT, 0));

	// Move to flush
	s_Data.QuadIndexCount = 0;
	s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	s_Data.TextureSlotIndex = 1;
}
