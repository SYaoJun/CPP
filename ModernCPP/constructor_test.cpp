#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class BB {
   public:
    BB() { cout << "BB constructor no argument" << endl; }
    BB(int age_) : age(age_) { cout << "BB constructor with argument" << endl; }
    BB(const BB &p) {
        age = p.age;
        cout << "Copy Constructor BB" << endl;
    }
    BB &operator=(const BB &p) {
        cout << "Copy Assign BB" << endl;
        age = p.age;
        return *this;
    }
    int age;
};
struct CC {
    CC() { cout << "no argument CC" << endl; }
    CC(int x) {
        cout << "CC constructor " << x << endl;
        cc_ = x;
    }
    int cc_;
};
class AA {
   public:
    // AA(BB b_) : cc(1) {
    //     cout << "enter AA constructor" << endl;
    //     bb = b_;
    // }
    AA(BB b_) : bb(b_), cc(1) {
        cout << "enter AA constructor" << endl;
        // bb = b_;
    }

   private:
    CC cc;
    BB bb;
};

int main() {
    BB b;
    cout << "==================" << endl;
    AA aa(b);
}