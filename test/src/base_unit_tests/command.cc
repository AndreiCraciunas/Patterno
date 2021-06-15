#include <catch2/catch.hpp>
#include <Patterno/command.hpp>
#include <map>

struct PhoneBook
{
	friend bool operator<(const PhoneBook& lhs, const PhoneBook& rhs)
	{
		lhs; rhs;
		return true;
	}

	std::map<std::string, std::string> _records;
};

struct InsertContact : public pat::Command<PhoneBook, std::string, std::size_t>
{
	InsertContact(std::string &&str, std::size_t pos = std::string::npos) : _str{ std::move(str) }, _pos{ pos } {}

	auto DoIt(PhoneBook &pb) -> bool
	{
		pb._records.insert(_str, _str);
		return true;
	}

	auto UndoIt(PhoneBook &) -> bool
	{
		return true;
	}

private:
	std::string _str;
	std::size_t _pos;
};

PhoneBook Pb;
pat::Commander<PhoneBook> Cmder(Pb);

TEST_CASE(
	"GIVEN"
	"An object that represents a phone book"
	"THEN"
	"Adding a new contact at any given position will be successful and will enlarge our record")
{
	REQUIRE(Cmder.DoIt(std::make_shared<InsertContact>("A true name", 2)));
	REQUIRE(Pb._records.size() == 1);
}
//
//class InsertStringCommand : public ICommand {
//	std::size_t _position{};
//	std::string _toInsert{};
//public:
//	InsertStringCommand(std::string &&toInsert, std::size_t position = std::string::npos) :
//		_position{ position },
//		_toInsert{ toInsert }
//	{}
//
//	bool IsLastPosition() const { return _position == std::string::npos; }
//	void doIt(std::string &text)    final { text.insert(_position, _toInsert); }
//	void undoIt(std::string &text)  final { text.erase(_position, _toInsert.size()); }
//};
//
//class DeleteStringCommand : public ICommand {
//	std::size_t _position{};
//	std::size_t _characterCount{};
//	std::string _deletedText{};
//public:
//	DeleteStringCommand(std::size_t position, std::size_t characterCount) :
//		_position{ position },
//		_characterCount{ characterCount }
//	{}
//
//	bool IsLastPosition() const { return _position == std::string::npos; }
//	void doIt(std::string &text) final {
//		_deletedText = text.substr(_position, text.size());
//		text.erase(text.size() - _characterCount);
//	}
//	void undoIt(std::string &text) final { text.insert(_position, _deletedText); }
//};
//
//class Editor {
//	std::vector<ICommand *> _history{};
//	std::size_t             _index{ 0 };
//	std::string             _text{};
//public:
//	Editor(std::string &&text) : _text{ std::move(text) } {}
//	~Editor() {
//		for (auto *elem : _history) {
//			delete elem;
//		}
//	}
//
//	void Add(ICommand *command) {
//		if (_index != _history.size())
//			_history.erase(_history.begin() + _index);
//		command->doIt(_text);
//		_history.push_back(command);
//		_index++;
//		Log();
//	}
//
//	void Undo() {
//		if (_history.empty())
//			return;
//		_history.at(--_index)->undoIt(_text);
//		Log();
//	}
//
//	void Redo() {
//		if (_index == _history.size())
//			return;
//		_history.at(_index++)->doIt(_text);
//		Log();
//	}
//
//	void Log() { std::cout << _text << std::endl; }
//};
//
//int main()
//{
//	Editor editor{ "O implementare a pattern-ului command" };
//	editor.Log();
//	editor.Add(new DeleteStringCommand(30, 7));
//	editor.Undo();
//	editor.Add(new InsertStringCommand("Inca ", 0));
//	editor.Undo();
//	editor.Redo();
//	return 0;
//}