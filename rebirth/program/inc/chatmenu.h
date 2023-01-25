#pragma once

// TODO: Guess
const int LinesPerMessage = 5;

class ChatMenu : public SimObject
{
	typedef SimObject Parent;

	DECLARE_PERSISTENT(ChatMenu);

public:

	static const size_t MaxHeadingLen = 32; // 31 + 1 for key char?
	// TODO: Guess
	static const size_t MaxArgs = 8; 

	struct Node
	{
		Node* firstChild;
		Node* nextSibling;
		Node* parent;
		char heading[MaxHeadingLen];
		char key;
		int argc;
		const char* argv[MaxArgs];
		int y_offset;
	};
	Node* curNode;
	Node* chatTree;
	

	char heading[MaxHeadingLen];
	char lastKey;


	enum
	{
		Inactive,
		OneShot = 2
	};
	int curMode;

	
	virtual bool processArguments(int argc, const char** argv);
	virtual bool processEvent(const SimEvent* event);
	bool onAdd() override;
	virtual bool processQuery(SimQuery* query);
	virtual bool processKey(char key);
	
	int getMode() const
	{
		return this->curMode;
	}

public:
	Node * curMenu;

	ChatMenu();
	void deltree(Node* node);
	virtual ~ChatMenu();

	virtual void setMode(int mode);
	virtual bool addMenuString(const char* menuString, int argc, const char** argv);
};
