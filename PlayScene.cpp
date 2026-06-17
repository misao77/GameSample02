#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "tankHead.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);//親をplaysceneにして地面を生成
	Instantiate<Tank>(this);
	Instantiate<tankHead>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
