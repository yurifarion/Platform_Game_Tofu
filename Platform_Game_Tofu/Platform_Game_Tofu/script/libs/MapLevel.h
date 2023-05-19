#pragma once
#include <vector>
class MapLevel
{
	std::vector<std::vector<int>> m_mapdata;
	bool m_mapCreated = false;

public:

	MapLevel();
	MapLevel(const int row,const int collumn);

	void setIndex(const int row, const int collumn, const int value);
	void createMapFile();
	void saveMapFile();
};