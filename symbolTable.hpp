#include "token.hpp"

#include <vector>

#ifndef symbolTableH
#define symbolTableH

/*

NOTES
    * It makes more sense to process everything with local scope rules, since global 

*/

namespace symbolTable {
    static std::vector<std::string> stack;
    bool verify(std::string);

    class Scope {
        public:
            Scope() {
                varCount = 0;
            }
            void push(std::string);
            void pop();
            int find(std::string);
            int getVarCount() {
                return varCount;
            }
        
        private:
            int varCount;
    };

}  // namespace symbolTable

#endif  // symbolTableH