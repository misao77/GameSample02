#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	text_.Initialize();
}

//更新
void TestScene::Update()
{
    if (Input::IsKeyDown(DIK_SPACE))
    {
        SceneManager* sceneManager =
            dynamic_cast<SceneManager*>(GetParent());

        if (sceneManager)
        {
            sceneManager->ChangeScene(SCENE_ID_PLAY);
        }
    }
}

//描画
void TestScene::Draw()
{
	text_.Draw(200, 200, "TANK GAME");
	text_.Draw(250, 300, "PRESS SPACE TO START");
}

//開放
void TestScene::Release()
{
}
