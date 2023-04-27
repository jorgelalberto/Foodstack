#ifndef MYOBJECT_H
#define MYOBJECT_H

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
#include <utility>
#include <napi.h>

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

class HashMap : public Napi::ObjectWrap<HashMap>{
private:
    struct HashNode {
        string key;
        FoodData value;
        HashNode* next;
    };
    int capacity = 0, size = 0;
    double lastRunTime = 0;
    vector<HashNode*> table;
    vector<FoodData> mealList;
    //HashMap();
    //~HashMap();
    unsigned int hash(const string& key);
    void rehash();
    void insert(const string& key, const FoodData& value);
    bool empty() const;
    vector<FoodData> search(const string& keyword);
    void printSpecificSearch(FoodData currFood);
    FoodData searchResults(const string& keyword);
    vector<FoodData> updateMealList(const string& keyword);
    vector<double> mealAverage(vector<FoodData> meal);
    vector<double> suggestedAverage(const string &gender, int weight, int height, int age, const string &activity_level);
    void ReadFile(const std::string &filename);
    bool ReadQuotedField(std::stringstream &ss, std::string &field);

    // Server Public
    Napi::Value SearchNapi(const Napi::CallbackInfo& info);
    Napi::Value GetTimeNapi(const Napi::CallbackInfo& info);

public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    HashMap(const Napi::CallbackInfo& info);
};

#endif