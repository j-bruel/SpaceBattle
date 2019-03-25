#ifndef AURHOUICOMPONENT_HH_
#define AURHOUICOMPONENT_HH_

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/Core/StringUtils.h>
#include <ui/component/IUIComponent.hh>

using namespace Urho3D;

class AUrhoUIComponent : public IUIComponent
{

protected:
  Context *_context;
  UIElement *_layout;
  ResourceCache *_resources;
  UI *_ui;

public:
  AUrhoUIComponent(Context *context)
  {
    _context = context;
  }

  ~AUrhoUIComponent() {}

  virtual void init() = 0;
  
};

#endif /* !AURHOUICOMPONENT_HH */