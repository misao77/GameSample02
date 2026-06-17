#include "tankHead.h"
#include "Engine//Model.h"
#include "Tank.h"

tankHead::tankHead(GameObject* parent)
	: GameObject(parent, "tankHead"), hModel_(-1)
{
}

void tankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);
}

void tankHead::Update()
{
	XMFLOAT3 TankPos = transform_.position_;
	TankPos.y = TankPos.y + 3.0f;
}

void tankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void tankHead::Release()
{
}
