#include <bits/stdc++.h>
using namespace std;


const vector<string> ALL_TAGS = {
    "action", "open-world", "rpg", "fps", "story-rich", "co-op", "sandbox", "adventure"
};


const vector<string> DISPLAY_TAGS = {
    "Action", "Open-World", "RPG", "FPS", "Story-Rich", "Co-Op", "Sandbox", "Adventure"
};

struct Game {
    string title;
    vector<int> tagVector; 
};

struct Recommendation {
    string title;
    double score;
};

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


int getTagIndex(string tag) {
    tag = toLowerCase(tag);
    for (size_t i = 0; i < ALL_TAGS.size(); ++i) {
        if (ALL_TAGS[i] == tag) return i;
    }
    return -1;
}

double calculateCosineSimilarity(const vector<int>& vecA, const vector<int>& vecB) {
    double dotProduct = 0.0, normA = 0.0, normB = 0.0;
    for (size_t i = 0; i < vecA.size(); ++i) {
        dotProduct += vecA[i] * vecB[i];
        normA += vecA[i] * vecA[i];
        normB += vecB[i] * vecB[i];
    }
    if (normA == 0.0 || normB == 0.0) return 0.0;
    return dotProduct / (sqrt(normA) * sqrt(normB));
}

int main() {

    vector<Game> database = {
        {"Grand Theft Auto V",                      {1, 1, 0, 0, 1, 0, 0, 1}}, // Action, Open-World, Story-Rich, Adventure
        {"The Witcher 3: Wild Hunt",                {1, 1, 1, 0, 1, 0, 0, 1}}, // Action, Open-World, RPG, Story-Rich, Adventure
        {"Call of Duty: Modern Warfare",            {1, 0, 0, 1, 1, 1, 0, 0}}, // Action, FPS, Story-Rich, Co-Op
        {"Minecraft",                               {0, 1, 0, 0, 0, 1, 1, 1}}, // Open-World, Co-Op, Sandbox, Adventure
        {"It Takes Two",                            {1, 0, 0, 0, 1, 1, 0, 1}}, // Action, Story-Rich, Co-Op, Adventure
        {"Hogwarts Legacy",                         {1, 1, 1, 0, 1, 0, 0, 1}}  // Action, Open-World, RPG, Story-Rich, Adventure
    };

    cout << "--- Available Game Tags ---\n";
    for (const auto& tag : DISPLAY_TAGS) cout << "- " << tag << "\n";
    cout << "---------------------------\n";

    vector<int> userVector(ALL_TAGS.size(), 0);
    string inputTag;
    
    cout << "Enter tags you prefer (type 'done' when finished):\n";
    while (true) {
        cout << "> ";
        cin >> inputTag;
        if (toLowerCase(inputTag) == "done") break;

        int index = getTagIndex(inputTag);
        if (index != -1) {
            userVector[index] = 1;
            cout << "Tag tracked successfully!\n";
        } else {
            cout << "Tag criteria unrecognized. Please try again.\n";
        }
    }


    vector<Recommendation> recommendations;
    for (const auto& game : database) {
        double score = calculateCosineSimilarity(userVector, game.tagVector);
        if (score > 0.0) {
            recommendations.push_back({game.title, score});
        }
    }


    sort(recommendations.begin(), recommendations.end(), [](const Recommendation& a, const Recommendation& b) {
        return a.score > b.score; 
    });

    cout << "\n========================================\n";
    cout << "   PERSONALIZED PC GAME RECOMMENDATIONS\n";
    cout << "========================================\n";
    if (recommendations.empty()) {
        cout << "No matching entries match your specific tag combination.\n";
    } else {
        cout << left << setw(32) << "Game Title" << "Match Score\n";
        cout << "----------------------------------------\n";
        for (const auto& rec : recommendations) {
            cout << left << setw(32) << rec.title << fixed << setprecision(2) << (rec.score * 100) << "%\n";
        }
    }
    return 0;
}