#pragma once

#include "CombatBehaviorThread.h"
#include "RE/B/BSFixedString.h"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;

	class CombatBehaviorTreeNode
	{
	public:
		virtual ~CombatBehaviorTreeNode() = default;
		virtual const char* GetName() const { return name.c_str(); }
		virtual void Enter(CombatBehaviorThread*) {}
		virtual void Exit(CombatBehaviorThread*) {}
		//virtual void Update(CombatBehaviorThread* thread) { thread->Ascend(); }
		//virtual void Abort(CombatBehaviorThread* thread) { thread->Ascend(); }
		virtual void SaveGame(CombatBehaviorThread*, BGSSaveFormBuffer*) {}
		virtual void LoadGame(CombatBehaviorThread*, BGSLoadFormBuffer*) {}
		virtual bool Validate(CombatBehaviorTreeNode*) const { return true; }
		virtual const BSFixedString& GetType() const { return name; }

		//CombatBehaviorTreeNode();
		CombatBehaviorTreeNode(const CombatBehaviorTreeNode&) = delete;
		CombatBehaviorTreeNode& operator=(CombatBehaviorTreeNode&) = delete;

		/*
		void AddChild(CombatBehaviorTreeNode*);
		CombatBehaviorTreeNode* FindChild(const BSFixedString& ch_name) const;
		int32_t FindChildIndex(const BSFixedString& ch_name) const;
		CombatBehaviorTreeNode* GetRoot();
		void SetVftable(REL::VariantID id);
		*/
		TES_HEAP_REDEFINE_NEW();

		// members
		BSFixedString name;                               // 08
		CombatBehaviorTreeNode* parent;                   // 10
		BSStaticArray<CombatBehaviorTreeNode*> children;  // 18 TODO: unique_ptr?
	};
	static_assert(sizeof(CombatBehaviorTreeNode) == 0x28);
}