#include "Guzuta.h"

//初期化処理
void Guzuta::Initialize()
{
	name = GUZUTA;
	nawabari_loc = (0.0f);
	wait_time = 0.0f;

	__super::Initialize();
}

//追跡モード
void Guzuta::Tuiseki(float delta_second)
{

}