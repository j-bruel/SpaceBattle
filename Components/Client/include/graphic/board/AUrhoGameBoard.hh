#ifndef AURHOGAMEBOARD_HH_
#define AURHOGAMEBOARD_HH_

#include <graphic/utils/UrhoGraphicsHeaders.hh>
#include <graphic/board/IGameBoard.hh>

using namespace Urho3D;

struct BoardCase
{

  BoardCase() {}
  BoardCase(int state, IShip *ship) : state(state), ship(ship) {}

  int state = 0;
  IShip *ship = NULL;
  Node *boardCase = NULL;
  bool selected = false;
};

class AUrhoGameBoard : public IGameBoard, public Object
{

public:

  AUrhoGameBoard(Context *context, Scene *currentScene, int boardId) : Object(context), id(boardId), scene(currentScene) {}
  virtual ~AUrhoGameBoard() {
    _gridNodeWrapper->Remove();
    _boardCases->Remove();
  }

protected:
  int id;

  Scene *scene;
  ResourceCache *cache;

  Node *_gridNode;
  Node *_gridNodeWrapper;
  Node *_boardCases;

  float xOrigin;
  float yOrigin;
  int unitSize;
  int rows;
  int columns;

  // Urho mandatory method overloads
  virtual StringHash GetType() const {}
  virtual const String &GetTypeName() const {}
  virtual const TypeInfo *GetTypeInfo() const {}
};

#endif /* AURHOGAMEBOARD_HH_ */