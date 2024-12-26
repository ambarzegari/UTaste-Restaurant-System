#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// کلاس محله
class District {
public:
    string name;                // نام محله
    vector<string> neighbors;   // لیست همسایه‌ها

    District(string n) : name(n) {}
};

// BFS روی محله‌ها
void bfs(const unordered_map<string, District*>& districts, const string& startDistrict) {
    // چک کردن اگر محله شروع وجود ندارد
    if (districts.find(startDistrict) == districts.end()) {
        cout << "Start district not found!" << endl;
        return;
    }

    // صف برای گره‌ها و مجموعه برای علامت‌گذاری بازدید شده‌ها
    queue<string> q;
    unordered_set<string> visited;

    // افزودن محله شروع به صف و بازدید شده‌ها
    q.push(startDistrict);
    visited.insert(startDistrict);

    cout << "BFS Traversal: ";

    while (!q.empty()) {
        string current = q.front();
        q.pop();
        cout << current << " ";

        // پردازش همسایه‌های محله فعلی
        for (const string& neighbor : districts.at(current)->neighbors) {
            if (visited.find(neighbor) == visited.end()) { // اگر بازدید نشده
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    // تعریف محله‌ها و لیست مجاورتی
    unordered_map<string, District*> districts;

    // افزودن محله‌ها
    districts["Azadi"] = new District("Azadi");
    districts["Enghelab"] = new District("Enghelab");
    districts["Shahrak"] = new District("Shahrak");
    districts["SaadatAbad"] = new District("SaadatAbad");
    districts["Tajrish"] = new District("Tajrish");

    // تعریف همسایه‌ها
    districts["Azadi"]->neighbors = {"Enghelab", "Shahrak"};
    districts["Enghelab"]->neighbors = {"Azadi", "Tajrish"};
    districts["Shahrak"]->neighbors = {"Azadi", "SaadatAbad"};
    districts["SaadatAbad"]->neighbors = {"Shahrak", "Tajrish"};
    districts["Tajrish"]->neighbors = {"Enghelab", "SaadatAbad"};

    // اجرای BFS
    bfs(districts, "Azadi");

    // آزادسازی حافظه
    for (auto& pair : districts) {
        delete pair.second;
    }

    return 0;
}





void District::SortResturantsVector()
{
    sort(resturants.begin(), resturants.end(),
         [](Resturant *left, Resturant *right)
         { return left->GetName() < right->GetName(); });
}