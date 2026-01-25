#include <vector>
#include <fstream>

class Cartridge {
private:
	std::vector<uint8_t> ROM;
	std::vector<uint8_t> RAM {};
public:
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t val);
	bool loadGame(const std::string& fname);
};