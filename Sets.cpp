#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <iomanip>

using namespace std;

unordered_set<int> positions;
bool isEmpty = false;

bool isPosUnique(int pos) {
    if (positions.find(pos) == positions.end()) { // проверка на уникальность
        positions.insert(pos);
        return true;
    }
    else {
        return false;
    }
}

class FoodSets {
public:
    string posName, quantityName, catalogsName;
    int pos = 0;
    int quantity = 0;
    vector<string> catalogs;

    vector<FoodSets> readDocuments(const string& path) {
        ifstream file(path);
        vector<FoodSets> sets;
        if (!file.is_open())
        {
            cerr << "Ошибка: файл не найден!" << endl;
            return {};
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            istringstream iss(line);
            FoodSets set;
            int pos = 0;
            if (line == "")
            {
                
            }
            iss >> pos;
            if (isPosUnique(pos))
            {
                iss >> set.quantity;
                set.pos = pos;
            }
            else {
                continue;
            }

            string catalog;
            while (iss >> catalog) {
                set.catalogs.push_back(catalog);
            }

            sets.push_back(set);
        }
        return sets;
    }
};

class KitSets {
public:
    int quantity = 0;
    string catalog;

    vector<KitSets> readKits(const string& path) {
        ifstream file(path);
        vector<KitSets> kits;
        if (!file.is_open())
        {
            cerr << "Ошибка: файл не найден!" << endl;
            return {};
        }

        if (file.peek() == EOF)
        {
            cerr << "Ошибка: файл пустой!" << endl;
            isEmpty = true;
            return {};
        }

        string line = "";
        while (getline(file, line)) {
            istringstream iss(line);
            KitSets kit;

            iss >> kit.catalog >> kit.quantity;

            kits.push_back(kit);
        }
        return kits;
    }
};


void isKitThere(const vector<FoodSets>& sets, const vector<KitSets>& kits) {
    bool flag = true;

    for (size_t i = 0; i < sets.size(); i++)
    {
        for (size_t j = 0; j < sets[i].catalogs.size(); j++)
        {
            for (size_t k = 0; k < kits.size(); k++)
            {
                if (flag)
                {
                    cout << "Набор содерижтся в документе." << endl;
                    cout << "Состав набора:" << endl;
                    cout << left << setw(10) << "Позиция"
                        << setw(12) << "Количество"
                        << setw(20) << "Каталог" << endl;
                    flag = false;
                }

                if (sets[i].catalogs[j] == kits[k].catalog && kits[k].quantity >= sets[i].quantity)
                {
                    cout << left << setw(12) 
                         << sets[i].pos << setw(10) << sets[i].quantity << setw(12) << kits[k].catalog << endl;
                }
            }
        }
    }

    if (flag)
    {
        cout << "Набор не содерижтся в документе." << endl;
    }
}

void read(const vector<KitSets>& kits, bool isEmpty) {
    if (!isEmpty)
    {
        cout << left << setw(10) << "Каталог"
            << setw(20) << "Количество" << endl;
    }  

    for (size_t i = 0; i < kits.size(); i++)
    {
        cout << left << setw(10) << kits[i].catalog << setw(12) << kits[i].quantity;
        cout << endl;
    }
}

void read(const vector<FoodSets>& sets, bool isEmpty) {
    if (!isEmpty)
    {
        cout << left << setw(10) << "Позиция"
            << setw(12) << "Количество"
            << setw(20) << "Каталог" << endl;
    }
    
    for (size_t i = 0; i < sets.size(); i++)
    {
        cout << left << setw(10) << sets[i].pos << setw(12) << sets[i].quantity;
        for (size_t k = 0; k < sets[i].catalogs.size(); k++)
        {
            cout << sets[i].catalogs[k] << " ";
        }
        cout << endl;
    }
}

int main()
{   
    setlocale(LC_ALL, "Russian");
    string pathToKit = "";
    cout << "Введите путь к набору: " << endl;
    getline(cin, pathToKit);
    KitSets kit;
    vector<KitSets> kits = kit.readKits(pathToKit);

    read(kits, isEmpty);
    cout << endl;

    string pathToDocument = "";
    cout << "Введите путь к документу: " << endl;
    getline(cin, pathToDocument);
    FoodSets set;
    vector<FoodSets> sets = set.readDocuments(pathToDocument);

    read(sets, isEmpty);
    cout << endl;

    isKitThere(sets,kits);
}

