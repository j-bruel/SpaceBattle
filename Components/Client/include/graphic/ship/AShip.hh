#ifndef ASHIP_HH_
#define ASHIP_HH_

#include <graphic/utils/UrhoGraphicsHeaders.hh>
#include <graphic/ship/IShip.hh>

class AShip : public IShip
{

public:
  static int getShipSize(IShip::ShipType type)
  {
    switch (type)
    {
    case IShip::ONE_SLOT:
      return 1;
      break;
    case IShip::TWO_SLOTS:
      return 2;
      break;
    case IShip::THREE_SLOTS:
      return 3;
      break;
    case IShip::THREE_SLOTS_2:
      return 3;
      break;
    case IShip::FOUR_SLOTS:
      return 4;
      break;
    case IShip::FIVE_SLOTS:
      return 5;
      break;
    case IShip::NONE:
      return -1;
    }
  }

  AShip(int xOrigin, int yOrigin, int rowOrigin,
        int colOrigin, ShipDirection direction, ShipType type, Scene *scene) : xOrigin(xOrigin), yOrigin(yOrigin),
                                                                               rowOrigin(rowOrigin), colOrigin(colOrigin),
                                                                               direction(direction), type(type), scene(scene) {}
  virtual ~AShip()
  {
    spaceShipNode->Remove();
  }
  
  void init()
  {
    auto *cache = scene->GetContext()->GetSubsystem<ResourceCache>();

    int size = getShipSize(type);

    int row = rowOrigin;
    int col = colOrigin;
    int unitSize = 20.0f;

    spaceShipNode = scene->CreateChild("SpaceShip");
    for (int i = 0; i < size; ++i)
    {
      Node *objectNode = spaceShipNode->CreateChild("Box");
      objectNode->SetPosition(Vector3(xOrigin + (unitSize * col) + 10.f, 0.0f, -(unitSize * row) - 10.f));
      objectNode->SetRotation(Quaternion(90.0f, direction * 90.0f, 0.0f));
      objectNode->SetScale(7.0f);
      auto *object = objectNode->CreateComponent<StaticModel>();
      object->SetModel(cache->GetResource<Model>("Models/Cylinder.mdl"));
      object->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
      object->SetCastShadows(true);

      switch (direction)
      {
      case IShip::ShipDirection::BOTTOM:
        ++row;
        break;
      case IShip::ShipDirection::TOP:
        --row;
        break;
      case IShip::ShipDirection::RIGHT:
        ++col;
        break;
      case IShip::ShipDirection::LEFT:
        --col;
        break;
      }
    }
  }

  void update()
  {
    if (spaceShipNode)
    {
      spaceShipNode->Remove();
      this->init();
    }
  }

  // GETTERS
  ShipType getType() const {
    return type;
  }

  ShipDirection getDirection() const {
    return direction;
  }

  uint getRow() const
  {
    return rowOrigin;
  }

  uint getCol() const
  {
    return colOrigin;
  }

  // SETTERS
  void setType(ShipType &type)
  {
    this->type = type;
  }

  void setDirection(ShipDirection &direction)
  {
    this->direction = direction;
  }

  void setRow(uint row)
  {
    this->rowOrigin = row;
  }

  void setCol(uint col)
  {
    this->colOrigin = col;
  }

protected:
  Node *spaceShipNode = NULL;

  int xOrigin;
  int yOrigin;
  int rowOrigin;
  int colOrigin;
  
  ShipDirection direction;
  ShipType type;

  Scene *scene;
};

#endif /* ASHIP_HH */