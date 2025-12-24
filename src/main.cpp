#include <print>


import Grammar_utils;

int main()
{
   using Grammar_utils::Grammar;
   using Grammar_utils::grammar_t;
   using Grammar_utils::print_grammar;
   using std::println;


   // Grammar grammar{grammar_t{
   //   {'S', {"aB", "e"}}, {'A', {"bA", "C"}}, {'B', {"b"}}, {'C', {"A"}}}};

   Grammar grammar{grammar_t{{'S', {"aT", "pU", "a", "A"}},
                             {'T', {"xT", "ax"}},
                             {'U', {"pU", "TT", "AU"}},
                             {'A', {"Bx", "AA"}},
                             {'B', {"BB", "xA"}}}};

   Grammar grammar2{grammar_t{{'S', {"AB", "CA"}},
                              {'A', {"a"}},
                              {'B', {"BC", "AB"}},
                              {'C', {"aB", "@"}}}};

   print_grammar(grammar.get_normalized_grammar());
   println();
   auto g{grammar2.get_normalized_grammar()};
   print_grammar(g);


   return 0;
}
