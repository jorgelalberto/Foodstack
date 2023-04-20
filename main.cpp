#include "SplayTree.h"

int main() {
    SplayTree splayTree("food.csv");

    int n;
    cout << "Enter how many Ingredients : " << endl;
    cin >> n;
    cin.ignore();

    vector<string> userIngredients;
    for (int i = 0; i < n; ++i) {
        string ingredient;
        getline(cin, ingredient);
        userIngredients.push_back(ingredient);
    }

    splayTree.CalculateFindMissing(userIngredients);
    return 0;
}
