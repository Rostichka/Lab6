#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node {
	string value;
	Node* left;
	Node* right;
};

Node* Create_Node(string s) {
	Node * temp = new Node;
	temp->value = s;
	temp->left = nullptr;
	temp->right = nullptr;
	return temp;
}
int priority(char c) {
	switch (c)
	{
	case '(':
		return -1;
		break;
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	default:
		return 0;
		break;
	}
}

void add(stack<Node*>& out, Node* temp) {
	temp->right = out.top();
	out.pop();
	temp->left = out.top();
	out.pop();
	out.push(temp);
}

Node* bild_tree(string s) {
	stack <Node*> out;
	stack <char> op;
	string s1 = "";
	int i = 0;
	while (i < s.length()) {
		string s1 = "";
		while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
			s1 += s[i];
			i++;
		}
		if (s1.length() > 0) {
			out.push(Create_Node(s1));
			i--;
		}
		else if (s[i] == '(')
			op.push(s[i]);
		else if (s[i] == ')') {
			while (op.top() != '(') {
				string x;
				x = op.top();
				add(out, Create_Node(x));
				op.pop();
			}
			op.pop();
		}
		else if (priority(s[i])) {
			while (op.size() != 0 && priority(s[i]) <= priority(op.top())) {
				string x;
				x = op.top();
				add(out, Create_Node(x));
				op.pop();
			}
			op.push(s[i]);
		}
		i++;
	}

	while (op.size()) {
		string x;
		x = op.top();
		add(out, Create_Node(x));
		op.pop();
	}
	return out.top();
}

void write_tree(Node* root, int l) {
	if (!root)
		return;
	write_tree(root->left, l + 1);
	for (int i = 0; i < l; i++)
		cout << "  ";
	cout << root->value << endl;
	write_tree(root->right, l + 1);
}

string write_exp(Node* root) {
	if (!root)
		return "";
	string result = "";
	if (root->left && priority(root->left->value[0]) && priority(root->left->value[0]) > priority(root->value[0]))
		result = "(" + write_exp(root->left) + ")";
	else
		result = write_exp(root->left);

	result += root->value;

	if (root->right && priority(root->right->value[0]) && priority(root->right->value[0]) <= priority(root->value[0]))
		result += "(" + write_exp(root->right) + ")";
	else
		result += write_exp(root->right);
	return result;
}
int main()
{
	string s;
	cin >> s;

	Node* tree = bild_tree(s);

	write_tree(tree, 0);

	cout << write_exp(tree);
	system("pause");
	return 0;
}

