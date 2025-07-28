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

#include <memory>

#include <detouring/classproxy.hpp>
#include <GarrysMod/Lua/Interface.h>

#include "eiface.h"

#include "support.hpp"
#include "stripper_interfaces.hpp"

namespace StripperProxy {

    class IServerGameDLLProxy : public Detouring::ClassProxy<IServerGameDLL, IServerGameDLLProxy> {
    public:

        IServerGameDLLProxy(IServerGameDLL* server_gamedll) {
            Initialize(server_gamedll);

            if (!Hook(&IServerGameDLL::LevelInit, &IServerGameDLLProxy::LevelInit))
                throw std::runtime_error("[Stripper Plugin] failed to hook IServerGameDLL::LevelInit");
        }

        ~IServerGameDLLProxy() {
            Msg("[Stripper Plugin] UnHooked IServerGameDLL::LevelInit\n");
            UnHook(&IServerGameDLL::LevelInit);
        }

        // Called any time a new level is started (after GameInit() also on level transitions within a game)
        virtual bool LevelInit( char const *pMapName,
                                        char const *pMapEntities, char const *pOldLevel,
                                        char const *pLandmarkName, bool loadGame, bool background ) {

            const char *ents = StripperSupport::parse_map(pMapName, pMapEntities);

            StripperSupport::newMapEntities = ents;

            return Call(&IServerGameDLL::LevelInit,pMapName,ents,pOldLevel,pLandmarkName,loadGame,background);
        };

    };

    class IVEngineServerProxy : public Detouring::ClassProxy<IVEngineServer, IVEngineServerProxy> {
    public:

        IVEngineServerProxy(IVEngineServer* server_gamedll) {
            Initialize(server_gamedll);

            if (!Hook(&IVEngineServer::GetMapEntitiesString, &IVEngineServerProxy::GetMapEntitiesString))
                throw std::runtime_error("[Stripper Plugin] failed to hook IVEngineServer::GetMapEntitiesString");
        }

        ~IVEngineServerProxy() {
            Msg("[Stripper Plugin] UnHooked IVEngineServer::GetMapEntitiesString\n");
            UnHook(&IVEngineServer::GetMapEntitiesString);
        }

        // Called any time a new level is started (after GameInit() also on level transitions within a game)
        virtual const char* GetMapEntitiesString() {

            if (StripperSupport::newMapEntities != nullptr) {
                return StripperSupport::newMapEntities;
            }

            return Call(&IVEngineServer::GetMapEntitiesString);
        };

    };

    std::shared_ptr<StripperProxy::IServerGameDLLProxy> gamedll_proxy;
    std::shared_ptr<IVEngineServerProxy> engine_proxy;

    void Initialize(){
        gamedll_proxy = std::make_shared<IServerGameDLLProxy>(gamedll);
        Msg("[Stripper Plugin] Created proxy for IServerGameDLL\n");

        engine_proxy = std::make_shared<IVEngineServerProxy>(engine);
        Msg("[Stripper Plugin] Created proxy for IVEngineServer\n");
    }

    void Deinitialize(){
        gamedll_proxy.reset();
        engine_proxy.reset();
        Msg("[Stripper Plugin] Proxies unloaded\n");
    }
}
