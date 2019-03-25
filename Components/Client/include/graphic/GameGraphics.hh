
#include <condition_variable>
#include <mutex>
#include <Tools/ConcurrentQueue.hpp>
#include <graphic/AUrhoGameGraphics.hh>
#include <graphic/board/GameBoard.hh>

using namespace Urho3D;

class GameGraphics : public AUrhoGameGraphics
{

  public:
    GameGraphics(Context *context);
    ~GameGraphics();

    void init();
    void reset();
    void start(bool isSpectator);
    void stop();

    void HandleUpdate(StringHash eventType, VariantMap &eventData);

    // GAME PHASES
    void startShipPlacementPhase();
    void startShootingPhase();

    void setOpponentBoardImpact(uint row, uint col, IGameBoard::ImpactType type);
    void setMyBoardImpact(uint row, uint col, IGameBoard::ImpactType type);

    void placeShip(std::string whichBoard, int col, int row, IShip::ShipDirection shipDirection, IShip::ShipType shipType, bool ghost);
    
    // UTILS
    IShip::ShipType getAvailableShipType();
    Node* raycast();

    // CAMERA
    void MoveCamera(float timeStep)
    {
      // Do not move if the UI has a focused element (the console)
      if (GetSubsystem<UI>()->GetFocusElement())
        return;

      auto *input = GetSubsystem<Input>();

      // Movement speed as world units per second
      const float MOVE_SPEED = 20.0f;
      // Mouse sensitivity as degrees per pixel
      const float MOUSE_SENSITIVITY = 0.1f;

      // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
      IntVector2 mouseMove = input->GetMouseMove();
      yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
      pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
      pitch_ = Clamp(pitch_, -90.0f, 90.0f);

      // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
      _cameraNode->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

      // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
      if (input->GetKeyDown(KEY_W))
        _cameraNode->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
      if (input->GetKeyDown(KEY_S))
        _cameraNode->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
      if (input->GetKeyDown(KEY_A))
        _cameraNode->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
      if (input->GetKeyDown(KEY_D))
        _cameraNode->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
    }

    // CALLBACKS
    void setProgressNotifySig(boost::signals2::signal<void(int, std::string)> &sig)
    {
      this->_progressNotifySig.swap(sig);
    }

    void setPlaceShipHandler(boost::signals2::signal<void(std::vector<std::vector<BoardCase>>, std::vector<IShip *>)> &handler)
    {
      this->_placeShipHandler.swap(handler);
    }
    void setShootHandler(boost::signals2::signal<void(uint)> &handler)
    {
      this->_shootHandler.swap(handler);
    }

  private:
    void onKeydown(StringHash eventType, VariantMap &eventData);
    void handleShipPlacementControls(int keydown);
    void handleShootingControls(int keydown);
    void reset(StringHash eventType, VariantMap &eventData);

    void setMyBoardImpact(StringHash eventType, VariantMap &params);
    void setOpponentBoardImpact(StringHash eventType, VariantMap &params);
    void startShipPlacementPhase(StringHash type, VariantMap &map);
    void placeMyBoardShip(StringHash type, VariantMap &params);
    void placeOpponentBoardShip(StringHash type, VariantMap &params);

    GameState _gameState;

    // SHIP PLACEMENT  
    uint _shipPlacementCount;
    IShip *_shipToPlace;
    IShip::ShipDirection _currentShipDirection;
    IShip::ShipType _currentShipType;
    uint _currentShipRow;
    uint _currentShipCol;

    // SHOOTING
    uint _selectedCaseCol;
    uint _selectedCaseRow;

    // COMPONENTS
    Input *_input;

    // CONCURRENCY
    spcbttl::client::tool::ConcurrentQueue<std::pair<StringHash, VariantMap>> _sharedBuffer;

    // CALLBACKS
    boost::signals2::signal<void(int, std::string)> _progressNotifySig;
    boost::signals2::signal<void(std::vector<std::vector<BoardCase>>, std::vector<IShip *>)> _placeShipHandler;
    boost::signals2::signal<void(uint pos)> _shootHandler;
    
    // CAMERA  
    Node *_cameraNode;
    float yaw_;
    float pitch_;
};
