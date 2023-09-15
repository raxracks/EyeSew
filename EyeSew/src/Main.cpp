#include "Editor.hpp"
#include "Game.hpp"
#include "Instance.hpp"
#include "Script.hpp"
#include <imgui.h>
#include <raylib.h>
#include <rlImGui.h>
#include <vector>

int main() {
  SetExitKey(KEY_NULL);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "iso");
  SetTargetFPS(60);
  MaximizeWindow();
  rlImGuiSetup(true);

  Game game;
  RenderTexture viewport = LoadRenderTexture(600, 400);
  Editor editor(game, viewport);

  new Instance("Part", game.workspace);
  Instance *script = new Instance("Script", game.workspace);
  script->Code = R"(
    for i, v in workspace:GetChildren() do
      print(i, v.Name, v:IsA("Part"))
    end
  )";

  // for (int i = 0; i < 10000; i++)
  //   new Instance("Part", game.workspace);

  bool editing = true;

  /*std::thread([&]() {
      std::vector<Instance*> p;

      while (true) {
          p.clear();
          for (Instance* child : game.workspace->GetDescendants()) {
              if (child->IsA("Part"))
                  p.push_back(child);
          }
          parts = p;
          std::this_thread::sleep_for(std::chrono::seconds(1));
      }
  }).detach();*/

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_E)) {
      editing = !editing;
    }

    if (editing) {
      editor.Update();
      BeginTextureMode(viewport);
    } else
      BeginDrawing();
    {
      ClearBackground(WHITE);
      BeginMode3D(game.camera->Camera);
      {
        DrawGrid(100, 1);
        for (Instance *child : game.workspace->GetDescendants()) {
          if (child->IsA("Part"))
            DrawCube(child->Position, child->Size.X, child->Size.Y,
                     child->Size.Z, child->Color);
        }
      }
      EndMode3D();
    }

    if (editing)
      EndTextureMode();
    else
      EndDrawing();

    if (editing) {
      BeginDrawing();
      {
        ClearBackground(BLACK);

        rlImGuiBegin();
        editor.DrawUI();
        rlImGuiEnd();
      }
      EndDrawing();
    }
  }

  rlImGuiShutdown();
  CloseWindow();
}
