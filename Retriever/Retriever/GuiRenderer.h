#pragma once

#include "Otter.h"

#include <map>

class GuiRenderer : public Otter::IRenderer
{
public:
	/* Loads a texture with the specified id and path. Exits if failure
	Parameter: ID of texture, source path of texture*/
	virtual void OnLoadTexture(int textureID, const char* szPath);

	/* Unloads a texture with the specified id*/
	virtual void OnUnloadTexture(int textureID);

	/* Called when a drawing pass has begun*/
	virtual void OnDrawBegin();

	/* Called when a drawing pass has ended*/
	virtual void OnDrawEnd();

	/* Commits a vertex buffer for rendering*/
	virtual void OnCommitVertexBuffer(const Otter::GUIVertex* pVertices, uint32 numVertices);

	/* Draws primitives on screen*/
	virtual void OnDrawBatch(const Otter::DrawBatch& batch);

private:
	//List of all current texture Ids
	std::map<int, ALLEGRO_BITMAP> textureList;
};
