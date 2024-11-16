// Pin.h
#ifndef PIN_H
#define PIN_H

#include <string>

class Pin
{
public:
    enum class DataType
    {
        Integer,
        Float,
        String,
		Boolean,
		Vector2,
		Vector3,
		Vector4,
		Matrix3x3,
		Matrix4x4,
		Quaternion,
		Color,
		Texture,
		Audio,
		Video,
		Animation,
		Font,
		Mesh,
		Material,
		Shader,
		Script,
		Scene,
		Physics,
		Particle,
		Light,
		Camera,
		Animation2D,
		Font2D,
		Mesh2D,
		Material2D,
		Shader2D,
		Script2D,
		Scene2D,
		Physics2D,
		Particle2D,
		Light2D,
		Camera2D,
		Animation3D,
		Font3D,
		Mesh3D,
		Material3D,
		Shader3D,
		Script3D,
		Scene3D,
		Physics3D,
		Particle3D,
		Light3D,
		Camera3D,
        // ... add other data types as needed
    };

    Pin(DataType dataType) : dataType(dataType) {}
	~Pin() {}

    DataType GetDataType() const { return dataType; }
	std::string GetName() const { return name; }
	std::any GetData() const { return data; }

private:
    DataType dataType;
	std::string name;
	std::any data;
};

#endif // PIN_H
