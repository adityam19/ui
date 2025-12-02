#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

int main() {
    int frames;
    cout << "Enter number of frames: ";
    cin >> frames;

    int n;
    cout << "Enter length of reference string: ";
    cin >> n;

    vector<int> refs(n);
    cout << "Enter reference string (space separated):\n";
    for (int i = 0; i < n; ++i) cin >> refs[i];
    
//Enter number of frames: 4
//Enter length of reference string: 20
//Enter reference string (space separated):
//7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 
//Total page faults: 8

    list<int> lruList; // front = most recently used, back = least recently used
    unordered_map<int, list<int>::iterator> pos; // maps page -> iterator in lruList
    int pageFaults = 0;

    for (int x : refs) {
        auto it = pos.find(x);
        if (it == pos.end()) {
            // page fault
            ++pageFaults;
            if ((int)lruList.size() == frames) {
                // remove least recently used (back)
                int lruPage = lruList.back();
                lruList.pop_back();
                pos.erase(lruPage);
            }
            // insert this page as most recently used (front)
            lruList.push_front(x);
            pos[x] = lruList.begin();
        } else {
            // hit: move the page to front (most recently used)
            lruList.erase(it->second);
            lruList.push_front(x);
            pos[x] = lruList.begin();
        }
    }

    cout << "Total page faults: " << pageFaults << "\n";
    return 0;
}