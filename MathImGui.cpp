#include "MathImGui.h"
#include <ImGui.h>

void MathImGui::DispQuaternion(const std::string& label, Quaternion& data) {

	ImGui::Text(label.c_str());
	ImGui::InputFloat4("", &data.x, "%.3f", ImGuiInputTextFlags_ReadOnly);

}

void MathImGui::DispVec3(const std::string& label, Vector3& data) {

	ImGui::Text(label.c_str());
	ImGui::InputFloat3("", &data.x, "%.3f", ImGuiInputTextFlags_ReadOnly);

}

void MathImGui::DispMat4x4(const std::string& label, Matrix4x4& data) {

	ImGui::Text(label.c_str());

	for (auto* row : data.m) {

		ImGui::InputFloat4("", row, "%.3f", ImGuiInputTextFlags_ReadOnly);

	}

}

void MathImGui::DispFloat(const std::string& label, float& data) {

	ImGui::Text(label.c_str());

	ImGui::InputFloat("", &data, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly);

}