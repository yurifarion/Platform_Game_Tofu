#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

typedef std::vector<std::vector<int>> Map2D;

class MapLevel
{
	Map2D m_mapdatadarkestbackground;
	Map2D m_mapdatabackground;
	Map2D m_mapdataforeground;
	bool m_mapCreated = false;
	std::string m_path;

public:

	MapLevel();
	MapLevel(const int row,const int collumn);

	void setIndexBackground(const int row, const int collumn, const int value);
	void setIndexDarkestBackground(const int row, const int collumn, const int value);
	void setIndexForeground(const int row, const int collumn, const int value);
	void createMapFile(const std::string& path);
	void loadfromMapFile(const std::string& path);
	void saveMapFile();
	Map2D& getMapDataBackground();
	Map2D& getMapDataForeground();
	Map2D& getMapDataDarkestBackground();
};