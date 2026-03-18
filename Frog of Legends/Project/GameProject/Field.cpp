#include "Field.h"

// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::Field)
	, mp_fieldImg(nullptr)
	,m_scrollx  (0.0f)
	,m_scrollspeed  (2.0f)
{
	// フィールド画像を読み込み
	mp_fieldImg = CImage::CreateImage("PlayScene_Background.png");
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

	// 背景画像の横幅を取得
	int imgW = 4096;

	// 画像の端まで来たらスクロール停止
	if (m_scrollx > imgW - SCREEN_WIDTH)
	{
		m_scrollx = imgW - SCREEN_WIDTH;
		m_scrollspeed = 0.0f;
	}
}

// 描画
void Field::PreRender()
{
	// フィールドを描画

	mp_fieldImg->SetPos(-(int)m_scrollx, 0); //追加

	mp_fieldImg->Draw();
}

