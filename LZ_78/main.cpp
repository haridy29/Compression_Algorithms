#include <bits/stdc++.h>

using namespace std;

struct Tag {
    int index;
    char Next;

    Tag(int idx, char Next) {
        index = idx;
        this->Next = Next;
    }
};

vector<Tag> Tags;
map<int,string>cmp;
void LZ78(const string &s) {

    int m = 1;
    map<string, int> mp;
    for (int i = 0; i < s.size(); ++i) {
        string ss = "";

        for (int j = i; j < s.size(); ++j) {
            ss += s[j];

            auto it = mp.find(ss);
            if (it == mp.end()) {//not found

                    string new_s = ss;
                    mp[ss] = m++;
                    cmp[m-1]=ss;
                    new_s.pop_back();
                    Tag t(mp[new_s], ss[ss.size() - 1]);
                    Tags.push_back(t);

                i = j;
                break;
            }
            else {
                if(j==s.size()-1){
                    string new_s = ss;
                    mp[ss] = m++;
                    new_s.pop_back();
                    Tag t(mp[new_s], ss[ss.size() - 1]);
                    Tags.push_back(t);
                }
                continue;
            }


        }
    }

}

void ExtractLZ78(){
    for (int i = 0; i <Tags.size() ; ++i) {
        cout<<cmp[Tags[i].index]<<Tags[i].Next;
    }
}
int main() {
    string s;
    cin >> s;

    LZ78(s);
    ExtractLZ78();

}
