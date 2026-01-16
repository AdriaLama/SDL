#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#define RANKING_MANAGER RankingManager::Instance()

struct ScoreEntry {
    std::string playerName;
    int score;

    ScoreEntry(const std::string& name = "", int s = 0)
        : playerName(name), score(s) {
    }
};

class RankingManager {
private:
    static const int MAX_ENTRIES = 10;
    std::vector<ScoreEntry> _rankings;
    std::string _filename = "rankings.dat";

    RankingManager() {
        LoadRankings();
    }

    RankingManager(const RankingManager&) = delete;
    RankingManager& operator=(const RankingManager&) = delete;

public:
    static RankingManager& Instance() {
        static RankingManager instance;
        return instance;
    }

    bool IsTopScore(int score) const {
        if (_rankings.size() < MAX_ENTRIES) 
            return true;

        return score > _rankings.back().score;
    }

    int GetRanking(int score) const {
        for (size_t i = 0; i < _rankings.size(); ++i) {
            if (score > _rankings[i].score) 
                return i + 1;
        }
        if (_rankings.size() < MAX_ENTRIES) 
            return _rankings.size() + 1;

        return -1; 
    }

    void AddScore(const std::string& playerName, int score) {
        ScoreEntry newEntry(playerName, score);

   
        auto it = std::lower_bound(_rankings.begin(), _rankings.end(), newEntry,[](const ScoreEntry& a, const ScoreEntry& b) {
                return a.score > b.score; 
            });

        _rankings.insert(it, newEntry);

  
        if (_rankings.size() > MAX_ENTRIES) {
            _rankings.resize(MAX_ENTRIES);
        }

        SaveRankings();
    }

    const std::vector<ScoreEntry>& GetRankings() const {
        return _rankings;
    }

    void SaveRankings() {
        std::ofstream file(_filename, std::ios::binary);
        if (!file.is_open()) return;

        size_t size = _rankings.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));

        for (const auto& entry : _rankings) {
            size_t nameLength = entry.playerName.length();
            file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
            file.write(entry.playerName.c_str(), nameLength);
            file.write(reinterpret_cast<const char*>(&entry.score), sizeof(entry.score));
        }

        file.close();
    }

    void LoadRankings() {
        std::ifstream file(_filename, std::ios::binary);
        if (!file.is_open()) return;

        _rankings.clear();

        size_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));

        for (size_t i = 0; i < size; ++i) {
            size_t nameLength;
            file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

            std::string name(nameLength, '\0');
            file.read(&name[0], nameLength);

            int score;
            file.read(reinterpret_cast<char*>(&score), sizeof(score));

            _rankings.emplace_back(name, score);
        }

        file.close();
    }

    void ClearRankings() {
        _rankings.clear();
        SaveRankings();
    }
};