#ifndef CPU_HPP
#define CPU_HPP

#include "PcPart.hpp"
#include <string>

enum class CpuSocketType
{
	INTEL,
	AMD
};

class CPU final : public PcPart
{
	public:
		CPU(const std::string& name, CpuSocketType socketType, const std::string& objectPath, const int tier);
		~CPU();

		std::string GetName() const override;
		void Display() const override;
		std::string GetObjectPath() const override;

		CpuSocketType socketType;

	private:
		std::string objectPath;
};
#endif
