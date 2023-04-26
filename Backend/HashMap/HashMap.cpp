#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>

using namespace std;

struct FoodData {
    int NDB_No = 0;
    string Shrt_Desc = "";
    double Water_g = 0.0, Energ_Kcal = 0.0, Protein_g = 0.0, Lipid_Tot_g = 0.0, Ash_g = 0.0; 
    double Carbohydrt_g = 0.0, Fiber_TD_g = 0.0, Sugar_Tot_g = 0.0, Calcium_mg = 0.0, Iron_mg = 0.0; 
    double Magnesium_mg = 0.0, Phosphorus_mg = 0.0, Potassium_mg = 0.0, Sodium_mg = 0.0, Zinc_mg = 0.0; 
    double Copper_mg = 0.0, Manganese_mg = 0.0, Selenium_ug = 0.0, Vit_C_mg = 0.0, Thiamin_mg = 0.0;
    double Riboflavin_mg = 0.0, Niacin_mg = 0.0, Panto_Acid_mg = 0.0, Vit_B6_mg = 0.0, Folate_Tot_ug = 0.0; 
    double Folic_Acid_ug = 0.0, Food_Folate_ug = 0.0, Folate_DFE_ug = 0.0, Choline_Tot_mg = 0.0, Vit_B12_ug = 0.0; 
    double Vit_A_IU = 0.0, Vit_A_RAE = 0.0, Retinol_ug = 0.0, Alpha_Carot_ug = 0.0, Beta_Carot_ug = 0.0; 
    double Beta_Crypt_ug = 0.0, Lycopene_ug = 0.0, Lut_Zea_ug = 0.0, Vit_E_mg = 0.0, Vit_D_ug = 0.0; 
    double Vit_D_IU = 0.0, Vit_K_ug = 0.0, FA_Sat_g = 0.0, FA_Mono_g = 0.0, FA_Poly_g = 0.0, Cholestrl_mg = 0.0; 
    double GmWt_1 = 0.0;
    string GmWt_Desc1 = "";
    double GmWt_2 = 0.0;
    string GmWt_Desc2 = "";
    double Refuse_Pct = 0.0;
};

class HashMap {
private:
    struct HashNode {
        string key;
        FoodData value;
        HashNode* next;
    };
    int capacity = 0, size = 0;
    vector<HashNode*> table;
    vector<FoodData> mealList;

    unsigned int hash(const string& key) { // return powers of 31 with ASCII values
        unsigned int hashVal = 0;
        for (int i = 0; i < key.length(); i++){
            hashVal = key[i] + (hashVal * 31);
        }
        return hashVal % capacity;
    }

    void rehash() {
        vector<HashNode*> oldTable = table;
        size = 0;
        capacity *= 2;
        for(int i = 0; i < capacity; i++) { 
            table.push_back(nullptr);
        }
        for (HashNode* &head : table) {
            head = new HashNode{ "", {}, nullptr };
        }
        for (HashNode* &head : oldTable) {
            HashNode* curr = head->next;
            while (curr != nullptr) {
                HashNode* node = new HashNode{ curr->key, curr->value, nullptr };
                unsigned int index = hash(node->key);
                HashNode* head = table[index];
                node->next = head->next;
                head->next = node;
                curr = curr->next;
                size++;
            }
        }
        for (HashNode* &head : oldTable) {
            HashNode* curr = head;
            while (curr != nullptr) {
                HashNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

public:
    HashMap() {
        size = 0;
        capacity = 10;
        for(int i = 0; i < capacity; i++) { 
            table.push_back(nullptr);
        }
        for (HashNode* &head : table) {
            head = new HashNode{ "", {}, nullptr };
        }
    }

    ~HashMap() {
        for (HashNode* & head : table) {
            HashNode* curr = head;
            while (curr != nullptr) {
                HashNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

    // HASH MAP: KEY is Short_Desc and VALUE is FoodData
    void insert(const string& key, const FoodData& value) {
        unsigned int index = hash(key);
        HashNode* head = table[index];
        HashNode* curr = head->next;
        while (curr != nullptr) {
            if (curr->key == key) {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }
        HashNode* node = new HashNode{ key, value, nullptr };
        node->next = head->next;
        head->next = node;
        size++;
        double loadFactor = ((double)size) / capacity;
        if (loadFactor > 0.8) {
            rehash();
        }
    }

    bool empty() const {
        return size == 0;
    }
    
    // SEARCH: return all Short_Desc containing keyword
    vector<FoodData> search(const string& keyword) {
        vector<FoodData> results;
        FoodData currFood;
        for (HashNode* &head : table) {
            HashNode* curr = head->next;
            while (curr != nullptr) {
                currFood = curr->value;
                if (currFood.Shrt_Desc.find(keyword) != string::npos) {
                    results.push_back(currFood);
                }
                curr = curr->next;
            }
        }
        return results;
    }

    // PRINT SEARCH RESULTS: need one specific keyword for this search (bc implements Hash function that depends on Shrt_Desc)
    FoodData searchResults(const string& keyword) {
        FoodData currFood;
        unsigned int hashVal = hash(keyword); 
        HashNode* curr = table[hashVal]; 
            while (curr != nullptr) {
                currFood = curr->value;
                if (currFood.Shrt_Desc == keyword) {
                    cout << "Nutrients for " << currFood.Shrt_Desc << ":" << endl;
                    cout << "Water_g: " << currFood.Water_g << endl; 
                    cout << "Energ_Kcal: " << currFood.Energ_Kcal << endl;
                    cout << "Protein_g: " << currFood.Protein_g << endl;
                    cout << "Lipid_Tot_g: " << currFood.Lipid_Tot_g << endl;
                    cout << "Ash_g: " << currFood.Ash_g << endl;
                    cout << "Carbohydrt_g: " << currFood.Carbohydrt_g << endl;
                    cout << "Fiber_TD_g: " << currFood.Fiber_TD_g << endl;
                    cout << "Sugar_Tot_g: " << currFood.Sugar_Tot_g << endl;
                    cout << "Calcium_mg: " << currFood.Calcium_mg << endl;
                    cout << "Iron_mg: " << currFood.Iron_mg << endl;
                    cout << "Magnesium_mg: " << currFood.Magnesium_mg << endl;
                    cout << "Phosphorus_mg: " << currFood.Phosphorus_mg << endl;
                    cout << "Potassium_mg: " << currFood.Potassium_mg << endl;
                    cout << "Sodium_mg: " << currFood.Sodium_mg << endl;
                    cout << "Zinc_mg: " << currFood.Zinc_mg << endl;
                    cout << "Copper_mg: " << currFood.Copper_mg << endl;
                    cout << "Manganese_mg: " << currFood.Manganese_mg << endl;
                    cout << "Selenium_ug: " << currFood.Selenium_ug << endl;
                    cout << "Vit_C_mg: " << currFood.Vit_C_mg << endl;
                    cout << "Thiamin_mg: " << currFood.Thiamin_mg << endl;
                    cout << "Riboflavin_mg: " << currFood.Riboflavin_mg << endl;
                    cout << "Niacin_mg: " << currFood.Niacin_mg << endl;
                    cout << "Panto_Acid_mg: " << currFood.Panto_Acid_mg << endl;
                    cout << "Vit_B6_mg: " << currFood.Vit_B6_mg << endl;
                    cout << "Folate_Tot_ug: " << currFood.Folate_Tot_ug << endl;
                    cout << "Folic_Acid_ug: " << currFood.Folic_Acid_ug << endl;
                    cout << "Food_Folate_ug: " << currFood.Food_Folate_ug << endl;
                    cout << "Folate_DFE_ug: " << currFood.Folate_DFE_ug << endl;
                    cout << "Choline_Tot_mg: " << currFood.Choline_Tot_mg << endl;
                    cout << "Vit_B12_ug: " << currFood.Vit_B12_ug << endl;
                    cout << "Vit_A_IU: " << currFood.Vit_A_IU << endl;
                    cout << "Vit_A_RAE: " << currFood.Vit_A_RAE << endl;
                    cout << "Retinol_ug: " << currFood.Retinol_ug << endl;
                    cout << "Alpha_Carot_ug: " << currFood.Alpha_Carot_ug << endl;
                    cout << "Beta_Carot_ug: " << currFood.Beta_Carot_ug << endl;
                    cout << "Beta_Crypt_ug: " << currFood.Beta_Crypt_ug << endl;
                    cout << "Lycopene_ug: " << currFood.Lycopene_ug << endl;
                    cout << "Lut_Zea_ug: " << currFood.Lut_Zea_ug << endl;
                    cout << "Vit_E_mg: " << currFood.Vit_E_mg << endl;
                    cout << "Vit_D_ug: " << currFood.Vit_D_ug << endl;
                    cout << "Vit_D_IU: " << currFood.Vit_D_IU << endl;
                    cout << "Vit_K_ug: " << currFood.Vit_K_ug << endl;
                    cout << "FA_Sat_g: " << currFood.FA_Sat_g << endl;
                    cout << "FA_Mono_g: " << currFood.FA_Mono_g << endl;
                    cout << "FA_Poly_g: " << currFood.FA_Poly_g << endl;
                    cout << "Cholestrl_mg: " << currFood.Cholestrl_mg << endl;
                    cout << "GmWt_1: " << currFood.GmWt_1 << endl; /*
                    cout << "GmWt_Desc1: " << currFood.GmWt_Desc1 << endl;
                    cout << "GmWt_2: " << currFood.GmWt_2 << endl;
                    cout << "GmWt_Desc2: " << currFood.GmWt_Desc2 << endl;
                    cout << "Refuse_Pct: " << currFood.Refuse_Pct << endl; */
                    break;
                }
                curr = curr->next;
            }
        return currFood;
    }

    // local vector<FoodData> mealList;
    //MEAL LIST: adds a specific food to the mealList vector of foods 
    vector<FoodData> updateMealList(const string& keyword){
        FoodData currFood;
        unsigned int hashVal = hash(keyword); 
        HashNode* curr = table[hashVal]; 
            while (curr != nullptr) {
                currFood = curr->value;
                if (currFood.Shrt_Desc == keyword) {
                    mealList.push_back(currFood);
                    break;
                }
                curr = curr->next;
            }
        return mealList;
    }

    // MEAL AVERAGES: return vector of avg cals, carbs, proteins, fats in food
    vector<double> mealAverage(vector<FoodData> meal){
        int size = meal.size();
        double avgCal = 0, avgCarb = 0, avgProtein = 0, avgFat = 0;
        vector<double> avgs;
        for (int i = 0; i < size; i ++){
            FoodData currFood = meal[i];
            avgCal += currFood.Energ_Kcal;
            avgCarb += currFood.Carbohydrt_g;
            avgProtein += currFood.Protein_g;
            avgFat += currFood.FA_Mono_g + currFood.FA_Poly_g + currFood.FA_Sat_g;
        }
        avgCal /= (double)size;
        avgs.push_back(avgCal);
        avgCarb /= (double)size;
        avgs.push_back(avgCarb);
        avgProtein /= (double)size;
        avgs.push_back(avgProtein);
        avgFat /= (double)size;
        avgs.push_back(avgFat);
        return avgs;
    }

    // SUGGESTED AVERAGES: use data to show what should be the meal averages
    vector<double> suggestedAverage(int age, int height, int weight, string gender, int activeLevel){
        double bmi = 0, cal = 0, carb = 0, protein = 0, fat = 0;
        vector<double> sugg;
        // TODO: make sure input is given in correct units 
        if (gender == "Male"){
            bmi = 66.47 + (13.75 * weight) + (5.003 * height) - (6.755 * age);
        }
        else if (gender == "Female"){
            bmi = 655.1 + (9.563 * weight) + (1.850 * height) - (4.676 * age);
        }
        switch (activeLevel) {
            case 1:
                cal = bmi * 1.2;
                break;
            case 2:
                cal = bmi * 1.375;
                break;
            case 3:
                cal = bmi * 1.55;
                break;
            case 4:
                cal = bmi * 1.725;
                break;
            case 5:
                cal = bmi * 1.9;
                break;
            default:
                cal = bmi * 1.2;
        }
        // CALCULATIONS also divide results by 3 to get meal avgs not daily avgs
        cal /= 3; 
        sugg.push_back(cal);
        carb = (0.55 * cal) / 4.0;
        carb /= 3; 
        sugg.push_back(carb);
        protein = (0.36 * weight);
        protein /= 3; 
        sugg.push_back(protein);
        fat = (0.3 * cal) / 9.0;
        fat /= 3; 
        sugg.push_back(fat);
        return sugg;
    }
};    


    vector<FoodData> readFile(string filename) { // , vector<FoodData> &foodVector) {
        vector<FoodData> foodList; // = foodVector;
        ifstream file(filename);
        if (file.is_open()){
            string line;
            getline(file, line); // skip header

            while (getline(file, line)){
                istringstream stream(line);
               
                string temp = ""; 
                int NDB_No = 0;
                string Shrt_Desc = "";
                double Water_g = 0.0, Energ_Kcal = 0.0, Protein_g = 0.0, Lipid_Tot_g = 0.0, Ash_g = 0.0; 
                double Carbohydrt_g = 0.0, Fiber_TD_g = 0.0, Sugar_Tot_g = 0.0, Calcium_mg = 0.0, Iron_mg = 0.0; 
                double Magnesium_mg = 0.0, Phosphorus_mg = 0.0, Potassium_mg = 0.0, Sodium_mg = 0.0, Zinc_mg = 0.0; 
                double Copper_mg = 0.0, Manganese_mg = 0.0, Selenium_ug = 0.0, Vit_C_mg = 0.0, Thiamin_mg = 0.0;
                double Riboflavin_mg = 0.0, Niacin_mg = 0.0, Panto_Acid_mg = 0.0, Vit_B6_mg = 0.0, Folate_Tot_ug = 0.0; 
                double Folic_Acid_ug = 0.0, Food_Folate_ug = 0.0, Folate_DFE_ug = 0.0, Choline_Tot_mg = 0.0, Vit_B12_ug = 0.0; 
                double Vit_A_IU = 0.0, Vit_A_RAE = 0.0, Retinol_ug = 0.0, Alpha_Carot_ug = 0.0, Beta_Carot_ug = 0.0; 
                double Beta_Crypt_ug = 0.0, Lycopene_ug = 0.0, Lut_Zea_ug = 0.0, Vit_E_mg = 0.0, Vit_D_ug = 0.0; 
                double Vit_D_IU = 0.0, Vit_K_ug = 0.0, FA_Sat_g = 0.0, FA_Mono_g = 0.0, FA_Poly_g = 0.0, Cholestrl_mg = 0.0; 
                double GmWt_1 = 0.0;
                string GmWt_Desc1 = "";
                double GmWt_2 = 0.0;
                string GmWt_Desc2 = "";
                double Refuse_Pct = 0.0;
                // 01001,"BUTTER,WITH SALT",15.87,717,0.85,81.11,2.11,0.06,0,0.06,24,0.02,2,24,24,643,0.09,0,0,1,0,0.005,0.034,0.042,0.11,0.003,3,0,3,3,18.8,0.17,2499,684,671,0,158,0,0,0,2.32,1.5,60,7,51.368,21.021,3.043,215,5,"1 pat,  (1"" sq, 1/3"" high)",14.2,1 tbsp,0

                getline(stream, temp, ',');
                //NDB_No = stod(temp);
                NDB_No = atof(temp.c_str());
                getline(stream, temp, '"'); // skip Shrt_Desc start "
                getline(stream, Shrt_Desc, '"'); // save Shrt_Desc start until end "
                getline(stream, temp, ','); // skip Shrt_Desc end "
                
                // TODO: WATER and PROTEIN are being stored as 0 for all foods... but cals and every other nutrient exactly matches CSV
                getline(stream, temp, ',');
                if (temp != "") {Water_g = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Energ_Kcal = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Protein_g = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Lipid_Tot_g = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Ash_g = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Carbohydrt_g = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Fiber_TD_g = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Sugar_Tot_g = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Calcium_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Iron_mg = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Magnesium_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Phosphorus_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Potassium_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Sodium_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Zinc_mg = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Copper_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Manganese_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Selenium_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Vit_C_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Thiamin_mg = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Riboflavin_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Niacin_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Panto_Acid_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Vit_B6_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Folate_Tot_ug = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Folic_Acid_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Food_Folate_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Folate_DFE_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Choline_Tot_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Vit_B12_ug = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Vit_A_IU = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Vit_A_RAE = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Retinol_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Alpha_Carot_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Beta_Carot_ug = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Beta_Crypt_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Lycopene_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Lut_Zea_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Vit_E_mg = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Vit_D_ug = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Vit_D_IU = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {Vit_K_ug = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {FA_Sat_g = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {FA_Mono_g = atof(temp.c_str());}
                getline(stream, temp, ',');
                if (temp != "") {FA_Poly_g = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {Cholestrl_mg = atof(temp.c_str());}

                getline(stream, temp, ',');
                if (temp != "") {GmWt_1 = atof(temp.c_str());}
                
                /*
                // TODO: Figure out how to read the last 4 inputs uniformly when they are not at all on csv 
                
                // String GmWt_Desc1 may have " and , inside or be empty so need special reading 
                // TODO: getline(stream, GmWt_Desc1, ','); 

                getline(stream, temp, ',');
                if (temp != "") {GmWt_2 = atof(temp.c_str());}

                // String GmWt_Desc2 may have " and , inside or be empty so need special reading 
                // TODO:

                getline(stream, temp);
                if (temp != "") {Refuse_Pct = atof(temp.c_str());}
                */

                // CREATE FoodData OBJECT
                FoodData food;

                food.NDB_No = NDB_No;
                food.Shrt_Desc = Shrt_Desc;
                food.Energ_Kcal = Energ_Kcal;
                food.Lipid_Tot_g = Lipid_Tot_g;
                food.Ash_g = Ash_g;

                food.Carbohydrt_g = Carbohydrt_g;
                food.Fiber_TD_g = Fiber_TD_g;
                food.Sugar_Tot_g = Sugar_Tot_g;
                food.Calcium_mg = Calcium_mg;
                food.Iron_mg = Iron_mg;

                food.Magnesium_mg = Magnesium_mg;
                food.Phosphorus_mg = Phosphorus_mg;
                food.Potassium_mg = Potassium_mg;
                food.Sodium_mg = Sodium_mg;
                food.Zinc_mg = Zinc_mg;

                food.Copper_mg = Copper_mg;
                food.Manganese_mg = Manganese_mg;
                food.Selenium_ug = Selenium_ug;
                food.Vit_C_mg = Vit_C_mg;
                food.Thiamin_mg = Thiamin_mg;

                food.Riboflavin_mg = Riboflavin_mg;
                food.Niacin_mg = Niacin_mg;
                food.Panto_Acid_mg = Panto_Acid_mg;
                food.Vit_B6_mg = Vit_B6_mg;
                food.Folate_Tot_ug = Folate_Tot_ug;

                food.Folic_Acid_ug = Folic_Acid_ug;
                food.Food_Folate_ug = Food_Folate_ug;
                food.Folate_DFE_ug = Folate_DFE_ug;
                food.Choline_Tot_mg = Choline_Tot_mg;
                food.Vit_B12_ug = Vit_B12_ug;

                food.Vit_A_IU = Vit_A_IU;
                food.Vit_A_RAE = Vit_A_RAE;
                food.Retinol_ug = Retinol_ug;
                food.Alpha_Carot_ug = Alpha_Carot_ug;
                food.Beta_Carot_ug = Beta_Carot_ug;

                food.Beta_Crypt_ug = Beta_Crypt_ug;
                food.Lycopene_ug = Lycopene_ug;
                food.Lut_Zea_ug = Lut_Zea_ug;
                food.Vit_E_mg = Vit_E_mg;
                food.Vit_D_ug = Vit_D_ug;

                food.Vit_D_IU = Vit_D_IU;
                food.Vit_K_ug = Vit_K_ug;
                food.FA_Sat_g = FA_Sat_g;
                food.FA_Mono_g = FA_Mono_g;
                food.FA_Poly_g = FA_Poly_g;

                food.Cholestrl_mg = Cholestrl_mg;

                food.GmWt_1 = GmWt_1;
                //food.GmWt_Desc1 = GmWt_Desc1;

                //food.GmWt_2 = GmWt_2;
                //food.GmWt_Desc2 = GmWt_Desc2;

                //food.Refuse_Pct = Refuse_Pct;

                foodList.push_back(food);

            }  
        }
        return foodList;
    }


// TODO: display computation times


int main() {

    vector<FoodData> data = readFile("FoodData.csv");

    // INITIALIZE HASHMAP W ALL CSV DATA
    HashMap foodMap;
    for (int i = 0; i < data.size(); i++){
        foodMap.insert(data[i].Shrt_Desc, data[i]);
    }

    // SEARCH: return all FoodData objects with Short_Desc containing keyword
    cout << "---General search results--- " << endl;
    vector<FoodData> search = foodMap.search("BUTTER");
    for (int i = 0; i < search.size(); i++){
        cout << search[i].Shrt_Desc << endl;
    }

    // PRINT SEARCH RESULTS: show all nutrients for one specific Short_Desc
    cout << "---Specific search results--- " << endl;
    FoodData specifiedSearch = foodMap.searchResults("CHEESE,BLUE");

    //MEAL LIST: adds a food to the mealList vector of foods
    cout << "---Foods currently in the meal--- " << endl;
    vector<FoodData> meal = foodMap.updateMealList("BUTTER,WITH SALT");
    vector<FoodData> mealAdd = foodMap.updateMealList("EGG,WHL,CKD,SCRMBLD");
    for (int i = 0; i < mealAdd.size(); i++){
        cout << mealAdd[i].Shrt_Desc << endl;
    }

    // MEAL AVERAGES: return vector of avg cals, carbs, proteins, fats in food
    cout << "---Averages for the meal--- " << endl;
    vector<double> mealAvgs = foodMap.mealAverage(mealAdd);
    // TODO: add units to make more clear
    cout << "Calories (Kcal): " << mealAvgs[0] << endl;
    cout << "Carbohydrates (g): " << mealAvgs[1] << endl;
    cout << "Protein (g): " << mealAvgs[2] << endl;
    cout << "Total Fat (g): " << mealAvgs[3] << endl;

    // SUGGESTED AVERAGES: use input data to show what should be the meal averages
    // TODO: make sure input is given in correct units or convert it in function
    cout << "---Suggested averages for a meal--- " << endl;
    vector<double> mealSuggAvgs = foodMap.suggestedAverage(28, 5'9, 150, "Male", 3);
    cout << "Calories (Kcal): " << mealSuggAvgs[0] << endl;
    cout << "Carbohydrates (g): " << mealSuggAvgs[1] << endl;
    cout << "Protein (g): " << mealSuggAvgs[2] << endl;
    cout << "Total Fat (g): " << mealSuggAvgs[3] << endl;

    return 0;
}




