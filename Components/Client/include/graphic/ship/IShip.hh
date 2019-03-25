#ifndef ISHIP_HH_
#define ISHIP_HH_

#include <vector>

class IShip
{

  public:
    enum ShipDirection
    {
        LEFT = 1,
        RIGHT = -1,
        TOP = -2,
        BOTTOM = 2,
    };

    enum ShipType
    {
        ONE_SLOT,
        TWO_SLOTS,
        THREE_SLOTS,
        THREE_SLOTS_2,
        FOUR_SLOTS,
        FIVE_SLOTS,
        NONE = -1
    };

    IShip() {}
    virtual ~IShip() {}

    virtual void init() = 0;
    virtual void update() = 0;

    // GETTERS
    virtual ShipType getType() const = 0;
    virtual ShipDirection getDirection() const = 0;
    virtual uint getRow() const = 0;
    virtual uint getCol() const = 0;

    // GETTERS
    virtual void setType(ShipType &type) = 0;
    virtual void setDirection(ShipDirection &direction) = 0;
    virtual void setRow(uint row) = 0;
    virtual void setCol(uint col) = 0;
};

#endif /* ISHIP_HH */