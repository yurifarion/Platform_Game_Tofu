#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

typedef std::vector<std::vector<int>> Map2D;

class MapLevel
{
	Map2D m_mapdata;
	bool m_mapCreated = false;
	std::string m_path;

public:

	MapLevel();
	MapLevel(const int row,const int collumn);

	void setIndex(const int row, const int collumn, const int value);
	void createMapFile(const std::string& path);
	void loadfromMapFile(const std::string& path);
	void saveMapFile();
	Map2D& getMapData();
};