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
       if (ptr >= s.length())
           throw std::out_of_range("Current char is out of bounds");
       return s[ptr];
   }

   inline bool has_next() const noexcept
   {
      return ptr < s.length();
   }

   inline void moveNext() noexcept
   {
      ptr++;
   }

   inline void skip_forbidden() noexcept
   {
      while (has_next() && !current_is_permitted())
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
