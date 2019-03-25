#include "Commun/Tools/Log/Initializer.hpp"
#include <GameLogic.hh>

namespace spcbttl
{
namespace client
{

using namespace Urho3D;

class App : public Application
{

  public:
    App(Context *context);

    virtual void Setup()
    {
        engineParameters_["FullScreen"] = false;
        engineParameters_["WindowWidth"] = 1600;
        engineParameters_["WindowHeight"] = 900;
        engineParameters_["WindowResizable"] = false;
        engineParameters_["LogQuiet"] = true;
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../OpenLibs/Urho3D/build/bin/;../assets/";
        engineParameters_[EP_RESOURCE_PATHS] = ";Data;CoreData;Autoload/LargeData;models;ui;style;materials;textures";

        _game = new GameLogic(GetContext());
    }

    virtual void Start()
    {
        // Game initialization
        this->_game->init();

        // Log initialization
        commun::tool::log::initialize(_logPath, plog::verbose, plog::verbose);

        SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(App, HandleKeyDown));
    }

    virtual void Stop() {
        this->_game->stop();
    }

    void HandleKeyDown(StringHash eventType, VariantMap &eventData)
    {
        using namespace KeyDown;
        int key = eventData[P_KEY].GetInt();
        if (key == KEY_ESCAPE)
            engine_->Exit();
    }

  private:
    UniquePtr<GameLogic> _game;
    std::string _logPath;

};

} // namespace client
} // namespace spcbttl

URHO3D_DEFINE_APPLICATION_MAIN(spcbttl::client::App)
