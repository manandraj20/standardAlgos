#include <bits/stdc++.h>
using namespace std;
struct TrieNode
{
    TrieNode *links[26];
    bool flag = false;
    bool possiblePrefix = true;
    bool containsKey(char ch)
    {
        return links[ch - 'a'] != NULL;
    }
    void put(TrieNode *node, char ch)
    {
        links[ch - 'a'] = node;
    }
    TrieNode *get(char ch)
    {
        return links[ch - 'a'];
    }
    void setEnd()
    {
        flag = true;
    }
    bool isEnd()
    {
        return flag;
    }
    void isNotPrefix()
    {
        possiblePrefix = false;
    }
    bool isPrefix()
    {
        return possiblePrefix;
    }
};
class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }
    void insert(string &word)
    {
        TrieNode *curr = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!curr->containsKey(word[i]))
            {
                curr->put(new TrieNode(), word[i]);
                curr = curr->get(word[i]);
            }
            else
            {
                curr = curr->get(word[i]);
                curr->isNotPrefix();
            }
        }
        curr->setEnd();
    }
    bool search(string &word)
    {
        TrieNode *curr = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!curr->containsKey(word[i]))
            {
                return false;
            }
            curr = curr->get(word[i]);
        }
        return curr->isEnd();
    }
    string findPrefix(string &word)
    {
        TrieNode *curr = root;
        string res = "";
        for (int i = 0; i < word.size(); ++i)
        {
            curr = curr->get(word[i]);
            res.push_back(word[i]);
            if (curr->isPrefix())
            {
                return res;
            }
        }
        return res;
    }
};