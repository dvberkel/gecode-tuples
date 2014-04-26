#include <iostream>

#include <gecode/int.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Tuple : public Space {
protected:
  IntVar x;
  IntVar y;

public:
  Tuple(void) {
    x = IntVar(*this, 0, 100);
    y = IntVar(*this, 0, 100);

    rel(*this, x, IRT_EQ, y);

    branch(*this, x, INT_VAL_MIN());
    branch(*this, y, INT_VAL_MIN());
  }

  Tuple(bool share, Tuple& t) : Space(share, t) {
    x.update(*this, share, t.x);
    y.update(*this, share, t.y);
  }

  virtual Space* copy(bool share) {
    return new Tuple(share, *this);
  }

  void print(void) const {
    std::cout << "(" << x << "," << y << ")" << std::endl;
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
