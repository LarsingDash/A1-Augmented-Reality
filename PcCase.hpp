#ifndef PCCASE_HPP
#define PCCASE_HPP

#include <vector>
#include "PcPart.hpp"

class PcCase : public PcPart
{
	public:
		PcCase(const std::string& name, const std::string& objectPath, const int tier);
		~PcCase();

		void AddComponent(PcPart* component);
		void RemoveComponent(PcPart* component);

		std::string GetName() const override;
		std::string GetObjectPath() const override;

		void Display() const override;

	private:
		std::vector<PcPart*> childComponents;
		std::string objectPath;
};

#endif  // PCCASE_HPP
