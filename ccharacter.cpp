#include "ccharacter.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <SDL.h>

enum class eAnimState
{
	StandRight,
	StandLeft,
	WalkRight,
	WalkLeft
};

CCharacter::CCharacter(CSDLBlitter *blitter)
	:CSpriteAnim(blitter)
	,CSDLInputSink()
	,State_(eAnimState::StandRight)
{
}

CCharacter::~CCharacter()
{
}

int CCharacter::Init(std::string &file, int framewidth, double frameperiod)
{
	return CSpriteAnim::Init(file, framewidth, frameperiod);
}

int CCharacter::ReadConfig(std::string &file)
{
	rapidxml::file<> f(file.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(f.data());
	return 0;
}

void CCharacter::SetAnimState(eAnimState state)
{
	switch(state)
	{
	case eAnimState::WalkRight:
		if(this->State_ != eAnimState::WalkRight)
			this->SetActiveFrames(1, 6);
		this->State_ = eAnimState::WalkRight;
		break;

	case eAnimState::WalkLeft:
		if(this->State_ != eAnimState::WalkLeft)
			this->SetActiveFrames(8, 13);
		this->State_ = eAnimState::WalkLeft;
		break;

	case eAnimState::StandRight:
		this->SetActiveFrames(0, 0);
		this->State_ = eAnimState::StandRight;
		break;

	case eAnimState::StandLeft:
		this->SetActiveFrames(7, 7);
		this->State_ = eAnimState::StandLeft;
		break;
	
	default:
		break;
	}
}

void CCharacter::UpdateKeybState(const unsigned char *keys)
{
	if(keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_UP])
	{
		this->MoveRight(1);
		this->MoveUp(1);
		this->SetAnimState(eAnimState::WalkRight);
		this->StartAnimation();
	}
	if(keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_DOWN])
	{
		this->MoveRight(1);
		this->MoveDown(1);
		this->SetAnimState(eAnimState::WalkRight);
		this->StartAnimation();
	}
	if(keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_UP])
	{
		this->MoveLeft(1);
		this->MoveUp(1);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	if(keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_DOWN])
	{
		this->MoveLeft(1);
		this->MoveDown(1);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		this->MoveRight(2);
		this->SetAnimState(eAnimState::WalkRight);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_LEFT])
	{
		this->MoveLeft(2);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_UP])
	{
		this->MoveUp(2);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_DOWN])
	{
		this->MoveDown(2);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else
	{
		if(State_ == eAnimState::WalkRight)
			this->SetAnimState(eAnimState::StandRight);
		if(State_ == eAnimState::WalkLeft)
			this->SetAnimState(eAnimState::StandLeft);
		//this->StopAnimation();
	}
}

