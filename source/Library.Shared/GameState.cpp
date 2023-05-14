#include "pch.h"
#include "GameState.h"

namespace FieaGameEngine
{
    GameState* GameState::Instance()
    {
        return _instance;
    }
    void GameState::CreateInstance()
    {
        assert(_instance == nullptr);
        _instance = new GameState();
    }
    void GameState::DestroyInstance()
    {
        delete _instance;
        _instance = nullptr;
    }
    GameTime GameState::Time()
    {
        return _time;
    }
    void GameState::SetGameTime(GameTime t)
    {
        _time = t;
    }
}