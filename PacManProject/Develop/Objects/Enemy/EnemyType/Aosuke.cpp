#include "Aosuke.h"

//初期化処理
void Aosuke::Initialize()
{
	name = AOSUKE;
	nawabari_loc = (0.0f);
	wait_time = 0.0f;

	__super::Initialize();
}

//追跡モード
void Aosuke::Tuiseki(float delta_second)
{

}