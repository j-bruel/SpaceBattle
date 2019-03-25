#ifndef UICOMPONENT_HH_
#define UICOMPONENT_HH_

class IUIComponent
{

public:
  virtual ~IUIComponent() {}

  virtual void init() = 0;

};

#endif /* !UICOMPONENT_HH */