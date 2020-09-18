#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std; 
  
int main() 
{ 
      
    string IP = "192.168.1.254"; 
      
    // Vector of string to save tokens 
    vector <string> valores; 
      
    // stringstream class check1 
    stringstream check1(IP); 
      
    string intermediate; 
      
    // Tokenizing w.r.t. space ' ' 
    while(getline(check1, intermediate, '.')) 
    { 
        valores.push_back(intermediate); 
    } 
      
    string localIp = valores[0] + "." + valores[1] + "." + valores[2];
    string userIP = valores[valores.size()-1];

    cout << IP << endl;
    cout << localIp << endl;
    cout << userIP << endl;
} 