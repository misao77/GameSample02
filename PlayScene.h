#pragma once
#include "Engine//GameObject.h"
#include "Engine/Text.h"
#include <vector>

class Enemy;
class PlayScene :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SpawnEnemy();
	void AddScore();

private:
	std::vector<Enemy*>enemies_;
	Text text_;
	int score_ = 0;
};

