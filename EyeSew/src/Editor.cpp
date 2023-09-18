#include "Editor.hpp"

Editor::Editor(Game &game, RenderTexture &renderTexture)
    : m_Game(game), m_RenderTexture(renderTexture), m_SelectedChild(nullptr),
      m_LastSize(0, 0), m_ShowMetrics(false) {
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
  ImFontConfig icons_config;
  icons_config.MergeMode = true;
  icons_config.PixelSnapH = true;
  icons_config.FontDataOwnedByAtlas = false;
  icons_config.GlyphRanges = icons_ranges;
  m_FiraFont = io.Fonts->AddFontFromFileTTF(
      "assets/FiraCode/FiraCode-Regular.ttf", 20.0f);
  m_MainFont =
      io.Fonts->AddFontFromFileTTF("assets/Roboto/Roboto-Regular.ttf", 18.0f);
  io.Fonts->AddFontFromMemoryCompressedTTF(
      (void *)fa_solid_900_compressed_data, fa_solid_900_compressed_size,
      FONT_AWESOME_ICON_SIZE, &icons_config, icons_ranges);
  rlImGuiReloadFonts();

  // m_TextEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
}

void Editor::Update() {
  if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_M)) {
    m_ShowMetrics = true;
  }
}

void Editor::DrawUI() {
  ImGui::PushFont(m_MainFont);
  ImGui::DockSpaceOverViewport();
  ShowViewport();
  ShowMetrics();
  ShowProperties();
  ShowPlayMenu();
  ShowInspector();
  ImGui::PopFont();
}

void Editor::ShowInspector() {
  ImGui::Begin("Inspector");
  {
    ImGui::BeginDisabled(m_SelectedChild == nullptr);
    {
      if (ImGui::Button("+")) {
        ImGui::OpenPopup("popup_new");
      }

      if (ImGui::BeginPopup("popup_new")) {
        for (std::pair<std::string, uint32_t> IClass : Instance::Classes) {
          if (ImGui::Button(IClass.first.c_str())) {
            Instance *instance = new Instance(IClass.first, m_SelectedChild);
            ImGui::CloseCurrentPopup();
          }
        }
        ImGui::EndPopup();
      }

      ImGui::SameLine();
      if (ImGui::Button("-")) {
        m_SelectedChild->Destroy();
      }
    }
    ImGui::EndDisabled();

    DrawChildren(m_Game.game);
  }
  ImGui::End();
}

void Editor::ShowViewport() {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("Viewport");
  {
    ImVec2 size = ImGui::GetContentRegionAvail();
    if ((size.x != m_LastSize.x || size.y != m_LastSize.y) &&
        !ImGui::IsMouseDragging(MouseButton::MOUSE_BUTTON_LEFT)) {
      m_LastSize = size;
      UnloadRenderTexture(m_RenderTexture);
      m_RenderTexture = LoadRenderTexture((int)size.x, (int)size.y);
    }

    rlImGuiImageRenderTexture(&m_RenderTexture);
  }
  ImGui::End();
  ImGui::PopStyleVar();
}

void Editor::ShowMetrics() {
  if (m_ShowMetrics) {
    ImGui::Begin("Metrics", &m_ShowMetrics, ImGuiWindowFlags_AlwaysAutoResize);
    {
      ImGui::Text("FPS: %d", GetFPS());
      ImGui::Text("Frame time: %fms", GetFrameTime());
      m_FrameTimes.push_back(GetFrameTime());
      if (m_FrameTimes.size() > 100)
        m_FrameTimes.erase(m_FrameTimes.begin());

      ImGui::PlotLines("##frametimes", &m_FrameTimes[0],
                       (int)m_FrameTimes.size(), 0, 0, 0.0f, 0.5f,
                       ImVec2(200, 50));
    }
    ImGui::End();
  }
}

void Editor::ShowProperties() {
  if (m_SelectedChild) {
    ImGui::Begin(("Properties - " + m_SelectedChild->ClassName + " \"" +
                  m_SelectedChild->Name + "\"###properties")
                     .c_str());
    {
      ImGui::Text("Name");
      ImGui::InputText("##name", &m_SelectedChild->Name);

      uint32_t props = m_SelectedChild->Properties;
      if (props & Properties::Position) {
        ImGui::Text("Position");
        ImGui::DragFloat3("##position", &m_SelectedChild->Position.X);
      }
      if (props & Properties::Size) {
        ImGui::Text("Size");
        ImGui::DragFloat3("##size", &m_SelectedChild->Size.X);
      }
      if (props & Properties::Color) {
        ImGui::Text("Color");
        ImGui::ColorEdit4("##color", &m_SelectedChild->Color.R);
      }
      if (props & Properties::Distance) {
        ImGui::Text("Distance");
        ImGui::DragFloat("##distance", &m_SelectedChild->Distance);
      }
      if (props & Properties::Code) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Edit");
        {
          // ImGui::PushFont(m_FiraFont);
          //  m_TextEditor.Render("##code");
          //  m_SelectedChild->Code = boost::join(m_TextEditor.GetTextLines(),
          //  "\n");
          // ImGui::PopFont();
        }
        ImGui::End();
        ImGui::PopStyleVar();
      }
    }
    ImGui::End();
  }
}

void Editor::ShowPlayMenu() {
  ImGui::Begin("Play");
  {
    if (!m_Game.running) {
      if (ImGui::Button(ICON_FA_PLAY)) {
        m_Game.Run();
      }
    } else {
      if (ImGui::Button(ICON_FA_STOP)) {
        m_Game.Stop();
      }
    }
  }
  ImGui::End();
}

void Editor::DrawChildren(Instance *i) {
  if (i) {
    for (Instance *child : i->GetChildren()) {
      if (child) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow |
                                   ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                   ImGuiTreeNodeFlags_SpanAvailWidth;
        if (m_SelectedChild == child)
          flags |= ImGuiTreeNodeFlags_Selected;

        bool isOpen = ImGui::TreeNodeEx(child, flags, child->Name.c_str());
        if (ImGui::IsItemClicked()) {
          m_SelectedChild = child;
          /*if (m_SelectedChild->IsA("Script"))
              m_TextEditor.SetText(m_SelectedChild->Code);*/
        }
        if (isOpen) {
          if (child->GetChildren().size() > 0)
            DrawChildren(child);
          ImGui::TreePop();
        }
      }
    }
  }
}
