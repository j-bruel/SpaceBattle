#ifndef GAMEBOARD_HH_
#define GAMEBOARD_HH_

#include <iostream>
#include <graphic/board/AUrhoGameBoard.hh>
#include <graphic/ship/Ship.hh>

class GameBoard : public AUrhoGameBoard
{
  public:
    GameBoard(Context *context, Scene *scene, int id) : AUrhoGameBoard(context, scene, id) {}
    ~GameBoard() {
      for (IShip *ship : _ships)
      {
        delete ship;
      }
    }

    void init(uint size);

    // GRID
    void showGrid();
    void hideGrid();
    bool setImpact(int col, int row, IGameBoard::ImpactType ImpactType);
    BoardCase selectBoardCase(int col, int row);
    BoardCase unselectBoardCase(int col, int row);

    // SHIP
    IShip *placeShip(int col, int row, IShip::ShipDirection shipDirection, IShip::ShipType shipType, bool ghost = false);
    void updateShip(IShip *ship);
    bool removeShip(int col, int row);
    bool testShip(int col, int row, IShip::ShipDirection shipDirection, IShip::ShipType shipType, bool ghost = false);

    // UTILS
    void logBoard();

    uint getSize() const {
        return rows;
    }

    std::vector<IShip *> getShips() const {
        return _ships;
    }

    std::vector<std::vector<BoardCase>> getBoard() const {
      return _board;
    }

  private:
    bool isBoardCaseValid(uint col, uint row);
    void createGrid();

  private:
    std::vector<IShip *> _ships;
    std::vector<std::vector<BoardCase>> _board;
};

#endif // !GAMEBOARD_HH_
