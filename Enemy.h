#pragma once
#include "Engine//GameObject.h"
class Enemy :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);
	//デストラクタ
	~Enemy() {}
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	float GetRadius() const { return radius_; }
	void OnCollision(GameObject* pTarget) override;
private:
	int hModel_;
	float radius_ = 1.0f;
};

