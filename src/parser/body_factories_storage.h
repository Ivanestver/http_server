#pragma once
#include "core/str.h"
#include <map>
#include <type_traits>

namespace parser
{
	class RequestBodyParserFactory;

	class BodyFactoriesStorage
	{
	public:
		template<typename FACTORY>
		void Register(const String& mimeType)
		{
			static_assert(std::is_base_of_v<RequestBodyParserFactory, FACTORY>, "FACTORY must be a body parser factory class");
			m_factories.emplace(mimeType, new FACTORY{});
		}

		static BodyFactoriesStorage& GetStorage();

		~BodyFactoriesStorage();

		const RequestBodyParserFactory* GetFactory(const String& mimeType) const;

	private:
		BodyFactoriesStorage();

	private:
		std::map<String, RequestBodyParserFactory*> m_factories;
	};

	template<typename Fn>
	void RegisterBodyFactory(const String& mimeType)
	{
		BodyFactoriesStorage& instance = BodyFactoriesStorage::GetStorage();
		instance.Register<Fn>(mimeType);
	}
}