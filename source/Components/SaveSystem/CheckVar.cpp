#include "CheckVar.h"


using namespace std;
using namespace nlohmann;


bool CheckVar::Has(json js, string nameVar) {
    if (js.find(nameVar) != js.end()) {
        return true;
    }
    else {
        std::cout << "isTrigger variable not found in JSON." << std::endl;
        return false;
    }

    return false;
}