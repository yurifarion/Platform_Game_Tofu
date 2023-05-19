#include "MapLevel.h"
#include <fstream>

MapLevel::MapLevel()
{}
MapLevel::MapLevel(const int row, const int collumn)
{
    std::vector<std::vector<int>> vec(row, std::vector<int>(collumn, 0));
    m_mapdata = vec;
}
void MapLevel::setIndex(const int row, const int collumn, const int value)
{
    m_mapdata[row][collumn] = value;
}
void MapLevel::createMapFile()
{
    if (!m_mapCreated)
    {
        m_mapCreated = true;

        // Create and open a text file
        std::ofstream MyFile("filename.level");

        // Write to the file
        MyFile << "Files can be tricky, but it is fun enough!";
     
        // Close the file
        MyFile.close();
      
    }
}
void MapLevel::saveMapFile()
{

}