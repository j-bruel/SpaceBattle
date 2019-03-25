#include <graphic/board/GameBoard.hh>

void GameBoard::init(uint size)
{
    cache = this->GetSubsystem<ResourceCache>();

    // Set board size
    this->rows = size;
    this->columns = size;

    // Set board unit size
    unitSize = 12.0f;

    // Absolute origin of the board
    xOrigin = id * ((unitSize * rows) + 120.0f);
    yOrigin = 0.0f;

    for (int i = 0; i < rows; ++i)
    {
        _board.push_back(std::vector<BoardCase>());
        for (int b = 0; b < columns; ++b)
        {
            _board.back().push_back(BoardCase());
        }
    }

    // Create grid
    this->createGrid();
}

// GRID

void GameBoard::showGrid()
{
    _gridNodeWrapper->SetDeepEnabled(true);
}

void GameBoard::hideGrid()
{
    _gridNodeWrapper->SetDeepEnabled(false);
}

void GameBoard::createGrid()
{
    _gridNodeWrapper = scene->CreateChild();
    _gridNode = _gridNodeWrapper->CreateChild("EditorGrid");
    _gridNode->SetName("EditorGrid");
    CustomGeometry *grid = _gridNode->CreateComponent<CustomGeometry>();
    grid->SetNumGeometries(1);
    grid->SetMaterial(cache->GetResource<Material>("Materials/VColUnlit.xml"));
    grid->SetViewMask(0x80000000);

    grid->BeginGeometry(0, LINE_LIST);

    Color gridColor(1, 1, 1, 0.5);

    float halfSize = rows / 2;
    float scale = 20.0f;

    for (int i = -halfSize; i <= halfSize; ++i)
    {
        grid->DefineVertex(Vector3((float)i * scale, 0.0f, -halfSize * scale));
        grid->DefineColor(gridColor);

        grid->DefineVertex(Vector3((float)i * scale, 0.0f, halfSize * scale));
        grid->DefineColor(gridColor);

        grid->DefineVertex(Vector3(-halfSize * scale, 0.0f, (float)i * scale));
        grid->DefineColor(gridColor);

        grid->DefineVertex(Vector3(halfSize * scale, 0.0f, (float)i * scale));
        grid->DefineColor(gridColor);
    }

    grid->Commit();
    _gridNode->SetPosition(Vector3(xOrigin + (halfSize * scale), 0.0f, yOrigin - (halfSize * scale)));

    int y = yOrigin;

    for (uint i = 0; i < rows; ++i)
    {
        Vector3 position(xOrigin - 10.0f, 0.0f, y - 10.0f);

        Node *casePositionNode = _gridNodeWrapper->CreateChild();

        auto *casePosition = casePositionNode->CreateComponent<Text3D>();
        casePositionNode->SetPosition(position);
        casePositionNode->SetRotation(Quaternion(90.0f, 0.0f, 0.0f));
        casePositionNode->SetScale(20.0f);
        casePosition->SetText(String(i));
        casePosition->SetFont(cache->GetResource<Font>("Fonts/BlueHighway.sdf"), 24);
        y -= scale;
    }

    int x = xOrigin;
    for (uint i = 0; i < rows; ++i)
    {
        Vector3 position(x + 10.0f, 0.0f, yOrigin + 10.0f);

        Node *casePositionNode = _gridNodeWrapper->CreateChild();

        auto *casePosition = casePositionNode->CreateComponent<Text3D>();
        casePositionNode->SetPosition(position);
        casePositionNode->SetRotation(Quaternion(90.0f, 0.0f, 0.0f));
        casePositionNode->SetScale(20.0f);
        casePosition->SetText(String((char)(65 + i)));
        casePosition->SetFont(cache->GetResource<Font>("Fonts/BlueHighway.sdf"), 24);
        x += scale;
    }

    y = yOrigin;
    bool alreadySelected = false;
    _boardCases = scene->CreateChild();
    for (uint i = 0; i < rows; ++i)
    {
        int x = xOrigin;
        for (uint b = 0; b < rows; ++b)
        {
            Vector3 position(x + 10.0f, 0.0f, y - 10.0f);
            Node *objectNode = _boardCases->CreateChild();
            objectNode->SetPosition(position);
            objectNode->SetScale(20.0f);
            auto *object = objectNode->CreateComponent<StaticModel>();
            object->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
            auto *material = cache->GetResource<Material>("Materials/VColUnlit.xml");
            object->SetMaterial(material->Clone());
            objectNode->SetDeepEnabled(false);

            _board[i][b].boardCase = objectNode;
            x += scale;
        }
        y -= scale;
    }
}

bool GameBoard::setImpact(int col, int row, IGameBoard::ImpactType impactType)
{
    _board[col][row].state = (int)impactType;
    _board[col][row].boardCase->SetEnabled(true);

    if ((IGameBoard::ImpactType)impactType == IGameBoard::SHIP)
        _board[col][row].boardCase->GetComponent<StaticModel>()->GetMaterial(0)->SetShaderParameter("MatDiffColor", Color::RED);
    else
        _board[col][row].boardCase->GetComponent<StaticModel>()->GetMaterial(0)->SetShaderParameter("MatDiffColor", Color::WHITE);
}

BoardCase GameBoard::selectBoardCase(int col, int row)
{
    _board[col][row].selected = true;

    _board[col][row].boardCase->SetDeepEnabled(true);
    return _board[col][row];
}

BoardCase GameBoard::unselectBoardCase(int col, int row)
{
    _board[col][row].selected = false;

    if (!_board[col][row].state)
        _board[col][row].boardCase->SetDeepEnabled(false);
    return _board[col][row];
}

// SHIP

IShip *GameBoard::placeShip(int col, int row, IShip::ShipDirection shipDirection, IShip::ShipType shipType, bool ghost)
{
    // Get ship size
    int limit = AShip::getShipSize(shipType);

    if (row < 0 || col < 0 || row >= rows || col >= columns)
        return NULL;
    else if (shipDirection == IShip::TOP && ((row - (limit - 1)) < 0 || row < 0))
        return NULL;
    else if (shipDirection == IShip::BOTTOM && ((row + limit) > rows || row > rows))
        return NULL;
    else if (shipDirection == IShip::LEFT && ((col - (limit - 1)) < 0 || col < 0))
        return NULL;
    else if (shipDirection == IShip::RIGHT && ((col + limit) > (columns) || col > columns))
        return NULL;

    // If out of game board bounds
    if (_board[row][col].state != 0)
        return NULL;

    // If not simulating a ship placement actually change the board map
    IShip *newShip = new Ship(xOrigin, yOrigin, row, col, shipDirection, shipType, scene);

    if (ghost)
    {
        newShip->init();
        return newShip;
    }
    else if (testShip(col, row, shipDirection, shipType))
    {
        int row_ = row;
        int col_ = col;

        for (int i = 0; i < limit; ++i)
        {
            _board[row_][col_].state = 1;
            _board[row_][col_].ship = newShip;
            switch (shipDirection)
            {
            case IShip::ShipDirection::BOTTOM:
                ++row_;
                break;
            case IShip::ShipDirection::TOP:
                --row_;
                break;
            case IShip::ShipDirection::RIGHT:
                ++col_;
                break;
            case IShip::ShipDirection::LEFT:
                --col_;
                break;
            }
        }

        newShip->init();
        _ships.push_back(newShip);

        return newShip;
    }
    else
        delete newShip;
    return NULL;
}

bool GameBoard::testShip(int colOrigin, int rowOrigin, IShip::ShipDirection shipDirection, IShip::ShipType shipType, bool ghost)
{
    int size = AShip::getShipSize(shipType);

    int row = rowOrigin;
    int col = colOrigin;

    if (row < 0 || col < 0 || row >= rows || col >= columns)
        return false;
    else if (shipDirection == IShip::TOP && ((row - (size - 1)) < 0 || row < 0))
        return false;
    else if (shipDirection == IShip::BOTTOM && ((row + size) > rows || row > rows))
        return false;
    else if (shipDirection == IShip::LEFT && ((col - (size - 1)) < 0 || col < 0))
        return false;
    else if (shipDirection == IShip::RIGHT && ((col + size) > (columns) || col > columns))
        return false;

    if (!ghost)
    {
        for (int i = 0; i < size; ++i)
        {
            if (_board[row][col].state != 0)
                return false;

            switch (shipDirection)
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
    return true;
}

void GameBoard::updateShip(IShip *ship)
{
    ship->update();
}

bool GameBoard::removeShip(int col, int row)
{
    if (col > columns || col < 0 || row > rows || row < 0)
        return false;

    if (_board[row][col].ship)
    {
        int row_ = row;
        int col_ = col;
        int limit = AShip::getShipSize(_board[row][col].ship->getType());
        IShip::ShipDirection direction = _board[row][col].ship->getDirection();

        delete _board[row][col].ship;

        for (int i = 0; i < limit; ++i)
        {
            _board[row_][col_] = BoardCase();
            switch (direction)
            {
            case IShip::ShipDirection::BOTTOM:
                ++row_;
                break;
            case IShip::ShipDirection::TOP:
                --row_;
                break;
            case IShip::ShipDirection::RIGHT:
                ++col_;
                break;
            case IShip::ShipDirection::LEFT:
                --col_;
                break;
            }
        }
    }
}

// UTILS

bool GameBoard::isBoardCaseValid(uint col, uint row)
{
    if (row < 0 || col < 0 || row >= rows || col >= columns)
        return false;
    return true;
}

void GameBoard::logBoard()
{
    for (int i = 0; i < _board.size(); ++i)
    {
        for (int b = 0; b < _board[i].size(); ++b)
        {
            std::cout << _board[i][b].state << (b == (_board[i].size() - 1) ? ' ' : ',');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}