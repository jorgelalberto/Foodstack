#include "SplayTree.h"

int main() {
    SplayTree splayTree("food.csv");
    bool running = true;

    cout << "Welcome to the Food Finder!" << endl;
    while (running) {
        cout << "Enter an option:\n"
                "1. Search for an ingredient's data\n"
                "2. Find missing ingredients from a diet\n"
                "3. Search meal totals\n"
                "4. Your BMR\n"
                "5. Print the list\n"
                "6. Print the root\n"
                "Exit: any other key\n";

        int option;
        cin >> option;
        cin.ignore();
        bool select = true;

        if (option == 1 && select) {
            cout << "Enter an ingredient: ";
            string input;
            getline(cin, input);
            FoodData ing = *splayTree.NarrowDownSearch(input);
            cout << "You've entered: " << ing.Shrt_Desc << endl;
            std::vector<pair<string, double>> nutrients = ing.GetNutrientValues();
            for (auto &nutrient: nutrients) {
                cout << nutrient.first << ": " << nutrient.second << endl;
            }
            select = false;
        } else if (option == 2 && select) {
            int n;
            cout << "Enter how many Ingredients : " << endl;
            cin >> n;
            cin.ignore();

            vector<string> userIngredients;
            for (int i = 0; i < n; ++i) {
                string input;
                getline(cin, input);
                FoodData ing = *splayTree.NarrowDownSearch(input);
                cout << "You've entered: " << ing.Shrt_Desc << endl;
                userIngredients.push_back(ing.Shrt_Desc);
            }
            cout << "Ingredients entered: \n";
            for (int i = 0; i < n; i++) {
                cout << i + 1 << ". " << userIngredients[i] << endl;
            }
            splayTree.CalculateFindMissing(userIngredients);
            select = false;
        } else if (option == 3 && select) {
            cout << "Enter a meal (5 ingredients) \n";
            vector<string> userIngredients;
            for (int i = 0; i < 5; ++i) {
                string input;
                getline(cin, input);
                FoodData ing = *splayTree.NarrowDownSearch(input);
                cout << "You've entered: " << ing.Shrt_Desc << endl;
                splayTree.UpdateUserDiet(ing);
            }
            SplayTree::PrintUserDiet(splayTree.GetUserDiet());
            select = false;
        } else if (option == 4 && select) {

            int weight, height, age;
            string gender, activity;

            cout << "Enter your gender(m or f): \n";
            cin >> gender;
            cout << "Enter your weight (in pounds): \n";
            cin >> weight;
            cout << "Enter your height (in inches): \n";
            cin >> height;
            cout << "Enter your age: \n";
            cin >> age;

            cout
                    << "Enter your activity level (sedentary, lightly active, moderately active, very active, extra active): \n";
            cin >> activity;

            SplayTree::CalculateUserBMR(gender, weight, height, age, activity);
            select = false;
        } else if (option == 5 && select) {
            splayTree.PrintPreOrder();
            select = false;

        } else if (option == 6 && select) {
            splayTree.PrintRoot();
            select = false;
        } else {
            running = false;
        }
    }
    return 0;
}
