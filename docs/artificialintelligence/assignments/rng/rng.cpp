// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <unordered_set>
const std::string TEST_FOLDER = "\\tests\\";
//State will store our randomly generated state
struct State {
  int a, b;

  bool operator==(const State& other) const {
    return a == other.a && b == other.b;
  }
};
//STD has specialization for State
namespace std {
  template <>
  struct hash<State> {
    std::size_t operator()(const State& p) const {
      return p.a ^ p.b;
    }
  };
}

unsigned int xorShift(unsigned int seed, int r1, int r2);
int main(){
  // code here
  std::unordered_set<State> states;
  State state = {1, 2};
  int warmup, cycle;

  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
  //Keep track of inital seed
  state.a = seed;
  unsigned int i;
  for(i = N; i >= 1; i--)
  {
    //Run xor shift
    seed = xorShift(seed, min, max);
    //Get the new internal state
    state.b = seed;
    //If there is no repetition we are still in the warming phase
    //Once the repetition starts we want to keep track of how long it repeats for
    if (!states.contains(state)) {
      warmup++;
    }
    else if (states.count(state) == 2) {
      cycle++;
    }
    states.insert({state});

  }
  std::cout << "The warmup period is: " << warmup << std::endl;
  std::cout << "The cycle period is: " << cycle << std::endl;
}
//The purpose of this function is to take the number and xor shift it to output a pseudo-random number
    unsigned int xorShift(unsigned int seed, int r1, int r2)
{
  seed = seed xor (seed << 13);
  seed = seed xor (seed >> 17);
  seed = seed xor (seed << 5);
  int value = r1 + (seed % (r2 - r1 + 1)); //clamps the value to between r1 and r2
          //output the new values
          std::cout << value << std::endl;
  return seed;
}
