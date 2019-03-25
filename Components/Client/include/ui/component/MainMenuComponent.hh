#include <ui/urho/component/AUrhoUIComponent.hh>

class MainMenuComponent : public AUrhoUIComponent 
{
  public:
    MainMenuComponent(Context *context, UI *ui) : AUrhoUIComponent(context), _ui(ui) {}
    ~MainMenuComponent() {}

    virtual void init() {
      _layout = _ui->LoadLayout(_resources->GetResource<XMLFile>("menu/main.xml"));
      _ui->GetRoot()->AddChild(_layout);
    }

    void add() {
      
    }

  private:
    UI *_ui;
};