#ifndef MOTHERBOARD_HPP
#define MOTHERBOARD_HPP

#include <vector>
#include "PcPart.hpp"
#include "RAM.hpp"
#include "CPU.hpp"

class Motherboard : public PcPart
{
	public:
		Motherboard(const std::string& name, CpuSocketType socketType, RamSocketType ramSocketType,
		            const std::string& objectPath, const int tier);
		~Motherboard();

		void AddComponent(PcPart* component);
		void RemoveComponent(PcPart* component);
		std::string GetObjectPath() const override;

		void Display() const override;
		std::string GetName() const override;

		CpuSocketType socketType;
		RamSocketType ramSocketType;

	private:
		std::vector<PcPart*> childComponents;
		std::string objectPath;
};

#endif  // MOTHERBOARD_HPP
