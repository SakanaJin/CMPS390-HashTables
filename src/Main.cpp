#include<iostream>
#include<fstream>
#include<string>

class HashTable{
private:
    std::string* hashTable;
    int tableLen;
    int clashCount;
    int total;

    std::string toLower(std::string name){//converts all the chars in a str to lowercase
        char c;
        std::string lowered = "";
        for(int i = 0; i < name.length(); i++){
            c = name[i];
            if(c <= 'Z' && c >= 'A'){
                c = c - ('Z' - 'z');
            }
            lowered = lowered + c;
        }
        return lowered;
    }

public:
    HashTable(int tablen){
        tableLen = tablen;
        clashCount = 0;
        total = 0;
        hashTable = new std::string[tablen];
        for(int i = 0; i < tablen; i++){
            hashTable[i] = "#";
        }
    }

    ~HashTable(){
        delete[] hashTable;
        hashTable = NULL;
    }

    void add(std::string ogname){
        std::string name = toLower(ogname);
        int namedex = int((((name[0] - 'a') * 676) + ((name[1] - 'a') * 26)) / (20000 / tableLen)) + (name[2] - 'a')/3; //dont worry about it
        bool placing = true;
        while(placing){
            if(hashTable[namedex] != "#"){
                namedex++;
                clashCount++;
            }
            else{
                placing = false;
            }
            if(namedex >= tableLen){
                return;
            }
        }
        hashTable[namedex] = ogname;
        total++;
    }

    int getClashes(){
        return clashCount;
    }

    int getTotal(){
        return total;
    }

    void showNames(){
        for(int i = 0; i < tableLen; i++){
            if(hashTable[i] != "#"){
                std::cout << hashTable[i] << "\n";
            }
        }
    }

    void showTable(){//shows the names with the spaces in between
        for(int i = 0; i < tableLen; i++){
            std::cout << hashTable[i] << '\n';
        }
    }

};

int main(){
    HashTable names = HashTable(700);
    std::cout << "Enter in the entire filepath to a list of names\n>>> ";
    std::string filepath;
    std::getline(std::cin, filepath);
    std::ifstream file;
    file.open(filepath.c_str());
    if(file.is_open() == 0){
         std::cout << "Invalid filepath";
         return 1;
    }
    std::string name;
    while(file >> name){
        names.add(name);
    }
    file.close();
    names.showNames();
    std::cout << '\n' << "Clashes: " << names.getClashes();
    return 0;
}