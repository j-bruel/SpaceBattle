#include <graphic/ship/AShip.hh>

class Ship : public AShip
{

public:
  Ship(int xOrigin, int yOrigin, int rowOrigin, int colOrigin, ShipDirection direction, ShipType type, Scene *scene) : AShip(xOrigin, yOrigin, rowOrigin, colOrigin, direction, type, scene) {}
  ~Ship() {}

};