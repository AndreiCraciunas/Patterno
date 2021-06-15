#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <iterator>

namespace pat
{
	template <typename ObjectToCommand, typename ... Args>
	struct Command
	{
		virtual ~Command() = default;

		virtual bool DoIt(ObjectToCommand &) = 0;
		virtual bool UndoIt(ObjectToCommand &) = 0;
	};

	template <typename ObjectToCommand>
	struct Commander
	{
		Commander() = delete;
		Commander(const Commander&) = delete;
		Commander(Commander&&) = delete;
		Commander& operator=(const Commander&) = delete;
		Commander& operator=(Commander&&) = delete;

		Commander(ObjectToCommand &object) : _object{ object } {};

		template <typename CommandChild>
		[[nodiscard]] auto DoIt(std::shared_ptr<CommandChild> cmd) noexcept -> bool
		{
			bool ok{ true };

			ok = ok && cmd->DoIt(std::ref(_object));
			ok = ok && RegisterCommand(std::move(cmd));

			return ok;
		}

		//template <typename CommandType, typename ... Args>
		//[[nodiscard]] auto DoIt(Args && ... args) noexcept -> bool
		//{
		//	return DoIt(std::make_shared<CommandType, typename ... Args>{std::forward<Args>(args)...});
		//}

		[[nodiscard]] auto UndoIt() noexcept -> bool
		{
			bool ok{ true };

			ok = ok && !_commands.empty();
			ok = ok && (*_it).UndoIt(std::ref(_object));
			ok = ok && MoveHeadBackward();

			return ok;
		}

		auto RedoIt() -> bool {
			bool ok{ true };

			ok = ok && MoveHeadForward();
			ok = ok && (*_it)->DoIt(std::ref(_object));

			return ok;
		}

	private:
		template <typename CommandChild>
		auto RegisterCommand(std::shared_ptr<CommandChild> && cmd) -> bool
		{
			_commands.emplace_back(std::move(cmd));
			return MoveHeadForward();
		}

		auto MoveHeadBackward() -> bool
		{
			if (_it == _commands.begin())
				return false;

			_it--;
			return true;
		}

		auto MoveHeadForward() -> bool
		{
			if (_it == _commands.end())
				return false;

			_it++;
			return true;
		}

	private:
		using Commands = std::vector<std::shared_ptr<Command<ObjectToCommand>>>;
		using CommandsIterator = typename std::vector<std::shared_ptr<Command<ObjectToCommand>>>::iterator;
		
		ObjectToCommand &_object;
		Commands _commands{};
		CommandsIterator _it{ _commands.begin() };
	};
}