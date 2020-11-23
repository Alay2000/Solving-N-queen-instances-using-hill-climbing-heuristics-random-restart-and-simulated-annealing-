#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include<map>
#include<iterator>
#include<iostream>

void WriteCSV(std::string filename, std::map<int, double> mapp){
 
    std::ofstream myFile {filename, std::ios_base::app};
    std::map<int, double>::iterator itr; 
    
    for (itr = mapp.begin(); itr != mapp.end(); ++itr) { 
    myFile << itr->first 
             << " " << itr->second << '\n'; 
    } 
    

    myFile.close();
}


       // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size
    
    // Create an output filestream object
    // Send column names to the stream
    // for(int j = 0; j < dataset.size(); ++j)
    // {
    //     myFile << dataset.at(j).first;
    //     if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    // }
    // myFile << "\n";
    
    // // Send data to the stream
    // for(int i = 0; i < dataset.at(0).second.size(); ++i)
    // {
    //     for(int j = 0; j < dataset.size(); ++j)
    //     {
    //         myFile << dataset.at(j).second.at(i);
    //         if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    //     }
    //     myFile << "\n";
    // }
    
    // Close the file
    // myFile.close();


// int main() {
//     // Make three vectors, each of length 100 filled with 1s, 2s, and 3s
//   std::map<int, double> mapp;
//   mapp.insert(std::pair<int,double>(1 ,0.343));
    
//     // Wrap into a vector
     
    
//     // Write the vector to CSV
//     WriteCSV("three_cols", mapp);
    
//     return 0;
// }
