#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

inline namespace SB
{
    extern size_t topCount;
    extern string fileName;
    struct scoreData
    {
        string name;
        int score = 0;
    };

    extern inline void sortScore(vector<scoreData>& datas)
    {
        for (size_t i = 0; i < datas.size(); i++)
        {
            for (size_t j = i + 1; j < datas.size(); j++)
            {
                if (datas.at(j).score > datas.at(i).score)
                {
                    scoreData temp = datas.at(i);
                    datas.at(i) = datas.at(j);
                    datas.at(j) = temp;
                }
            }
        }
    }

    extern inline vector<scoreData> getLeaderBoard()
    {
        fstream scoreFile;
        vector<scoreData> scores;
        scoreData thisScore;
        scoreFile.open(fileName, ios::app | ios::in);
        for (int i = 0; i < topCount; i++)
        {
            string tempname;
            string tempscore;
            sortScore(scores);
            if (!getline(scoreFile, tempname))
                return scores;
            if (!getline(scoreFile, tempscore))
                return scores;
            thisScore.name = tempname;
            try
            {
                thisScore.score = stoi(tempscore);
            }
            catch(const std::exception& e)
            {
                cout << "Error: " << e.what() << endl;
                thisScore.score = -1;
            }
            scores.push_back(thisScore);
        }
        scoreFile.close();
        sortScore(scores);
        return scores;
    }

    extern inline void addLeaderBoard(string name, int score)
    {
        vector<scoreData> datas = getLeaderBoard();
        scoreData newData;
        newData.name = name;
        newData.score = score;
        datas.push_back(newData);
        sortScore(datas);
        if (datas.size() > topCount)
        {
            datas.pop_back();
        }
        fstream scoreFile;
        scoreFile.open(fileName, ios::out | ios::in);
        for (size_t i = 0; i < datas.size(); i++)
        {
            scoreFile << datas.at(i).name << endl << datas.at(i).score << endl;
        }
        scoreFile.close();
    }
}