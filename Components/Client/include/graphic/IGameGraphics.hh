#include <boost/signals2.hpp>
#include <graphic/board/IGameBoard.hh>

class IGameGraphic
{

  public:
    enum GameState
    {
        WAITING_FOR_PLAYERS,
        SHIP_PLACEMENT,
        SHOOTING,
        NONE
    };

    virtual ~IGameGraphic() = default;

    virtual void init() = 0;
    virtual void reset() = 0;
    virtual void start(bool isSpectator) = 0;
    virtual void stop() = 0;

    virtual void setMyBoardImpact(uint row, uint col, IGameBoard::ImpactType type) = 0;
    virtual void setOpponentBoardImpact(uint row, uint col, IGameBoard::ImpactType type) = 0;

    virtual void placeShip(std::string whichBoard, int col, int row, IShip::ShipDirection shipDirection, IShip::ShipType shipType, bool ghost) = 0;
    
    // BOARD
    virtual IGameBoard *getPlayerGameboard() const = 0;
    virtual IGameBoard *getOpponentGameBoard() const = 0;

    virtual void startShipPlacementPhase() = 0;
    virtual void startShootingPhase() = 0;

    // CALLBACKS
    virtual void setProgressNotifySig(boost::signals2::signal<void(int, std::string)> &handler) = 0;
    virtual void setPlaceShipHandler(boost::signals2::signal<void(std::vector<std::vector<BoardCase>>, std::vector<IShip *>)> &handler) = 0;
    virtual void setShootHandler(boost::signals2::signal<void(uint)> &handler) = 0;
};