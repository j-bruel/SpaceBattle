#include <memory>
#include <queue>
#include <mutex>
#include <Urho3D/Graphics/Graphics.h>
#include <ui/urho/AUrhoGameUI.hh>
#include <ui/component/MainMenuComponent.hh>
#include <ui/component/ChatComponent.hh>
#include <Tools/ConcurrentQueue.hpp>

class GameUI : public AUrhoGameUI
{

public:
  GameUI(Context *context);
  ~GameUI();

  virtual void init();
  virtual void update(StringHash eventType, VariantMap &eventData);

  virtual void showConnectServerMenu();
  virtual void showMainMenu();
  virtual void showCreateGameMenu();
  virtual void showRoomChat();
  virtual void showGeneralChat();
  virtual void showLoadingScreen();
  virtual void showWaitingScreen();

  virtual void showText(std::string message);

  // ROOMS
  virtual void addRoom(std::string roomName, int connectedPlayers);
  virtual void clearRooms();

  // WAITING SCREEN
  virtual void clearPlayersList();
  virtual void addPlayer(std::string playerName);
  virtual void addSpectator(std::string playerName);
  virtual void setPlayerReady();

  // CHAT
  virtual void addChatMessage(std::string player, std::string message, bool channel);

  // MISC
  virtual void setLoadingScreenValue(float value, std::string &state);

protected:
  virtual void loadWaitingRoomMenu();
  virtual void loadConnectServerMenu();
  virtual void loadMainMenu();
  virtual void loadCreateGameMenu();
  virtual void loadRoomChat();
  virtual void loadGeneralChat();
  virtual void loadLoadingScreen();

private:

  // Event Handlers
  void addRoom(StringHash eventType, VariantMap &eventData);
  void addChatMessage(StringHash eventType, VariantMap &eventData);
  void addPlayer(StringHash eventType, VariantMap &eventData);
  void addSpectator(StringHash eventType, VariantMap &eventData);
  void setPlayerReady(StringHash eventType, VariantMap &eventData);
  void showText(StringHash eventType, VariantMap &eventData);

  void refreshRoomsHandler(StringHash eventType, VariantMap &eventData);
  void connectServerHandler(StringHash eventType, VariantMap &eventData);
  void createGameMenuHandler(StringHash eventType, VariantMap &eventData);
  void createGameHandler(StringHash eventType, VariantMap &eventData);
  void joinGameHandler(StringHash eventType, VariantMap &eventData);
  void spectateGameHandler(StringHash eventType, VariantMap &eventData);
  void goBackHandler(StringHash eventType, VariantMap &eventData);
  void sendChatHandler(StringHash eventType, VariantMap &eventData);
  void sendNotificationHandler(StringHash eventType, VariantMap &eventData);
  void exitRoomHandler(StringHash eventType, VariantMap &eventData);
  void readyHandler(StringHash eventType, VariantMap &eventData);
  
  boost::signals2::signal<void(std::string, std::string, int)> _connectServerHandler;
  boost::signals2::signal<void(std::string, spcbttl::commun::engine::TimeLimit, bool)> _createGameHandler;
  boost::signals2::signal<void(std::string)> _joinGameHandler;
  boost::signals2::signal<void(std::string)> _spectateGameHandler;
  boost::signals2::signal<void(std::string, int)> _chatHandler;
  boost::signals2::signal<void()> _refreshRoomsListHandler;
  boost::signals2::signal<void()> _exitRoomHandler;
  boost::signals2::signal<void()> _readyHandler;

  // Concurrency
  spcbttl::client::tool::ConcurrentQueue<std::pair<StringHash, VariantMap>> _sharedBuffer;

  // Custom UI components
  std::shared_ptr<ChatComponent> _chat;
  std::shared_ptr<MainMenuComponent> _mainMenu;

  SharedPtr<UIElement> _currentLayout;
  SharedPtr<UIElement> _createGameMenuLayout;
  SharedPtr<UIElement> _waitingMenuLayout;
  SharedPtr<UIElement> _mainMenuLayout;
  SharedPtr<UIElement> _roomChatLayout;
  SharedPtr<UIElement> _generalChatLayout;
  SharedPtr<UIElement> _loadingLayout;
  SharedPtr<UIElement> _connectServerLayout;

public:
  virtual void setConnectServerHandler(boost::signals2::signal<void(std::string, std::string, int)> &sig)
  {
    _connectServerHandler.swap(sig);
  }

  virtual void setJoinGameHandler(boost::signals2::signal<void(std::string)> &sig)
  {
    _joinGameHandler.swap(sig);
  }

  virtual void setCreateGameHandler(boost::signals2::signal<void(std::string, spcbttl::commun::engine::TimeLimit, bool)> &sig)
  {
    _createGameHandler.swap(sig);
  }

  virtual void setChatHandler(boost::signals2::signal<void(std::string, int channel)> &sig)
  {
    _chatHandler.swap(sig);
  }

  virtual void setRefreshRoomsListHandler(boost::signals2::signal<void()> &sig)
  {
    _refreshRoomsListHandler.swap(sig);
  }

  virtual void setExitRoomHandler(boost::signals2::signal<void()> &sig)
  {
    _exitRoomHandler.swap(sig);
  }

  virtual void setReadyHandler(boost::signals2::signal<void()> &sig)
  {
    _readyHandler.swap(sig);
  }

  virtual void setSpectacteGameHandler(boost::signals2::signal<void(std::string)> &sig)
  {
    _spectateGameHandler.swap(sig);
  }

  virtual void hideUI();

  virtual void openNotification(std::string message)
  {
    VariantMap params;

    params["message"] = String(message.c_str());

    _sharedBuffer.push(std::pair<StringHash, VariantMap>("sendNotificationEvent", params));
  }
};
