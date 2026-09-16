#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
//#include "tankHead.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	text_.Initialize();

	Instantiate<Ground>(this);//親をplaysceneにして地面を生成
	Instantiate<Tank>(this);
	for (int i = 0; i < 10; i++)
	{
		/*Enemy* enemy = Instantiate<Enemy>(this);
		enemies_.push_back(enemy);*/
		SpawnEnemy();
	}
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
	text_.Draw(20, 20, score_);
}

void PlayScene::Release()
{
	text_.Release();
}

void PlayScene::SpawnEnemy()
{
	Enemy* enemy = Instantiate<Enemy>(this);
	enemies_.push_back(enemy);
}

void PlayScene::AddScore()
{
	score_++;
}
