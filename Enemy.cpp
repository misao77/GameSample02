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

	Model::SetAnimFrame(hModel_, 100, 100, 1.0f);
	transform_.position_.x = (float)(rand() % 40 - 20);
	transform_.position_.z = (float)(rand() % 40 - 20);

	transform_.position_.y = 0.0f;
	SphereCollider* collider = new SphereCollider({ 0,0,0 }, 0.5f);//半径0.5の球体
	AddCollider(collider);//当たり判定をBulletに追加する
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

void Enemy::OnCollision(GameObject* other)
{
	if (other->GetName() == "Bullet")
	{
		Destroy();
	}
}
