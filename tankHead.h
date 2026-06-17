#pragma once
#include "Engine//GameObject.h"
class tankHead :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	tankHead(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
private:
	int hModel_;
	int camType_;//カメラの種類
};

