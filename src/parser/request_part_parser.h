#pragma once
#include "core/str.h"

template<typename T>
class RequestPartParser
{
public:
   template<typename STR>
   RequestPartParser(STR&& s_)
      : s{ std::move(s_) }
   {
      static_assert(std::is_same_v<std::decay_t<STR>, String>, "RequestPartParser::ctor: STR must be of String type");
   }

   virtual T* Parse() = 0;

protected:
   inline char current() const
   {
      return s[ptr];
   }

   inline bool has() const
   {
      return ptr < s.length();
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
      static String s = " \r\n\t";
      return !s.contains(toTest);
   }

   inline bool current_is_permitted() const
   {
      return is_permitted(current());
   }

   inline void reset(const String& newS/* = {}*/)
   {
      ptr = 0;
      if (!newS.is_empty())
         s = newS;
   }

   inline const String& get_raw() const
   {
       return s;
   }

private:
   size_t ptr{ 0 };
   String s;
};
