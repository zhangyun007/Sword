#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using std::string;

struct Label {
	string name;	//标签名，可能取值：Rectangle, Text.....
	unordered_map<string, string> property; //属性值，通过property['id']取得标签的id以及各种其他属性
	struct Label *child;	//子标签指针，可以为NULL
	vector<struct Label*> *next;	//兄弟标签列表指针，可能为NULL。
};

/*
 * 将一个嵌套的标签结构掐头去尾，得到子标签字符串。
 */
string Get_Sub(string str) {
	
	return str;
}

/*
 * 去掉一个并列的标签结构中的第一个标签字符串，得到剩下的兄弟标签字符串
 */
string Get_Next(string str) {
	return str;
}

// Text是底层标签（叶子标签），里面不可能再包含其他标签。
struct Label *Parse_Text(string str) {
	struct Label * tmp = (struct Label *)malloc(sizeof(struct Label));
	
	//填充tmp中name和property
	
	return tmp;
}

/*
 *分析顶层Rectangle标签内嵌套的东西
 */
struct Label *Parse_Label(string str) {
	struct Label * tmp;
	
	//可能会有一个Text
	tmp = Parse_Text(str);
	
	return tmp;
}

/*
 * 从字符串解析出一个可能会嵌套的Rectangle标签，期望参数str，是一个完整的、可以嵌套的<Rectangle>
 */
struct Label *Parse_Rectangle(string str)
{
	struct Label * tmp = (struct Label *)malloc(sizeof(struct Label));
	
	//填充tmp中name和property
	
	//去头尾<Rectangle>，得到子字符串。
	string SubStr = Get_Sub(str);
	
	//子字符串依然可能有嵌套、也可能并列，可能是Rectangle，也可能是Text等其他标签
	tmp->child = Parse_Label(SubStr);
	
	return tmp;
}

int main() {

    std::ifstream t("test.gui");
    std::stringstream  sb;
    sb << t.rdbuf();
	
	string str = sb.str();
	cout << str;
	
	//解析出第一个Rectangel标签
	struct Label *first = Parse_Rectangle(str);
	
	struct Label *tmp;
	
	//继续解析下一个Rectangel标签，如果返回NULL表示解析完成
	while (tmp = Parse_Rectangle(Get_Next(str))) {
		first->next->push_back(tmp);
	}

	return 0;
}