#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "tigl.h"

class Material;

class GameObject
{
	private:
		//Inner classes
		class IndexedVertex
		{
			public:
				int pos;
				int texture;
				int normal;
		};

		struct ObjectGroup
		{
			std::string name;
			int materialIndex;
			std::vector<std::vector<IndexedVertex>> faces;
		};

		//Vars
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureCoords;
		std::vector<ObjectGroup*> groups;
		std::vector<Material*> materials;

		//Material loader
		void LoadMaterialFile(const std::string& fileName, const std::string& dirName);

	public:
		GameObject(const std::string& fileName);
		~GameObject(void);

		void Draw() const;
};

//String extension methods
static std::string Replace(std::string& str, const std::string& toReplace, const std::string& replacement);
static std::vector<std::string> Split(std::string str, const std::string& separator);
static inline std::string ToLower(std::string data);
static inline std::string CleanLine(std::string line);
