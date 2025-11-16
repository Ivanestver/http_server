#pragma once

#ifndef IS_CXX17
#define IS_CXX17 ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#endif

#if (IS_CXX17) && (!defined(SERVER_USE_OWN_IMPL_OPTIONAL))
#include <optional>
#else

#include <cstdint>
#include <exception>
#include <type_traits>

namespace std
{
	class bad_optional_access : public exception
	{
	public:
		bad_optional_access()
			: exception{ "Bad optional access" }
		{}
	};

#ifndef IS_CXX17
	struct in_place_t { explicit in_place_t() = default; };
	constexpr in_place_t in_place{};

	template<class T>
	struct is_swappable
	{
		static constexpr bool value = true;
	};
#endif

	struct nullopt_t { constexpr explicit nullopt_t() = default; };
	constexpr nullptr_t nullopt{};

	template<class T>
	class optional;

	template<class T>
	struct hash<optional<T>>
	{
		std::size_t operator()(const optional<T>& o) const
		{
			return o ? std::hash<std::remove_const<T>::type>{}(*o) : std::size_t{ 0 };
		}
	};

	template<typename T>
	class optional
	{
	public:
		constexpr optional() {}

		constexpr optional(std::nullptr_t) noexcept {}

		constexpr optional(const optional& other)
		{
			if (has_value())
			{
				construct(*other.object);
			}
		}

		constexpr optional(optional&& other) noexcept(std::is_nothrow_move_constructible<T>::value)
		{
			if (has_value())
			{
				construct(std::move(*other.object));
				other.destroy();
			}
		}

		template<class U,
			typename std::enable_if<
			std::conjunction<
			std::is_constructible<T, const U&>,
			std::negation<
			std::disjunction<
			std::is_constructible<T, optional<U>&>, std::is_constructible<T, const optional<U>&>,
			std::is_constructible<T, optional<U>&&>, std::is_constructible<T, const optional<U>&&>,
			std::is_convertible<optional<U>&, T>, std::is_convertible<const optional<U>&, T>,
			std::is_convertible<optional<U>&&, T>, std::is_convertible<const optional<U>&&, T>
			>
			>
			>::value,
			bool
			>::type = true
		>
		constexpr optional(const optional<U>& other)
		{
		}

		template<class U,
			typename std::enable_if<
			std::conjunction<
			std::is_constructible<T, const U&>,
			std::negation<
			std::disjunction<
			std::is_constructible<T, optional<U>&>, std::is_constructible<T, const optional<U>&>,
			std::is_constructible<T, optional<U>&&>, std::is_constructible<T, const optional<U>&&>,
			std::is_convertible<optional<U>&, T>, std::is_convertible<const optional<U>&, T>,
			std::is_convertible<optional<U>&&, T>, std::is_convertible<const optional<U>&&, T>
			>
			>
			>::value,
			bool
			>::type = true
		>
		constexpr optional(optional<U>&& other)
		{
		}

		template<class... Args,
			typename std::enable_if<
			std::is_constructible<T, Args...>::value, bool
			>::type = true
		>
		constexpr optional(in_place_t, Args&&... args)
		{
			construct(std::forward<Args>(args)...);
		}

		template<class U, class... Args,
			typename std::enable_if<
			std::is_constructible<T, std::initializer_list<U>, Args...>::value, bool
			>::type = true
		>
		constexpr optional(in_place_t, std::initializer_list<U> ilist, Args&&... args)
		{
			construct(ilist, std::forward<Args>(args)...);
		}

		template<class U = std::remove_cv<T>::type,
			typename std::enable_if<
			std::conjunction<
			std::is_constructible<T, U>,
			std::negation<std::is_same<typename std::decay<U>::type, in_place_t>>,
			std::negation<std::is_same<typename std::decay<U>::type, optional<T>>>
			>::value, bool
		>::type = true>
		constexpr optional(U&& value)
			: optional(in_place, std::forward<U>(value))
		{
		}

		~optional()
		{
			destroy_safe();
		}

		optional& operator=(nullopt_t) noexcept
		{
			destroy_safe();
			return *this;
		}

		constexpr optional& operator=(const optional& other)
		{
			if (this == &other)
				return *this;

			if (other.has_value())
			{
				if (has_value())
					**this = *other;
				else
					construct(*other.object);
			}
			else
				destroy_safe();

			return *this;
		}

		constexpr optional& operator=(optional&& other) noexcept(std::is_nothrow_move_assignable_v<T>&& std::is_nothrow_move_constructible_v<T>)
		{
			if (this == &other)
				return *this;

			if (other.has_value())
			{
				if (has_value())
					**this = std::move(*other);
				else
					construct(std::move(*other.object));
				other.destroy();
			}
			else
			{
				destroy_safe();
			}

			return *this;
		}

		template<typename U,
			typename std::enable_if <
			std::conjunction<
			std::negation<
			std::disjunction<
			std::is_constructible<T, optional<U>&>,
			std::is_constructible<T, const optional<U>&>,
			std::is_constructible<T, optional<U>&&>,
			std::is_constructible<T, const optional<U>&&>,
			std::is_convertible<optional<U>&, T>,
			std::is_convertible<const optional<U>&, T>,
			std::is_convertible<optional<U>&&, T>,
			std::is_convertible<const optional<U>&&, T>,
			std::is_assignable<T&, optional<U>&>,
			std::is_assignable<T&, const optional<U>&>,
			std::is_assignable<T&, optional<U>&&>,
			std::is_assignable<T&, const optional<U>&&>
			>
			>,
			std::is_constructible<T, const U&>,
			std::is_assignable<T&, const U&>
			>::value, bool
			> ::type = true
		>
		optional& operator=(const optional<U>& other)
		{
			if (this == reinterpret_cast<const optional*>(&other))
				return *this;

			if (other.has_value())
			{
				if (has_value())
					**this = *other;
				else
					construct(*other);
			}
			else
			{
				destroy_safe();
			}

			return *this;
		}

		template<typename U,
			typename std::enable_if <
			std::conjunction<
			std::negation<
			std::disjunction<
			std::is_constructible<T, optional<U>&>,
			std::is_constructible<T, const optional<U>&>,
			std::is_constructible<T, optional<U>&&>,
			std::is_constructible<T, const optional<U>&&>,
			std::is_convertible<optional<U>&, T>,
			std::is_convertible<const optional<U>&, T>,
			std::is_convertible<optional<U>&&, T>,
			std::is_convertible<const optional<U>&&, T>,
			std::is_assignable<T&, optional<U>&>,
			std::is_assignable<T&, const optional<U>&>,
			std::is_assignable<T&, optional<U>&&>,
			std::is_assignable<T&, const optional<U>&&>
			>
			>,
			std::is_constructible<T, U>,
			std::is_assignable<T&, U>
			>::value, bool
			> ::type = true
		>
		optional& operator=(optional<U>&& other)
		{
			if (this == reinterpret_cast<const optional*>(&other))
				return *this;

			if (other.has_value())
			{
				if (has_value())
					**this = std::move(*other);
				else
					construct(std::move(*other));
				other = nullopt_t{};
			}
			else
			{
				destroy_safe();
			}

			return *this;
		}

		template<class U = std::remove_cv_t<T>,
			typename std::enable_if<
			std::conjunction<
			std::negation<std::is_same<typename std::decay<U>::type, optional<T>>>,
			std::is_constructible<T, U>,
			std::is_assignable<T&, U>,
			std::disjunction<
			std::negation<std::is_scalar<T>>,
			std::negation<
			std::is_same<
			typename std::decay<U>::type,
			T
			>
			>
			>
			>::value, bool
			>::value = true
		>
		optional& operator=(U&& value)
		{
			if (has_value())
			{
				**this = std::forward<U>(value);
			}
			else
			{
				construct(std::forward<U>(value));
			}
			return *this;
		}

		constexpr const T* operator->() const noexcept
		{
			return reinterpret_cast<const T*>(object);
		}

		constexpr T* operator->() noexcept
		{
			return reinterpret_cast<T*>(object);
		}

		constexpr const T& operator*() const& noexcept
		{
			return *reinterpret_cast<const T*>(object);
		}

		constexpr T& operator*() & noexcept
		{
			return *reinterpret_cast<T*>(object);
		}

		constexpr const T&& operator*() const&& noexcept
		{
			return std::move(*reinterpret_cast<const T*>(object));
		}

		constexpr T&& operator*() && noexcept
		{
			return std::move(*reinterpret_cast<T*>(object));
		}

		constexpr explicit operator bool() const noexcept
		{
			return m_hasValue;
		}

		constexpr bool has_value() const noexcept
		{
			return m_hasValue;
		}

		constexpr T& value()&
		{
			if (!has_value())
				throw bad_optional_access{};
			return operator*();
		}

		constexpr const T& value() const&
		{
			if (!has_value())
				throw bad_optional_access{};
			return operator*();
		}

		constexpr T&& value()&&
		{
			if (!has_value())
				throw bad_optional_access{};
			return operator*();
		}

		constexpr const T&& value() const&&
		{
			if (!has_value())
				throw bad_optional_access{};
			return operator*();
		}

		template<class U = std::remove_cv<T>::type>
		constexpr T value_or(U&& default_value) const&
		{
			if (has_value())
				return **this;
			else
				return static_cast<T>(std::forward<U>(default_value));
		}

		template<class U = std::remove_cv<T>::type>
		constexpr T value_or(U&& default_value)&&
		{
			if (has_value())
				return std::move(**this);
			else
				return static_cast<T>(std::forward<U>(default_value));
		}

		void swap(optional& other) noexcept(std::is_nothrow_move_constructible<T>::value&&
			std::is_nothrow_swappable<T>::value)
		{
			// if neither of them has
			if (!has_value() && !other.has_value())
				return;
			else if (has_value() && other.has_value())
				std::swap(**this, *other);
			else if (has_value())
			{
				other = std::move(**this);
				destroy();
			}
			else
			{
				construct(*other.object);
				other.destroy();
			}
		}

		void reset()
		{
			destroy_safe();
		}

		template<class... Args>
		T& emplace(Args&&... args)
		{
			destroy_safe();
			construct(std::forward<Args>(args));
			return **this;
		}

		template<class U, class... Args,
			typename std::enable_if<
			std::is_constructible<T, std::initializer_list<U>&, Args&&...>::value
			, bool
			>::type = true
		>
		T& emplace(std::initializer_list<U> ilist, Args&&... args)
		{
			destroy_safe();
			construct(ilist, std::forward<Args>(args)...);
			return **this;
		}

	private:
		template<class... Args>
		inline void construct(Args&&... args)
		{
			new (object) T(std::forward<Args>(args)...);
			m_hasValue = true;
		}

		inline void destroy()
		{
			reinterpret_cast<T*>(object)->~T();
			std::memset(object, 0, sizeof(object));
			m_hasValue = false;
		}

		inline void destroy_safe()
		{
			if (has_value())
				destroy();
		}

	private:
		alignas(T) uint8_t object[sizeof(T)]{ { 0 } };
		bool m_hasValue{ false };
	};

	template<class T>
	constexpr optional<typename decay<T>::type> make_optional(T&& value)
	{
		return optional<typename decay<T>::type>(forward<T>(value));
	}

	template<class T, class... Args,
		typename enable_if<
		is_constructible<T, Args...>::value
		, bool
		>::type = true
	>
	constexpr optional<T> make_optional(Args&&... args)
	{
		return optional<T>(in_place, forward<Args>(args)...);
	}

	template<class T, class U, class... Args,
		typename enable_if<
			is_constructible<T, initializer_list<U>&, Args...>::value
			, bool
		>::type = true
	>
	constexpr optional<T> make_optional(initializer_list<U> ilist, Args&&... args)
	{
		return optional<T>(in_place, ilist, forward<Args>(args)...);
	}

	template< class T, class U >
	constexpr bool operator==(const optional<T>& lhs, const optional<U>& rhs)
	{
		return lhs.has_value() != rhs.has_value() ? false :
			(lhs.has_value() == false ? true : *lhs == *rhs);
	}

	template< class T, class U >
	constexpr bool operator!=(const optional<T>& lhs, const optional<U>& rhs)
	{
		return lhs.has_value() != rhs.has_value() ? true :
			(lhs.has_value() == false ? false : *lhs != *rhs);
	}

	template< class T, class U >
	constexpr bool operator<(const optional<T>& lhs, const optional<U>& rhs)
	{
		return !rhs ? false : (!lhs ? true : *lhs < *rhs);
	}

	template< class T, class U >
	constexpr bool operator<=(const optional<T>& lhs, const optional<U>& rhs)
	{
		return !lhs ? true : (!rhs ? false : *lhs <= *rhs);
	}

	template< class T, class U >
	constexpr bool operator>(const optional<T>& lhs, const optional<U>& rhs)
	{
		return !lhs ? false : (!rhs ? true : *lhs > *rhs);
	}

	template< class T, class U >
	constexpr bool operator>=(const optional<T>& lhs, const optional<U>& rhs)
	{
		return !rhs ? true : (!lhs ? false : *lhs >= *rhs);
	}

	template< class T >
	constexpr bool operator==(const optional<T>& opt, nullopt_t) noexcept
	{
		return !opt;
	}

	template< class T >
	constexpr bool operator==(nullopt_t, const optional<T>& opt) noexcept
	{
		return !opt;
	}

	template< class T >
	constexpr bool operator!=(const optional<T>& opt, nullopt_t) noexcept
	{
		return opt.has_value();
	}

	template< class T >
	constexpr bool operator!=(nullopt_t, const optional<T>& opt) noexcept
	{
		return opt.has_value();
	}

	template< class T >
	constexpr bool operator<(const optional<T>& opt, nullopt_t) noexcept
	{
		return false;
	}

	template< class T >
	constexpr bool operator<(nullopt_t, const optional<T>& opt) noexcept
	{
		return opt.has_value();
	}

	template< class T >
	constexpr bool operator<=(const optional<T>& opt, nullopt_t) noexcept
	{
		return !opt;
	}

	template< class T >
	constexpr bool operator<=(nullopt_t, const optional<T>& opt) noexcept
	{
		return true;
	}

	template< class T >
	constexpr bool operator>(const optional<T>& opt, nullopt_t) noexcept
	{
		return opt.has_value();
	}

	template< class T >
	constexpr bool operator>(nullopt_t, const optional<T>& opt) noexcept
	{
		return false;
	}

	template< class T >
	constexpr bool operator>=(const optional<T>& opt, nullopt_t) noexcept
	{
		return true;
	}

	template< class T >
	constexpr bool operator>=(nullopt_t, const optional<T>& opt) noexcept
	{
		return !opt;
	}

	template< class T, class U >
	constexpr bool operator==(const optional<T>& opt, const U& value)
	{
		return opt.has_value() ? *opt == value : false;
	}

	template< class U, class T >
	constexpr bool operator==(const U& value, const optional<T>& opt)
	{
		return opt.has_value() ? value == *opt : false;
	}

	template< class T, class U >
	constexpr bool operator!=(const optional<T>& opt, const U& value)
	{
		return opt.has_value() ? *opt != value : true;
	}

	template< class U, class T >
	constexpr bool operator!=(const U& value, const optional<T>& opt)
	{
		return opt.has_value() ? value != *opt : true;
	}

	template< class T, class U >
	constexpr bool operator<(const optional<T>& opt, const U& value)
	{
		return opt.has_value() ? *opt < value : true;
	}

	template< class U, class T >
	constexpr bool operator<(const U& value, const optional<T>& opt)
	{
		return opt.has_value() ? value < *opt : false;
	}

	template< class T, class U >
	constexpr bool operator<=(const optional<T>& opt, const U& value)
	{
		return opt.has_value() ? *opt <= value : true;
	}

	template< class U, class T >
	constexpr bool operator<=(const U& value, const optional<T>& opt)
	{
		return opt.has_value() ? value <= *opt : false;
	}

	template< class T, class U >
	constexpr bool operator>(const optional<T>& opt, const U& value)
	{
		return opt.has_value() ? *opt > value  : false;
	}

	template< class U, class T >
	constexpr bool operator>(const U& value, const optional<T>& opt)
	{
		return opt.has_value() ? value > *opt  : true;
	}

	template< class T, class U >
	constexpr bool operator>=(const optional<T>& opt, const U& value)
	{
		return opt.has_value() ? *opt >= value : false;
	}

	template< class U, class T >
	constexpr bool operator>=(const U& value, const optional<T>& opt)
	{
		return opt.has_value() ? value >= *opt : true;
	}

	template<class T,
		typename enable_if<
		conjunction<
		is_move_constructible<T>,
		is_swappable<T>
		>::value
		, bool
		>::type = true
	>
	void swap(optional<T>& lhs, optional<T>& rhs) noexcept(noexcept(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}
#endif
