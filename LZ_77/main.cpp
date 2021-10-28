#include <bits/stdc++.h>

using namespace std;


struct Tag {
    int pos;
    int length;
    char Next;

    Tag() : pos(0), length(0) {}

    Tag(int pos, int length, char Next) {
        this->pos = pos;
        this->length = length;
        this->Next = Next;
    }
};

int find(string s, int lim, string search) {
    int idx = -1;
    int si = s.size() - search.size();
    for (int i = min(si - 1, int(lim - search.size())); i >= 0; --i) {

        for (int j = i; j < i + search.size() && j < lim; ++j) {
            if (s[j] != search[j - i]) {

                break;
            } else if (j == (i + search.size() - 1)) {
                idx = i;
                break;
            }
        }
        if (idx != -1)
            return idx;
    }
    return idx;
}

vector<Tag> Tags;

void LZ77(const string &s) {
    int si = s.size();

    for (int i = 0, j; i < si; ++i) {
        string search = "";
        int fin = 0;
        for (j = i; j < si; ++j) {
            search += s[j];
            fin = find(s, i, search);
            if (fin == -1 || fin >= i || i < fin + search.size())
                break;

        }

        Tag t;
        if (search.size() == 1) {

            t = {0, 0, search[0]};

        } else {
            string copy = search;
            copy.pop_back();
            fin = find(s, i, copy);
            t = {i - fin, int(search.size() - 1), search[search.size() - 1]};
        }

        i = j;
        Tags.push_back(t);
    }

}

string Extract() {
    string s;

    for (int i = 0; i < Tags.size(); ++i) {
        Tag tag = Tags[i];
        for (int j = s.size() - tag.pos, cnt = tag.length; cnt > 0; ++j, cnt--) {
            s += s[j];
        }
        s += tag.Next;

    }
    return s;
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

    LZ77(ss);

    out << Extract();

    int llength = 0, lpos = 0;

    for (int i = 0; i < Tags.size(); ++i) {
        lpos = max(lpos, Tags[i].pos);
        llength = max(llength, Tags[i].length);
    }

    cout << "===========================================================\n";
    cout << setfill(' ') << setw(40) << "Welcome in LZ77\n";
    cout << "===========================================================\n";
    cout << "Original size = " << ss.size() * 8 << " Bits\n";

    cout << "Compressed size = " << (ceil(log2(lpos)) + ceil(log2(llength)) + 8) * Tags.size() << " Bits\n";
    cout << "===========================================================\n";

    Tags.clear();
    out.close();
    infile.close();
}
