#include <gtest/gtest.h>

import Grammar_utils;
using Grammar_utils::grammar_t;

TEST(inaccessible_removal, no_inaccessible)
{
   Grammar_utils::Grammar grammar{grammar_t{{'S', {"AB", "CA"}},
                                            {'A', {"a"}},
                                            {'B', {"BC", "AB", "C"}},
                                            {'C', {"aB", "@"}}}};
   auto without_inaccessible{grammar.get_normalized_grammar()};

   ASSERT_EQ(grammar.get_grammar(), without_inaccessible);
}

TEST(inaccessible_removal, with_inaccessible)
{
   Grammar_utils::Grammar grammar{grammar_t{{'S', {"aT", "pU", "a", "A"}},
                                            {'T', {"xT", "ax"}},
                                            {'U', {"pU", "TT", "AU"}},
                                            {'A', {"x", "AA"}},
                                            {'B', {"BB", "xA"}}}};
   Grammar_utils::Grammar grammar2{grammar_t{
     {'S', {"A", "a"}}, {'A', {"a"}}, {'B', {"BC", "AB"}}, {'C', {"aB", "@"}}}};

   auto without_inaccessible{grammar_t{{'S', {"aT", "pU", "a", "A"}},
                                       {'T', {"xT", "ax"}},
                                       {'U', {"pU", "TT", "AU"}},
                                       {'A', {"x", "AA"}}}};
   auto without_inaccessible2{grammar_t{{'S', {"A", "a"}}, {'A', {"a"}}}};

   ASSERT_EQ(grammar.get_normalized_grammar(), without_inaccessible);
   ASSERT_EQ(grammar2.get_normalized_grammar(), without_inaccessible2);
}


