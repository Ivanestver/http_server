#pragma once
#include <string>

template<typename T>
class RequestPartParser
{
public:
   template<typename STR>
   RequestPartParser(STR&& s_)
      : s{ std::move(s_) }
   {
      static_assert(std::is_same_v<STR, std::string>, "RequestPartParser::ctor: STR must be of std::string type");
   }

   virtual T* Parse() = 0;

protected:
   inline char current() const
   {
      return s[ptr];
   }

   inline bool has() const
   {
      return ptr < s.size();
   }

   inline void moveNext()
   {
      ptr++;
   }

   inline void skip_forbidden()
   {
      while (has() && !is_permitted(current()))
         moveNext();
   }

   inline bool is_permitted(char toTest) const
   {
      static std::string s = " \r\n\t";
      return std::find(s.begin(), s.end(), toTest) == s.end();
   }

   inline bool current_is_permitted() const
   {
      return is_permitted(current());
   }

   inline void reset(const std::string& newS = {})
   {
      ptr = 0;
      if (!newS.empty())
         s = newS;
   }

private:
   size_t ptr{ 0 };
   std::string s;
};
