#include "Field.h"

// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::Field)
	, mp_fieldImg(nullptr)
{
	// フィールド画像を読み込み
	mp_fieldImg = CImage::CreateImage("field.png");
}

// デストラクタ
Field::~Field()
{
	// フィールドの画像を削除
	if (mp_fieldImg != nullptr)
	{
		delete mp_fieldImg;
		mp_fieldImg = nullptr;
	}
}

// 更新
void Field::Update()
{
}

// 描画
void Field::PreRender()
{
	// フィールドを描画
	mp_fieldImg->Draw();
}
