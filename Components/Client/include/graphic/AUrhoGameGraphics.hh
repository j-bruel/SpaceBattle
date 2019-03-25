#include <graphic/utils/UrhoGraphicsHeaders.hh>
#include <graphic/IGameGraphics.hh>
#include <graphic/board/AUrhoGameBoard.hh>

using namespace Urho3D;

class AUrhoGameGraphics : public IGameGraphic, public Object
{

protected:
  Context *_context;
  Scene *_scene;

public:
  AUrhoGameGraphics(Context *context) : Object(context), _context(context) {}
  ~AUrhoGameGraphics() {}

  // GETTERS
  IGameBoard *getPlayerGameboard() const
  {
    return myBoard;
  }

  IGameBoard *getOpponentGameBoard() const
  {
    return otherBoard;
  }

protected:

  // Game boards
  AUrhoGameBoard *myBoard;
  AUrhoGameBoard *otherBoard;

  // Urho mandatory method overloads
  virtual StringHash GetType() const {}
  virtual const String &GetTypeName() const {}
  virtual const TypeInfo *GetTypeInfo() const {}

};