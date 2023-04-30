#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm> 
#include <ctime>

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

    void printSpecificSearch(FoodData currFood){
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
        cout << "GmWt_1: " << currFood.GmWt_1 << endl; 
        cout << "GmWt_Desc1: " << currFood.GmWt_Desc1 << endl;
        cout << "GmWt_2: " << currFood.GmWt_2 << endl;
        cout << "GmWt_Desc2: " << currFood.GmWt_Desc2 << endl;
        cout << "Refuse_Pct: " << currFood.Refuse_Pct << endl; 
    }

    // PRINT SEARCH RESULTS: need one specific keyword for this search (bc implements Hash function that depends on Shrt_Desc)
    FoodData searchResults(const string& keyword) {
        // MEASUREMENTS
        clock_t start, end;
        double cpu_time_used;
        start = clock(); // Get the starting time

        FoodData currFood;
        unsigned int hashVal = hash(keyword); 
        HashNode* curr = table[hashVal]; 
            while (curr != nullptr) {
                currFood = curr->value;
                if (currFood.Shrt_Desc == keyword) {
                    printSpecificSearch(currFood);
                    break;
                }
                curr = curr->next;
            }

        // END MEASUREMENTS
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "***Time to search HashMap: " << cpu_time_used << " seconds" << std::endl;   

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
    vector<double> suggestedAverage(const string &gender, int weight, int height, int age, const string &activity_level){
        double bmrCal = 0, carb = 0, protein = 0, fat = 0;
        vector<double> sugg;
        // REQUIRED INPUT FORMAT:"m" or "f", pounds, inches, integer, string
        if (gender == "m"){
            bmrCal = 66.47 + ((13.75*0.454) * weight) + ((5.003*2.54) * height) - (6.755 * age);
        }
        else if (gender == "f"){
            bmrCal = 655.1 + ((9.563*0.454) * weight) + ((1.85*2.54) * height) - (4.676 * age);
        }
        if (activity_level == "sedentary") {
            bmrCal *= 1.2;
        } else if (activity_level == "lightly active") {
            bmrCal *= 1.375;
        } else if (activity_level == "moderately active") {
            bmrCal *= 1.55;
        } else if (activity_level == "very active") {
            bmrCal *= 1.725;
        } else if (activity_level == "extra active") {
            bmrCal *= 1.9;
        }
        // CALCULATIONS also divide results by 3 to get meal avgs not daily avgs
        bmrCal /= 3.0; 
        sugg.push_back(bmrCal);
        carb = (0.55 * bmrCal) / 4.0;
        carb /= 3.0; 
        sugg.push_back(carb);
        protein = (0.36 * weight);
        protein /= 3.0; 
        sugg.push_back(protein);
        fat = (0.3 * bmrCal) / 9.0;
        fat /= 3.0; 
        sugg.push_back(fat);
        return sugg;
    }

};
     

   bool ReadQuotedField(std::stringstream &ss, std::string &field) {
    field.clear();
    char c;
    ss.get(c);

    bool inside_quotes = (c == '"');

    if (inside_quotes) {
        // Consume the initial double quote
    } else {
        field.push_back(c);
    }

    bool prev_char_was_quote = false;
    while (ss.get(c)) {
        if (inside_quotes && c == '"' && !prev_char_was_quote) {
            prev_char_was_quote = true;
            continue;
        }
        if (inside_quotes && c == '"' && prev_char_was_quote) {
            prev_char_was_quote = false;
        } else if (inside_quotes && prev_char_was_quote) {
            ss.get(c); // Consume the following character, which should be a comma
            return true;
        } else if (!inside_quotes && c == ',') {
            return true;
        } else {
            prev_char_was_quote = false;
        }
        field.push_back(c);
    }

    return !field.empty();
}

// READ FILE: RETURNS A VECTOR, HASHMAP INITIALIZATION IN MAIN
vector<FoodData> ReadFile(string filename) { 
    std::vector<FoodData> food_data_list;
    std::ifstream file(filename);
    if (file.is_open()) {

    std::string line;
    getline(file, line); // Skip the header
    int lineNumber = 2; // Start from the second line as we have already skipped the header

    while (getline(file, line)) {
        std::stringstream ss(line);
        FoodData food_data;

        // Fill the struct with data
        string temp;
        getline(ss, temp, ',');
        food_data.NDB_No = stoi(temp);
        ReadQuotedField(ss, food_data.Shrt_Desc);

        #define READ_OR_DEFAULT(variable) \
        if (!getline(ss, line, ',')) { \
            food_data.variable = 0; \
        } else { \
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); \
            if (line.empty() || \
                !std::all_of(line.begin(), line.end(), [](char c) { return std::isdigit(c) || c == '.' || c == '-'; })) { \
                food_data.variable = 0; \
            } else { \
                try { \
                    food_data.variable = std::stod(line); \
                } catch (const std::invalid_argument& e) { \
                    std::cerr << "Invalid argument: " << e.what() << " for " << #variable << std::endl; \
                    food_data.variable = 0; \
                } catch (const std::out_of_range& e) { \
                    std::cerr << "Out of range: " << e.what() << " for " << #variable << std::endl; \
                    food_data.variable = 0; \
                } \
            } \
        }

        READ_OR_DEFAULT(Water_g)
        READ_OR_DEFAULT(Energ_Kcal)
        READ_OR_DEFAULT(Protein_g)
        READ_OR_DEFAULT(Lipid_Tot_g)
        READ_OR_DEFAULT(Ash_g)
        READ_OR_DEFAULT(Carbohydrt_g)
        READ_OR_DEFAULT(Fiber_TD_g)
        READ_OR_DEFAULT(Sugar_Tot_g)
        READ_OR_DEFAULT(Calcium_mg)
        READ_OR_DEFAULT(Iron_mg)
        READ_OR_DEFAULT(Magnesium_mg)
        READ_OR_DEFAULT(Phosphorus_mg)
        READ_OR_DEFAULT(Potassium_mg)
        READ_OR_DEFAULT(Sodium_mg)
        READ_OR_DEFAULT(Zinc_mg)
        READ_OR_DEFAULT(Copper_mg)
        READ_OR_DEFAULT(Manganese_mg)
        READ_OR_DEFAULT(Selenium_ug)
        READ_OR_DEFAULT(Vit_C_mg)
        READ_OR_DEFAULT(Thiamin_mg)
        READ_OR_DEFAULT(Riboflavin_mg)
        READ_OR_DEFAULT(Niacin_mg)
        READ_OR_DEFAULT(Panto_Acid_mg)
        READ_OR_DEFAULT(Vit_B6_mg)
        READ_OR_DEFAULT(Folate_Tot_ug)
        READ_OR_DEFAULT(Folic_Acid_ug)
        READ_OR_DEFAULT(Food_Folate_ug)
        READ_OR_DEFAULT(Folate_DFE_ug)
        READ_OR_DEFAULT(Choline_Tot_mg)
        READ_OR_DEFAULT(Vit_B12_ug)
        READ_OR_DEFAULT(Vit_A_IU)
        READ_OR_DEFAULT(Vit_A_RAE)
        READ_OR_DEFAULT(Retinol_ug)
        READ_OR_DEFAULT(Alpha_Carot_ug)
        READ_OR_DEFAULT(Beta_Carot_ug)
        READ_OR_DEFAULT(Beta_Crypt_ug)
        READ_OR_DEFAULT(Lycopene_ug)
        READ_OR_DEFAULT(Lut_Zea_ug)
        READ_OR_DEFAULT(Vit_E_mg)
        READ_OR_DEFAULT(Vit_D_ug)
        READ_OR_DEFAULT(Vit_D_IU)
        READ_OR_DEFAULT(Vit_K_ug)
        READ_OR_DEFAULT(FA_Sat_g)
        READ_OR_DEFAULT(FA_Mono_g)
        READ_OR_DEFAULT(FA_Poly_g)
        READ_OR_DEFAULT(Cholestrl_mg)
        READ_OR_DEFAULT(GmWt_1)
        ReadQuotedField(ss, food_data.GmWt_Desc1);
        READ_OR_DEFAULT(GmWt_2);
        ReadQuotedField(ss, food_data.GmWt_Desc2);

        if (!getline(ss, line, ',')) {
            food_data.Refuse_Pct = 0;
        } else {
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (line.empty() ||
                !std::all_of(line.begin(), line.end(), [](char c) { return std::isdigit(c) || c == '.'; })) {
                food_data.Refuse_Pct = 0;
            } else {
                try {
                    food_data.Refuse_Pct = std::stod(line);
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Problematic line number: " << lineNumber << std::endl;
                    std::cerr << "Problematic line content: " << line << std::endl;
                    std::cerr << "Invalid argument: " << e.what() << " for Refuse_Pct" << std::endl;
                    food_data.Refuse_Pct = 0;
                } catch (const std::out_of_range &e) {
                    std::cerr << "Problematic line number: " << lineNumber << std::endl;
                    std::cerr << "Problematic line content: " << line << std::endl;
                    std::cerr << "Out of range: " << e.what() << " for Refuse_Pct" << std::endl;
                    food_data.Refuse_Pct = 0;
                }
            }
        }

        #undef READ_OR_DEFAULT
        food_data_list.push_back(food_data);
        lineNumber++; 
    }
    }
    return food_data_list;
}

int main() {

    vector<FoodData> data = ReadFile("food.csv");

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
    FoodData specifiedSearch = foodMap.searchResults("BUTTER OIL,ANHYDROUS");
    // TIME FOR SEARCH FUNCTION OUTPUTTED 

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
    cout << "Calories (Kcal): " << mealAvgs[0] << endl;
    cout << "Carbohydrates (g): " << mealAvgs[1] << endl;
    cout << "Protein (g): " << mealAvgs[2] << endl;
    cout << "Total Fat (g): " << mealAvgs[3] << endl;

    // SUGGESTED AVERAGES: use input data (must be correct units/ format) to show what should be the meal averages
    cout << "---Suggested averages for a meal--- " << endl;
    vector<double> mealSuggAvgs = foodMap.suggestedAverage("m", 150, 65, 25, "moderately active");
    cout << "Calories (Kcal): " << mealSuggAvgs[0] << endl;
    cout << "Carbohydrates (g): " << mealSuggAvgs[1] << endl;
    cout << "Protein (g): " << mealSuggAvgs[2] << endl;
    cout << "Total Fat (g): " << mealSuggAvgs[3] << endl;

    return 0;
}