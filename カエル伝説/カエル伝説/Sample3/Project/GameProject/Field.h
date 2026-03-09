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

protected:
	CImage* mp_fieldImg;	// フィールドの画像
};