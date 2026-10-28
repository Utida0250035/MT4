#pragma once
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix3D.h"
#include <string>

class MathImGui {

private:
	MathImGui() = default;

public:
	static void DispQuaternion(const std::string& label, Quaternion& data);
	static void DispVec3(const std::string& label, Vector3& data);
	static void DispMat4x4(const std::string& label, Matrix4x4& data);
	static void DispFloat(const std::string& label, float& data);
};