#include <print>


import Grammar_utils;

int main()
{
   using Grammar_utils::Grammar;
   using Grammar_utils::grammar_t;
   using Grammar_utils::print_grammar;
   using std::println;


   Grammar grammar1{grammar_t{
     {'S', {"aB", "e"}}, {'A', {"bA", "C"}}, {'B', {"b"}}, {'C', {"A"}}}};

   Grammar grammar2{grammar_t{{'S', {"aT", "pU", "a", "A", "@"}},
                              {'T', {"xT", "ax"}},
                              {'U', {"pU", "TT", "AU"}},
                              {'A', {"Bx", "AA"}},
                              {'B', {"BB", "xA"}}}};

   Grammar grammar3{grammar_t{
     {'S', {"AB", "A"}}, {'A', {"a"}}, {'B', {"B", "AB"}}, {'C', {"aB", "@"}}}};

   print_grammar(grammar1.get_normalized_grammar());
   println();
   print_grammar(grammar2.get_normalized_grammar());
   println();
   print_grammar(grammar3.get_normalized_grammar());
   println();

   return 0;
}
