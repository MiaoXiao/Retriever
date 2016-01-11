#include "stdafx.h"
#include "GuiRenderer.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include <iostream>
#include <string>
#include <utility> 

using namespace Otter;
using namespace std;

/* Loads a texture with the specified id and path. Exits if failure
Parameter: ID of texture, source path of texture*/
void GuiRenderer::OnLoadTexture(int textureID, const char* szPath)
{
	string path = "images/";
	string fullPath = path + szPath;

	ALLEGRO_BITMAP *texture = al_load_bitmap(fullPath.c_str());
	if (!texture)
	{
		cerr << "Could not load " << szPath << "!" << endl;
		al_rest(10);
		exit(1);
	}
	
	textureList[textureID] = texture;
}

/* Unloads a texture with the specified id.
Parameter: textureID to remove from textureList*/
void GuiRenderer::OnUnloadTexture(int textureID)
{
	textureList.erase(textureID);
}

/* Called when a drawing pass has begun*/
void GuiRenderer::OnDrawBegin()
{

}

/* Called when a drawing pass has ended*/
void GuiRenderer::OnDrawEnd()
{

}

/* Commits a vertex buffer for rendering*/
void GuiRenderer::OnCommitVertexBuffer(const Otter::GUIVertex* pVertices, uint32 numVertices)
{

}

/* Draws primitives on screen*/
void GuiRenderer::OnDrawBatch(const Otter::DrawBatch& batch)
{

}