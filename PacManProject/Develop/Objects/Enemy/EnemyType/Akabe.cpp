#include "Akabe.h"

Akabe::Akabe()
{

}

Akabe::~Akabe()
{

}

//初期化処理
void Akabe::Initialize()
{
	__super::Initialize();

	name = AKABE;
	nawabari_loc = (400.0f,0.0f);
	wait_time = 0.0f;
}

//追跡モード
void Akabe::Tuiseki(float delta_second)
{

}