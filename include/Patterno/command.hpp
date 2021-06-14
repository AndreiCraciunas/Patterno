#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>

namespace pat
{
	template <typename ObjectToCommand, typename ... Args>
	struct Command
	{
		virtual ~Command() = default;
		Command(Args && ... args) = default;

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

		Commander(ObjectToCommand &object) : object_{ object };

		[[nodiscard]] auto DoIt(Command &&cmd) noexcept -> bool
		{
			bool ok{ true };

			ok = ok && cmd.DoIt(std::ref(_object));
			ok = ok && RegisterCommand(std::move(cmd))

				return ok;
		}

		template <typename CommandType,
			//typename std::enable_if<std::is_base_of<Command, CommandType>::value>::type,
			typename ... Args>
			[[nodiscard]] auto DoIt(Args && ... args) noexcept -> bool
		{
			return DoIt(CommandType<ObjectToCommand>{std::forward<Args>(args)...});
		}

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
			ok = ok && (*_it).DoIt(std::ref(_object));

			return ok;
		}

	private:
		template <typename CommandType>
		auto RegisterCommand(CommandType && cmd) -> bool
		{
			_commands.emplace_back(std::move(cmd));
			return MoveHeadForward();
		}

		auto MoveHeadBackward() -> bool
		{
			if (_it == _commands.begin())
				return false;

			--it;
			return true;
		}

		auto MoveHeadForward() -> bool
		{
			if (_it == _commands.end())
				return false;

			++it;
			return true;
		}

	private:
		ObjectToCommand &_object;
		std::vector<Command> _commands{};
		std::vector<Command>::iterator _it{ _commands.end() };
	};
}