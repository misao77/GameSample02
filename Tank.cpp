#include "Tank.h"
#include "Engine//Model.h"
#include "Engine//Input.h"
#include "Engine//Debug.h"
#include "Ground.h"
#include "Engine//Camera.h"

namespace
{
	XMVECTOR vFront = { 0,0,1,0 };//タンクの前方
	const float moveSpeed = 0.1f;
	const float CAM_HEIGT_BIAS = 0.2f;//カメラの高さ
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
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);


	if (Input::IsKeyDown(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
	}
	switch (camType_)
	{
	case FIXED_CAM:
		//固定カメラの処理
		SetFixedCam();
		break;
	case TPS_CAM:
	{
		//三人称カメラの処理
		XMFLOAT3 camPos = transform_.position_;//タンクの位置をカメラの位置にする
		camPos.y = camPos.y + 3.0f;//カメラの高さをタンクの位置より少し高く
		camPos.z = camPos.z - 7.0f;//カメラの位置をタンクの位置より少し後ろにする
		Camera::SetPosition(camPos);//カメラの位置を設定
		Camera::SetTarget(transform_.position_);//カメラの注視点をタンクの前にする
		
	}
	break;

	case TPS_CAMROT:
	{
		//三人称（回転）カメラの処理
		XMFLOAT3 camPos;
		XMVECTOR vCAM = { 0.0f,3.0f,-7.0f,0.0f };
		vCAM = XMVector3TransformCoord(vCAM, matRot);
		XMStoreFloat3(&camPos, vPos + vCAM);
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
	}
	break;
		
	case FPS_CAM:
		//一人称カメラの処理
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + CAM_HEIGT_BIAS;
		Camera::SetPosition(camPos);//カメラの位置をタンクの位置にする
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);//カメラの注視点をタンクの前にする
		Camera::SetTarget(camTarget);
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

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}
