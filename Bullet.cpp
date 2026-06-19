#include "Bullet.h"
#include "Engine//Model.h"
#include "Engine//Input.h"

Bullet::Bullet(GameObject* parent)
	: GameObject(parent, "Bullet"), hModel_(-1), move_(XMFLOAT3(0,0,0))
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);
}

void Bullet::Update()
{
	move_.y -= 0.01f;
	//transform_.position_ = transform_.position_ + move_;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード：読み込み
	XMVECTOR vMove = XMLoadFloat3(&move_);//ロード：読み込み
	vPos = vPos + vMove;//弾の進行方向に移動する
	XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み

}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}


//①弾の弾道を重力をつける
//②敵を配置（敵もレイキャスして、xz座標ランダムで置く）まずは１匹
//③当たり判定（コライダーの配置）
