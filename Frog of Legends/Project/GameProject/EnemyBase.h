#pragma once
#include "CharaBase.h"

// 敵のベースクラス
class EnemyBase : public CharaBase
{
public:
	// コンストラクタ
	EnemyBase();
	EnemyBase(const CVector3D& pos);
	// デストラクタ
	virtual ~EnemyBase();

	virtual CVector3D GetHitRange() const
	{
		return CVector3D(50.0f, 50.0f, 50.0f);
	}

private:
};
