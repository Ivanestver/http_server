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

   virtual T* Parse() noexcept = 0;

protected:
   inline char current() const
   {
       return s[ptr];
   }

   inline bool has() const noexcept
   {
      return ptr < s.length();
   }

   inline void moveNext() noexcept
   {
      ptr++;
   }

   inline void skip_forbidden() noexcept
   {
      while (has() && !is_permitted(current()))
         moveNext();
   }

   inline bool is_permitted(char toTest) const noexcept
   {
      static String s = " \r\n\t";
      return !s.contains(toTest);
   }

   inline bool current_is_permitted() const noexcept
   {
      return is_permitted(current());
   }

   inline void reset(const String& newS/* = {}*/) noexcept
   {
      ptr = 0;
      if (!newS.is_empty())
         s = newS;
   }

   inline const String& get_raw() const noexcept
   {
       return s;
   }

private:
   size_t ptr{ 0 };
   String s;
};
