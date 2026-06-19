#include "tankHead.h"
#include "Engine//Model.h"
#include "Tank.h"
#include "Engine//Input.h"
#include "Bullet.h"

tankHead::tankHead(GameObject* parent)
	: GameObject(parent, "tankHead"), hModel_(-1)
{//コンストラクタはメンバぼ初期化をする場所
}

void tankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);
}

void tankHead::Update()
{

	if (Input::IsKey(DIK_LEFT)) {
		//タンクヘッドの回転
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		//タンクヘッドの回転
		transform_.rotate_.y += 2.0f;
	}
	if (Input::IsKeyDown(DIK_SPACE)) 
	{
		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);
		XMVECTOR vMove = vTop -vRoot;
		//vMove = XMVector3Normalize(vMove);
		vMove = 0.2f * vMove;
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);

		//弾を生成する
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
		pBullet->SetMoveVector(move);
		pBullet->SetPosition(cannonTop);
	}
}

void tankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void tankHead::Release()
{
}
