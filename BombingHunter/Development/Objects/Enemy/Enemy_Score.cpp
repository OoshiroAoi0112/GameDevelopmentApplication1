#include "Enemy_Score.h"
#include <math.h>
#include "DxLib.h"

Enemy_Score::Enemy_Score() : blend(255),direction(0.0),s_digit(0)
{
	for (int i = 0; i < 5; i++)
	{
		s_image[i] = NULL;
	}
	for (int i = 0; i < 11; i++)
	{
		number_image[i] = NULL;
	}
}

Enemy_Score::~Enemy_Score()
{

}

void Enemy_Score::Initialize()
{
	location += (40.0f, -40.0f);

	direction.x = 0.0f;
	direction.y = 2.0f;

	object_type = NOHIT;

	//ƒnƒCƒtƒ“ŠÜ‚ß‚½”Žš‰æ‘œ
	number_image[0] = LoadGraph("Resource/Images/number/0.png");
	number_image[1] = LoadGraph("Resource/Images/number/1.png");
	number_image[2] = LoadGraph("Resource/Images/number/2.png");
	number_image[3] = LoadGraph("Resource/Images/number/3.png");
	number_image[4] = LoadGraph("Resource/Images/number/4.png");
	number_image[5] = LoadGraph("Resource/Images/number/5.png");
	number_image[6] = LoadGraph("Resource/Images/number/6.png");
	number_image[7] = LoadGraph("Resource/Images/number/7.png");
	number_image[8] = LoadGraph("Resource/Images/number/8.png");
	number_image[9] = LoadGraph("Resource/Images/number/9.png");
	number_image[10] = LoadGraph("Resource/Images/number/-.png");

	for (int i = 0; i < 11; i++)
	{
		if (number_image[i] == -1)
		{
			throw("”wŒi‰æ‘œ‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ");
		}
	}
}

void Enemy_Score::Update()
{
	blend -= 1;

	location += direction;

	if (blend <= 0 || location.y<=400.0f)
	{
		destroy = true;
	}
}

void Enemy_Score::Draw()const
{
	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, blend);
	for (int i = 0; i < s_digit; i++)
	{
		DrawRotaGraph(location.x, location.y, 0.7, radian, s_image[i], TRUE, FALSE);
	}
	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

void Enemy_Score::Finalize()
{
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(s_image[i]);
	}

	for (int i = 0; i < 11; i++)
	{
		DeleteGraph(number_image[i]);
	}
}

void Enemy_Score::SetScoreImage(int score)
{
	int i = 0;
	if (score >= 10000 || score<=-1000)
	{
		s_digit = 5;
	}
	else if (score >= 1000 || score<=-100)
	{
		s_digit = 4;
	}
	else if (score >= 100 || score<=-10)
	{
		s_digit = 3;
	}
	else if (score >= 10 || score<0)
	{
		s_digit = 2;
	}
	else
	{
		s_digit = 1;
	}

	if (score < 0)
	{
		s_image[0] = GetNumberImage(0);
		score *= -1;
		i++;
	}

	int s = score;
	for (i; i < 5; i++)
	{
		if (s_digit == 1)
		{
			s_image[i] = GetNumberImage(s % 10);
		}
		else
		{
			if (i < s_digit)
			{
				int p = pow(10, s_digit - (i + 1));
				int image = s / p;
				s_image[i] = GetNumberImage(image);
				s = s % p;
			}
			else
			{
				s_image[i] = NULL;
			}
		}
	}
}

//’l‚É‰ž‚¶‚½”Žš‚Ì‰æ‘œ‚ð•Ô‚·
int Enemy_Score::GetNumberImage(int number)
{
	return number_image[number];
}