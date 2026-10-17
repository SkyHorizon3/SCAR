#include "LoadGame.h"
#include "DataHandler.h"
#include "Hook_AttackCombo.h"
#include "Hook_AttackStart.h"

namespace SCAR
{
	void EventCallback(SKSE::MessagingInterface::Message* msg)
	{
		if (msg->type == SKSE::MessagingInterface::kPostLoad) {
			// For First Attack
			AIAttackStartHook::InstallHook();

			// For Combos Attack
			AnimEventHook::InstallHook();

			auto dataHandler = SCAR::DataHandler::GetSingleton();
			if (dataHandler->precisionPtr) {
				SKSE::log::info("Obtained PrecisionAPI!");
			}

			if (dataHandler->settings->enableDebugLog) {
				spdlog::set_level(spdlog::level::debug);
				SKSE::log::debug("Enable Debug Log!");
			}

			if (dataHandler->settings->enableDebugOverlay) {
				//DebugOverlay
				if (!dataHandler->trueHUD_API) {
					SKSE::log::warn("TrueHUD API Not Found! DebugOverlay Disabled");
					return;
				}

				if (REL::Module::IsVR()) {
					SKSE::log::warn("DebugOverlay not supported in VR; ignoring setting");
					return;
				}

				SKSE::log::debug("Enable Debug Overlay!");
			}
		}
	}

}
