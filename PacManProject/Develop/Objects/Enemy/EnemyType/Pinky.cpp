#include "Pinky.h"

//初期化処理
void Pinky::Initialize()
{
	name = PINKY;
	nawabari_loc = (0.0f);
	wait_time = 0.0f;

	__super::Initialize();
}

//追跡モード
void Pinky::Tuiseki(float delta_second)
{

}