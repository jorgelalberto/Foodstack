#include "SplayTree.h"

// Description: - callback method when module is registered w/Node.js
//              - calls constructor
//              - sets export keys and values, and returns exports
// Call Flow: first_js_module_use -> Init
Napi::Object SplayTree::Init(Napi::Env env, Napi::Object exports) {

    // returns constructor
    Napi::Function func =
        DefineClass(env,
                  "SplayTree",
                  {InstanceMethod("searchnapi", &SplayTree::SearchNapi),
                   InstanceMethod("searchpartialmatchesnapi", &SplayTree::SearchPartialMatchesNapi),
                    InstanceMethod("gettimenapi", &SplayTree::GetTimeNapi)
                    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("SplayTree", func);
    return exports;
}

// Description: - constructor
//              - reads food.csv
//              - creates balanced diet
//              - creates user diet
// Call Flow: first_js_module_use -> Init -> this_constructor
SplayTree::SplayTree(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<SplayTree>(info) {
    Napi::Env env = info.Env();
    int length = info.Length();

    // Error Handling
    if (length > 0) {
        Napi::TypeError::New(env, "Constructor does not take in value(s)").ThrowAsJavaScriptException();
        return;
    }

    root = nullptr;
    ReadFile("food.csv");
    CreateBalanced();
    CreateUserDiet();
}

Napi::Value SplayTree::SearchNapi(const Napi::CallbackInfo& info) {
    std::string ingredient = (std::string) info[0].ToString();

    // Search for food's data
    // struct -> vector<pair<string, double>> -> napi array of FoodData's values (aka nutritional info)
    std::vector<FoodData*> current_results = {};
    // note: resultVecFoodWillAlways be of size 1
    FoodData* ingredientInfo = NarrowDownSearch(ingredient);
    int napiArraySize = 5;
    Napi::Array resultNapi = Napi::Array::New(info.Env(), napiArraySize);
    
    // populate napi array
    int ind0 = 0;
    int ind1 = 1;
    int ind2 = 2;
    int ind3 = 3;
    int ind4 = 4;
    double cals = ingredientInfo->Energ_Kcal;
    double protein = ingredientInfo->Protein_g;
    double carbs = ingredientInfo->Carbohydrt_g;
    double fat = ingredientInfo->Lipid_Tot_g;
    double sugar = ingredientInfo->Sugar_Tot_g;
    resultNapi[ind0] = Napi::Number::New(info.Env(), cals);
    resultNapi[ind1] = Napi::Number::New(info.Env(), protein);
    resultNapi[ind2] = Napi::Number::New(info.Env(), carbs);
    resultNapi[ind3] = Napi::Number::New(info.Env(), fat);
    resultNapi[ind4] = Napi::Number::New(info.Env(), sugar);

    return resultNapi;
}

Napi::Value SplayTree::SearchPartialMatchesNapi(const Napi::CallbackInfo& info) {
    std::string typed = (std::string) info[0].ToString();

    // search for typed letter's partial matches
    // ex: burg is a partial match for burger
    // vector<FoodData *> -> napi array of FoodData's description (aka food name)
    // FIXME: currently passing in empty vector, ideally pass in vector of current results
    std::vector<FoodData*> current_results = {};
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<FoodData*> resultVecFood = SearchPartialMatches(typed, current_results);
    auto end = std::chrono::high_resolution_clock::now();
    this->lastRunTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    Napi::Array resultNapi = Napi::Array::New(info.Env(), resultVecFood.size());

    // populate napi array
    for (int i=0; i < resultVecFood.size(); i++) {
        std::string foodDescription = resultVecFood[i]->Shrt_Desc;
        resultNapi[i] = Napi::String::New(info.Env(), foodDescription);
    }

    return resultNapi;
}

// get stored lastRunTime var, which stores in obj the time the last search opeartion took to run
Napi::Value SplayTree::GetTimeNapi(const Napi::CallbackInfo& info) {
    // Error Handling
    if (info.Length() > 0) {
        Napi::TypeError::New(info.Env(), "GetTime does not take in value(s)").ThrowAsJavaScriptException();
        return Napi::Number::New(info.Env(), -1);
    }
    
    return Napi::Number::New(info.Env(), this->lastRunTime);
}

/*
FIXME
Napi::Value CalculateFindMissingNapi(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int length = info.Length();

    // Error Handling
    if (length > 0) {
        Napi::TypeError::New(env, "CalculateFindMissingNapi does not take in value(s)").ThrowAsJavaScriptException();
        return;
    }
}
*/

// Call Flow: first_js_module_use -> Init -> Constructor -> CreateBalanced
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
}

// Call Flow: first_js_module_use -> Init -> Constructor -> CreateUserDiet
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

// Commmand Line Interface, NOT Server Interface
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

// Description: Reads food.csv file while storing contents in splay tree
// Call Flow: first_js_module_use -> Init -> Constructor -> ReadFile
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
    if (line.empty()) { \
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
        ReadQuotedField(ss, food_data.GmWt_Desc1);
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
        Insert(food_data); // Insert the food data into the SplayTree
        lineNumber++; // Increment the line number
    }
}

//Insert a FoodData object into the splay tree
void SplayTree::Insert(const FoodData &food_data) {
    root = InsertHelper(root, food_data);
}

SplayTree::Node *SplayTree::InsertHelper(Node *root, const FoodData &food_data) {
    if (!root) {
        return NewNode(food_data);
    }

    // Splay the node with the closest key to the target key
    root = Splay(root, food_data.NDB_No);

    if (root->data.NDB_No == food_data.NDB_No) {
        // If the key already exists, replace the data
        root->data = food_data;
    } else if (root->data.NDB_No < food_data.NDB_No) {
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

/*Returns food data*/
FoodData *SplayTree::Search(const std::string &key) {
    // Search for a FoodData object based on a given key (Shrt_Desc)
    auto begin = std::chrono::high_resolution_clock::now();
    root = SearchHelper(root, key);

    if (root && root->data.Shrt_Desc == key) {
        auto end = std::chrono::high_resolution_clock::now();
        this->lastRunTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

        return &(root->data);
    }

    auto end = std::chrono::high_resolution_clock::now();
    this->lastRunTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

    return nullptr;
}

// Call Flow: CalculateFindMissing -> NarrowDownSearch
FoodData *SplayTree::NarrowDownSearch(const std::string &key) {
    auto begin = std::chrono::high_resolution_clock::now();

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
        root = SearchHelper(root, results[0]->Shrt_Desc); // Reorganize the splay tree
        
        auto end = std::chrono::high_resolution_clock::now();
        this->lastRunTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

        return results[0];
    }


    auto end = std::chrono::high_resolution_clock::now();

    return nullptr;
}

std::vector<FoodData *> SplayTree::SearchPartialMatches(const std::string &key, const std::vector<FoodData *> &current_results) {
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

// Recursive helper function to search for a node with the given key
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
        return !root->right ? root : LeftRotate(root);
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
        return !root->left ? root : RightRotate(root);
    }
}

FoodData *SplayTree::FindMaxNutrient(const std::string &nutrient) {
    if (!root) {
        return nullptr;
    }

    FoodData *max_food_data = nullptr;
    double max_value = -1;

    std::function<void(Node *)> traverse = [&](Node *node) {
        if (!node) {
            return;
        }

        double current_value = node->data.GetValue(nutrient);
        if (current_value > max_value) {
            max_value = current_value;
            max_food_data = &(node->data);
        }

        traverse(node->left);
        traverse(node->right);
    };

    traverse(root);
    return max_food_data;
}

SplayTree::Node *SplayTree::SearchNode(Node *root, const std::string &key) {
    root = SearchHelper(root, key);
    return root;
}

// Delete a FoodData object based on a given key (e.g., NDB_No or Shrt_Desc)
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

// Perform a right rotation on the given node x
SplayTree::Node *SplayTree::RightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Perform a left rotation on the given node x
SplayTree::Node *SplayTree::LeftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Join two splay trees with all elements in the left tree having smaller keys than elements in the right tree
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
    left = SearchHelper(left, temp->data.NDB_No);

    // Set the right tree as the right child of the left tree
    left->right = right;
    return left;
}

// Split the splay tree into two trees: left tree contains all elements with keys smaller than the given key,
// and the right tree contains all elements with keys greater than or equal to the given key
void SplayTree::Split(Node *root, const std::string &key, Node *&left, Node *&right) {
    if (!root) {
        left = right = nullptr;
        return;
    }

    // Splay the root node based on the given key
    root = SearchHelper(root, key);

    if (root->data.NDB_No < key) {
        left = root;
        right = root->right;
        left->right = nullptr;
    } else {
        right = root;
        left = root->left;
        right->left = nullptr;
    }
}

// Splay the node with the given key to the root of the splay tree rooted at the given root
SplayTree::Node *SplayTree::Splay(Node *root, const std::string &key) {
    if (!root) {
        return nullptr;
    }

    if (root->data.NDB_No == key) {
        return root;
    }

    if (root->data.NDB_No < key) {
        // Key is in the right subtree
        if (!root->right) {
            return root;
        }

        if (root->right->data.NDB_No < key) {
            // Right-right case: rotate left
            root->right->right = Splay(root->right->right, key);
            root = LeftRotate(root);
        } else if (root->right->data.NDB_No > key) {
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

        if (root->left->data.NDB_No < key) {
            // Left-right case: rotate left and then right
            root->left->right = Splay(root->left->right, key);
            if (root->left->right) {
                root->left = LeftRotate(root->left);
            }
        } else if (root->left->data.NDB_No > key) {
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
    std::cout << node->data.Shrt_Desc << std::endl;
    PrintInOrderHelper(node->right);
}

void SplayTree::Print(const FoodData &food) {
    int sum_fats = food.FA_Sat_g + food.FA_Mono_g + food.FA_Poly_g;
    std::cout << "Ingredient: " << food.Shrt_Desc << " Calories: " << food.Energ_Kcal <<
         " Protein: " << food.Protein_g << " Carbs: " << food.Carbohydrt_g << " Fats: " << sum_fats << std::endl;
}

void SplayTree::PrintUserDiet(const FoodData &food) {
    int sum_fats = food.FA_Sat_g + food.FA_Mono_g + food.FA_Poly_g;
    std::cout << "Your daily intake: " << food.Shrt_Desc << " Calories: " << food.Energ_Kcal <<
         " Protein: " << food.Protein_g << " Carbs: " << food.Carbohydrt_g << " Fats: " << sum_fats << std::endl;
}

void SplayTree::PrintSearchResults(std::vector<FoodData *> &results) {
    std::cout << "Search results:\n";
    for (const auto &result: results) {
        std::cout << result->Shrt_Desc << std::endl;
    }
}

// Calculate and print the missing nutrients from diet
/*
void SplayTree::CalculateFindMissing(std::vector<std::string> &keys) {
    for (const std::string &key: keys) {
        FoodData *temp = NarrowDownSearch(key);
        if (temp == nullptr) {
            std::cout << "Ingredient not found" << std::endl;
            continue;
        }
        user_diet = user_diet + *temp;
    }

    PrintUserDiet(user_diet);

    // TODO: Calculate % nutrient missing from diet and get top 3 missing ingredients
    FoodData percent_missing = user_diet / balanced_diet;
    percent_missing = percent_missing * 100;

    vector<std::pair<std::string, double>> percents = percent_missing.GetNutrientValues();
    // Sort the percents vector by lowest value first
    std::sort(percents.begin(), percents.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    });

    // Put the 3 lowest values in a vector of strings
    std::vector<std::string> lowest_three_nutrients;
    std::cout << "Most missing nutrients: ";
    for (auto & percent : percents) {
        if (percent.first != "Refuse_Pct" && percent.first != "GmWt_2" && percent.first != "GmWt_1") {
            lowest_three_nutrients.push_back(percent.first);
        }
        if (lowest_three_nutrients.size() >= 3) {
            break;
        }
    }
    for (const auto & lowest_three_nutrient : lowest_three_nutrients)
    {
        std::cout << lowest_three_nutrient << " ";
    }
    std::cout << std::endl;
    // now find the 3 highest ingredients with these nutrients
    // now find the 3 highest ingredients with these nutrients
    vector<FoodData*> missing_from_diet;
    set<std::string> added_ingredients;
    for (const std::string& i : lowest_three_nutrients) {
        FoodData* max_nutrient_food = FindMaxNutrient(i);

        // Check if the ingredient is already added
        if (added_ingredients.find(max_nutrient_food->Shrt_Desc) == added_ingredients.end()) {
            missing_from_diet.push_back(max_nutrient_food);
            added_ingredients.insert(max_nutrient_food->Shrt_Desc);
        }
    }

    // Print missing ingredients
    for(FoodData *f: missing_from_diet) {
        Print(*f);
    }
}
*/