module;

#include <algorithm>
#include <initializer_list>
#include <print>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

export module Grammar_utils;

export namespace Grammar_utils
{
using std::print;
using std::println;
using std::queue;
using std::set;
using std::string;
using std::vector;


using grammar_t = std::unordered_map<char, vector<string>>;

class Grammar
{
 public:
   /**
    * @brief Class to represent CFG ('@' represents epsilon)
    * @param grammar List of production rules
    */
   Grammar(grammar_t grammar) : _grammar{std::move(grammar)} {}

   [[nodiscard]] auto get_grammar() const -> grammar_t;
   [[nodiscard]] auto get_normalized_grammar() -> grammar_t;

 private:
   grammar_t _grammar;
   grammar_t _normalized_grammar;
   bool _is_grammar_normilized{false};

   static constexpr char eps{'@'};

   void remove_non_productive();
   void remove_inaccessible();
   void remove_epsilon();
   void remove_chained();

   /***
    * @brief Normalizes class grammar.
    * @return Normalized grammar.
    */
   void normalize();
   [[nodiscard]] bool is_all_terminals(const string& str) const;
   [[nodiscard]] bool is_terminal(char ch);
};

auto Grammar::get_grammar() const -> grammar_t
{
   return _grammar;
}

void Grammar::normalize()
{
   _normalized_grammar = _grammar;
   // remove_non_productive();
   // todo implement and uncomment
   remove_inaccessible();
   // remove_epsilon();
   // remove_chained();
   // remove_non_productive();
   // remove_inaccessible();
   _is_grammar_normilized = true;
}

bool Grammar::is_all_terminals(const string& str) const
{
   return std::ranges::all_of(
     str, [](const char ch) -> bool
     { return islower(ch) || isdigit(ch) || ch == eps; });
}

bool Grammar::is_terminal(const char ch)
{
   return islower(ch) || isdigit(ch) || ch == '@';
}

auto Grammar::get_normalized_grammar() -> grammar_t
{
   if (!_is_grammar_normilized)
      normalize();

   return _normalized_grammar;
}

// warts and all
// TODO rewrite to lower cognitive complexity to <25
void Grammar::remove_non_productive()
{
   set<char> f{};
   queue<char> q{};

   auto is_all_in_f{[&f](const string& s) -> bool
                    {
                       return std::ranges::all_of(s.begin(), s.end(),
                                                  [&f](char ch) -> bool
                                                  { return f.contains(ch); });
                    }};

   for (auto prod{_normalized_grammar.begin()};
        prod != _normalized_grammar.end(); ++prod)
   {
      for (const auto& x : prod->second)
      {
         if (is_all_terminals(x))
         {
            f.insert(prod->first);
            q.push(prod->first);
            break;
         }
      }
   }

   while (!q.empty())
   {
      auto p = q.front();
      q.pop();

      for (auto prod{_normalized_grammar.begin()};
           prod != _normalized_grammar.end(); ++prod)
      {
         if (auto [nonterm, symbols] = *prod; !f.contains(nonterm))
         {
            for (auto s : symbols)
            {
               if (is_all_in_f(s))
               {
                  f.insert(nonterm);
                  q.push(nonterm);
               }
            }
         }
      }
   }

   grammar_t result;
   for (auto prod{_normalized_grammar.begin()};
        prod != _normalized_grammar.end(); ++prod)
   {
      auto [nonterm, symbols]{*prod};
      if (f.contains(nonterm))
      {
         for (const auto& x : symbols)
         {
            bool is_in_f{true};
            for (const char ch : x)
            {
               if (!is_terminal(ch) && !f.contains(ch))
               {
                  is_in_f = false;
                  break;
               }
            }
            if (is_in_f)
               result[prod->first].push_back(x);
         }
      }
   }

   _normalized_grammar = std::move(result);
}

void Grammar::remove_inaccessible()
{
   set<char> reachable{'S'};
   queue<char> q{};
   q.push('S');

   while (!q.empty())
   {
      auto a{q.front()};
      q.pop();
      for (auto x : _normalized_grammar[a])
      {
         for (char ch : x)
         {
            if (!is_terminal(ch) && !reachable.contains(ch))
            {
               reachable.insert(ch);
               q.push(ch);
            }
         }
      }
   }

   grammar_t result{};

   auto is_all_nonterms_reachable{
     [&reachable, this](const string& s) -> bool
     {
        return std::ranges::all_of(
          s.begin(), s.end(), [&reachable, this](char ch) -> bool
          { return is_terminal(ch) || reachable.contains(ch); });
     }};


   for (auto nonterm : reachable)
   {
      for (auto s : _normalized_grammar[nonterm])
      {
         if (is_all_nonterms_reachable(s))
            result[nonterm].push_back(s);
      }
   }

   _normalized_grammar = std::move(result);
}

void print_grammar(const grammar_t& grammar)
{
   for (const auto& [fst, snd] : grammar)
   {
      print("{} -> ", fst);
      for (const auto& x : snd)
         print("{}|", x);

      println();
   }
}




} // namespace Grammar_utils




