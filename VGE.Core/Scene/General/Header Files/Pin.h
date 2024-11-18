#pragma once
#ifndef VGE_CORE_SCENE_GENERAL_PIN_H
#define VGE_CORE_SCENE_GENERAL_PIN_H

// Include standard library headers
#include <string> // For std::string

namespace VGE
{
	// Pin class
	class Pin
	{
	public:
		// Data type of the pin
		enum class DataType
		{
			Integer, // Integer data type
			Float, // Float data type
			String, // String data type
			Boolean, // Boolean data type
			Vector2, // 2D vector data type
			Vector3, // 3D vector data type
			Vector4, // 4D vector data type
			Matrix3x3, // 3x3 matrix data type
			Matrix4x4, // 4x4 matrix data type
			Quaternion, // Quaternion data type
			Color, // Color data type
			Texture, // Texture data type
			Audio, // Audio data type
			Video, // Video data type
			Animation, // Animation data type
			Font, // Font data type
			Mesh, // Mesh data type
			Material, // Material data type
			Shader, // Shader data type
			Script, // Script data type
			Scene, // Scene data type
			Physics, // Physics data type
			Particle, // Particle data type
			Light, // Light data type
			Camera, // Camera data type
			Animation2D, // 2D animation data type
			Font2D, // 2D font data type
			Mesh2D, // 2D mesh data type
			Material2D, // 2D material data type
			Shader2D, // 2D shader data type
			Script2D, // 2D script data type
			Scene2D, // 2D scene data type
			Physics2D, // 2D physics data type
			Particle2D, // 2D particle data type
			Light2D, // 2D light data type
			Camera2D, // 2D camera data type
			Animation3D, // 3D animation data type
			Font3D, // 3D font data type
			Mesh3D, // 3D mesh data type
			Material3D, // 3D material data type
			Shader3D, // 3D shader data type
			Script3D, // 3D script data type
			Scene3D, // 3D scene data type
			Physics3D, // 3D physics data type
			Particle3D, // 3D particle data type
			Light3D, // 3D light data type
			Camera3D, // 3D camera data type

			// ... add other data types as needed
		};
	};
}


#endif // VGE_CORE_SCENE_GENERAL_PIN_H
