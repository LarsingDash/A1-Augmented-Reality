#ifndef PSU_HPP
#define PSU_HPP

#include "PcPart.hpp"
#include <string>

class PSU : public PcPart
{
	public:
		PSU(const std::string& name, const std::string& objectPath, const int tier);
		~PSU();

		std::string GetName() const override;
		std::string GetObjectPath() const override;
		void Display() const override;

	private:
		std::string objectPath;
};

#endif // PSU_HPP
