#include "MapLevel.h"


MapLevel::MapLevel()
{}
MapLevel::MapLevel(const int row, const int collumn)
{
    Map2D vec(row, std::vector<int>(collumn, 0));
    m_mapdata = vec;
}
void MapLevel::setIndex(const int row, const int collumn, const int value)
{
    m_mapdata[row][collumn] = value;
}
void MapLevel::createMapFile(const std::string& path)
{
    m_path = path;
    //Open a text file
    std::ofstream MyFile(path);

    if (!m_mapCreated)
    {
        m_mapCreated = true;

        // Create and open a text file
        std::ofstream MyFile(m_path);

        // Write to the file
        for (int row = 0; row < m_mapdata.size(); ++row)
        {
            for (int collum = 0; collum < m_mapdata[row].size(); collum++)
            {
                MyFile << m_mapdata[row][collum] << " ";
            }
            MyFile << std::endl;
        }

        // Close the file
        MyFile.close();

    }
    std::cout << "Created map file from " << m_path << std::endl;
}
void MapLevel::saveMapFile()
{
    //Open a text file
    std::ofstream MyFile(m_path);

    // Write to the file
    for (int row = 0; row < m_mapdata.size(); ++row)
    {
        for (int collum = 0; collum < m_mapdata[row].size(); collum++)
        {
            MyFile << m_mapdata[row][collum] << " ";
        }
        MyFile << std::endl;
    }

    // Close the file
    MyFile.close();
    std::cout << "Saved map file at " << m_path << std::endl;
}
void MapLevel::loadfromMapFile(const std::string& path)
{
    m_path = path;
    std::ifstream file(m_path);
    std::string str;
    int row = 0;
    int collumn = 0;

    bool isOutLimit = row >= m_mapdata.size() && collumn >= m_mapdata[0].size();

    if (file.fail())
    {
        std::cout << "File reading failed"<<std::endl;
    }
    while (file.good() && !isOutLimit)
    {
        file >> str;
        
        if (collumn != 0 && collumn % m_mapdata[0].size() == 0)
        {
            row++;
            collumn = 0;
        }
        isOutLimit = row >= m_mapdata.size() || collumn >= m_mapdata[0].size();
        if(!isOutLimit) m_mapdata[row][collumn] = std::stoi(str);
        
        collumn++;
    
        
    }
    std::cout << "Loaded map file from " << m_path<<std::endl;
}
Map2D& MapLevel::getMapData()
{
    return m_mapdata;
}