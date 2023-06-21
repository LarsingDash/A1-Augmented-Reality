#ifndef FAN_FPP
#define FAN_HPP

#include "PcPart.hpp"
#include <string>

class Fan : public PcPart
{
	public:
		Fan(const std::string& name, const std::string& objectPath, const int tier);
		~Fan();

		std::string GetName() const override;
		std::string GetObjectPath() const override;
		void Display() const override;

	private:
		std::string objectPath;
};

#endif
