#ifndef IGAMEBOARD_HH_
#define IGAMEBOARD_HH_

#include <boost/signals2.hpp>
#include <graphic/ship/IShip.hh>

struct BoardCase;

class IGameBoard
{

  public:
    enum ImpactType
    {
      WATER = 1,
      SHIP = 2
    };

    IGameBoard() {}
    virtual ~IGameBoard() {}

    virtual void init(uint) = 0;

    // SHIP
    virtual bool testShip(int col, int row, IShip::ShipDirection direction, IShip::ShipType, bool ghost = false) = 0;
    virtual IShip *placeShip(int col, int row, IShip::ShipDirection direction, IShip::ShipType, bool ghost = false) = 0;
    virtual void updateShip(IShip *ship) = 0;
    virtual bool removeShip(int col, int row) = 0;

    // GRID
    virtual void showGrid() = 0;
    virtual void hideGrid() = 0;
    virtual bool setImpact(int col, int row, ImpactType impactType) = 0;
    virtual BoardCase selectBoardCase(int col, int row) = 0;
    virtual BoardCase unselectBoardCase(int col, int row) = 0;

    // UTILS
    virtual bool isBoardCaseValid(uint col, uint row) = 0;
    virtual uint getSize() const = 0;
    virtual std::vector<IShip *> getShips() const = 0;
    virtual std::vector<std::vector<BoardCase>> getBoard() const = 0;
};

#endif /* IGAMEBOARD_HH_ */