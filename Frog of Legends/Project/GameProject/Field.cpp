#include "Field.h"
#include "Timer.h"

// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::Field)
	, mp_fieldImg(nullptr)
	, mp_fieldImg2(nullptr)
	,m_scrollx  (0.0f)
	,m_scrollspeed  (1.0f)
	,m_isSecondPhase(false)
{
	// フィールド画像を読み込み
	mp_fieldImg = CImage::CreateImage("PlayScene_Background.png");
	mp_fieldImg2 = CImage::CreateImage("Boss_Background.png");

	m_isSecondPhase = false;
	
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
	// ボスフィールドの画像を削除
	if (mp_fieldImg2 != nullptr)
	{
		delete mp_fieldImg2;
		mp_fieldImg2 = nullptr;
	}
}

// 更新
void Field::Update()
{
	int imgW = 4096;

	// 最初のスクロールフェーズ
	if (!m_isSecondPhase) {
		if (m_scrollx < imgW - SCREEN_WIDTH) {
			m_scrollx += m_scrollspeed;
		}
		else {
			m_scrollx = imgW - SCREEN_WIDTH; // 端で停止
			m_scrollspeed = 0.0f;
		}

		// ★残り20秒で後半開始
		if (Timer::GetRemaining() <= 20) {
			m_isSecondPhase = true;
			m_scrollspeed = 3.0f; // ★好きな速度
		}
	}
	// 後半フェーズのスクロール
	else {
		m_scrollx += m_scrollspeed;

		// ★2枚目が端まで来たら停止
		if (m_scrollx > imgW * 2 - SCREEN_WIDTH) {
			m_scrollx = imgW * 2 - SCREEN_WIDTH;
			m_scrollspeed = 0.0f;
		}
	}
	/*
	m_scrollx += m_scrollspeed;

	// 背景画像の横幅を取得
	int imgW = 4096;

	// 画像の端まで来たらスクロール停止
	if (m_scrollx > imgW - SCREEN_WIDTH)
	{
		m_scrollx = imgW - SCREEN_WIDTH;
		m_scrollspeed = 0.0f;
	}*/
}

// 描画
void Field::PreRender()
{
	// フィールドを描画
	int imgW = 4096;

	// ★一枚目は常に描画
	if (mp_fieldImg) {
		mp_fieldImg->SetPos(-(int)m_scrollx, 0);
		mp_fieldImg->Draw();
	}

	// ★二枚目は後半フェーズから描画
	if (m_isSecondPhase && mp_fieldImg2) {
		mp_fieldImg2->SetPos(-(int)m_scrollx + imgW, 0);
		mp_fieldImg2->Draw();
	}
	/*
	mp_fieldImg->SetPos(-(int)m_scrollx, 0); //追加

	mp_fieldImg->Draw();*/
}

