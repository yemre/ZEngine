#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "cspriteanim.h"
#include "csdlinputsink.h"
#include "ccollider.h"

enum class eAnimState;

class CCharacter: public CSpriteAnim, public CSDLInputSink, CCollider
{
public:
	CCharacter(CSDLBlitter *blitter);
	virtual ~CCharacter();

	void UpdateKeybState(const unsigned char *keys) override;

	int Init(std::string &file, int framewidth, double frameperiod);

private:
	eAnimState State_;

	int ReadConfig(std::string &file);
	void SetAnimState(eAnimState state);
};

#endif

