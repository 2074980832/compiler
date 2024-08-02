#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<utility>

using namespace std;

#define identifier 1
#define integer 2
#define plus 3
#define subtract 4
#define multiply 5
#define divide 6
#define	equal 7
#define greater 8
#define less 9
#define equal2 10
#define greaterorequal 11
#define lessorequal 12
#define or 13
#define also 14
#define reverse 15
#define colon 16
#define semicolon 17
#define questionmark 18
#define leftbracket 19
#define rightbracket 20
#define leftbigbracket 21
#define rightbigbracket 22
#define functionname 23
#define mainfunction 24
#define VAR 25
#define def 26
#define l_if 27
#define l_else 28
#define l_while 29
#define input 30
#define output 31
#define l_return 32
#define endmark 33
#define delivery 34

int MEM[10000] = { 0 };//虚拟计算机的内存

class Token {
public:
	char* start;
	char* end;
	int tokenType;
	int value = 0;
	Token(char* tstart, char* tend,int type)
	{
		start = tstart;
		end = tend;
		tokenType = type;
		if (type == integer)
		{
			int i = 1;
			for (; end != start; end--)
			{
				value += i * (*end - '0');
				i *= 10;
			}
			value += i * (*end - '0');
		}
		else if (type == functionname && *start == 'm' && *(start + 1) == 'a' && *(start + 2) == 'i' && *(start + 3) == 'n' && (start + 5) == end)
			tokenType = mainfunction;
		else if (tokenType == functionname)
		{
			char* cur = start;
			while (*cur != '(')
				cur++;
			char* tend = end;
			end = cur - 1;
			if (cur + 1 == tend)
				value = 0;
			else 
			{
				value++;
				for (; cur != tend; cur++)
					if (*cur == ',')
						value++;
			}
		}
	}
};
//基本词法单元类
 
class Command {
private:
public:
	int op, x, y, z;
	virtual void execute() = 0;
};
class OpStore :public Command {
public:
	OpStore(int a, int b, int c){op = 0; x = a; y = b; z = c;}
	OpStore() { op = 0; }
	void execute() override { MEM[z] = x; }
};
class OpArrayStore :public Command {
public:
	OpArrayStore(int a, int b, int c) { op = 1; x = a; y = b; z = c; }
	OpArrayStore() { op = 1; }
	void execute() override { MEM[y + MEM[z]] = MEM[x]; }
};
class OpArrayRead :public Command {
public:
	OpArrayRead(int a, int b, int c) { op = 2; x = a; y = b; z = c; }
	OpArrayRead() { op = 2; }
	void execute() override { MEM[z] = MEM[x + MEM[y]]; }
};
class OpCopy :public Command {
public:
	OpCopy(int a, int b, int c) { op = 3; x = a; y = b; z = c; }
	OpCopy() { op = 3; }
	void execute() override { MEM[z] = MEM[x]; }
};
class OpPlus :public Command {
public:
	OpPlus(int a, int b, int c) { op = 4; x = a; y = b; z = c; }
	OpPlus() { op = 4; }
	void execute() override { MEM[z] = MEM[x] + MEM[y]; }
};
class OpSubtract :public Command {
public:
	OpSubtract(int a, int b, int c) { op = 5; x = a; y = b; z = c; }
	OpSubtract() { op = 5; }
	void execute() override { MEM[z] = MEM[x] - MEM[y]; }
};
class OpMultiply :public Command {
public:
	OpMultiply(int a, int b, int c) { op = 6; x = a; y = b; z = c; }
	OpMultiply() { op = 6; }
	void execute() override { MEM[z] = MEM[x] * MEM[y]; }
};
class OpDivide :public Command {
public:
	OpDivide(int a, int b, int c) { op = 7; x = a; y = b; z = c; }
	OpDivide() { op = 7; }
	void execute() override { MEM[z] = MEM[x] / MEM[y]; }
};
class OpDelivery :public Command {
public:
	OpDelivery(int a, int b, int c) { op = 8; x = a; y = b; z = c; }
	OpDelivery() { op = 8; }
	void execute() override { MEM[z] = MEM[x] % MEM[y]; }
};
class OpIfEqual :public Command {
public:
	OpIfEqual(int a, int b, int c) { op = 9; x = a; y = b; z = c; }
	OpIfEqual() { op = 9; }
	void execute() override { MEM[z] = MEM[x] == MEM[y]; }
};
class OpGreater :public Command {
public:
	OpGreater(int a, int b, int c) { op = 10; x = a; y = b; z = c; }
	OpGreater() { op = 10; }
	void execute() override { MEM[z] = MEM[x] > MEM[y]; }
};
class OpLess :public Command {
public:
	OpLess(int a, int b, int c) { op = 11; x = a; y = b; z = c; }
	OpLess() { op = 11; }
	void execute() override { MEM[z] = MEM[x] < MEM[y]; }
};
class OpAlso :public Command {
public:
	OpAlso(int a, int b, int c) { op = 12; x = a; y = b; z = c; }
	OpAlso() { op = 12; }
	void execute() override { MEM[z] = MEM[x] && MEM[y]; }
};
class OpOr :public Command {
public:
	OpOr(int a, int b, int c) { op = 13; x = a; y = b; z = c; }
	OpOr() { op = 13; }
	void execute() override { MEM[z] = MEM[x] || MEM[y]; }
};
class OpReverse :public Command {
public:
	OpReverse(int a, int b, int c) { op = 14; x = a; y = b; z = c; }
	OpReverse() { op = 14; }
	void execute() override { MEM[z] = !MEM[x]; }
};
class OpOutput :public Command {
public:
	OpOutput(int a, int b, int c) { op = 50, x = a, y = b, z = c; }
	OpOutput() { op = 50; }
	void execute() override { cout << MEM[x] << ' '; }
};
class OpReadIn :public Command {
public:
	OpReadIn(int a, int b, int c) { op = 60, x = a, y = b, z = c; }
	OpReadIn() { op = 60; }
	void execute() override { cin >> MEM[x]; }
};
class OpCheckSkip :public Command {
public:
	vector<Command*>cmd;
	OpCheckSkip(int a, int b, int c, vector<Command*> &tcmd) { op = 20, x = a, y = b, z = c; cmd = tcmd; }
	OpCheckSkip() { op = 20; }
	void execute() override {if (MEM[x] == 0)cmd[z]->execute(); }
};
class OpSkipX :public Command {
public:
	vector<Command*>cmd;
	OpSkipX(int a, int b, int c, vector<Command*>& tcmd) { op = 30, x = a, y = b, z = c; cmd = tcmd; }
	OpSkipX() { op = 30; }
	void execute() override { cmd[z]->execute(); }
};
class OpSkipIndex :public Command {
public:
	vector<Command*>cmd;
	OpSkipIndex(int a, int b, int c, vector<Command*>& tcmd) { op = 40, x = a, y = b, z = c; cmd = tcmd; }
	OpSkipIndex() { op = 40; }
	void execute() override { cmd[MEM[z]]->execute(); }
};
//Command模式类

class Lexer {
private:
	char lexer[1000000];//输入的语句
	vector<Token> tokenLexer;//token形式
	vector<Command*>Cmd;

	map<string, int>indexOfIden;//全局变量的存放地址
	vector<pair<int, int>>globalIdenVAR;//全局变量声明片段

	vector<map<string, int>>stackIndexOfIden;//局部变量以及函数参数
	map<pair<string, int>, int>indexOfFunction;//函数的指令位置
	map<pair<string, int>, vector<string>>formParaOfFunc;//函数的形式参数map
	map<int,int> addressOfFuncReturnValueStore;//generateExpression_1中使用的函数返回地址
	
	int indexOfMainfunctionStart;
	int indexOfMainfunctionEnd;
	bool ifInMainfunction = 0;

	string _VAR = "VAR";
	string _def = "def";
	string _return = "return";
	string _if = "if";
	string _else = "else";
	string _while = "while";
	string _input = "input";
	string _output = "output";

	int addressOfExpressionCalculateStart = 0;
	int addressOfExpressionCalculateEnd = 99;
	//表达式计算区域

	int addressOfFuncReturnValue = 100;
	//函数返回地址

	int addressOfGlobalValueStart = 101;
	int addressOfGlobalValueCur = 101;
	int addressOfGlobalValueEnd = 199;
	//堆区

	bool ifInStack = 0;
	int addressOfLastStackTop = 200;
	int addressOfStackStart = 201;
	int addressOfStackEnd = 1000;
	//栈区

	bool CheckIfMark(char* start, string toBeCheck)
	{
		for (int i = 0; i < toBeCheck.length(); i++)
		{
			char* end = start + i;
			if (*end != toBeCheck[i])return false;
		}
		return true;
	}
	//generateTokenLexer的附属函数
	 
	void generateTokenLexer()
	{
		char* start = lexer;
		char* end = lexer;
		while (*end != '\x1a' && *end != EOF)
		{
			switch (*start)
			{
			case '+': {Token curToken(start, end, plus); tokenLexer.push_back(curToken); break; }
			case '-': {Token curToken(start, end, subtract); tokenLexer.push_back(curToken); break; }
			case '*': {Token curToken(start, end, multiply); tokenLexer.push_back(curToken); break; }
			case '/': {Token curToken(start, end, divide); tokenLexer.push_back(curToken); break; }
			case '=':
			{
				char* curCh = end + 1;
				if (*curCh == '=')
				{
					Token curToken(start, curCh, equal2);
					tokenLexer.push_back(curToken);
					end++;
				}
				else
				{
					Token curToken(start, end, equal);
					tokenLexer.push_back(curToken);
				}
				break;
			}
			case '>':
			{
				char* curCh = end + 1;
				if (*curCh == '=')
				{
					Token curToken(start, curCh, greaterorequal);
					tokenLexer.push_back(curToken);
					end++;
				}
				else
				{
					Token curToken(start, end, greater);
					tokenLexer.push_back(curToken);
				}
				break;
			}
			case '<':
			{
				char* curCh = end + 1;
				if (*curCh == '=')
				{
					Token curToken(start, curCh, lessorequal);
					tokenLexer.push_back(curToken);
					end++;
				}
				else
				{
					Token curToken(start, end, less);
					tokenLexer.push_back(curToken);
				}
				break;
			}
			case '%': {Token curToken(start, end, delivery); tokenLexer.push_back(curToken); break; }
			case '|': {end++; Token curToken(start, end, or); tokenLexer.push_back(curToken); break; }
			case '&': {end++; Token curToken(start, end, also); tokenLexer.push_back(curToken); break; }
			case '!': {Token curToken(start, end, reverse); tokenLexer.push_back(curToken); break; }
			case ':': {Token curToken(start, end, colon); tokenLexer.push_back(curToken); break; }
			case ';': {Token curToken(start, end, semicolon); tokenLexer.push_back(curToken); break; }
			case '?': {Token curToken(start, end, questionmark); tokenLexer.push_back(curToken); break; }
			case '(': {Token curToken(start, end, leftbracket); tokenLexer.push_back(curToken); break; }
			case ')': {Token curToken(start, end, rightbracket); tokenLexer.push_back(curToken); break; }
			case '{': {Token curToken(start, end, leftbigbracket); tokenLexer.push_back(curToken); break; }
			case '}': {Token curToken(start, end, rightbigbracket); tokenLexer.push_back(curToken); break; }
			case '\x1a': {Token curToken(start, end, endmark); tokenLexer.push_back(curToken); break; }
			case EOF: {Token curToken(start, end, endmark); tokenLexer.push_back(curToken); break; }
			}
			if ((*start >= 'a' && *start <= 'z') || (*start >= 'A' && *start <= 'Z')||*start=='_')
			{
				if (CheckIfMark(start, _VAR)) { end += _VAR.size() - 1; Token curToken(start, end, VAR); tokenLexer.push_back(curToken); }
				else if (CheckIfMark(start, _def)) { end += _def.size() - 1; Token curToken(start, end, def); tokenLexer.push_back(curToken); }
				else if (CheckIfMark(start, _if)) { end += _if.size() - 1; Token curToken(start, end, l_if); tokenLexer.push_back(curToken); }
				else if (CheckIfMark(start, _else)) { end += _else.size() - 1; Token curToken(start, end, l_else); tokenLexer.push_back(curToken); }
				else if (CheckIfMark(start, _while)) { end += _while.size() - 1; Token curToken(start, end, l_while); tokenLexer.push_back(curToken); }
				else if (CheckIfMark(start, _input)) { end += _input.size() - 1; Token curToken(start, end, input); tokenLexer.push_back(curToken); }
				else if (CheckIfMark(start, _output)) { end += _output.size() - 1; Token curToken(start, end, output); tokenLexer.push_back(curToken); }
				else if (CheckIfMark(start, _return)) { end += _return.size() - 1; Token curToken(start, end, l_return); tokenLexer.push_back(curToken); }
				else {
					while ((*end >= 'a' && *end <= 'z') || (*end >= 'A' && *end <= 'Z') || *end == '_' || (*end >= '0' && *end <= '9')) { end++; }
					if (*end == '(')
					{
						while (*end != ')')
							end++;
						Token curToken(start, end, functionname);
						tokenLexer.push_back(curToken);
					}
					else
					{
						end--;
						Token curToken(start, end, identifier);
						tokenLexer.push_back(curToken);
					}
				}
			}
			else if (*start >= '0' && *start <= '9')
			{
				while (*end >= '0' && *end <= '9') { end++; }
				end--;
				Token curToken(start, end, integer);
				tokenLexer.push_back(curToken);
			}
			end++;
			while (*end == ' ')end++;
			start = end;
		}
	}
	//用于生成Token总式

	int skipBracket(int indexOfLeftBracket)
	{
		int i = 1;
		int index = indexOfLeftBracket + 1;
		while (i != 0)
		{
			if (tokenLexer[index].tokenType == leftbracket)i++;
			else if (tokenLexer[index].tokenType == rightbracket)i--;
			index++;
		}
		return index - 1;
	}
	//用于查找对应右括号

	int skipBigBracket(int indexOfLeftBigBracket)
	{
		int i = 1;
		int index = indexOfLeftBigBracket + 1;
		while (i != 0)
		{
			if (tokenLexer[index].tokenType == leftbigbracket)i++;
			else if (tokenLexer[index].tokenType == rightbigbracket)i--;
			index++;
		}
		return index - 1;
	}
	//用于查找对应右大括号

	int findSemicolon(int indexOfStartToken)
	{
		int index = indexOfStartToken;
		while (tokenLexer[index].tokenType != semicolon)
			index++;
		return index;
	}
	//用于查找此赋值语句结尾

	int findEnd(int indexOfStartToken)
	{
		switch (tokenLexer[indexOfStartToken].tokenType)
		{
		case leftbigbracket:return skipBigBracket(indexOfStartToken);
		case l_if:return findEnd(skipBracket(indexOfStartToken + 1) + 1);
		case l_while:return findEnd(skipBracket(indexOfStartToken + 1) + 1);
		default:return findSemicolon(indexOfStartToken);
		}
	}
	//用于查找此语句结尾

	int findElse(int indexOfIf)
	{
		int index = indexOfIf;
		int i = 1;
		while (i != 0)
		{
			if (tokenLexer[index].tokenType == l_if)i++;
			else if (tokenLexer[index].tokenType == l_else)i--;
			index++;
		}
		return index - 1;
	}
	//用于查找对应else

	string constructString(char* start, char* end)
	{
		int length = end - start + 1;
		string curString(start, length);
		return curString;
	}
	//generateExpression的附属函数

	void generateExpression(int startIndex, int endIndex, int& addressOfResult)
	{
		
		for (int i = startIndex; i <= endIndex; i++)
		{
			if (tokenLexer[i].tokenType == functionname)
			{
				generateFuncExecute(i, i);
				OpCopy* curOp = new OpCopy(addressOfFuncReturnValue, 0, addressOfResult);
				Cmd.push_back(curOp);
				addressOfFuncReturnValueStore[i] = addressOfResult;
				addressOfResult++;
			}
		}
		generateExpression_1(startIndex, endIndex, addressOfResult);
	}

	void generateExpression_1(int startIndex,int endIndex,int& addressOfResult)
	{
		if (tokenLexer[startIndex].tokenType == leftbracket && skipBracket(startIndex) == endIndex)
			generateExpression_1(startIndex + 1, endIndex - 1, addressOfResult);
		else 
		{
			if (startIndex == endIndex)
			{
				if (tokenLexer[startIndex].tokenType == identifier)
				{
					if (stackIndexOfIden.empty())
					{
						int tindex = indexOfIden[constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
						OpCopy* curOp = new OpCopy(tindex, 0, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
					else 
					{
						auto index = stackIndexOfIden[stackIndexOfIden.size() - 1].find(constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end));
						if (index != stackIndexOfIden[stackIndexOfIden.size() - 1].end())
						{
							int tindex = stackIndexOfIden[stackIndexOfIden.size() - 1][constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
							int disindex = stackIndexOfIden[stackIndexOfIden.size() - 1].size() - tindex;
							OpArrayRead* curOp = new OpArrayRead(-disindex, addressOfLastStackTop, addressOfResult);
							Cmd.push_back(curOp);
							return;
						}
						else
						{
							int tindex = indexOfIden[constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
							OpCopy* curOp = new OpCopy(tindex, 0, addressOfResult);
							Cmd.push_back(curOp);
							return;
						}
					}
				}
				else if (tokenLexer[startIndex].tokenType == integer)
				{
					OpStore* curOp=new OpStore(tokenLexer[startIndex].value, 0, addressOfResult);
					Cmd.push_back(curOp);
					return;
				}
				else if (tokenLexer[startIndex].tokenType == functionname)
				{
					OpCopy* curOp = new OpCopy(addressOfFuncReturnValueStore[startIndex], 0, addressOfResult);
					Cmd.push_back(curOp);
					return;
				}
			}
			else
			{
				for (int i = startIndex; i <= endIndex; i++)
				{

				}
				//?与：

				for (int i = startIndex; i <= endIndex; i++)
				{
					if (tokenLexer[i].tokenType == leftbracket)i = skipBracket(i);
					else if (tokenLexer[i].tokenType == or)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpOr* curOp=new OpOr(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
				}
				//||运算

				for (int i = startIndex; i <= endIndex; i++)
				{
					if (tokenLexer[i].tokenType == leftbracket)i = skipBracket(i);
					else if (tokenLexer[i].tokenType == also)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpAlso* curOp=new OpAlso(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
				}
				//&&运算

				for (int i = startIndex; i <= endIndex; i++)
				{
					if (tokenLexer[i].tokenType == leftbracket)i = skipBracket(i);
					else if (tokenLexer[i].tokenType == equal2)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpIfEqual* curOp=new OpIfEqual(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
				}
				//==与！=

				for (int i = startIndex; i <= endIndex; i++)
				{
					if (tokenLexer[i].tokenType == leftbracket)i = skipBracket(i);
					else if (tokenLexer[i].tokenType == greater)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpGreater* curOp=new OpGreater(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
					else if (tokenLexer[i].tokenType == less)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpLess* curOp=new OpLess(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
				}
				//>与<

				for (int i = startIndex; i <= endIndex; i++)
				{
					if (tokenLexer[i].tokenType == leftbracket)i = skipBracket(i);
					else if (tokenLexer[i].tokenType == plus)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpPlus* curOp=new OpPlus(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
					else if (tokenLexer[i].tokenType == subtract && (tokenLexer[i-1].tokenType == identifier || tokenLexer[i-1].tokenType == integer))
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpSubtract* curOp=new OpSubtract(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
				}
				//+与-

				for (int i = startIndex; i <= endIndex; i++)
				{
					if (tokenLexer[i].tokenType == leftbracket)i = skipBracket(i);
					else if (tokenLexer[i].tokenType == multiply)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpMultiply* curOp=new OpMultiply(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
					else if (tokenLexer[i].tokenType == divide)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpDivide* curOp=new OpDivide(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
					else if (tokenLexer[i].tokenType == delivery)
					{
						generateExpression_1(startIndex, i - 1, addressOfResult);
						int address1 = addressOfResult;
						addressOfResult++;
						generateExpression_1(i + 1, endIndex, addressOfResult);
						int address2 = addressOfResult;
						addressOfResult++;
						OpDelivery* curOp=new OpDelivery(address1, address2, addressOfResult);
						Cmd.push_back(curOp);
						return;
					}
				}//*and/
				//*与/与%

				if (tokenLexer[startIndex].tokenType == subtract)
				{
					generateExpression_1(startIndex + 1, endIndex, addressOfResult);
					addressOfResult++;
					OpStore* curOp=new OpStore(-1, 0, addressOfResult);
					addressOfResult++;
					OpMultiply* cur1Op=new OpMultiply(addressOfResult - 2, addressOfResult - 1, addressOfResult);
					Cmd.push_back(curOp);
					Cmd.push_back(cur1Op);
					return;
				}
				//负号

				if (tokenLexer[startIndex].tokenType == reverse)
				{
					generateExpression_1(startIndex + 1, endIndex, addressOfResult);
					addressOfResult++;
					OpReverse* curOp=new OpReverse(addressOfResult - 1, 0, addressOfResult);
					Cmd.push_back(curOp);
					return;
				}
				//！运算
			}
		}
	}
	//用于处理赋值表达式

	void generateIdentifier(int startIndex, int endIndex)
	{
		int taddress = addressOfExpressionCalculateStart;
		generateExpression(startIndex + 2, endIndex, taddress);
		if (stackIndexOfIden.empty())
		{
			int tindex = indexOfIden[constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
			OpCopy* curOp = new OpCopy(taddress, 0, tindex);
			Cmd.push_back(curOp);
			return;
		}
		else 
		{
			auto index = stackIndexOfIden[stackIndexOfIden.size() - 1].find(constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end));
			if (index != stackIndexOfIden[stackIndexOfIden.size() - 1].end())
			{
				int tindex = stackIndexOfIden[stackIndexOfIden.size() - 1][constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
				int disindex = stackIndexOfIden[stackIndexOfIden.size() - 1].size() - tindex;
				OpArrayStore* curOp = new OpArrayStore(taddress, -disindex, addressOfLastStackTop);
				Cmd.push_back(curOp);
				return;
			}
			else
			{
				int tindex = indexOfIden[constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
				OpCopy* curOp = new OpCopy(taddress, 0, tindex);
				Cmd.push_back(curOp);
				return;
			}
		}
	}
	//用于处理标识符赋值

	void generateIf_Else(int startIndexOfCond,int endIndexOfCond,int startIndexOfBranch_1,int endIndexOfBranch_1,int startIndexOfBranch_2,int endIndexOfBranch_2)
	{
		int taddress = addressOfExpressionCalculateStart;
		generateExpression(startIndexOfCond, endIndexOfCond, taddress);
		Command* tcmd;
		Cmd.push_back(tcmd);
		int skipCmd_1 = Cmd.size() - 1;
		generateCmd(startIndexOfBranch_1, endIndexOfBranch_1);
		Cmd.push_back(tcmd);
		int skipCmd_2 = Cmd.size() - 1;
		int skipCmdGoal_1 = Cmd.size();
		generateCmd(startIndexOfBranch_2, endIndexOfBranch_2);
		int skipCmdGoal_2 = Cmd.size();
		OpCheckSkip* curOp=new OpCheckSkip(taddress, 0, skipCmdGoal_1, Cmd);
		OpSkipX* cur1Op=new OpSkipX(0, 0, skipCmdGoal_2, Cmd);
		Cmd[skipCmd_1] = curOp;
		Cmd[skipCmd_2] = cur1Op;
		return;
	}
	//用于处理If-else语句

	void generateWhile(int startIndexOfCond,int endIndexOfCond,int startIndex,int endIndex)
	{
		int skipBackGoal = Cmd.size();
		int taddress = addressOfExpressionCalculateStart;
		generateExpression(startIndexOfCond, endIndexOfCond, taddress);
		Command* tcmd;
		Cmd.push_back(tcmd);
		int checkSkip = Cmd.size() - 1;
		generateCmd(startIndex, endIndex);
		Cmd.push_back(tcmd);
		int skipBack = Cmd.size() - 1;
		int checkSkipGoal = Cmd.size();
		OpCheckSkip* curOp=new OpCheckSkip(taddress, 0, checkSkipGoal, Cmd);
		OpSkipX* cur1Op=new OpSkipX(0, 0, skipBackGoal, Cmd);
		Cmd[checkSkip] = curOp;
		Cmd[skipBack] = cur1Op;
		return;
	}
	//用于处理While语句

	void generateDefFunc(int startIndex,int endIndex)
	{
		if (tokenLexer[startIndex].tokenType == mainfunction)
		{
			ifInMainfunction = 1;
			indexOfMainfunctionStart = Cmd.size();
			int start = startIndex + 1; 
			int end = skipBigBracket(start + 1) - 1;
			map<string, int> tmap;
			stackIndexOfIden.push_back(tmap);
			generateCmd(start, end); 
			indexOfMainfunctionEnd = Cmd.size() - 1; 
			ifInMainfunction = 0;
		}
		else
		{
			pair<string, int> thisFunc = make_pair(constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end), tokenLexer[startIndex].value);
			indexOfFunction[thisFunc] = Cmd.size();

			vector<string>formPara;
			char* start = tokenLexer[startIndex].end + 2;
			char* end = start;
			for (int i = 1; i <= tokenLexer[startIndex].value; i++)
			{
				while (*end != ')' && *end != ',')
					end++;
				string curString = constructString(start, end - 1);
				formPara.push_back(curString);
				end++;
				start = end;
			}// 形式参数，目前不支持空格
			formParaOfFunc[thisFunc] = formPara;

			map<string, int> tmap;
			for (int i = 1; i <= formPara.size(); i++)
				tmap[formPara[i - 1]] = i;
			stackIndexOfIden.push_back(tmap);

			generateCmd(startIndex + 1, endIndex);

			stackIndexOfIden[stackIndexOfIden.size() - 1].clear();//清空栈
			return;
		}
	}
	//用于处理函数声明

	void generateFuncExecute(int startIndex, int endIndex)
	{
		int taddress = addressOfExpressionCalculateStart;
		OpStore* curOp=new OpStore(1, 0, taddress);
		OpPlus* cur1Op=new OpPlus(taddress, addressOfLastStackTop, addressOfLastStackTop);
		taddress++;
		Cmd.push_back(curOp);
		Cmd.push_back(cur1Op);
		//栈顶位置+1（用于存放调用位置）
		vector<string> truePara;
		vector<string>formPara;
		char* start = tokenLexer[startIndex].end + 2;
		char* end = start;
		for (int i = 1; i <= tokenLexer[startIndex].value; i++)
		{
			while (*end != ')' && *end != ',')
				end++;
			string curString = constructString(start, end - 1);
			truePara.push_back(curString);
			end++;
			start = end;
		}// 真实参数，目前不支持空格
		pair<string, int> thisFunc = make_pair(constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end), tokenLexer[startIndex].value);
		formPara = formParaOfFunc[thisFunc];//形式参数
		for (int i = 0; i < truePara.size(); i++)
		{
			if (stackIndexOfIden.empty())
			{
				int indexOfPara = indexOfIden[truePara[i]];
				OpStore* t1Op = new OpStore(1, 0, taddress);
				OpPlus* t2Op = new OpPlus(taddress, addressOfLastStackTop, addressOfLastStackTop);//栈顶位置+1
				OpArrayStore* t3Op = new OpArrayStore(indexOfPara, 0, addressOfLastStackTop);//实参数值传递给形参 
				taddress++;
				Cmd.push_back(t1Op);
				Cmd.push_back(t2Op);
				Cmd.push_back(t3Op);
			}
			else
			{
				auto index = stackIndexOfIden[stackIndexOfIden.size() - 1].find(truePara[i]);
				if (index != stackIndexOfIden[stackIndexOfIden.size() - 1].end())
				{
					int tindex = stackIndexOfIden[stackIndexOfIden.size() - 1][truePara[i]];
					int disindex = stackIndexOfIden[stackIndexOfIden.size() - 1].size() - tindex + 1 + i;
					OpArrayRead* tOp = new OpArrayRead(-disindex, addressOfLastStackTop, taddress);
					int indexOfPara = taddress;
					taddress++;
					OpStore* t1Op = new OpStore(1, 0, taddress);
					OpPlus* t2Op = new OpPlus(taddress, addressOfLastStackTop, addressOfLastStackTop);//栈顶位置+1
					OpArrayStore* t3Op = new OpArrayStore(indexOfPara, 0, addressOfLastStackTop);//实参数值传递给形参 
					taddress++;
					Cmd.push_back(tOp);
					Cmd.push_back(t1Op);
					Cmd.push_back(t2Op);
					Cmd.push_back(t3Op);
				}
				else
				{
					int indexOfPara = indexOfIden[truePara[i]];
					OpStore* t1Op = new OpStore(1, 0, taddress);
					OpPlus* t2Op = new OpPlus(taddress, addressOfLastStackTop, addressOfLastStackTop);//栈顶位置+1
					OpArrayStore* t3Op = new OpArrayStore(indexOfPara, 0, addressOfLastStackTop);//实参数值传递给形参 
					taddress++;
					Cmd.push_back(t1Op);
					Cmd.push_back(t2Op);
					Cmd.push_back(t3Op);
				}
			}
		}
		//赋值形参、构造map
		int invokeIndex = Cmd.size() + 3;
		OpStore* cur2Op=new OpStore(invokeIndex, 0, taddress);
		int size = truePara.size();
		OpArrayStore* cur3Op=new OpArrayStore(taddress, -size, addressOfLastStackTop);//栈尾存放调用函数的命令地址
		int skipGoal = indexOfFunction[thisFunc];
		OpSkipX* cur4Op = new OpSkipX(0, 0, skipGoal, Cmd);
		Cmd.push_back(cur2Op);
		Cmd.push_back(cur3Op);
		Cmd.push_back(cur4Op);
		//两个skip指令
		return;
	}
	//用于处理函数运行

	void generateInput(int startIndex, int endIndex)
	{
		if (stackIndexOfIden.empty())
		{
			int tindex = indexOfIden[constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
			OpReadIn* curOp = new OpReadIn(tindex, 0, 0);
			Cmd.push_back(curOp);
			return;
		}
		else
		{
			auto index = stackIndexOfIden[stackIndexOfIden.size() - 1].find(constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end));
			if (index != stackIndexOfIden[stackIndexOfIden.size() - 1].end())
			{
				int tindex = stackIndexOfIden[stackIndexOfIden.size() - 1][constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
				int disindex = stackIndexOfIden[stackIndexOfIden.size() - 1].size() - tindex;
				int taddress = addressOfExpressionCalculateStart;
				OpReadIn* curOp = new OpReadIn(taddress, 0, 0);
				OpArrayStore* cur1Op = new OpArrayStore(taddress, -disindex, addressOfLastStackTop);
				Cmd.push_back(curOp);
				Cmd.push_back(cur1Op);
				return;
			}
			else
			{
				int tindex = indexOfIden[constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)];
				OpReadIn* curOp = new OpReadIn(tindex, 0, 0);
				Cmd.push_back(curOp);
				return;
			}
		}
	}
	//用于处理输入

	void generateOutput(int startIndex, int endIndex)
	{
		int taddress = addressOfExpressionCalculateStart;
		generateExpression(startIndex, endIndex, taddress);
		OpOutput* curOp=new OpOutput(taddress, 0, 0);
		Cmd.push_back(curOp);
		return;
	}
	//用于处理输出

	void generateVAR(int startIndex, int endIndex)
	{
		if (ifInStack) 
		{
			if (startIndex == endIndex)
			{
				int taddress = addressOfExpressionCalculateStart;
				OpStore* curOp=new OpStore(1, 0, taddress);
				OpPlus* cur1Op=new OpPlus(taddress, addressOfLastStackTop, addressOfLastStackTop);
				taddress++;
				Cmd.push_back(curOp);
				Cmd.push_back(cur1Op);
				//最后一个栈的栈顶位置+1
				int size = stackIndexOfIden[stackIndexOfIden.size() - 1].size();
				stackIndexOfIden[stackIndexOfIden.size() - 1][constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)] = size + 1;
				//提供该局部变量的map
				return;
			}
			else
			{
				int taddress = addressOfExpressionCalculateStart;
				OpStore* curOp=new OpStore(1, 0, taddress);
				OpPlus* cur1Op=new OpPlus(taddress, addressOfLastStackTop, addressOfLastStackTop);
				taddress++;
				Cmd.push_back(curOp);
				Cmd.push_back(cur1Op);
				//最后一个栈的栈顶位置+1
				int size = stackIndexOfIden[stackIndexOfIden.size() - 1].size();
				stackIndexOfIden[stackIndexOfIden.size() - 1][constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)] = size + 1;
				//提供该局部变量的map
				generateExpression(startIndex + 2, endIndex, taddress);
				OpArrayStore* cur2Op=new OpArrayStore(taddress, 0, addressOfLastStackTop);
				Cmd.push_back(cur2Op);
				return;
			}
		}
		else
		{
			int start = Cmd.size();
			if (startIndex == endIndex)
			{
				indexOfIden[constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)] = addressOfGlobalValueCur;
				addressOfGlobalValueCur++;
				//自动设置为0
			}
			else
			{
				indexOfIden[constructString(tokenLexer[startIndex].start, tokenLexer[startIndex].end)] = addressOfGlobalValueCur;
				int taddress = addressOfExpressionCalculateStart;
				generateExpression(startIndex + 2, endIndex, taddress);
				OpCopy* curOp=new OpCopy(taddress, 0, addressOfGlobalValueCur);
				Cmd.push_back(curOp);
				addressOfGlobalValueCur++;
			}
			int end = Cmd.size() - 1;
			pair<int, int> tpair = make_pair(start, end);
			if(end>=start)
				globalIdenVAR.push_back(tpair);
		}
	}
	//用于处理声明

	void generateReturn(int startIndex, int endIndex,bool ifInmainfunction)
	{
		if (ifInmainfunction);
		else
		{
			int taddress = addressOfExpressionCalculateStart;
			generateExpression(startIndex, endIndex, taddress);
			OpCopy* curOp = new OpCopy(taddress, 0, addressOfFuncReturnValue);
			taddress++;
			int size = stackIndexOfIden[stackIndexOfIden.size() - 1].size();
			OpArrayRead* cur1Op = new OpArrayRead(-size, addressOfLastStackTop, taddress);
			int skipIndex = taddress;
			taddress++;
			OpStore* cur2Op = new OpStore(stackIndexOfIden[stackIndexOfIden.size() - 1].size() + 1, 0, taddress);
			OpSubtract* cur3Op = new OpSubtract(addressOfLastStackTop, taddress, addressOfLastStackTop);
			OpSkipIndex* cur4Op = new OpSkipIndex(0, 0, skipIndex, Cmd);
			Cmd.push_back(curOp);
			Cmd.push_back(cur1Op);
			Cmd.push_back(cur2Op);
			Cmd.push_back(cur3Op);
			Cmd.push_back(cur4Op);
			return;
		}
	}
	//用于处理return

	void generateCmd(int startIndex, int endIndex)
	{
		for (int i = startIndex; i <= endIndex;)
		{
			switch (tokenLexer[i].tokenType)
			{
			case VAR: {int start = i + 1; int end = findSemicolon(start) - 1; generateVAR(start, end); i = end + 2; break; }
			case def: {ifInStack = 1; int start = i + 1; int end = skipBigBracket(start + 1); generateDefFunc(start, end); i = end + 1; ifInStack = 0; break; }
			case identifier: {int start = i; int end = findSemicolon(start) - 1; generateIdentifier(start, end); i = end + 2; break; }
			case l_if: {int start_1 = i + 2; int end_1 = skipBracket(start_1 - 1) - 1; int start_2 = end_1 + 2; int end_2 = findElse(start_2 - 1) - 1;
				int start_3 = end_2 + 2; int end_3 = findEnd(start_3);generateIf_Else(start_1, end_1, start_2, end_2, start_3, end_3); i = end_3 + 1; break; }
			case l_while: {int start_1 = i + 2; int end_1 = skipBracket(start_1 - 1) - 1; int start_2 = end_1 + 2; int end_2 = findEnd(start_2);
				generateWhile(start_1, end_1, start_2, end_2); i = end_2 + 1; break; }
			case l_return: {int start = i + 1; int end = findSemicolon(start) - 1; generateReturn(start, end, ifInMainfunction); i = end + 2; break; }
			case functionname: {int start = i; int end = start; generateFuncExecute(start, end); i = end + 1; break; }
			//case mainfunction: {indexOfMainfunctionStart = Cmd.size(); ifInStack = 1; int start = i + 1; int end = skipBigBracket(start + 1) + 1; generateDefFunc(Cmd, start, end); indexOfMainfunctionEnd = Cmd.size() - 1; i = end + 1; ifInStack = 0; break; }
			case input: {int start = i + 1; int end = findSemicolon(start) - 1; generateInput(start, end); i = end + 2; break; }
			case output: {int start = i + 1; int end = findSemicolon(start) - 1; generateOutput(start, end); i = end + 2; break; }
			case leftbigbracket: {int start = i + 1; int end = skipBigBracket(start - 1) - 1; generateCmd(start, end); i = end + 2; break; }
			case semicolon: {i++; break; }
			case rightbigbracket: {i++; break; }
			}
		}
	}
public:
	void readIn()
	{
		char ch;
		int i = 0;
		do
		{
			ch = getchar();
			lexer[i] = ch;
			i++;
		} while (lexer[i - 1] != '\x1a' && lexer[i - 1] != EOF);
		generateTokenLexer();
	}

	void generateAllCmd()
	{
		int startIndex = 0;
		int endIndex = tokenLexer.size() - 2;
		generateCmd(startIndex, endIndex);
		return;
	}

	void setSpaceAllocate()
	{
		cout << "现分配堆栈空间如下：" << endl;
		cout << "表达式计算区域：" << addressOfExpressionCalculateStart << "--" << addressOfExpressionCalculateEnd << endl;
		cout << "函数返回存放地址：" << addressOfFuncReturnValue << endl;
		cout << "堆区范围（此计算机中为存放全局变量范围）：" << addressOfGlobalValueStart << "--" << addressOfGlobalValueEnd << endl;
		cout << "栈区范围（此计算机中为存放局部变量范围）：" << addressOfStackStart << "--" << addressOfStackEnd << endl;
		cout << "用于存放栈顶位置的地址：" << addressOfLastStackTop << endl;
		cout << endl;
		cout << "请依次输入：表达式计算区域始、末、函数返回存放地址、堆区范围始、末、栈区范围始、末、用于存放栈顶位置的地址" << endl;
		cout << "注意不要使空间冲突导致运行错误" << endl;
		cin >> addressOfExpressionCalculateStart >> addressOfExpressionCalculateEnd >> addressOfFuncReturnValue >> addressOfGlobalValueStart >> addressOfGlobalValueEnd >> addressOfStackStart >> addressOfStackEnd >> addressOfLastStackTop;
	}

	void setKeyString()
	{
		cout << "现关键字符字符串如下：" << endl;
		cout << "变量声明：" << _VAR << endl;
		cout << "函数声明：" << _def << endl;
		cout << "函数返回：" << _return << endl;
		cout << "if语句：" << _if << endl;
		cout << "else语句：" << _else << endl;
		cout << "while语句：" << _while << endl;
		cout << "输入语句：" << _input << endl;
		cout << "输出语句：" << _output << endl;
		cout << endl;
		cout << "输入0以设置变量声明，输入1以设置函数声明，输入2以设置函数返回，输入3以设置if语句，输入4以设置else语句，输入5以设置while语句，输入6以设置输入语句，输入7以设置输出语句，" << endl;
		int op;
		cin >> op;
		switch (op)
		{
		case 0: {cin >> _VAR; break; }
		case 1: {cin >> _def; break; }
		case 2: {cin >> _return; break; }
		case 3: {cin >> _if; break; }
		case 4: {cin >> _else; break; }
		case 5: {cin >> _while; break; }
		case 6: {cin >> _input; break; }
		case 7: {cin >> _output; break; }
		}
	}

	void execute()
	{
		MEM[addressOfLastStackTop] = addressOfLastStackTop;

		for (int i = 0; i < globalIdenVAR.size(); i++)
			for (int ti = globalIdenVAR[i].first; ti <= globalIdenVAR[i].second; ti++)
				Cmd[ti]->execute();

		for (int ti = indexOfMainfunctionStart; ti != indexOfMainfunctionEnd + 1;)
		{
			switch (Cmd[ti]->op)
			{
			case 20: {if (MEM[Cmd[ti]->x] == 0) { ti = Cmd[ti]->z; } else ti++; break; }
			case 30: { ti = Cmd[ti]->z; break; }
			case 40: { ti = MEM[Cmd[ti]->z]; break; }
			default: {Cmd[ti]->execute(); ti++; break; }
			}
		}
	}

	void out()
	{
		for (auto i = tokenLexer.begin(); i != tokenLexer.end(); i++)
		{
			char* ch = i->start;
			for (; ch != i->end; ch++)
				cout << *ch;
			cout << *ch << ' ' << i->tokenType << ' ' << i->value << endl;
		}
	}

	void showCompiledCmd()
	{
		for (int i = 0; i < Cmd.size(); i++)
			cout << i << "   " << Cmd[i]->op << ' ' << Cmd[i]->x << ' ' << Cmd[i]->y << ' ' << Cmd[i]->z << endl;
	}
};

class Computer {
private:
	vector<Command*> code;
	Lexer curlexer;

	void write()
	{
		curlexer.readIn();
	}

	void compile()
	{
		curlexer.generateAllCmd();
	}

	void showCompiledCmd()
	{
		curlexer.showCompiledCmd();
	}

	void execute()
	{
		curlexer.execute();
	}

	void op1()
	{
		write();
		compile();
		execute();
		end();
	}

	void op2()
	{
		write();
		compile();
		showCompiledCmd();
		cout << "以上为Command指令代码，输入1以运行代码，输入2以重启计算机" << endl;
		int op_1;
		cin >> op_1;
		if (op_1 == 1)
		{
			execute();
			end();
		}
		else if (op_1 == 2)
			op2();
	}

	void op3()
	{
		cout << "输入1以设置堆栈空间分配，输入2以设置关键字字符串" << endl;
		int op;
		cin >> op;
		if (op == 1)
			curlexer.setSpaceAllocate();
		else if (op == 2)
			curlexer.setKeyString();
		cout << "设置完毕，输入1以重启计算机" << endl;
		cin >> op;
		if (op == 1)initialization();
	}

	void end()
	{
		cout << "结果已运行，输入1以重启计算机，输入2以结束运行" << endl;
		int op_1;
		cin >> op_1;
		if (op_1 == 1)
			initialization();
		else if (op_1 == 2)
			cout << "计算机已运行完毕，谢谢您的使用" << endl;
	}
public:
	void initialization()
	{
		cout << "欢迎使用该虚拟计算机，输入1以编写并运行代码、输入2以编译出Command指令、输入3以设置环境变量" << endl;
		int op;
		cin >> op;
		if (op == 1)op1();
		else if (op == 2)op2();
		else if (op == 3)op3();
		return;
	}
};
int main()
{
	Computer thisCom;
	thisCom.initialization();
	return 0;
}