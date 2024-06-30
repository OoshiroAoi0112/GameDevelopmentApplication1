#pragma once

#include "../Utility/Vector2D.h"

//�G�̐����Ǘ�
#define HAKO  (0)
#define HANE  (1)
#define HARPY (2)
#define GOLD  (3)
#define ENEMY_TYPE  (4)
//�����蔻�莞�̋��
#define PLAYER (0)
#define ENEMY  (1)
#define BULLET (2)
#define ENEMY_BULLET (3)
#define NOHIT  (4)

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location; //�ʒu���
	Vector2D box_size; //�傫��
	double scale;      //�傫��
	double radian;     //����
	int image;         //�`�悷��摜
	int sound;         //�Đ����鉹��
	//�A�j���[�V�����E�����蔻�菈�����s�����̕ϐ�
	bool hit;          //�I�u�W�F�N�g�ɓ����蔻�肪�c���Ă��邩
	bool destroy;      //�I�u�W�F�N�g���󂵂�����
	int object_type;   //�I�u�W�F�N�g�̎��
	int create_type;   //�����������I�u�W�F�N�g�̎��
	//�G�������I�ɒe��łĂ�悤�ɂ��邽�߂̕ϐ�
	int shot_count;		  //�e��ł܂łɕK�v�ȃt���[���J�E���g
	int shot_span;        //�e��łԊu
	bool shot_flag;       //�e��ł��ǂ���

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();     //����������
	virtual void Update();         //�X�V����
	virtual void Draw() const;     //�`�揈��
	virtual void Finalize();       //�I������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//�����蔻��̗L��
	bool GetHit()const;
	//�I�u�W�F�N�g�������������ǂ���
	bool GetDestroy()const;
	//�I�u�W�F�N�g�T�C�Y�擾
	Vector2D GetBoxSize() const;
	//�I�u�W�F�N�g�̎�ގ擾
	int GetObjectType() const;
	//�����������G�̎�ގ擾
	int GetCreateType() const;
	//�G������łĂ��Ԃ��擾
	bool GetShotFlag() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& locaiton);
	//�G���U���ł��邩
	void SetShotFlag();
};

