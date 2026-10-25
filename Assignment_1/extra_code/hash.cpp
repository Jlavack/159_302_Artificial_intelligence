#include "puzzle.h"
#include <iostream>
#include <cmath>
#include <assert.h>
#include <string>
#include <queue>
#include <vector>
#include <algorithm> 
#include <unordered_set>
#include <unordered_map>

using namespace std;


// namespace std {template <> struct hash<const Puzzle> {
//     size_t operator()(Puzzle& p) const{
//         //compute hash value of two puzzles 
//         return((hash<string>()(p.getPath())
//                 ^(hash<int>()(p.getPathLength()) << 1)
//                 ^(hash<int>()(p.getHCost()) << 1)
//                 ^(hash<int>()(p.getFCost()) << 1)
//                 ^(hash<string>()(p.getString()) << 1)
//                 ^(hash<int>()(p.getDepth()) << 1)
//                 )
//             );
//         }
//     };
// }

// namespace std {
//     template<>
//     struct hash<Puzzle>{
//         size_t operator()(const Puzzle& key)
//         {
//             return  hash<std::string>()(key.strBoard);
//         }
//     };
// }






int main() {

   // std::unordered_map<std::string, Puzzle> puzzlestates;

    Puzzle *state1 = new Puzzle("120345678", "123456780");
    Puzzle *state2 = new Puzzle("123456078", "123456780");
    Puzzle *state3 = new Puzzle("120345678", "123456780");

    //cout << state1->strBoard;

    // puzzlestates[state1->strBoard] = *state1;

  
    // for(auto& [puzzlestates->strBoard] : puzzlestates) {
    //     cout << strBoard << endl;
    // }

}


// struct PuzzleHasher {
//     size_t operator()(Puzzle & p) const {
//         return hash<string>()(p.getString());
//     }
// };

// struct PuzzleHashComparator {
//     bool operator()(Puzzle &p1, Puzzle &p2) const {
//         if(p1.getString() == p2.getString()) {
//             return true; }
//         return false;
//         }
//     };


// namespace std {
//     template<>
//     struct hash<Puzzle>{
//         size_t operator()(const Puzzle& key)
//         {
//             return  hash<int>()(key.puzzleKey);
//         }
//     };
// }

// struct puzzleHasher {
// 	size_t operator()(const Puzzle& key) const {
// 		return hash<int>()(key.puzzleKey);
// 	}
// };

// struct puzzleComparator {
// 	bool operator()(const Puzzle & state1, const Puzzle & state2) const{
// 		if(state1.puzzleKey == state2.puzzleKey) {
// 			return true; 
// 		} else {return false; }
// 	}
// };

// class HashFn{
// 	public:
// 	size_t operator()(const Puzzle& p) const{
// 		return p.puzzleKey;
// 	}
// };