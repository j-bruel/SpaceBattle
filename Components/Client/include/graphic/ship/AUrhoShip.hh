#ifndef AURHOSHIP_HH_
#define AURHOSHIP_HH_

#include <graphic/urho/UrhoGraphicsHeaders.hh>
#include <graphic/IShip.hh>

using namespace Urho3D;

class AUrhoShip : public IShip, public Object
{

public:
  AUrhoShip(Context *context) : Object(context) {}
  ~AUrhoShip() {}

protected:

  virtual StringHash GetType() const {}
  virtual const String &GetTypeName() const {}
  virtual const TypeInfo *GetTypeInfo() const {}

};

#endif /* AURHOSHIP_HH_ */