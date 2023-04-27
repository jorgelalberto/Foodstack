#include "SplayTree.h"

SplayTree::SplayTree() {
    root = nullptr;
    CreateBalanced();
    CreateUserDiet();
}

SplayTree::SplayTree(const std::string &filename) {
    root = nullptr;
    ReadFile(filename);
    CreateBalanced();
    CreateUserDiet();
}

SplayTree::~SplayTree() {
    std::function<void(Node *)> deleteNodes = [&](Node *node) {
        if (node == nullptr) {
            return;
        }
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
    };
    deleteNodes(root);
}

void SplayTree::CreateBalanced() {
    balanced_diet.Energ_Kcal = 2000;
    balanced_diet.Protein_g = 50;
    balanced_diet.Lipid_Tot_g = 70;
    balanced_diet.Carbohydrt_g = 310;
    balanced_diet.Fiber_TD_g = 30;
    balanced_diet.Sugar_Tot_g = 90;
    balanced_diet.Calcium_mg = 1000;
    balanced_diet.Iron_mg = 18;
    balanced_diet.Magnesium_mg = 400;
    balanced_diet.Phosphorus_mg = 1000;
    balanced_diet.Potassium_mg = 3500;
    balanced_diet.Sodium_mg = 2400;
    balanced_diet.Zinc_mg = 11;
    balanced_diet.Copper_mg = 0.9;
    balanced_diet.Manganese_mg = 2.3;
    balanced_diet.Selenium_ug = 55;
    balanced_diet.Vit_C_mg = 90;
    balanced_diet.Thiamin_mg = 1.2;
    balanced_diet.Riboflavin_mg = 1.3;
    balanced_diet.Niacin_mg = 16;
    balanced_diet.Panto_Acid_mg = 5;
    balanced_diet.Vit_B6_mg = 1.7;
    balanced_diet.Folate_Tot_ug = 400;
    balanced_diet.Folic_Acid_ug = 400;
    balanced_diet.Food_Folate_ug = 400;
    balanced_diet.Folate_DFE_ug = 400;
    balanced_diet.Choline_Tot_mg = 425;
    balanced_diet.Vit_B12_ug = 2.4;
    balanced_diet.Vit_A_IU = 5000;
    balanced_diet.Vit_A_RAE = 900;
    balanced_diet.Retinol_ug = 900;
    balanced_diet.Alpha_Carot_ug = 700;
    balanced_diet.Beta_Carot_ug = 700;
    balanced_diet.Beta_Crypt_ug = 700;
    balanced_diet.Lycopene_ug = 700;
    balanced_diet.Lut_Zea_ug = 700;
    balanced_diet.Vit_D_ug = 20;
    balanced_diet.Vit_D_IU = 800;
    balanced_diet.Vit_K_ug = 120;
    balanced_diet.FA_Sat_g = 20;
    balanced_diet.FA_Mono_g = 25;
    balanced_diet.FA_Poly_g = 25;
    balanced_diet.Cholestrl_mg = 300;
    balanced_diet.FA_Tot = 20 + 25 + 25;
}

void SplayTree::CreateUserDiet() {
    user_diet.Energ_Kcal = 0;
    user_diet.Protein_g = 0;
    user_diet.Lipid_Tot_g = 0;
    user_diet.Carbohydrt_g = 0;
    user_diet.Fiber_TD_g = 0;
    user_diet.Sugar_Tot_g = 0;
    user_diet.Calcium_mg = 0;
    user_diet.Iron_mg = 0;
    user_diet.Magnesium_mg = 0;
    user_diet.Phosphorus_mg = 0;
    user_diet.Potassium_mg = 0;
    user_diet.Sodium_mg = 0;
    user_diet.Zinc_mg = 0;
    user_diet.Copper_mg = 0;
    user_diet.Manganese_mg = 0;
    user_diet.Selenium_ug = 0;
    user_diet.Vit_C_mg = 0;
    user_diet.Thiamin_mg = 0;
    user_diet.Riboflavin_mg = 0;
    user_diet.Niacin_mg = 0;
    user_diet.Panto_Acid_mg = 0;
    user_diet.Vit_B6_mg = 0;
    user_diet.Folate_Tot_ug = 0;
    user_diet.Folic_Acid_ug = 0;
    user_diet.Food_Folate_ug = 0;
    user_diet.Folate_DFE_ug = 0;
    user_diet.Choline_Tot_mg = 0;
    user_diet.Vit_B12_ug = 0;
    user_diet.Vit_A_IU = 0;
    user_diet.Vit_A_RAE = 0;
    user_diet.Retinol_ug = 0;
    user_diet.Alpha_Carot_ug = 0;
    user_diet.Beta_Carot_ug = 0;
    user_diet.Beta_Crypt_ug = 0;
    user_diet.Lycopene_ug = 0;
    user_diet.Lut_Zea_ug = 0;
    user_diet.Vit_D_ug = 0;
    user_diet.Vit_D_IU = 0;
    user_diet.Vit_K_ug = 0;
    user_diet.FA_Sat_g = 0;
    user_diet.FA_Mono_g = 0;
    user_diet.FA_Poly_g = 0;
    user_diet.Cholestrl_mg = 0;
}

bool SplayTree::ReadQuotedField(std::stringstream &ss, std::string &field) {
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

void SplayTree::ReadFile(const std::string &filename) {

    std::vector<FoodData> food_data_list;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    getline(file, line); // Skip the header
    int lineNumber = 2; // Start from the second line as we have already skipped the header

    while (getline(file, line)) {
        std::stringstream ss(line);
        FoodData food_data;

        // Fill the struct with data
        getline(ss, food_data.NDB_No, ',');
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
        READ_OR_DEFAULT(GmWt_2)
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
        this->Insert(food_data); // Insert the food data into the tree
        lineNumber++; // Increment the line number
    }
}

void SplayTree::Insert(const FoodData &food_data) {
    root = InsertHelper(root, food_data);
}

SplayTree::Node *SplayTree::InsertHelper(Node *root, const FoodData &food_data) {
    if (!root) {
        return NewNode(food_data);
    }

    // Splay the node with the closest key to the target key
    root = Splay(root, food_data.Shrt_Desc);

    if (root->data.Shrt_Desc == food_data.Shrt_Desc) {
        // If the key already exists, replace the data
        root->data = food_data;
    } else if (root->data.Shrt_Desc < food_data.Shrt_Desc) {
        // Insert the new node to the right of the splayed node
        Node *new_node = NewNode(food_data);
        new_node->right = root->right;
        new_node->left = root;
        root->right = nullptr;
        root = new_node;
    } else {
        // Insert the new node to the left of the splayed node
        Node *new_node = NewNode(food_data);
        new_node->left = root->left;
        new_node->right = root;
        root->left = nullptr;
        root = new_node;
    }

    return root;
}

SplayTree::Node *SplayTree::NewNode(const FoodData &food_data) {
    Node *node = new Node;
    node->data = food_data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

SplayTree::Node *SplayTree::SearchHelper(Node *root, const std::string &key) {
    if (!root || root->data.Shrt_Desc == key) {
        return root;
    }

    if (root->data.Shrt_Desc < key) {
        if (!root->right) {
            return root;
        }
        if (root->right->data.Shrt_Desc < key) {
            root->right->right = SearchHelper(root->right->right, key);
            root = LeftRotate(root);
        } else if (root->right->data.Shrt_Desc > key) {
            root->right->left = SearchHelper(root->right->left, key);
            if (root->right->left) {
                root->right = RightRotate(root->right);
            }
        }
        // Update the root of the subtree after rotations
        root = !root->right ? root : LeftRotate(root);
    } else {
        if (!root->left) {
            return root;
        }
        if (root->left->data.Shrt_Desc > key) {
            root->left->left = SearchHelper(root->left->left, key);
            root = RightRotate(root);
        } else if (root->left->data.Shrt_Desc < key) {
            root->left->right = SearchHelper(root->left->right, key);
            if (root->left->right) {
                root->left = LeftRotate(root->left);
            }
        }
        // Update the root of the subtree after rotations
        root = !root->left ? root : RightRotate(root);
    }
    return root;
}

FoodData *SplayTree::Search(const string &key) {
    // MEASUREMENTS
    clock_t start, end;
    double cpu_time_used;
    start = clock(); // Get the starting time

    // Search for a FoodData object based on a given key (Shrt_Desc)
    root = SearchHelper(root, key);
    if (root && root->data.Shrt_Desc == key) {

        // END MEASUREMENTS
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << "Time taken: " << cpu_time_used << " seconds" << std::endl;

        return &(root->data);
    }
    return nullptr;
}

FoodData *SplayTree::NarrowDownSearch(const std::string &key) {

    // MEASUREMENTS
    clock_t start, end;
    double cpu_time_used;
    start = clock(); // Get the starting time

    std::vector<FoodData *> results = SearchPartialMatches(key, {});
    std::vector<FoodData *> prev_results;
    std::string input_key = key;

    while (results.size() > 1 || results.empty()) {
        PrintSearchResults(results);

        if (results.empty()) {
            std::cout << "No matches found. Please try again: ";
        } else {
            std::cout << "Please refine your search: ";
        }

        std::getline(std::cin, input_key);

        prev_results = results; // Save previous results
        results = SearchPartialMatches(input_key, results);

        // If the new search has no matches, revert to the previous results
        if (results.empty()) {
            results = prev_results;
        }
    }

    if (results.size() == 1) {

        // END MEASUREMENTS
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << "Time taken: " << cpu_time_used << " seconds" << std::endl;

        root = SearchHelper(root, results[0]->Shrt_Desc); // Reorganize the splay tree
        return results[0];
    }

    return nullptr;
}

std::vector<FoodData *>
SplayTree::SearchPartialMatches(const std::string &key, const std::vector<FoodData *> &current_results) {
    std::vector<FoodData *> results;
    std::string key_upper = key;
    std::transform(key_upper.begin(), key_upper.end(), key_upper.begin(), ::toupper);

    if (current_results.empty()) {
        // If no current results, search the entire tree
        SearchPartialMatchesHelper(root, key_upper, results);
    } else {
        // If there are current results, search only within them
        for (auto &food_data: current_results) {
            std::string shrt_desc_upper = food_data->Shrt_Desc;
            std::transform(shrt_desc_upper.begin(), shrt_desc_upper.end(), shrt_desc_upper.begin(), ::toupper);

            if (shrt_desc_upper.find(key_upper) != std::string::npos) {
                results.push_back(food_data);
            }
        }
    }

    return results;
}

void SplayTree::SearchPartialMatchesHelper(Node *node, const std::string &key, std::vector<FoodData *> &results) {
    if (!node) {
        return;
    }

    std::string shrt_desc_upper = node->data.Shrt_Desc;
    std::transform(shrt_desc_upper.begin(), shrt_desc_upper.end(), shrt_desc_upper.begin(), ::toupper);

    if (shrt_desc_upper.find(key) != std::string::npos) {
        results.push_back(&(node->data));
    }

    SearchPartialMatchesHelper(node->left, key, results);
    SearchPartialMatchesHelper(node->right, key, results);
}

FoodData *SplayTree::FindMaxNutrient(const std::string &nutrient) {
    if (!root) {
        return nullptr;
    }

    FoodData *max_food_data = nullptr;
    double max_value = -1;
    Traverse(root, nutrient, max_food_data, max_value);
    return max_food_data;
}

void SplayTree::Traverse(Node *node, const std::string &nutrient, FoodData *&max_food_data, double &max_value) {
    if (!node) {
        return;
    }

    double current_value = node->data.GetValue(nutrient);
    if (current_value > max_value) {
        max_value = current_value;
        max_food_data = &(node->data);
    }

    Traverse(node->left, nutrient, max_food_data, max_value);
    Traverse(node->right, nutrient, max_food_data, max_value);
}

bool SplayTree::Delete(const std::string &key) {
    if (!root) {
        return false;
    }

    root = Splay(root, key);
    if (root->data.NDB_No != key) {
        return false; // Key not found
    }

    Node *left = root->left;
    Node *right = root->right;
    delete root;
    root = Join(left, right);

    return true;
}

SplayTree::Node *SplayTree::RightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayTree::Node *SplayTree::LeftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayTree::Node *SplayTree::Join(Node *left, Node *right) {
    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }

    // Find the largest element in the left tree
    Node *temp = left;
    while (temp->right) {
        temp = temp->right;
    }

    // Splay the largest element to the root of the left tree
    left = SearchHelper(left, temp->data.Shrt_Desc);

    // Set the right tree as the right child of the left tree
    left->right = right;
    return left;
}

SplayTree::Node *SplayTree::Splay(Node *root, const std::string &key) {
    if (!root) {
        return nullptr;
    }

    if (root->data.Shrt_Desc == key) {
        return root;
    }

    if (root->data.Shrt_Desc < key) {
        // Key is in the right subtree
        if (!root->right) {
            return root;
        }

        if (root->right->data.Shrt_Desc < key) {
            // Right-right case: rotate left
            root->right->right = Splay(root->right->right, key);
            root = LeftRotate(root);
        } else if (root->right->data.Shrt_Desc > key) {
            // Right-left case: rotate right and then left
            root->right->left = Splay(root->right->left, key);
            if (root->right->left) {
                root->right = RightRotate(root->right);
            }
        }

        return root->right ? LeftRotate(root) : root;
    } else {
        // Key is in the left subtree
        if (!root->left) {
            return root;
        }

        if (root->left->data.Shrt_Desc < key) {
            // Left-right case: rotate left and then right
            root->left->right = Splay(root->left->right, key);
            if (root->left->right) {
                root->left = LeftRotate(root->left);
            }
        } else if (root->left->data.Shrt_Desc > key) {
            // Left-left case: rotate right
            root->left->left = Splay(root->left->left, key);
            root = RightRotate(root);
        }

        return root->left ? RightRotate(root) : root;
    }
}

void SplayTree::PrintInOrder() const {
    PrintInOrderHelper(root);
    std::cout << std::endl;
}

void SplayTree::PrintInOrderHelper(const Node *node) const {
    if (node == nullptr) {
        return;
    }
    PrintInOrderHelper(node->left);
    std::cout << node->data.Shrt_Desc << endl;
    PrintInOrderHelper(node->right);
}
void SplayTree::PrintPreOrder() {
    PrintPreOrderHelper(root);
    std::cout << std::endl;
}

void SplayTree::PrintPreOrderHelper(const Node *node) const {
    if (!node) {
        return;
    }

    // Print the current node's data
    std::cout << node->data.Shrt_Desc << endl;

    // Recursively print the left and right subtrees
    PrintPreOrderHelper(node->left);
    PrintPreOrderHelper(node->right);
}
void SplayTree::PrintRoot(){
    cout << root->data.Shrt_Desc << endl;
}

void SplayTree::Print(const FoodData &food) {
    double sum_fats = food.FA_Sat_g + food.FA_Mono_g + food.FA_Poly_g;
    cout << "Ingredient: " << food.Shrt_Desc << " Calories: " << food.Energ_Kcal <<
         " Protein: " << food.Protein_g << " Carbs: " << food.Carbohydrt_g << " Fats: " << sum_fats << endl;
}

void SplayTree::PrintUserDiet(const FoodData &food) {
    double sum_fats = food.FA_Sat_g + food.FA_Mono_g + food.FA_Poly_g;
    cout << "Your daily intake: " << food.Shrt_Desc << " Calories: " << food.Energ_Kcal <<
         " Protein: " << food.Protein_g << " Carbs: " << food.Carbohydrt_g << " Fats: " << sum_fats << endl;
}

void SplayTree::PrintSearchResults(vector<FoodData *> &results) {
    std::cout << "Search results:\n";
    for (const auto &result: results) {
        std::cout << result->Shrt_Desc << std::endl;
    }
}

void SplayTree::CalculateFindMissing(vector<string> &keys) {
    for (const string &key: keys) {
        FoodData *temp = Search(key);
        if (temp == nullptr) {
            cout << "Ingredient not found" << endl;
            continue;
        }
        user_diet = user_diet + *temp;
    }

    PrintUserDiet(user_diet);
    FoodData percent_missing = user_diet / balanced_diet;
    percent_missing = percent_missing * 100;

    vector<pair<string, double>> percents = percent_missing.GetNutrientValues();
    // Sort the percents vector by lowest value first
    std::sort(percents.begin(), percents.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    });

    // Put the 3 lowest values in a vector of strings
    std::vector<std::string> lowest_three_nutrients;
    cout << "Most missing nutrients: ";
    for (auto &percent: percents) {
        if (percent.first != "Refuse_Pct" && percent.first != "GmWt_2" && percent.first != "GmWt_1") {
            lowest_three_nutrients.push_back(percent.first);
        }
        if (lowest_three_nutrients.size() >= 3) {
            break;
        }
    }
    for (const auto &lowest_three_nutrient: lowest_three_nutrients) {
        cout << lowest_three_nutrient << " ";
    }
    cout << endl;

    // now find the 3 highest ingredients with these nutrients
    vector<FoodData *> missing_from_diet;
    set<string> added_ingredients;
    for (const string &i: lowest_three_nutrients) {
        FoodData *max_nutrient_food = FindMaxNutrient(i);

        // Check if the ingredient is already added
        if (added_ingredients.find(max_nutrient_food->Shrt_Desc) == added_ingredients.end()) {
            missing_from_diet.push_back(max_nutrient_food);
            added_ingredients.insert(max_nutrient_food->Shrt_Desc);
        }
    }

    // Print missing ingredients
    for (FoodData *f: missing_from_diet) {
        Print(*f);
    }
}

void SplayTree::CalculateUserBMR(const string &gender, int weight, int height, int age, const string &activity_level) {
    double bmr;
    if (gender == "m") {
        bmr = 66.47 + ((13.75 * 0.454) * weight) + ((5.003 * 2.54) * height) - (6.755 * age);
    } else {
        bmr = 655.1 + ((9.563 * 0.454) * weight) + ((1.85 * 2.54) * height) - (4.676 * age);
    }
    if (activity_level == "sedentary") {
        bmr *= 1.2;
    } else if (activity_level == "lightly active") {
        bmr *= 1.375;
    } else if (activity_level == "moderately active") {
        bmr *= 1.55;
    } else if (activity_level == "very active") {
        bmr *= 1.725;
    } else if (activity_level == "extra active") {
        bmr *= 1.9;
    }

    double protein = bmr * 0.36;
    double carbs = bmr * 0.44;
    double fats = bmr * 0.3;

    // TODO: - maybe implement this - for saving the balanced diet and calculating the missing nutrients.
    /*
    balanced_diet.Energ_Kcal = bmr;
    balanced_diet.Protein_g = protein/4;
    balanced_diet.Carbohydrt_g = carbs/4;
    balanced_diet.FA_Tot = fats/9; */

    cout << "Your BMR is: " << bmr << " calories" << endl;
    cout << "Your daily protein intake should be: " << fixed << setprecision(2) << protein / 4 << " grams" << endl;
    cout << "Your daily carbs intake should be: " << fixed << setprecision(2) << carbs / 4 << " grams" << endl;
    cout << "Your daily fats intake should be: " << fixed << setprecision(2) << fats / 9 << " grams" << endl;
}
