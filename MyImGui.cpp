#include "MyImGui.h"

void DispVector2(const std::string& label, Vector2& vector) {

	ImGui::InputFloat2(label.c_str(), &vector.x, "%.3f", ImGuiInputTextFlags_ReadOnly);

}

void DispFloat(const std::string& label, float& val) {

	ImGui::InputFloat(label.c_str(), &val, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly);

}