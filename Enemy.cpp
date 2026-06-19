#include "Enemy.h"
#include "Engine//Model.h"
#include "Engine//Input.h"
#include "Bullet.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = (float)(rand() % 40 - 20);
	transform_.position_.z = (float)(rand() % 40 - 20);

	transform_.position_.y = 0.0f;
}

void Enemy::Update()
{
	
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
