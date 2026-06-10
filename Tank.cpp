#include "Tank.h"
#include "Engine//Model.h"
#include "Engine//Input.h"
#include "Engine//Debug.h"
#include "Ground.h"

namespace
{
	XMVECTOR vFront = { 0,0,1,0 };//タンクの前方
	const float moveSpeed = 0.1f;
	enum CAM_TYPE
	{
		FIXED_CAM,//固定
		TPS_CAM,//三人称
		TPS_CAMROT,//三人称（回転）
		FPS_CAM,//一人称
		CAM_TYPE_MAX
	};
}
//タンクのボディを表すクラス
Tank::Tank(GameObject* parent)
	: GameObject(parent, "Tank"),hModel_(-1),camType_(FIXED_CAM)
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
}

void Tank::Update()
{
	if (Input::IsKeyDown(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
	}
	switch (camType_)
	{
	case FIXED_CAM:
		//固定カメラの処理
		Camera::SetTarget(XMFLOAT3(0, 0, 0));
		Camera::SetPosition(XMFLOAT3(0, 20, -30));
		break;
	case TPS_CAM:
		//三人称カメラの処理
		break;
	case TPS_CAMROT:
		//三人称（回転）カメラの処理
		break;
	case FPS_CAM:
		//一人称カメラの処理
		break;

	}
	//Aキーを押している間、左に回転する
	//Dキーを押している間、右に回転する
	if (Input::IsKey(DIK_LEFT) || Input::IsKey(DIK_A)) 
	{
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.0f;
	}
	Debug::Log("CAMTYPE = ");
	Debug::Log(camType_, true);//後のtrueは改行
	//Wキーを押している間、前に進む
	if (Input::IsKey(DIK_UP) || Input::IsKey(DIK_W))
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);
	}

	//レイキャストして、浮いたら、地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は０より下に掘られて作られている。
	data.dir = { 0,-1,0 };//真下にレイを飛ばす

	Ground* pGround = (Ground*)FindObject("Ground");
	int hGroundModel = pGround->GetModelHandle();
	Model::RayCast(hGroundModel, &data);

	if (data.hit == true)
	{
		transform_.position_.y =  - data.dist;
		//レイの発射位置から、地面までの距離を引いて、地面にぴったりつける
	}
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
