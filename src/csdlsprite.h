#ifndef __CSDLSPRITE_H__
#define __CSDLSPRITE_H__

#include "cdrawable.h"
#include "ccollider.h"
#include "csdlblitter.h"

#include "rapidxml.hpp"

#include <string>

class CSDLBlitter;
struct SDL_Texture;

class CSDLSprite: public CDrawable, public CCollider
{
public:
	CSDLSprite(int id, CSDLBlitter *blitter);
	virtual ~CSDLSprite();

	int LoadImage(std::string &file);
	int Draw() override;
	int DrawFrame(int frameno);
	void DrawCollisionPolygons(CBlitter *blitter);
	
	int GetAbsolutePosX() {return GetPosX() + Blitter_->GetOffsetX();}
	int GetAbsolutePosY() {return GetPosY() + Blitter_->GetOffsetY();}

protected:
	int ReadConfig(const rapidxml::xml_node<> *node);

private:
	SDL_Texture *Texture_ = nullptr;
	
protected:
	CSDLBlitter *Blitter_ = nullptr;
};

#endif
