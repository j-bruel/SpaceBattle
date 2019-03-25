#include <graphic/GameGraphics.hh>

GameGraphics::GameGraphics(Context *context) : AUrhoGameGraphics(context)
{
}

GameGraphics::~GameGraphics()
{
}

void GameGraphics::init()
{
    _progressNotifySig(1, "Get subsystems");

    auto *cache = _context->GetSubsystem<ResourceCache>();
    auto *graphics = _context->GetSubsystem<Graphics>();
    _input = _context->GetSubsystem<Input>();
    auto *renderer = _context->GetSubsystem<Renderer>();

    _progressNotifySig(2, "Create scene");

    _scene = new Scene(_context);
    _scene->CreateComponent<Octree>();

    _progressNotifySig(3, "Add light");

    // Init lighting
    Node *lightNode = _scene->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    auto *light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetSpecularIntensity(0.5f);

    _progressNotifySig(4, "Add skybox");

    // Init sky
    Node *skyNode = _scene->CreateChild("Sky");
    skyNode->SetScale(500.0f);
    auto *skybox = skyNode->CreateComponent<Skybox>();
    skybox->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    skybox->SetMaterial(cache->GetResource<Material>("Skybox.xml"));

    _progressNotifySig(6, "Add game boards");

    // Init boards
    myBoard = new GameBoard(_context, _scene, 0);
    otherBoard = new GameBoard(_context, _scene, 1);

    myBoard->init(10);
    otherBoard->init(10);

    _progressNotifySig(8, "Add camera");

    // Init camera
    _cameraNode = new Node(context_);
    Camera *camera = _cameraNode->CreateComponent<Camera>();
    camera->SetFarClip(750.0f);

    _cameraNode->SetPosition(Vector3(200.0f, 350.0f, -150.0f));
    _cameraNode->LookAt(Vector3(200.0f, 0.0f, -100.0f));

    _progressNotifySig(10, "Create viewport");

    sleep(0.5);

    // Init viewport
    SharedPtr<Viewport> viewport(new Viewport(_context, _scene, _cameraNode->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(GameGraphics, HandleUpdate));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(GameGraphics, onKeydown));
    SubscribeToEvent("MyBoardImpactEvent", URHO3D_HANDLER(GameGraphics, setMyBoardImpact));
    SubscribeToEvent("OpponentBoardImpactEvent", URHO3D_HANDLER(GameGraphics, setOpponentBoardImpact));
    SubscribeToEvent("StartShipPlacementEvent", URHO3D_HANDLER(GameGraphics, startShipPlacementPhase));
    SubscribeToEvent("PlaceOpponentShipEvent", URHO3D_HANDLER(GameGraphics, placeOpponentBoardShip));
    SubscribeToEvent("PlaceMyShipEvent", URHO3D_HANDLER(GameGraphics, placeMyBoardShip));
    SubscribeToEvent("ResetGameEvent", URHO3D_HANDLER(GameGraphics, reset));
}

void GameGraphics::start(bool isSpectator) {
    if (!isSpectator)
        startShipPlacementPhase();
}

void GameGraphics::stop()
{
}

void GameGraphics::reset()
{
    _sharedBuffer.push(std::pair<StringHash, VariantMap>("ResetGameEvent", VariantMap()));

}

void GameGraphics::reset(StringHash eventType, VariantMap &map)
{
    _scene->Clear();
 
    init();
}

void GameGraphics::HandleUpdate(StringHash eventType, VariantMap &eventData)
{
    while (_sharedBuffer.size())
    {
        boost::optional<std::pair<StringHash, VariantMap>> event = _sharedBuffer.pop();
        if (event)
        {
            SendEvent((*event).first, (*event).second);
        }
    }
}

// GAMES PHASES

void GameGraphics::startShipPlacementPhase()
{
    _sharedBuffer.push(std::pair<StringHash, VariantMap>("StartShipPlacementEvent", VariantMap()));
}

void GameGraphics::startShipPlacementPhase(StringHash type, VariantMap &map)
{
    _gameState = SHIP_PLACEMENT;

    _shipPlacementCount = 0;
    _currentShipRow = 0;
    _currentShipCol = 0;
    _currentShipDirection = IShip::BOTTOM;
    _currentShipType = IShip::FOUR_SLOTS;

    _shipToPlace = this->myBoard->placeShip(_currentShipCol, _currentShipRow, _currentShipDirection, _currentShipType, true);
}

void GameGraphics::placeShip(std::string whichShip, int col, int row, IShip::ShipDirection shipDirection, IShip::ShipType shipType, bool ghost)
{
    VariantMap params;

    params["col"] = col;
    params["row"] = row;
    params["direction"] = (int)shipDirection;
    params["type"] = (int)shipType;
    params["ghost"] = ghost;

    if (whichShip == "myboard")
        _sharedBuffer.push(std::pair<StringHash, VariantMap>("PlaceMyShipEvent", params));
    else
        _sharedBuffer.push(std::pair<StringHash, VariantMap>("PlaceOpponentShipEvent", params));
}

void GameGraphics::placeMyBoardShip(StringHash eventType, VariantMap &params)
{
    int col = params["col"].GetInt();
    int row = params["row"].GetInt();
    IShip::ShipDirection direction = (IShip::ShipDirection) params["direction"].GetInt();
    IShip::ShipType type = (IShip::ShipType) params["type"].GetInt();
    bool ghost = params["ghost"].GetBool();

    myBoard->placeShip(col, row, direction, type, ghost);
}

void GameGraphics::placeOpponentBoardShip(StringHash eventType, VariantMap &params)
{
    int col = params["col"].GetInt();
    int row = params["row"].GetInt();
    IShip::ShipDirection direction = (IShip::ShipDirection)params["direction"].GetInt();
    IShip::ShipType type = (IShip::ShipType)params["type"].GetInt();
    bool ghost = params["ghost"].GetBool();

    otherBoard->placeShip(col, row, direction, type, ghost);
}

void GameGraphics::startShootingPhase()
{
    _gameState = SHOOTING;

    _selectedCaseCol = 0;
    _selectedCaseRow = 0;

    if (otherBoard->getBoard()[_selectedCaseCol][_selectedCaseRow].state == 0)
    {
        otherBoard->selectBoardCase(_selectedCaseCol, _selectedCaseRow);
    }
}

void GameGraphics::handleShootingControls(int keydown)
{
    uint colTmp = _selectedCaseCol;
    uint rowTmp = _selectedCaseRow;

    if (keydown == KEY_UP)
    {
        colTmp--;
    }
    else if (keydown == KEY_DOWN)
    {
        colTmp++;
    }
    else if (keydown == KEY_RIGHT)
    {
        rowTmp++;

    }
    else if (keydown == KEY_LEFT)
    {
        rowTmp--;
    }
    else if (keydown == KEY_RETURN)
    {
        otherBoard->unselectBoardCase(_selectedCaseCol, _selectedCaseRow);
        _shootHandler((_selectedCaseCol * 10) + _selectedCaseRow);
        _gameState = GameState::NONE;
    }

    if (otherBoard->isBoardCaseValid(colTmp, rowTmp))
    {
        otherBoard->unselectBoardCase(_selectedCaseCol, _selectedCaseRow);
        _selectedCaseCol = colTmp;
        _selectedCaseRow = rowTmp;

        if (otherBoard->getBoard()[_selectedCaseCol][_selectedCaseRow].state == 0)
        {
            otherBoard->selectBoardCase(_selectedCaseCol, _selectedCaseRow);
        }
    }
}

void GameGraphics::handleShipPlacementControls(int keydown)
{
    if (keydown == KEY_RETURN)
    {
        if (this->myBoard->testShip(_currentShipCol, _currentShipRow,
                                    _currentShipDirection, _currentShipType))
        {
            this->myBoard->placeShip(_currentShipCol, _currentShipRow, _currentShipDirection, _currentShipType);
            _shipPlacementCount++;
            _currentShipType = getAvailableShipType();
        }
        if (_shipPlacementCount < 6)
        {
            _currentShipRow = 0;
            _currentShipCol = 0;
            _currentShipDirection = IShip::BOTTOM;

            this->_shipToPlace->setRow(_currentShipRow);
            this->_shipToPlace->setCol(_currentShipCol);
            this->_shipToPlace->setDirection(_currentShipDirection);
            this->_shipToPlace->setType(_currentShipType);

            this->_shipToPlace->update();
        }
        else
        {
            _placeShipHandler(myBoard->getBoard(), myBoard->getShips());

            delete _shipToPlace;
        }
    }
    else if (keydown == KEY_UP)
    {
        if (this->myBoard->testShip(this->_shipToPlace->getCol(), this->_shipToPlace->getRow() - 1,
                                    this->_shipToPlace->getDirection(), this->_shipToPlace->getType(), true))
        {
            _currentShipRow--;
            this->_shipToPlace->setRow(_currentShipRow);
            this->myBoard->updateShip(this->_shipToPlace);
        }
    }
    else if (keydown == KEY_DOWN)
    {
        if (this->myBoard->testShip(this->_shipToPlace->getCol(), this->_shipToPlace->getRow() + 1,
                                    this->_shipToPlace->getDirection(), this->_shipToPlace->getType(), true))
        {
            _currentShipRow++;
            this->_shipToPlace->setRow(_currentShipRow);
            this->myBoard->updateShip(this->_shipToPlace);
        }
    }
    else if (keydown == KEY_LEFT)
    {
        if (this->myBoard->testShip(this->_shipToPlace->getCol() - 1, this->_shipToPlace->getRow(),
                                    this->_shipToPlace->getDirection(), this->_shipToPlace->getType(), true))
        {
            _currentShipCol--;
            this->_shipToPlace->setCol(_currentShipCol);
            this->myBoard->updateShip(this->_shipToPlace);
        }
    }
    else if (keydown == KEY_RIGHT)
    {
        if (this->myBoard->testShip(this->_shipToPlace->getCol() + 1, this->_shipToPlace->getRow(),
                                    this->_shipToPlace->getDirection(), this->_shipToPlace->getType(), true))
        {
            _currentShipCol++;
            this->_shipToPlace->setCol(_currentShipCol);
            this->myBoard->updateShip(this->_shipToPlace);
        }
    }
    else if (keydown == KEY_R)
    {
        IShip::ShipDirection tmpDirection;
        if (_currentShipDirection == IShip::BOTTOM)
            tmpDirection = IShip::LEFT;
        else if (_currentShipDirection == IShip::LEFT)
            tmpDirection = IShip::TOP;
        else if (_currentShipDirection == IShip::TOP)
            tmpDirection = IShip::RIGHT;
        else if (_currentShipDirection == IShip::RIGHT)
            tmpDirection = IShip::BOTTOM;

        if (this->myBoard->testShip(this->_shipToPlace->getCol(), this->_shipToPlace->getRow(), tmpDirection, this->_shipToPlace->getType(), true))
        {
            _currentShipDirection = tmpDirection;
            this->_shipToPlace->setDirection(tmpDirection);
            this->myBoard->updateShip(this->_shipToPlace);
        }
    }
}

void GameGraphics::onKeydown(StringHash eventType, VariantMap &eventData)
{
    using namespace KeyDown;
    int key = eventData[P_KEY].GetInt();

    if (_gameState == SHIP_PLACEMENT && _shipPlacementCount < 6)
    {
        handleShipPlacementControls(key);
    }
    else if (_gameState == SHOOTING)
    {
        handleShootingControls(key);
    }
}

void GameGraphics::setMyBoardImpact(uint row, uint col, IGameBoard::ImpactType type)
{
    VariantMap params;

    params["row"] = row;
    params["col"] = col;
    params["type"] = (int)type;
    _sharedBuffer.push(std::pair<StringHash, VariantMap>("MyBoardImpactEvent", params));
}

void GameGraphics::setOpponentBoardImpact(uint row, uint col, IGameBoard::ImpactType type)
{
    VariantMap params;

    params["row"] = row;
    params["col"] = col;
    params["type"] = (int)type;
    _sharedBuffer.push(std::pair<StringHash, VariantMap>("OpponentBoardImpactEvent", params));
}

void GameGraphics::setMyBoardImpact(StringHash eventType, VariantMap &params)
{
    int row = params["row"].GetInt();
    int col = params["col"].GetInt();
    int impactType = params["type"].GetInt();

    myBoard->setImpact(col, row, (IGameBoard::ImpactType) impactType);
}

void GameGraphics::setOpponentBoardImpact(StringHash eventType, VariantMap &params)
{
    int row = params["row"].GetInt();
    int col = params["col"].GetInt();
    int impactType = params["type"].GetInt();

    otherBoard->setImpact(col, row, (IGameBoard::ImpactType) impactType);
}

// UTILS

IShip::ShipType GameGraphics::getAvailableShipType()
{
    bool hasOneSlot(false), hasTwoSlots(false), hasThreeSlot(false), hasThreeSlot2(false), hasFourSlots(false), hasFiveSlots(false);

    for (int i = 0; i < myBoard->getShips().size(); ++i)
    {
        if (myBoard->getShips().at(i)->getType() == IShip::ONE_SLOT)
        {
            hasOneSlot = true;
        }
        else if (myBoard->getShips().at(i)->getType() == IShip::TWO_SLOTS)
        {
            hasTwoSlots = true;
        }
        else if (myBoard->getShips().at(i)->getType() == IShip::THREE_SLOTS)
        {
            hasThreeSlot = true;
        }
        else if (myBoard->getShips().at(i)->getType() == IShip::THREE_SLOTS_2)
        {
            hasThreeSlot2 = true;
        }
        else if (myBoard->getShips().at(i)->getType() == IShip::FOUR_SLOTS)
        {
            hasFourSlots = true;
        }
        else if (myBoard->getShips().at(i)->getType() == IShip::FIVE_SLOTS)
        {
            hasFiveSlots = true;
        }
    }
    if (!hasOneSlot)
        return IShip::ONE_SLOT;
    else if (!hasTwoSlots)
        return IShip::TWO_SLOTS;
    else if (!hasThreeSlot)
        return IShip::THREE_SLOTS;
    else if (!hasThreeSlot2)
        return IShip::THREE_SLOTS_2;
    else if (!hasFourSlots)
        return IShip::FOUR_SLOTS;
    else if (!hasFiveSlots)
        return IShip::FIVE_SLOTS;
    return IShip::NONE;
}

Node* GameGraphics::raycast()
{
    auto pos = GetSubsystem<Input>()->GetMousePosition();
    auto graphics = GetSubsystem<Graphics>();
    auto camera = _cameraNode->GetComponent<Camera>();
    auto x = (float)pos.x_ / graphics->GetWidth();
    auto y = (float)pos.y_ / graphics->GetHeight();
    auto cameraRay = camera->GetScreenRay(x, y);
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, cameraRay, RAY_TRIANGLE, 1000, DRAWABLE_GEOMETRY);
    //RayOctreeQuery query(results, cameraRay, RAY_OBB, 1000, DRAWABLE_GEOMETRY);
    _scene->GetComponent<Octree>()->RaycastSingle(query);
    if (results.Size() == 0)
        return nullptr;
    auto node = results[0].node_;
    if (node->HasTag("Selectable"))
        return node;
    return nullptr;
}