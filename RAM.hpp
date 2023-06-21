#ifndef RAM_HPP
#define RAM_HPP

#include "PcPart.hpp"
#include <string>

enum class RamSocketType
{
	DDR3,
	DDR4
};

class RAM : public PcPart
{
	public:
		RamSocketType socketType;

		RAM(const std::string& name, RamSocketType socketType, const std::string& objectPath, const int tier);
		~RAM();

		std::string GetName() const override;
		std::string GetObjectPath() const override;
		void Display() const override;

	private:
		std::string objectPath;
};

#endif  // RAM_HPP
