#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>
using namespace std;

void replace(string &line, char at, char with)
{
  for (int i = 0; i < line.length(); i++)
  {
    if (line[i] == at)
    {
      line[i] = with;
    }
  }
}

void calculateBrandAverage(vector<string> vBrand, vector<float> vPrice, ofstream &out_stream)
{ // Calculates the average price per brand
  map<string, vector<float>> brandMap;

  for (int i = 0; i < vBrand.size(); i++)
  {
    brandMap[vBrand[i]].push_back(vPrice[i]);
  }

  out_stream << "Brand\tAverage\n";

  map<string, vector<float>>::iterator it;

  for (it = brandMap.begin(); it != brandMap.end(); it++)
  {
    string curBrand = it->first;
    vector<float> curPrices = it->second;
    float brandSum = accumulate(curPrices.begin(), curPrices.end(), 0.0);
    float average = brandSum / curPrices.size();

    out_stream << curBrand << "\t\t" << average << "\n";
  }

  out_stream << endl;
}

void calculateCategoryAverage(vector<string> vCategory, vector<float> vPrice, ofstream &out_stream)
{ // Calculates the average price per category
  map<string, vector<float>> categoryMap;

  for (int i = 0; i < vCategory.size(); i++)
  {
    categoryMap[vCategory[i]].push_back(vPrice[i]);
  }

  out_stream << "Category\tAverage\n";

  map<string, vector<float>>::iterator it;

  for (it = categoryMap.begin(); it != categoryMap.end(); it++)
  {
    string curCategory = it->first;
    vector<float> curPrices = it->second;
    float categorySum = accumulate(curPrices.begin(), curPrices.end(), 0.0);
    float average = categorySum / curPrices.size();

    out_stream << curCategory << "\t\t\t" << average << "\n";
  }

  out_stream << endl;
}

void calculateSKU(vector<int> vYear, vector<int> vSKU, ofstream &out_stream)
{
  map<int, vector<int>> yearMap;

  for (int i = 0; i < vYear.size(); i++)
  {
    yearMap[vYear[i]].push_back(vSKU[i]);
  }

  out_stream << "Year\tSKU's\n";

  map<int, vector<int>>::iterator it;

  for (it = yearMap.begin(); it != yearMap.end(); it++)
  {
    out_stream << it->first << "\t";

    vector<int>::iterator sku_it;

    for (sku_it = it->second.begin(); sku_it != it->second.end(); sku_it++)
    {
      out_stream << *sku_it;

      if (sku_it != it->second.end())
      {
        out_stream << " ";
      }
      else
      {
        out_stream << "\t";
      }
    }

    out_stream << "(Count: " << it->second.size() << ")" << endl;
  }
}

int main()
{
  vector<int> vSKU;
  vector<string> vBrand;
  vector<string> vCategory;
  vector<int> vYear;
  vector<float> vPrice;

  ifstream in_stream;
  ofstream out_stream;

  in_stream.open("data.csv");
  out_stream.open("output.txt");

  if (!in_stream.fail())
  {
    string line;
    getline(in_stream, line);

    while (getline(in_stream, line))
    {
      replace(line, ',', ' ');

      stringstream ss(line);

      int iSKU;
      string brand;
      string category;
      int iYear;
      float fPrice;

      ss >> iSKU;
      ss >> brand;
      ss >> category;
      ss >> iYear;
      ss >> fPrice;

      vSKU.push_back(iSKU);
      vBrand.push_back(brand);
      vCategory.push_back(category);
      vYear.push_back(iYear);
      vPrice.push_back(fPrice);
    }

    in_stream.close();
  }
  else
  {
    out_stream << "Unable to open file";
  }

  out_stream << "SKU"
         << "\t"
         << "Brand"
         << "\t"
         << "Category"
         << "\t\t"
         << "Year"
         << "\t"
         << "Price"
         << endl;

  for (int j = 0; j < vSKU.size(); j++)
  {
    out_stream << vSKU[j] << "\t" << vBrand[j] << "\t   " << vCategory[j] << "\t\t\t\t" << vYear[j] << "\t" << vPrice[j] << endl;
  }

  out_stream << endl;


  calculateBrandAverage(vBrand, vPrice, out_stream);

  calculateCategoryAverage(vCategory, vPrice, out_stream);

  calculateSKU(vYear, vSKU, out_stream);

  in_stream.close();
  out_stream.close();
}