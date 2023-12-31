#pragma once
#include "Game.hpp"
// #include "ImGuiColorTextEdit/TextEditor.h"
#include "Instance.hpp"
#include "extras/FA6FreeSolidFontData.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include <raylib.h>
#include <rlImGui.h>

class Editor {
public:
  Editor(Game &game, RenderTexture &renderTexture);

  void Update();
  void DrawUI();
  void ShowMetrics();

  Instance *m_SelectedChild;

private:
  Game &m_Game;
  RenderTexture &m_RenderTexture;
  ImVec2 m_LastSize;
  // TextEditor m_TextEditor;
  ImFont *m_MainFont;
  ImFont *m_FiraFont;
  bool m_ShowMetrics;
  std::vector<float> m_FrameTimes;

  void ShowInspector();
  void ShowViewport();
  void ShowProperties();
  void ShowPlayMenu();

  void DrawChildren(Instance *i);
};
