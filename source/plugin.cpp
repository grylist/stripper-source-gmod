/** vim: set ts=4 sw=4 et tw=99:
 *
 * === Stripper for Metamod:Source ===
 * Copyright (C) 2005-2009 David "BAILOPAN" Anderson
 * No warranties of any kind.
 * Based on the original concept of Stripper2 by botman
 *
 * License: see LICENSE.TXT
 * ===================================
 */

#include <GarrysMod/InterfacePointers.hpp>

#include "convar.h"

#include "proxy.hpp"
#include "support.hpp"
#include "plugin.h"

// The plugin is a static singleton that is exported as an interface
CServerPlugin ServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CServerPlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, ServerPlugin);

IServerGameDLL *gamedll = nullptr;
IVEngineServer *engine = nullptr;

CON_COMMAND_F(stripper_status, "Checks stripper status", FCVAR_SERVER_CAN_EXECUTE)
{
    Msg("[Stripper Plugin] Plugin is active and have applied those files:\n");

    for (const auto &file : StripperSupport::AppliedFiles)
    {
        Msg("\t%s\n", file.c_str());
    }
    
    Msg("[Stripper Plugin] End of checking a status\n");
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is loaded, load the interface we need from the engine
//---------------------------------------------------------------------------------

bool g_bPluginLoaded = false;
bool g_bIgnoreNextUnLoad = false;
bool CServerPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
    Msg("[Stripper Plugin] Loading\n");

    if (g_bPluginLoaded)
    {
        Msg("[Stripper Plugin] Plugin was told to be loaded while already being loaded, returning fail...\n");
        g_bIgnoreNextUnLoad = true;

        return false;
    }

    gamedll = InterfacePointers::ServerGameDLL();
    if (gamedll == nullptr) 
	{
        Msg("[Stripper Plugin] Failed to load required IServerGameDLL interface\n");
		return false;
    }

    engine = InterfacePointers::VEngineServer();
    if (engine == nullptr)
    {
        Msg("[Stripper Plugin] Failed to load required IVEngineServer interface\n");
		return false;
    }

    // Need this for console commands
    g_pCVar = InterfacePointers::Cvar();
    if (g_pCVar == nullptr)
    {
        Msg("[Stripper Plugin] Failed to load required ICvar interface\n");
		return false;
    }

    ConVar_Register();

    StripperProxy::Initialize();
    g_bPluginLoaded = true;
	Msg("[Stripper Plugin] Loaded\n");

	return true;
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unloaded (turned off)
//---------------------------------------------------------------------------------
void CServerPlugin::Unload(void)
{
    if (g_bIgnoreNextUnLoad)
    {
        g_bIgnoreNextUnLoad = false;
        return;
    }

    ConVar_Unregister();

    StripperProxy::Deinitialize();
    g_bPluginLoaded = false;
    Msg("[Stripper Plugin] Unloaded\n");
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is paused (i.e should stop running but isn't unloaded)
//---------------------------------------------------------------------------------
void CServerPlugin::Pause(void)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unpaused (i.e should start executing again)
//---------------------------------------------------------------------------------
void CServerPlugin::UnPause(void)
{
}

//---------------------------------------------------------------------------------
// Purpose: the name of this plugin, returned in "plugin_print" command
//---------------------------------------------------------------------------------
const char* CServerPlugin::GetPluginDescription(void)
{
	return "Stripper plugin V1";
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CServerPlugin::LevelInit(char const *pMapName)
{
}

//---------------------------------------------------------------------------------
// Purpose: called on level start, when the server is ready to accept client connections
//		edictCount is the number of entities in the level, clientMax is the max client count
//---------------------------------------------------------------------------------
void CServerPlugin::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
}

//---------------------------------------------------------------------------------
// Purpose: called once per server frame, do recurring work here (like checking for timeouts)
//---------------------------------------------------------------------------------
void CServerPlugin::GameFrame(bool simulating)
{
}

//---------------------------------------------------------------------------------
// Purpose: called on level end (as the server is shutting down or going to a new map)
//---------------------------------------------------------------------------------
void CServerPlugin::LevelShutdown(void) // !!!!this can get called multiple times per map change
{
}

//---------------------------------------------------------------------------------
// Purpose: called when a client spawns into a server (i.e as they begin to play)
//---------------------------------------------------------------------------------
void CServerPlugin::ClientActive(edict_t *pEntity)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when a client leaves a server (or is timed out)
//---------------------------------------------------------------------------------
void CServerPlugin::ClientDisconnect(edict_t *pEntity)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when a client spawns?
//---------------------------------------------------------------------------------
void CServerPlugin::ClientPutInServer(edict_t *pEntity, char const *playername)
{
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CServerPlugin::SetCommandClient(int index)
{
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CServerPlugin::ClientSettingsChanged(edict_t *pEdict)
{
}

//---------------------------------------------------------------------------------
// Purpose: called when a client joins a server
//---------------------------------------------------------------------------------
PLUGIN_RESULT CServerPlugin::ClientConnect(bool* bAllowConnect, edict_t* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen)
{
	return PLUGIN_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a client types in a command (only a subset of commands however, not CON_COMMAND's)
//---------------------------------------------------------------------------------
PLUGIN_RESULT CServerPlugin::ClientCommand(edict_t *pEntity, const CCommand &args)
{
	return PLUGIN_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a client is authenticated
//---------------------------------------------------------------------------------
PLUGIN_RESULT CServerPlugin::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID)
{
	return PLUGIN_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a cvar value query is finished
//---------------------------------------------------------------------------------
void CServerPlugin::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue)
{
}

void CServerPlugin::OnEdictAllocated(edict_t *edict)
{
}

void CServerPlugin::OnEdictFreed(const edict_t *edict)
{
}