#include "Akabe.h"

//初期化処理
void Akabe::Initialize()
{
	name = AKABE;
	nawabari_loc = (0.0f);
	wait_time = 0.0f;

	__super::Initialize();
}

//追跡モード
void Akabe::Tuiseki(float delta_second)
{

}