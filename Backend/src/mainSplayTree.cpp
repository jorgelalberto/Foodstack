#include "SplayTree.h"

int main() {
    SplayTree splayTree();
    cout << "Welcome to the Food Finder!" << endl
    << "Enter an option:\n 1. Search for an ingredient's data\n"
       "2. Find missing ingredients from a diet\n"
       "3. Exit\n";
    int option;
    cin >> option;
    cin.ignore();

    if (option == 1)
    {
        cout << "Enter an ingredient: ";
        string input;
        getline(cin, input);
        FoodData ing = *splayTree.NarrowDownSearch(input);
        cout << "You've entered: " << ing.Shrt_Desc << endl;
        std::vector<pair<string, double>> nutrients = ing.GetNutrientValues();
        for (int i = 0; i < nutrients.size(); i++) {
            cout << nutrients[i].first << ": " << nutrients[i].second << endl;
        }
    }
    else if (option == 2){
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
    }

    return 0;
}
