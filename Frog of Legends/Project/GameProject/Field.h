#pragma once
#include "Task.h"

// フィールドクラス
class Field : public Task
{
public:
	// コンストラクタ
	Field();
	// デストラクタ
	~Field();

	// 更新
	void Update() override;
	// 描画
	void PreRender() override;
	// スクロール速度取得
	float GetScrollSpeed() const { return m_scrollspeed; }



protected:
	CImage* mp_fieldImg;	// フィールドの画像
	CImage* mp_fieldImg2;	// フィールドの画像2
	bool m_isSecondPhase;
	float m_scrollx = 0.0f;
	float m_scrollspeed = 2.0f;
};