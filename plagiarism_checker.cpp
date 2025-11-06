#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// to make the whole text lowercase
string makelower(string s)
{
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

// to remove any punctuations
string removepunc(string s)
{
    string result = "";
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if (isalnum(s[i]) || s[i] == ' ') // Fixed the missing parenthesis
        {
            result += s[i];
        }
    }
    return result;
}

// to split the words and store in an array
vector<string> splitwords(string s)
{
    string a = "";
    vector<string> ans;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ')
        {
            if (!a.empty())
            {
                ans.push_back(a);
                a = "";
            }
        }
        else
        {
            a += s[i];
        }
    }
    if (!a.empty())
    {
        ans.push_back(a);
    }
    return ans;
}

double check(vector<string> word1, vector<string> word2)
{
    double match = 0;
    double tot = word1.size();

    if (tot == 0)
        return 0.0;
    for (int i = 0; i < word1.size(); i++)
    {
        for (int j = 0; j < word2.size(); j++)
        {
            if (word1[i] == word2[j])
            {
                match++;
                break;
            }
        }
    }

    return (match) / tot;
}

string readFile(string filename) // Removed the reference
{
    ifstream file(filename);
    string content = "";
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            content += line + " ";
        }
        file.close();
    }
    else
    {
        cout << "Error: Cannot open file " << filename << endl;
    }

    return content;
}

int main()
{
    string file1, file2;

    cout << "PLAGIARISM CHECKER" << endl;
    cout << "Enter first file name: ";
    cin >> file1;
    cout << "Enter second file name: ";
    cin >> file2;

    string text1 = readFile(file1);
    string text2 = readFile(file2);

    if (text1.empty() || text2.empty())
    {
        cout << "Error reading files. Please check file names." << endl;
        return 1;
    }

    cout << "\nProcessing files..." << endl;
    text1 = makelower(text1);
    text2 = makelower(text2);
    text1 = removepunc(text1);
    text2 = removepunc(text2);

    vector<string> word1 = splitwords(text1);
    vector<string> word2 = splitwords(text2);

    cout << "File 1 has " << word1.size() << " words" << endl;
    cout << "File 2 has " << word2.size() << " words" << endl;
    double similar = check(word1, word2);
    double percent = similar * 100;

    cout << "\nRESULTS" << endl;
    cout << "Similarity: " << percent << "%" << endl;

    if (percent > 80)
    {
        cout << "Possible plagiarism!" << endl;
    }
    else if (percent > 50)
    {
        cout << "Some matching content" << endl;
    }
    else if (percent > 20)
    {
        cout << "Normal common words" << endl;
    }
    else
    {
        cout << "Original content" << endl;
    }

    return 0;
}