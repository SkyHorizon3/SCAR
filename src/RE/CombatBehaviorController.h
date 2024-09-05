#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class Actor;
	class CombatBehaviorResource;
	class CombatBehaviorThread;
	class CombatBehaviorTreeNode;
	class CombatController;
	class CombatGroup;
	class CombatInventory;
	class CombatState;

	class CombatBehaviorController
	{
	public:
		/*
		static Actor* GetCurrentAttacker();
		static CombatController* GetCurrentCombatController();
		static CombatGroup* GetCurrentCombatGroup();
		static CombatInventory* GetCurrentCombatInventory();
		static CombatState* GetCurrentCombatState();

		void Abort();
		void AddResource(CombatBehaviorResource* resource);
		void AddThread(CombatBehaviorThread* thread);
		void AddThreads(const BSTArray<CombatBehaviorThread*>& threads);
		bool GetResource(const BSFixedString& name, NiPointer<CombatBehaviorResource>& resource);
		CombatBehaviorThread* GetThread(uint32_t ind) const;
		void RemoveResource(CombatBehaviorResource* resource);
		void RemoveThread(CombatBehaviorThread* thread);
		void Start(CombatBehaviorTreeNode* start_node);
		void QueueThread(CombatBehaviorThread* thread);
		void Update();
		void UpdateThread(CombatBehaviorThread* thread);
		*/

		// members
		CombatBehaviorThread* root_thread;                                       // 00 -- TODO unique_ptr?
		BSTArray<CombatBehaviorThread*> active_threads;                          // 08
		CombatController* combat_control;                                        // 20
		BSTHashMap<BSFixedString, NiPointer<CombatBehaviorResource>> resources;  // 28
		BSTArray<CombatBehaviorThread*> queued;                                  // 58
		uint32_t threads_ind;                                                    // 70
		uint32_t pad_74;                                                         // 74
	};
	static_assert(sizeof(CombatBehaviorController) == 0x78);
}