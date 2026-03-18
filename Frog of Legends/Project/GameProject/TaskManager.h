#pragma once

class Task;

//タスクを管理するラス
class TaskManager
{
public:
	//TaskManagerのインスタンスを取得
	static TaskManager* Instance();
	//TaskManagerのインスタンスを破棄
	static void ClearInstance();

	//タスクリストにタスクを追加
	void Add(Task* task, bool sort = false);
	//タスクリストからインスタンスを取り除く
	void Remove(Task* task, bool sort = false);

	//全てのタスクを削除
	void DeleteAll();
	//削除フラグが立っているタスクを削除
	void DeleteKilledTasks();

	//タスクリストに登録されているタスクを全て更新
	void Update();

	void PreRender();
	//タスクリストに登録されているタスクを全て描画
	void Render();

private:
	//コンストラクタ
	TaskManager();
	//TaskManagerのコピーコンストラクタを破棄する
	TaskManager(const TaskManager&) = delete;
	//TaskManagerの代入演算子も無効にする
	TaskManager& operator=(const TaskManager&) = delete;

	//デストラクタ
	~TaskManager();

	//TaskManagerのインスタンスのポインタ
	static TaskManager* ms_instance;

	//生成済みのタスクのリスト
	std::list<Task*>m_taskList;
	//生成済みのオブジェクトのリスト
	std::list<Task*>m_objectList;
};