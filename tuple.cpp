#include <iostream>

#include <gecode/int.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Tuple : public Space {
protected:
  IntVar x;
  IntVar y;
  BoolVar b;

public:
  Tuple(void) {
    x = IntVar(*this, 0, 10);
    y = IntVar(*this, 0, 10);
    b = BoolVar(*this, 0, 1);

    rel(*this, x, IRT_EQ, y);
    rel(*this, x, IRT_EQ, 5, b);

    branch(*this, x, INT_VAL_MIN());
    branch(*this, y, INT_VAL_MIN());
  }

  Tuple(bool share, Tuple& t) : Space(share, t) {
    x.update(*this, share, t.x);
    y.update(*this, share, t.y);
    b.update(*this, share, t.b);
  }

  virtual Space* copy(bool share) {
    return new Tuple(share, *this);
  }

  void print(void) const {
    std::cout << "(" << x << "," << y << "," << b << ")" << std::endl;
  }
};

int main(int argc, char* argv[]) {
  Tuple* t = new Tuple;
  DFS<Tuple> engine(t);
  delete t;

  while (Tuple* solution = engine.next()) {
    solution->print();
    delete(solution);
  }

  return 0;
}
