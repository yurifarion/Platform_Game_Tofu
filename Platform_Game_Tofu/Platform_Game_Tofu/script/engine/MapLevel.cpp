#include "MapLevel.h"


MapLevel::MapLevel()
{}
MapLevel::MapLevel(const int row, const int collumn)
{
    Map2D vec(row, std::vector<int>(collumn, 0));
    m_mapdatabackground = vec;
    m_mapdataforeground = vec;
}
void MapLevel::setIndexBackground(const int row, const int collumn, const int value)
{
    m_mapdatabackground[row][collumn] = value;
}
void MapLevel::setIndexForeground(const int row, const int collumn, const int value)
{
    m_mapdataforeground[row][collumn] = value;
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
        for (int row = 0; row < m_mapdatabackground.size(); ++row)
        {
            for (int collum = 0; collum < m_mapdatabackground[row].size(); collum++)
            {
                MyFile << m_mapdatabackground[row][collum] << " ";
            }
            MyFile << std::endl;
        }
        for (int row = 0; row < m_mapdataforeground.size(); ++row)
        {
            for (int collum = 0; collum < m_mapdataforeground[row].size(); collum++)
            {
                MyFile << m_mapdataforeground[row][collum] << " ";
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
    for (int row = 0; row < m_mapdatabackground.size(); ++row)
    {
        for (int collum = 0; collum < m_mapdatabackground[row].size(); collum++)
        {
            MyFile << m_mapdatabackground[row][collum] << " ";
        }
        MyFile << std::endl;
    }
    
    for (int row = 0; row < m_mapdataforeground.size(); ++row)
    {
        for (int collum = 0; collum < m_mapdataforeground[row].size(); collum++)
        {
            MyFile << m_mapdataforeground[row][collum] << " ";
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

    bool isOutLimit = row >= m_mapdatabackground.size() * 2 && collumn >= m_mapdatabackground[0].size();

    if (file.fail())
    {
        std::cout << "File reading failed"<<std::endl;
    }
    while (file.good() && !isOutLimit)
    {
        file >> str;
        
        if (collumn != 0 && collumn % m_mapdatabackground[0].size() == 0)
        {
            row++;
            collumn = 0;
        }
        isOutLimit = row >= (m_mapdatabackground.size() * 2 )|| collumn >= m_mapdatabackground[0].size();
        if (!isOutLimit)
        {
            if (row >= m_mapdatabackground.size())
            {
                auto rowsize = m_mapdataforeground.size();
                m_mapdataforeground[row - rowsize][collumn] = std::stoi(str);
            }
            else
            {
                m_mapdatabackground[row][collumn] = std::stoi(str);
            }
        }
        collumn++;
    }
    std::cout << "Loaded map file from " << m_path<<std::endl;
}
Map2D& MapLevel::getMapDataBackground()
{
    return m_mapdatabackground;
}
Map2D& MapLevel::getMapDataForeground()
{
    return m_mapdataforeground;
}