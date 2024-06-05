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
	object_type(0)
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

int GameObject::GetObjectType() const
{
	return object_type;
}

//�ʒu���ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void GameObject::SetObjectType(int object_type)
{
	this->object_type = object_type;
}

bool GameObject::GetHit() const
{
	return hit;
}

bool GameObject::GetDestroy() const
{
	return destroy;
}