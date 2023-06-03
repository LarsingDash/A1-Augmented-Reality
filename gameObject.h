#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

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
			int materialIndex = -1;
			std::vector<std::vector<IndexedVertex>> faces;
		};

		//Vars
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureCoords;
		std::vector<ObjectGroup*> groups;
		std::vector<Material*> materials;

		//Material loader
		void LoadMaterialFile(const std::string& mtlPath);

	public:
		GameObject(const std::string& dir, const std::string& fileName);
		~GameObject(void);

		void Draw(glm::mat4 translation) const;
};

//String extension methods
static std::string Replace(std::string& str, const std::string& toReplace, const std::string& replacement);
static std::vector<std::string> Split(std::string str, const std::string& separator);
static inline std::string ToLower(std::string data);
static inline std::string CleanLine(std::string line);
