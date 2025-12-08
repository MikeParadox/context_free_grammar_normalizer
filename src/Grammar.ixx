module;

#include <initializer_list>
#include <map>
#include <print>
#include <string>
#include <vector>

export module Grammar_utils;

namespace Grammar_utils
{
using std::print;
using std::string;
using std::vector;

/**
 * Class to represent context free grammar. Capital letters represent
 * non-terminal symbols, while small letters and digits represents terminal
 * symbols
 */
class Grammar
{
   using grammar_t = std::map<char, vector<string>>;

 public:
   /**
    *
    * @param grammar List of production rules
    */
   Grammar(
     const std::initializer_list<std::pair<char, vector<string>>>& grammar)
   {
      for (const auto& production : grammar)
         _grammar[production.first] = production.second;
   }

   [[nodiscard]] grammar_t get_grammar() const;

   [[nodiscard]] grammar_t get_normilized_grammar() const;



 private:
   grammar_t _grammar;
   mutable grammar_t _normalized_grammar;
   mutable bool _is_grammar_normilized{false};

   void remove_non_productive() const;
   void remove_unaccessible() const;
   void remove_epsilon() const;
   void remove_chained() const;

   /**
    * @brief Normalizes class grammar.
    * @return Normalized grammar.
    */
   void normalize() const;
};

Grammar::grammar_t Grammar::get_grammar() const
{
   return _grammar;
}

void Grammar::normalize() const
{
   _normalized_grammar = _grammar;
   remove_non_productive();
   remove_unaccessible();
   remove_epsilon();
   remove_chained();
   remove_non_productive();
   remove_unaccessible();
   _is_grammar_normilized = true;
}

Grammar::grammar_t Grammar::get_normilized_grammar() const
{
   if (!_is_grammar_normilized) normalize();

   return _normalized_grammar;
}







} // namespace Grammar_utils




