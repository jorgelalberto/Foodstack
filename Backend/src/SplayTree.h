#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <napi.h>


struct FoodData {
    // nutrient database # of food
    std::string NDB_No = "";
    // short description of food
    std::string Shrt_Desc = "";
    double Water_g = 0, Energ_Kcal = 0, Protein_g = 0, Lipid_Tot_g = 0, Ash_g = 0, Carbohydrt_g = 0, Fiber_TD_g = 0, Sugar_Tot_g = 0;
    double Calcium_mg = 0, Iron_mg = 0, Magnesium_mg = 0, Phosphorus_mg = 0, Potassium_mg = 0, Sodium_mg = 0, Zinc_mg = 0, Copper_mg = 0, Manganese_mg = 0, Selenium_ug = 0;
    double Vit_C_mg = 0, Thiamin_mg = 0, Riboflavin_mg = 0, Niacin_mg = 0, Panto_Acid_mg = 0, Vit_B6_mg = 0, Folate_Tot_ug = 0, Folic_Acid_ug = 0, Food_Folate_ug = 0, Folate_DFE_ug = 0;
    double Choline_Tot_mg = 0, Vit_B12_ug = 0, Vit_A_IU = 0, Vit_A_RAE = 0, Retinol_ug = 0, Alpha_Carot_ug = 0, Beta_Carot_ug = 0, Beta_Crypt_ug = 0, Lycopene_ug = 0, Lut_Zea_ug = 0;
    double Vit_E_mg = 0, Vit_D_ug = 0, Vit_D_IU = 0, Vit_K_ug = 0, FA_Sat_g = 0, FA_Mono_g = 0, FA_Poly_g = 0, Cholestrl_mg = 0, GmWt_1 = 0, GmWt_2 = 0, Refuse_Pct = 0;
    std::string GmWt_Desc1 = "", GmWt_Desc2 = "";

    // Overloaded + operator
    FoodData operator+(const FoodData &other) const {

        //Defaulting
        FoodData result;
        result.NDB_No = "";
        result.Shrt_Desc = "";
        result.GmWt_1 = 0;
        result.GmWt_2 = 0;
        result.GmWt_Desc1 = "";
        result.GmWt_Desc2 = "";
        result.Refuse_Pct = 0;

        // Add each nutrient value from the two FoodData objects
        result.Water_g = Water_g + other.Water_g;
        result.Energ_Kcal = Energ_Kcal + other.Energ_Kcal;
        result.Protein_g = Protein_g + other.Protein_g;
        result.Lipid_Tot_g = Lipid_Tot_g + other.Lipid_Tot_g;
        result.Ash_g = Ash_g + other.Ash_g;
        result.Carbohydrt_g = Carbohydrt_g + other.Carbohydrt_g;
        result.Fiber_TD_g = Fiber_TD_g + other.Fiber_TD_g;
        result.Sugar_Tot_g = Sugar_Tot_g + other.Sugar_Tot_g;
        result.Calcium_mg = Calcium_mg + other.Calcium_mg;
        result.Iron_mg = Iron_mg + other.Iron_mg;
        result.Magnesium_mg = Magnesium_mg + other.Magnesium_mg;
        result.Phosphorus_mg = Phosphorus_mg + other.Phosphorus_mg;
        result.Potassium_mg = Potassium_mg + other.Potassium_mg;
        result.Sodium_mg = Sodium_mg + other.Sodium_mg;
        result.Zinc_mg = Zinc_mg + other.Zinc_mg;
        result.Copper_mg = Copper_mg + other.Copper_mg;
        result.Manganese_mg = Manganese_mg + other.Manganese_mg;
        result.Selenium_ug = Selenium_ug + other.Selenium_ug;
        result.Vit_C_mg = Vit_C_mg + other.Vit_C_mg;
        result.Thiamin_mg = Thiamin_mg + other.Thiamin_mg;
        result.Riboflavin_mg = Riboflavin_mg + other.Riboflavin_mg;
        result.Niacin_mg = Niacin_mg + other.Niacin_mg;
        result.Panto_Acid_mg = Panto_Acid_mg + other.Panto_Acid_mg;
        result.Vit_B6_mg = Vit_B6_mg + other.Vit_B6_mg;
        result.Folate_Tot_ug = Folate_Tot_ug + other.Folate_Tot_ug;
        result.Folic_Acid_ug = Folic_Acid_ug + other.Folic_Acid_ug;
        result.Food_Folate_ug = Food_Folate_ug + other.Food_Folate_ug;
        result.Folate_DFE_ug = Folate_DFE_ug + other.Folate_DFE_ug;
        result.Choline_Tot_mg = Choline_Tot_mg + other.Choline_Tot_mg;
        result.Vit_B12_ug = Vit_B12_ug + other.Vit_B12_ug;
        result.Vit_A_IU = Vit_A_IU + other.Vit_A_IU;
        result.Vit_A_RAE = Vit_A_RAE + other.Vit_A_RAE;
        result.Retinol_ug = Retinol_ug + other.Retinol_ug;
        result.Alpha_Carot_ug = Alpha_Carot_ug + other.Alpha_Carot_ug;
        result.Beta_Carot_ug = Beta_Carot_ug + other.Beta_Carot_ug;
        result.Beta_Crypt_ug = Beta_Crypt_ug + other.Beta_Crypt_ug;
        result.Lycopene_ug = Lycopene_ug + other.Lycopene_ug;
        result.Lut_Zea_ug = Lut_Zea_ug + other.Lut_Zea_ug;
        result.Vit_E_mg = Vit_E_mg + other.Vit_E_mg;
        result.Vit_D_ug = Vit_D_ug + other.Vit_D_ug;
        result.Vit_D_IU = Vit_D_IU + other.Vit_D_IU;
        result.Vit_K_ug = Vit_K_ug + other.Vit_K_ug;
        result.FA_Sat_g = FA_Sat_g + other.FA_Sat_g;
        result.FA_Mono_g = FA_Mono_g + other.FA_Mono_g;
        result.FA_Poly_g = FA_Poly_g + other.FA_Poly_g;
        result.Cholestrl_mg = Cholestrl_mg + other.Cholestrl_mg;

        return result;
    }

    // Overloaded - operator
    FoodData operator-(const FoodData &other) const {

        //Defaulting
        FoodData result;
        result.NDB_No = "";
        result.Shrt_Desc = "";
        result.GmWt_1 = 0;
        result.GmWt_2 = 0;
        result.GmWt_Desc1 = "";
        result.GmWt_Desc2 = "";
        result.Refuse_Pct = 0;

        // Add each nutrient value from the two FoodData objects
        result.Water_g = Water_g - other.Water_g;
        result.Energ_Kcal = Energ_Kcal - other.Energ_Kcal;
        result.Protein_g = Protein_g - other.Protein_g;
        result.Lipid_Tot_g = Lipid_Tot_g - other.Lipid_Tot_g;
        result.Ash_g = Ash_g - other.Ash_g;
        result.Carbohydrt_g = Carbohydrt_g - other.Carbohydrt_g;
        result.Fiber_TD_g = Fiber_TD_g - other.Fiber_TD_g;
        result.Sugar_Tot_g = Sugar_Tot_g - other.Sugar_Tot_g;
        result.Calcium_mg = Calcium_mg - other.Calcium_mg;
        result.Iron_mg = Iron_mg - other.Iron_mg;
        result.Magnesium_mg = Magnesium_mg - other.Magnesium_mg;
        result.Phosphorus_mg = Phosphorus_mg - other.Phosphorus_mg;
        result.Potassium_mg = Potassium_mg - other.Potassium_mg;
        result.Sodium_mg = Sodium_mg - other.Sodium_mg;
        result.Zinc_mg = Zinc_mg - other.Zinc_mg;
        result.Copper_mg = Copper_mg - other.Copper_mg;
        result.Manganese_mg = Manganese_mg - other.Manganese_mg;
        result.Selenium_ug = Selenium_ug - other.Selenium_ug;
        result.Vit_C_mg = Vit_C_mg - other.Vit_C_mg;
        result.Thiamin_mg = Thiamin_mg - other.Thiamin_mg;
        result.Riboflavin_mg = Riboflavin_mg - other.Riboflavin_mg;
        result.Niacin_mg = Niacin_mg - other.Niacin_mg;
        result.Panto_Acid_mg = Panto_Acid_mg - other.Panto_Acid_mg;
        result.Vit_B6_mg = Vit_B6_mg - other.Vit_B6_mg;
        result.Folate_Tot_ug = Folate_Tot_ug - other.Folate_Tot_ug;
        result.Folic_Acid_ug = Folic_Acid_ug - other.Folic_Acid_ug;
        result.Food_Folate_ug = Food_Folate_ug - other.Food_Folate_ug;
        result.Folate_DFE_ug = Folate_DFE_ug - other.Folate_DFE_ug;
        result.Choline_Tot_mg = Choline_Tot_mg - other.Choline_Tot_mg;
        result.Vit_B12_ug = Vit_B12_ug - other.Vit_B12_ug;
        result.Vit_A_IU = Vit_A_IU - other.Vit_A_IU;
        result.Vit_A_RAE = Vit_A_RAE - other.Vit_A_RAE;
        result.Retinol_ug = Retinol_ug - other.Retinol_ug;
        result.Alpha_Carot_ug = Alpha_Carot_ug - other.Alpha_Carot_ug;
        result.Beta_Carot_ug = Beta_Carot_ug - other.Beta_Carot_ug;
        result.Beta_Crypt_ug = Beta_Crypt_ug - other.Beta_Crypt_ug;
        result.Lycopene_ug = Lycopene_ug - other.Lycopene_ug;
        result.Lut_Zea_ug = Lut_Zea_ug - other.Lut_Zea_ug;
        result.Vit_E_mg = Vit_E_mg - other.Vit_E_mg;
        result.Vit_D_ug = Vit_D_ug - other.Vit_D_ug;
        result.Vit_D_IU = Vit_D_IU - other.Vit_D_IU;
        result.Vit_K_ug = Vit_K_ug - other.Vit_K_ug;
        result.FA_Sat_g = FA_Sat_g - other.FA_Sat_g;
        result.FA_Mono_g = FA_Mono_g - other.FA_Mono_g;
        result.FA_Poly_g = FA_Poly_g - other.FA_Poly_g;
        result.Cholestrl_mg = Cholestrl_mg - other.Cholestrl_mg;
        return result;
    }

    // Overloaded / operator
    FoodData operator/(const FoodData &other) const {

        //Defaulting
        FoodData result;
        result.NDB_No = "";
        result.Shrt_Desc = "";
        result.GmWt_1 = 0;
        result.GmWt_2 = 0;
        result.GmWt_Desc1 = "";
        result.GmWt_Desc2 = "";
        result.Refuse_Pct = 0;

        // Add each nutrient value from the two FoodData objects
        result.Water_g = Water_g / other.Water_g;
        result.Energ_Kcal = Energ_Kcal / other.Energ_Kcal;
        result.Protein_g = Protein_g / other.Protein_g;
        result.Lipid_Tot_g = Lipid_Tot_g / other.Lipid_Tot_g;
        result.Ash_g = Ash_g / other.Ash_g;
        result.Carbohydrt_g = Carbohydrt_g / other.Carbohydrt_g;
        result.Fiber_TD_g = Fiber_TD_g / other.Fiber_TD_g;
        result.Sugar_Tot_g = Sugar_Tot_g / other.Sugar_Tot_g;
        result.Calcium_mg = Calcium_mg / other.Calcium_mg;
        result.Iron_mg = Iron_mg / other.Iron_mg;
        result.Magnesium_mg = Magnesium_mg / other.Magnesium_mg;
        result.Phosphorus_mg = Phosphorus_mg / other.Phosphorus_mg;
        result.Potassium_mg = Potassium_mg / other.Potassium_mg;
        result.Sodium_mg = Sodium_mg / other.Sodium_mg;
        result.Zinc_mg = Zinc_mg / other.Zinc_mg;
        result.Copper_mg = Copper_mg / other.Copper_mg;
        result.Manganese_mg = Manganese_mg / other.Manganese_mg;
        result.Selenium_ug = Selenium_ug / other.Selenium_ug;
        result.Vit_C_mg = Vit_C_mg / other.Vit_C_mg;
        result.Thiamin_mg = Thiamin_mg / other.Thiamin_mg;
        result.Riboflavin_mg = Riboflavin_mg / other.Riboflavin_mg;
        result.Niacin_mg = Niacin_mg / other.Niacin_mg;
        result.Panto_Acid_mg = Panto_Acid_mg / other.Panto_Acid_mg;
        result.Vit_B6_mg = Vit_B6_mg / other.Vit_B6_mg;
        result.Folate_Tot_ug = Folate_Tot_ug / other.Folate_Tot_ug;
        result.Folic_Acid_ug = Folic_Acid_ug / other.Folic_Acid_ug;
        result.Food_Folate_ug = Food_Folate_ug / other.Food_Folate_ug;
        result.Folate_DFE_ug = Folate_DFE_ug / other.Folate_DFE_ug;
        result.Choline_Tot_mg = Choline_Tot_mg / other.Choline_Tot_mg;
        result.Vit_B12_ug = Vit_B12_ug / other.Vit_B12_ug;
        result.Vit_A_IU = Vit_A_IU / other.Vit_A_IU;
        result.Vit_A_RAE = Vit_A_RAE / other.Vit_A_RAE;
        result.Retinol_ug = Retinol_ug / other.Retinol_ug;
        result.Alpha_Carot_ug = Alpha_Carot_ug / other.Alpha_Carot_ug;
        result.Beta_Carot_ug = Beta_Carot_ug / other.Beta_Carot_ug;
        result.Beta_Crypt_ug = Beta_Crypt_ug / other.Beta_Crypt_ug;
        result.Lycopene_ug = Lycopene_ug / other.Lycopene_ug;
        result.Lut_Zea_ug = Lut_Zea_ug / other.Lut_Zea_ug;
        result.Vit_E_mg = Vit_E_mg / other.Vit_E_mg;
        result.Vit_D_ug = Vit_D_ug / other.Vit_D_ug;
        result.Vit_D_IU = Vit_D_IU / other.Vit_D_IU;
        result.Vit_K_ug = Vit_K_ug / other.Vit_K_ug;
        result.FA_Sat_g = FA_Sat_g / other.FA_Sat_g;
        result.FA_Mono_g = FA_Mono_g / other.FA_Mono_g;
        result.FA_Poly_g = FA_Poly_g / other.FA_Poly_g;
        result.Cholestrl_mg = Cholestrl_mg / other.Cholestrl_mg;

        return result;
    }

    // Overloaded * operator
    FoodData operator*(int n) const {

        //Defaulting
        FoodData result;
        result.NDB_No = "";
        result.Shrt_Desc = "";
        result.GmWt_1 = 0;
        result.GmWt_2 = 0;
        result.GmWt_Desc1 = "";
        result.GmWt_Desc2 = "";
        result.Refuse_Pct = 0;

        // Add each nutrient value from the two FoodData objects
        result.Water_g = Water_g * n;
        result.Energ_Kcal = Energ_Kcal * n;
        result.Protein_g = Protein_g * n;
        result.Lipid_Tot_g = Lipid_Tot_g * n;
        result.Ash_g = Ash_g * n;
        result.Carbohydrt_g = Carbohydrt_g * n;
        result.Fiber_TD_g = Fiber_TD_g * n;
        result.Sugar_Tot_g = Sugar_Tot_g * n;
        result.Calcium_mg = Calcium_mg * n;
        result.Iron_mg = Iron_mg * n;
        result.Magnesium_mg = Magnesium_mg * n;
        result.Phosphorus_mg = Phosphorus_mg * n;
        result.Potassium_mg = Potassium_mg * n;
        result.Sodium_mg = Sodium_mg * n;
        result.Zinc_mg = Zinc_mg * n;
        result.Copper_mg = Copper_mg * n;
        result.Manganese_mg = Manganese_mg * n;
        result.Selenium_ug = Selenium_ug * n;
        result.Vit_C_mg = Vit_C_mg * n;
        result.Thiamin_mg = Thiamin_mg * n;
        result.Riboflavin_mg = Riboflavin_mg * n;
        result.Niacin_mg = Niacin_mg * n;
        result.Panto_Acid_mg = Panto_Acid_mg * n;
        result.Vit_B6_mg = Vit_B6_mg * n;
        result.Folate_Tot_ug = Folate_Tot_ug * n;
        result.Folic_Acid_ug = Folic_Acid_ug * n;
        result.Food_Folate_ug = Food_Folate_ug * n;
        result.Folate_DFE_ug = Folate_DFE_ug * n;
        result.Choline_Tot_mg = Choline_Tot_mg * n;
        result.Vit_B12_ug = Vit_B12_ug * n;
        result.Vit_A_IU = Vit_A_IU * n;
        result.Vit_A_RAE = Vit_A_RAE * n;
        result.Retinol_ug = Retinol_ug * n;
        result.Alpha_Carot_ug = Alpha_Carot_ug * n;
        result.Beta_Carot_ug = Beta_Carot_ug * n;
        result.Beta_Crypt_ug = Beta_Crypt_ug * n;
        result.Lycopene_ug = Lycopene_ug * n;
        result.Lut_Zea_ug = Lut_Zea_ug * n;
        result.Vit_E_mg = Vit_E_mg * n;
        result.Vit_D_ug = Vit_D_ug * n;
        result.Vit_D_IU = Vit_D_IU * n;
        result.Vit_K_ug = Vit_K_ug * n;
        result.FA_Sat_g = FA_Sat_g * n;
        result.FA_Mono_g = FA_Mono_g * n;
        result.FA_Poly_g = FA_Poly_g * n;
        result.Cholestrl_mg = Cholestrl_mg * n;

        return result;
    }

    // Return one nutrient value for a given nutrient name
    double GetValue(const std::string &nutrient) const {
        if (nutrient == "Energ_Kcal") return Energ_Kcal;
        if (nutrient == "Protein_g") return Protein_g;
        if (nutrient == "Lipid_Tot_g") return Lipid_Tot_g;
        if (nutrient == "Ash_g") return Ash_g;
        if (nutrient == "Carbohydrt_g") return Carbohydrt_g;
        if (nutrient == "Fiber_TD_g") return Fiber_TD_g;
        if (nutrient == "Sugar_Tot_g") return Sugar_Tot_g;
        if (nutrient == "Calcium_mg") return Calcium_mg;
        if (nutrient == "Iron_mg") return Iron_mg;
        if (nutrient == "Magnesium_mg") return Magnesium_mg;
        if (nutrient == "Phosphorus_mg") return Phosphorus_mg;
        if (nutrient == "Potassium_mg") return Potassium_mg;
        if (nutrient == "Sodium_mg") return Sodium_mg;
        if (nutrient == "Zinc_mg") return Zinc_mg;
        if (nutrient == "Copper_mg") return Copper_mg;
        if (nutrient == "Manganese_mg") return Manganese_mg;
        if (nutrient == "Selenium_ug") return Selenium_ug;
        if (nutrient == "Vit_C_mg") return Vit_C_mg;
        if (nutrient == "Thiamin_mg") return Thiamin_mg;
        if (nutrient == "Riboflavin_mg") return Riboflavin_mg;
        if (nutrient == "Niacin_mg") return Niacin_mg;
        if (nutrient == "Panto_Acid_mg") return Panto_Acid_mg;
        if (nutrient == "Vit_B6_mg") return Vit_B6_mg;
        if (nutrient == "Folate_Tot_ug") return Folate_Tot_ug;
        if (nutrient == "Folic_Acid_ug") return Folic_Acid_ug;
        if (nutrient == "Food_Folate_ug") return Food_Folate_ug;
        if (nutrient == "Folate_DFE_ug") return Folate_DFE_ug;
        if (nutrient == "Choline_Tot_mg") return Choline_Tot_mg;
        if (nutrient == "Vit_B12_ug") return Vit_B12_ug;
        if (nutrient == "Vit_A_IU") return Vit_A_IU;
        if (nutrient == "Vit_A_RAE") return Vit_A_RAE;
        if (nutrient == "Retinol_ug") return Retinol_ug;
        if (nutrient == "Alpha_Carot_ug") return Alpha_Carot_ug;
        if (nutrient == "Beta_Carot_ug") return Beta_Carot_ug;
        if (nutrient == "Beta_Crypt_ug") return Beta_Crypt_ug;
        if (nutrient == "Lycopene_ug") return Lycopene_ug;
        if (nutrient == "Lut_Zea_ug") return Lut_Zea_ug;
        if (nutrient == "Vit_E_mg") return Vit_E_mg;
        if (nutrient == "Vit_D_ug") return Vit_D_ug;
        if (nutrient == "Vit_D_IU") return Vit_D_IU;
        if (nutrient == "Vit_K_ug") return Vit_K_ug;
        if (nutrient == "FA_Sat_g") return FA_Sat_g;
        if (nutrient == "FA_Mono_g") return FA_Mono_g;
        if (nutrient == "FA_Poly_g") return FA_Poly_g;
        if (nutrient == "Cholestrl_mg") return Cholestrl_mg;
        if (nutrient == "GmWt_1") return GmWt_1;
        if (nutrient == "GmWt_2") return GmWt_2;
        if (nutrient == "Refuse_Pct") return Refuse_Pct;
        return -1; // If nutrient not found, return -1
    }

    // Return a vector of nutrient values
    std::vector<std::pair<std::string, double>> GetNutrientValues() {
        std::cout << "getnutrientvals" <<std::endl;
        return {
                {"Water_g",        Water_g},
                {"Energ_Kcal",     Energ_Kcal},
                {"Protein_g",      Protein_g},
                {"Lipid_Tot_g",    Lipid_Tot_g},
                {"Ash_g",          Ash_g},
                {"Carbohydrt_g",   Carbohydrt_g},
                {"Fiber_TD_g",     Fiber_TD_g},
                {"Sugar_Tot_g",    Sugar_Tot_g},
                {"Calcium_mg",     Calcium_mg},
                {"Iron_mg",        Iron_mg},
                {"Magnesium_mg",   Magnesium_mg},
                {"Phosphorus_mg",  Phosphorus_mg},
                {"Potassium_mg",   Potassium_mg},
                {"Sodium_mg",      Sodium_mg},
                {"Zinc_mg",        Zinc_mg},
                {"Copper_mg",      Copper_mg},
                {"Manganese_mg",   Manganese_mg},
                {"Selenium_ug",    Selenium_ug},
                {"Vit_C_mg",       Vit_C_mg},
                {"Thiamin_mg",     Thiamin_mg},
                {"Riboflavin_mg",  Riboflavin_mg},
                {"Niacin_mg",      Niacin_mg},
                {"Panto_Acid_mg",  Panto_Acid_mg},
                {"Vit_B6_mg",      Vit_B6_mg},
                {"Folate_Tot_ug",  Folate_Tot_ug},
                {"Folic_Acid_ug",  Folic_Acid_ug},
                {"Food_Folate_ug", Food_Folate_ug},
                {"Folate_DFE_ug",  Folate_DFE_ug},
                {"Choline_Tot_mg", Choline_Tot_mg},
                {"Vit_B12_ug",     Vit_B12_ug},
                {"Vit_A_IU",       Vit_A_IU},
                {"Vit_A_RAE",      Vit_A_RAE},
                {"Retinol_ug",     Retinol_ug},
                {"Alpha_Carot_ug", Alpha_Carot_ug},
                {"Beta_Carot_ug",  Beta_Carot_ug},
                {"Beta_Crypt_ug",  Beta_Crypt_ug},
                {"Lycopene_ug",    Lycopene_ug},
                {"Lut_Zea_ug",     Lut_Zea_ug},
                {"Vit_E_mg",       Vit_E_mg},
                {"Vit_D_ug",       Vit_D_ug},
                {"Vit_D_IU",       Vit_D_IU},
                {"Vit_K_ug",       Vit_K_ug},
                {"FA_Sat_g",       FA_Sat_g},
                {"FA_Mono_g",      FA_Mono_g},
                {"FA_Poly_g",      FA_Poly_g},
                {"Cholestrl_mg",   Cholestrl_mg},
                {"GmWt_1",         GmWt_1},
                {"GmWt_2",         GmWt_2},
                {"Refuse_Pct",     Refuse_Pct}
        };
    }
};

class SplayTree : public Napi::ObjectWrap<SplayTree>{

private:
    /*Server Private*/
    struct Node {
        FoodData data;
        Node *left;
        Node *right;
    };
    int dummy = 1;
    Node *root;
    // an average balanced diet
    FoodData balanced_diet;
    // total sum of user's food intake
    FoodData user_diet;
    Node *SearchNode(Node *root, const std::string &key); // return a node
    void Insert(const FoodData &food_data);
    void ReadFile(const std::string &filename);
    void CreateUserDiet();
    void CreateBalanced();
    // Additional helper functions for splay tree operations
    Node *NewNode(const FoodData &food_data);
    Node *RightRotate(Node *x);
    Node *LeftRotate(Node *x);
    Node *Splay(Node *root, const std::string &key);
    Node *InsertHelper(Node *root, const FoodData &food_data);
    Node *SearchHelper(Node *root, const std::string &key);
    Node *Join(Node *left, Node *right);
    void Split(Node *root, const std::string &key, Node *&left, Node *&right);
    void SearchPartialMatchesHelper(Node *node, const std::string &key, std::vector<FoodData *> &results);
    FoodData *NarrowDownSearch(const std::string &key);
    // Print Functions (Non Server/Napi Interfaces ∴ NOT called)
    void PrintInOrder() const; // splay tree in order (entire list)
    void PrintInOrderHelper(const Node *node) const;
    void Print(const FoodData &food); // single food item
    void PrintUserDiet(const FoodData &food);
    void PrintSearchResults(std::vector<FoodData *> &results);
    // Other (Non Server/Napi Interfaces ∴ NOT called)
    bool ReadQuotedField(std::stringstream &ss, std::string &field);
    // Other (No Current Website Use)
    FoodData *FindMaxNutrient(const std::string &nutrient);
    bool Delete(const std::string &key); // Delete a FoodData object based on a given key (e.g., NDB_No or Shrt_Desc)



    /*Server Almost Public - directly called by Napi functions*/
    // Search for a FoodData object based on a given key (e.g., NDB_No or Shrt_Desc)
    FoodData *Search(const std::string &key);
    std::vector<FoodData *> SearchPartialMatches(const std::string &key,
                                            const std::vector<FoodData *> &current_results); // Return a vector of matches
    //void CalculateFindMissing(std::vector<std::string> &keys);



    /*Server Public*/
    Napi::Value SearchNapi(const Napi::CallbackInfo& info);
    Napi::Value SearchPartialMatchesNapi(const Napi::CallbackInfo& info);
    Napi::Value DummyNapi(const Napi::CallbackInfo& info);
    //Napi::Value CalculateFindMissingNapi(const Napi::CallbackInfo& info); FIXME



public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    SplayTree(const Napi::CallbackInfo& info);

};

#endif