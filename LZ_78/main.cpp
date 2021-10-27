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
                new_s.pop_back();
                Tag t(mp[new_s], ss[ss.size() - 1]);
                Tags.push_back(t);

                i = j;
                break;
            } else {
                if (j == s.size() - 1) {

                    string new_s = ss;
                    mp[ss] = m++;
                    new_s.pop_back();
                    Tag t(mp[new_s], ss[ss.size() - 1]);
                    Tags.push_back(t);
                    i = j;

                }
                continue;
            }


        }
    }

};

void ExtractLZ78(fstream &out) {
    int m = 1;
    map<int, string> mp;
    mp[0] = "";
    for (int i = 0; i < Tags.size(); ++i) {

        Tag tag = Tags[i];

        if (i != Tags.size() - 1)
            mp[m++] = mp[tag.index] + tag.Next;
        out << mp[tag.index] + tag.Next;
    }

}

int main() {
    char s[1000000];
    string ss = "";
    fstream infile, out;
    infile.open("Test.txt", ios::in);
    out.open("output.txt", ios::out);

    if (infile) {
        infile.getline(s, 1000000);

        while (infile) {
            ss += s;
            infile.getline(s, 1000000);
            ss += '\n';
        }
        ss.pop_back();

    } else {
        cout << "unable to open file\n";
    }

    LZ78(ss);

    ExtractLZ78(out);
    int largeindex = 0;
    for (int i = 0; i < Tags.size(); ++i) {
        largeindex = max(largeindex, Tags[i].index);
    }
    cout << "===========================================================\n";
    cout << setfill(' ') << setw(40) << "Welcome in LZ78\n";
    cout << "===========================================================\n";
    cout << "Original size = " << ss.size() * 8 << " Bits\n";

    cout << "Compressed size = " << (ceil(log2(largeindex)) + 8) * Tags.size() << " Bits\n";

    cout << "===========================================================\n";

    Tags.clear();
    out.close();
    infile.close();
}
