#include "LoadGame.h"

#define DLLEXPORT __declspec(dllexport)

SKSE_PLUGIN_VERSION = []() {
	SKSE::PluginVersionData v;
	v.PluginName(Plugin::NAME);
	v.PluginVersion(Plugin::VERSION);
	v.AuthorName("Maxsu and SkyHorizon"sv);
	v.UsesAddressLibrary();
	v.UsesNoStructs();
	return v;
}();

SKSE_PLUGIN_QUERY(const SKSE::QueryInterface*, SKSE::PluginInfo* pluginInfo)
{
	pluginInfo->name = SKSEPlugin_Version.pluginName;
	pluginInfo->infoVersion = SKSE::PluginInfo::kVersion;
	pluginInfo->version = SKSEPlugin_Version.pluginVersion;
	return true;
}

SKSE_PLUGIN_LOAD(const SKSE::LoadInterface* skse)
{
	/*
#ifndef NDEBUG
	while (!IsDebuggerPresent()) {
		Sleep(100);
	}
#endif
	*/

	spdlog::set_pattern("[%H:%M:%S:%e] [%l] %v"s);

	SKSE::log::info("Game version: {}", skse->RuntimeVersion());

	auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener(SCAR::EventCallback);

	return true;
}
