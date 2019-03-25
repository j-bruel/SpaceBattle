#include <memory>
#include <iostream>
#include <Tools/BufferDataManager.hpp>
#include <Tools/Observer.hpp>
#include <Commun/Network/Packet.hpp>
#include <Commun/Network/Requests/Requests.hpp>
#include <Network/Client.hpp>
#include <Network/BattleAPI.hpp>
#include <graphic/GameGraphics.hh>
#include <ui/GameUI.hh>

namespace spcbttl
{
namespace client
{

class GameLogic : public tool::Observer<tool::BufferDataManager<std::shared_ptr<commun::net::Packet>>>
{

public:
  GameLogic(Urho3D::Context *context);
  ~GameLogic() = default;

  void init();
  void stop();

  void joinGame();
  void startGame();
  void backToMenu();

  // COMMANDS
  void onAuthenticateResponse(std::shared_ptr<commun::net::Packet> command);
  void onCreateRoomResponse(std::shared_ptr<commun::net::Packet> command);
  void onJoinRoomResponse(std::shared_ptr<commun::net::Packet> command);
  void onRoomListResponse(std::shared_ptr<commun::net::Packet> command);
  void onShootShipResponse(std::shared_ptr<commun::net::Packet> command);
  void onLaunchGameResponse(std::shared_ptr<commun::net::Packet> command);
  void onChatResponse(std::shared_ptr<commun::net::Packet> command);
  void onLobbyStateResponse(std::shared_ptr<commun::net::Packet> command);
  void onEndGameResponse(std::shared_ptr<commun::net::Packet> command);
  void onGameStartResponse(std::shared_ptr<commun::net::Packet> command);
  void onPlayersTurnResponse(std::shared_ptr<commun::net::Packet> command);
  void onViewRomResponse(std::shared_ptr<commun::net::Packet> command);
  void onPlaceShipResponse(std::shared_ptr<commun::net::Packet> command);

  void simulateBoard(std::vector<size_t> ship, std::string currentBoard, IShip::ShipType type);

  // MANDATORY URHO FUNCTIONS
  virtual StringHash GetType() const {}
  virtual const String &GetTypeName() const {}
  virtual const TypeInfo *GetTypeInfo() const {}

private:
  void update(tool::BufferDataManager<std::shared_ptr<commun::net::Packet>> *buffer);

private:

  // INFOS
  std::string _roomName;
  std::string _playerName;
  bool _isSpectator = false;
  unsigned short _clientId;

  std::vector<std::pair<int, std::string>> _players;  

  // CALLBACKS
  boost::signals2::signal<void(int, std::string)> _gameLoadingHandler;
  boost::signals2::signal<void(std::string, std::string, int)> _connectServerHandler;
  boost::signals2::signal<void(std::string)> _joinRoomHandler;
  boost::signals2::signal<void(std::string, spcbttl::commun::engine::TimeLimit, bool)> _gameCreateGameHandler;
  boost::signals2::signal<void(std::vector<std::vector<BoardCase>>, std::vector<IShip *>)> _placeShipHandler;
  boost::signals2::signal<void()> _refreshRoomsListHandler;
  boost::signals2::signal<void(uint)> _shootHandler;
  boost::signals2::signal<void(std::string message, int channel)> _chatHandler;
  boost::signals2::signal<void()> _exitRoomHandler;
  boost::signals2::signal<void()> _readyHandler;
  boost::signals2::signal<void(std::string)> _spectacteGameHandler;

  // MAIN COMPONENTS
  std::shared_ptr<IGameGraphic> _gameGraphic;
  std::shared_ptr<IGameUI> _gameUI;

  Context *_context;

  std::thread keepAliveThread;
  std::thread networkThread;
  
  // NETWORK
  bool _isAuthFailed = false;
  net::Client _client;
  net::BattleAPI *_battleAPI;
  tool::BufferDataManager<std::shared_ptr<commun::net::Packet>> &_buffer;
  sckcpp::tcp::ClientSocket *_clientSocket = NULL;
  
};

} // namespace client
} // namespace spcbttl
