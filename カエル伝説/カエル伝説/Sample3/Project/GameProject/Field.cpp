#include "Field.h"

// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::Field)
	, mp_fieldImg(nullptr)
	,m_scrollx  (0.0f)
	,m_scrollspeed  (2.0f)
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
	m_scrollx += m_scrollspeed;
}

// 描画
void Field::PreRender()
{
	// フィールドを描画

	mp_fieldImg->SetPos(-(int)m_scrollx, 0); //追加

	mp_fieldImg->Draw();
}
