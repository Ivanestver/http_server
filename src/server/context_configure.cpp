#include "context_configure.h"
#include <memory>

namespace server
{
	std::unique_ptr<Context> context = nullptr;

	void ConfigureContext()
	{
		const String pathToRoot{ "./" };
		context.reset(new Context{ pathToRoot });
	}

	Context* GetInnerContext()
	{
		return context.get();
	}
}
