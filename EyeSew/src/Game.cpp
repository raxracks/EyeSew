#include "Game.hpp"

Game::Game()
{
    game = new Instance("game");
    gameClone = nullptr;
    workspace = new Instance("Workspace", game);
    camera = new Instance("Camera", game);
}

Instance* Copy(Instance* instance)
{
    Instance* clone = new Instance(*instance);
    clone->child = nullptr;
    for (Instance* child : instance->GetChildren()) {
        Instance* childClone = Copy(child);
        childClone->Parent = nullptr;
        childClone->SetParent(clone);
    }

    return clone;
}

void Game::Run()
{
    gameClone = game;
    game = Copy(game);
    workspace = game->FindFirstChild("Workspace");
    camera = game->FindFirstChild("Camera");

    for (Instance* child : game->GetDescendants()) {
        if (child->IsA("Script")) {
            Script* script = new Script(game, workspace, child, child->Code);
            m_Scripts.push_back(script);
        }
    }

    running = true;
}

void Game::Stop()
{
    Instance* toDelete = game;
    game = gameClone;
    toDelete->Destroy();
    workspace = game->FindFirstChild("Workspace");
    camera = game->FindFirstChild("Camera");

    for (Script* s : m_Scripts) {
        s->~Script();
    }

    running = false;
}
