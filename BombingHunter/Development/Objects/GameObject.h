#pragma once
#include "../Utility/Vector2D.h"

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
	bool hit;          //�I�u�W�F�N�g�ɓ����蔻�肪�c���Ă��邩
	bool destroy;      //�I�u�W�F�N�g���󂵂�����
	int object_type;   //�I�u�W�F�N�g�̎��

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

	int GetObjectType() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& locaiton);

	void SetObjectType(int object_type);
};

