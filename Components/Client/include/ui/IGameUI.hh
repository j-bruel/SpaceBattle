#include <boost/signals2.hpp>
#include <Commun/Engine/TimeLimit.hpp>

class IGameUI
{

public:
    virtual ~IGameUI() {}

    virtual void init() = 0;

    virtual void showConnectServerMenu() = 0;
    virtual void showMainMenu() = 0;
    virtual void showCreateGameMenu() = 0;
    virtual void showRoomChat() = 0;
    virtual void showGeneralChat() = 0;
    virtual void showLoadingScreen() = 0;
    virtual void showWaitingScreen() = 0;

    virtual void showText(std::string message) = 0;

    // MAIN MENU
    virtual void addRoom(std::string roomName, int playersConnected) = 0;
    virtual void clearRooms() = 0;

    // WAITING SCREEEN
    virtual void clearPlayersList() = 0;
    virtual void addPlayer(std::string name) = 0;
    virtual void addSpectator(std::string name) = 0;
    virtual void setPlayerReady() = 0;

    // CHAT
    virtual void addChatMessage(std::string player, std::string message, bool channel) = 0;

    virtual void hideUI() = 0;

    virtual void setLoadingScreenValue(float value, std::string &state) = 0;
    virtual void setConnectServerHandler(boost::signals2::signal<void(std::string, std::string, int)> &sig) = 0;
    virtual void setJoinGameHandler(boost::signals2::signal<void(std::string)> &sig) = 0;
    virtual void setCreateGameHandler(boost::signals2::signal<void(std::string, spcbttl::commun::engine::TimeLimit, bool)> &sig) = 0;
    virtual void setRefreshRoomsListHandler(boost::signals2::signal<void()> &sig) = 0;
    virtual void setChatHandler(boost::signals2::signal<void(std::string, int channel)> &sig) = 0;
    virtual void setExitRoomHandler(boost::signals2::signal<void()> &sig) = 0;
    virtual void setReadyHandler(boost::signals2::signal<void()> &sig) = 0;
    virtual void setSpectacteGameHandler(boost::signals2::signal<void(std::string)> &sig) = 0;

    virtual void openNotification(std::string message) = 0;

  protected:
    virtual void loadWaitingRoomMenu() = 0;
    virtual void loadConnectServerMenu() = 0;
    virtual void loadMainMenu() = 0;
    virtual void loadCreateGameMenu() = 0;
    virtual void loadGeneralChat() = 0;
    virtual void loadRoomChat() = 0;

};