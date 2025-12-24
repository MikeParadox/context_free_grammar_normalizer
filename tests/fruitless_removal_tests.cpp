#include <gtest/gtest.h>

import Grammar_utils;
using Grammar_utils::grammar_t;

TEST(fruitless_removal, no_fruitless)
{
   Grammar_utils::Grammar grammar{grammar_t{{'S', {"AB", "CA"}},
                                            {'A', {"a"}},
                                            {'B', {"BC", "AB", "C"}},
                                            {'C', {"aB", "@"}}}};
   auto without_fruitless{grammar.get_normalized_grammar()};

   ASSERT_EQ(grammar.get_grammar(), without_fruitless);
}

TEST(fruitless_removal, with_fruitless)
{
   Grammar_utils::Grammar grammar{grammar_t{{'S', {"aT", "pU", "a", "A"}},
                                            {'T', {"xT", "ax"}},
                                            {'U', {"pU", "TT", "AU"}},
                                            {'A', {"Bx", "AA"}},
                                            {'B', {"BB", "xA"}}}};
   Grammar_utils::Grammar grammar2{grammar_t{{'S', {"AB", "CA"}},
                                             {'A', {"a"}},
                                             {'B', {"BC", "AB"}},
                                             {'C', {"aB", "@"}}}};

   auto without_fruitless{grammar_t{
     {'S', {"aT", "pU", "a"}}, {'T', {"xT", "ax"}}, {'U', {"pU", "TT"}}}};
   auto without_fruitless2{
     grammar_t{{'S', {"CA"}}, {'A', {"a"}}, {'C', {"@"}}}};

   ASSERT_EQ(grammar.get_normalized_grammar(), without_fruitless);
   ASSERT_EQ(grammar2.get_normalized_grammar(), without_fruitless2);
}


