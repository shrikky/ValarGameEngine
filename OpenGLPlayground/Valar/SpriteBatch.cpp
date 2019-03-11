#include "SpriteBatch.h"
#include <algorithm>
#include <vector>

namespace Valar {

	SpriteBatch::SpriteBatch()
	{
		_vao = 0;
		_vbo = 0;
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::Init() 
	{
		CreateVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sortType)
	{
		_sortType = sortType;
		_renderBatches.clear();
		for (int i = 0; i < _glyphs.size(); i++)
		{
			delete _glyphs[i];
		}
		_glyphs.clear();
	}

	void SpriteBatch::End()
	{
		SortGlyphs();
		CreateRenderBatches();
	}

	void SpriteBatch::Draw(glm::vec4& destRect, glm::vec4& uvRect, GLuint& texture, float depth, Color& color)
	{
		Glyph* newGlyph = new Glyph();
		newGlyph->texture = texture;
		newGlyph->depth = depth;
				
		newGlyph->topleft.color = color;
		newGlyph->topleft.SetPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topleft.SetUV(uvRect.x, uvRect.y + uvRect.w);
				
		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.SetPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.SetUV(uvRect.x, uvRect.y);
				
		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);
				
		newGlyph->topRight.color = color;
		newGlyph->topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
				
		_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::CreateRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);

			
		if(_glyphs.empty())
		{
			return;
		}
		int offset = 0;
		int cv = 0;
		_renderBatches.emplace_back(0, 6, _glyphs[0]->texture);
		vertices[cv++] = _glyphs[0]->topleft;
		vertices[cv++] = _glyphs[0]->bottomLeft;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->topRight;
		vertices[cv++] = _glyphs[0]->topleft;
		offset += 6;
		for (int cg = 1; cg < _glyphs.size(); cg++)
		{
			if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture) {
				_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
			}
			else
			{
				_renderBatches.back().numVertices += 6;
			}
			vertices[cv++] = _glyphs[cg]->topleft;
			vertices[cv++] = _glyphs[cg]->bottomLeft;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->topRight;
			vertices[cv++] = _glyphs[cg]->topleft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0,vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::RenderBatch() 
	{

		glBindVertexArray(_vao);

		for (size_t i = 0; i < _renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::CreateVertexArray()
	{
		if(_vao==0)
		glGenVertexArrays(1, &_vao);

		glBindVertexArray(_vao);

		if(_vbo==0)
		glGenBuffers(1, &_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//Position attrib
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//color attrib
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		//UV attrib
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);

	}

	void SpriteBatch::SortGlyphs()
	{
		
		switch (_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(),_glyphs.end(), CompareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), ComparTextures);
			break;
		}
	
	}

	bool SpriteBatch::CompareFrontToBack(Glyph* glyph, Glyph* glyph2)
	{
		return (glyph->depth < glyph2->depth);
	}

	bool  SpriteBatch::CompareBackToFront(Glyph* glyph, Glyph* glyph2)
	{
		return (glyph->depth > glyph2->depth);
	}

	bool  SpriteBatch::ComparTextures(Glyph* glyph, Glyph* glyph2)
	{
		return (glyph->texture < glyph2->texture);
	}
}