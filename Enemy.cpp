#include "Enemy.h"
#include "Engine//Model.h"
#include "Engine//Input.h"
#include "Bullet.h"
#include "Ground.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");

	Model::SetAnimFrame(hModel_, 100, 100, 1.0f);
	assert(hModel_ >= 0);
	SphereCollider* collider = new SphereCollider({ 0,0,0 }, 0.5f);//半径0.5の球体
	AddCollider(collider);//当たり判定をBulletに追加する

	float x = (rand() / RAND_MAX) * 5.0f - 10.0f;
	float z = (rand() / RAND_MAX) * 5.0f - 10.0f;
	SetPosition(x, 0, z);
	
	
}

void Enemy::Update()
{
	//レイキャストして、浮いてたら、地面まで落とすRayCastData data;
	RayCastData data;

	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は0より下に掘られて作られている。そうじゃないときはもっと上から！
	data.dir = { 0, -1, 0 };
	Ground* pGround = (Ground*)FindObject("Ground");//
	int hGroundModel = pGround->GetModelHandle();//
	Model::RayCast(hGroundModel, &data);
	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
	}
	
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	Bullet* pBullet = dynamic_cast<Bullet*>(pTarget);

	if (pBullet)
	{
		pBullet->KillMe();
		KillMe();
	}
}
