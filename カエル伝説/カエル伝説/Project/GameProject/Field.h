#pragma once

// フィールドクラス
class Field
{
public:
	// コンストラクタ
	Field();
	// デストラクタ
	~Field();

	// 更新
	virtual void Update();
	// 描画
	virtual void Render();

protected:
	CImage* mp_fieldImg;	// フィールドの画像
};