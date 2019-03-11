#pragma once
#include<GL/glew.h>
#include <glm/glm.hpp>
#include "vertex.h"
#include <vector>
namespace Valar {

	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph {

		GLuint texture;
		float depth;

		Vertex topleft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;

	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint Offset, GLuint Numvertices, GLuint Texture) 
		{
			offset = Offset;
			numVertices = Numvertices;
			texture = Texture;
		}

		public:
			GLuint offset;
			GLuint numVertices;
			GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();
		void Init();
		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void End();
		void Draw(glm::vec4& destRect, glm::vec4& uvRect, GLuint& texture, float depth, Color& color);
		void RenderBatch();
		static bool CompareFrontToBack(Glyph* glyph, Glyph* Glyph2);
		static	bool CompareBackToFront(Glyph* glyph, Glyph* Glyph2);
		static	bool ComparTextures(Glyph* glyph, Glyph* Glyph2);

	private:

		void CreateRenderBatches();
		void CreateVertexArray();
		void SortGlyphs();
		GLuint _vbo;
		GLuint _vao;
		GlyphSortType _sortType;
		std::vector<Glyph*> _glyphs;
		std::vector<Valar::RenderBatch> _renderBatches;
	};



}