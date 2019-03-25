#include <Urho3D/Engine/Application.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/ListView.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Window.h>
#include <ui/IGameUI.hh>

using namespace Urho3D;

class AUrhoGameUI : public IGameUI, public Object
{

protected:
  Context *_context;
  UI *_ui;
  ResourceCache *_resources;

public:
  AUrhoGameUI(Context *context) : Object(context), _context(context) {}
  ~AUrhoGameUI() {}

protected:
  
  // Urho mandatory method overloads
  virtual StringHash GetType() const {}
  virtual const String &GetTypeName() const {}
  virtual const TypeInfo *GetTypeInfo() const {}

};