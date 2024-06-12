#include "GameObject.h"
//�R���X�g���N�^
GameObject::GameObject() :
	location(0.0f),
	scale(0.0),
	radian(0.0),
	image(0),
	sound(0),
	hit(false),
	destroy(false),
	object_type(0),
	create_type(5)
{

}

//�f�X�g���N�^
GameObject::~GameObject()
{

}

//����������
void GameObject::Initialize()
{

}

//�X�V����
void GameObject::Update()
{

}

//�`�揈��
void GameObject::Draw() const
{

}

//�I��������
void GameObject::Finalize()
{

}

//�����蔻�菈���ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//���������Ƃ��ɍs������

}

//�ʒu���擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//�I�u�W�F�N�g�T�C�Y�擾
Vector2D GameObject::GetBoxSize() const
{
	return this->box_size;
}

//�I�u�W�F�N�g�̎�ގ擾
int GameObject::GetObjectType() const
{
	return object_type;
}

//�����������G�̎�ގ擾
int GameObject::GetCreateType() const
{
	return create_type;
}

//�q�b�g������Ԃ��擾
bool GameObject::GetHit() const
{
	return hit;
}

//�����������ǂ����擾
bool GameObject::GetDestroy() const
{
	return destroy;
}

//�ʒu���ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}