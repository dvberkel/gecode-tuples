#include <iostream>

#include <gecode/int.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Tuple : public Space {
protected:
  IntVar x;
  IntVar y;

public:
  Tuple(std::vector<int> values){
    {
      auto minimum = std::min_element(std::begin(values), std::end(values));
      auto maximum = std::max_element(std::begin(values), std::end(values));
      x = IntVar(*this, 0, values.size() - 1);
      y = IntVar(*this, *minimum, *maximum);
    }

    {
      std::vector<int>::iterator v = values.begin();
      for (IntVarValues i(x); i(); ++i, ++v) {
	BoolVar b = BoolVar(*this, 0, 1);
	rel(*this, x, IRT_EQ, i.val(), b);
	rel(*this, y, IRT_EQ, *v, b);
      }
    }

    branch(*this, x, INT_VAL_MIN());
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
  Tuple* t = new Tuple({ 3, 1, 4, 2, 6, 5 });
  DFS<Tuple> engine(t);
  delete t;

  while (Tuple* solution = engine.next()) {
    solution->print();
    delete(solution);
  }

  return 0;
}
