#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>
using namespace std;
vector<string> inputall,label;
vector<int>lbnum;

string toBin(string str,int n)
{
	bool neg = false;
	string ans = "00000000000000000000000000000000";
	string s;
	if(str[0]=='x')
		str=str.substr(1, str.length());
	if (str[0] == '-'){
		ans = "11111111111111111111111111111111";
		str = str.substr(1, str.length());
		neg = true;
	}

	int buffer;
	stringstream ss;
	ss << str;
	ss >> buffer;
	ss.str("");
	ss.clear();
	long long int total = 0, m = 1;
	
	while (buffer != 0) {
		total += ((buffer % 2) * m);
		buffer /= 2;
		m *= 10; 
	}
	ss << total;
	ss >> s;
	if (neg) {
		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '1')
				s[i] = '0';
			else
				s[i] = '1';
		}
		for (int i = s.length()-1; i >0 ; --i) {
			if (s[i] == '1')
				s[i] = '0';
			else {
				s[i] = '1';
				break;
			}
		}
	}
	ans += s;
	return ans.substr(ans.length() - n, ans.length());
}
string findoffset(string str,int pc,int limit) {
	int offset = 0;
	string ans;
	for (int i = 0; i < label.size(); ++i) {
		if (str == label[i]) {
			offset = 4*(lbnum[i] - pc);
			break;
		}
	}
	ans = to_string(offset);
	ans = toBin(ans, limit);
	return ans;
}


void rType(string input, int pc)
{
	string fun7, rs2, rs1, fun3, rd, op,str[4];
	int p;
	p = input.find(" ", 0);
	str[0] = input.substr(0, p);
	input = input.substr(p + 1, input.length());
	for(int i=1;i<4;i++){
		p = input.find(",", 0);
		str[i] = input.substr(0, p);
		input = input.substr(p + 1, input.length());
	}
	if (str[0] == "sub" || str[0] == "sra")
		fun7 = "0100000";
	else
		fun7 = "0000000";
	if (str[0] == "add" || str[0] == "sub")
		fun3 = "000";
	else if (str[0] == "sll")
		fun3 = "001";
	else if (str[0] == "slt")
		fun3 = "010";
	else if (str[0] == "sltu")
		fun3 = "011";
	else if (str[0] == "xor")
		fun3 = "100";
	else if (str[0] == "srl" || str[0] == "sra")
		fun3 = "101";
	else if (str[0] == "or")
		fun3 = "110";
	else
		fun3 = "111";
	
	op = "0110011";
	rs2 = toBin(str[3],5);
	rs1 = toBin(str[2],5);
	rd= toBin(str[1],5);
	cout << fun7 << " | " << rs2 << " | " << rs1 << " | " << fun3 << " | " << rd << " | " << op << endl;
}

void iType(string input, int pc)
{
	string imm, rs1, fun3, rd, op, str[4];
	int p;
	p = input.find(" ", 0);
	str[0] = input.substr(0, p);
	input = input.substr(p + 1, input.length());
	if (str[0][0] == 'l') {
		p = input.find(",", 0);
		str[1] = input.substr(0, p);
		if(input[p+1]!=' ')
			input = input.substr(p + 1, input.length());
		else
			input = input.substr(p + 2, input.length());
		p = input.find("(", 0);
		str[3] = input.substr(0, p);
		input = input.substr(p + 1, input.length());
		str[2] = input.substr(0, input.length()-1);	
	}
	else {
		for (int i = 1; i < 4; i++) {
			p = input.find(",", 0);
			str[i] = input.substr(0, p);
			input = input.substr(p + 1, input.length());
		}
	}
	if (str[0] == "addi" || str[0] == "jalr"|| str[0] == "lb")
		fun3 = "000";
	else if (str[0] == "lh"|| str[0]=="slli")
		fun3 = "001";
	else if(str[0] == "slti"||str[0]=="lw")
		fun3 = "010";
	else if (str[0] == "sltiu")
		fun3 = "011";
	else if (str[0] == "xori"||str[0]=="lbu")
		fun3 = "100";
	else if (str[0] == "lhu"||str[0]=="srai"||str[0]=="srli")
		fun3 = "101";
	else if (str[0] == "ori")
		fun3 = "110";
	else if (str[0] == "andi")
		fun3 = "111";
	if (str[0] == "jalr")
		op = "1100111";
	else if (str[0][0] == 'l')
		op = "0000011";
	else
		op = "0010011";
	rs1 = toBin(str[2], 5);
	rd = toBin(str[1], 5);
	imm = toBin(str[3], 12);
	cout << imm << " | " << rs1 << " | " << fun3 << " | " << rd << " | " << op << endl;
}

void sType(string input, int pc)
{
	string temp,immf,immb, rs2, rs1, fun3, op, str[4];
	int p;
	p = input.find(" ", 0);
	str[0] = input.substr(0, p);
	input = input.substr(p + 1, input.length());
	p = input.find(",", 0);
	str[1] = input.substr(0, p);
	input = input.substr(p + 1, input.length());
	p = input.find("(", 0);
	str[2] = input.substr(0, p);
	if (str[2][0] == ' ')
		str[2] = str[2].substr(1, str[2].length());
	input = input.substr(p + 1, input.length());
	str[3] = input.substr(0, input.length()-1);
	if (str[0] == "sb")
		fun3 = "000";
	else if (str[0] == "sh")
		fun3 = "001";
	else if (str[0] == "sw")
		fun3 = "010";
	else
		fun3 = "011";
	op = "0100011";
	rs2 = toBin(str[1], 5);
	rs1 = toBin(str[3], 5);
	temp = toBin(str[2], 12);
	immf = temp.substr(0, 7);
	immb = temp.substr(7, 11);
	cout << immf << " | " << rs2 << " | " << rs1 << " | " << fun3 << " | " << immb << " | " << op << endl;
}

void uType(string input, int pc)
{
	string op, imm, rd, str[3];
	int p;
	p = input.find(" ", 0);
	str[0] = input.substr(0, p);
	input = input.substr(p + 1, input.length());
	for (int i = 1; i < 3; i++) {
		p = input.find(",", 0);
		str[i] = input.substr(0, p);
		input = input.substr(p + 1, input.length());
	}
	rd = toBin(str[1],5);
	imm = toBin(str[2],32);
	imm = imm.substr(imm.length()-20, imm.length());
	if (str[0] == "lui")
		op = "0110111";
	else
		op = "0010111";
	cout << imm <<" | " << rd << " | " << op << endl;
}

void ujType(string input,int pc) 
{
	string offset,op, rd, str[3],i20,i10,i11,i19;//
	int p,off;
	p = input.find(" ", 0);
	str[0] = input.substr(0, p);
	input = input.substr(p + 1, input.length());
	p = input.find(",", 0);
	str[1] = input.substr(0, p);
	input = input.substr(p + 1, input.length());
	str[2] = input.substr(0, input.length());
	rd = toBin(str[1], 5);
	offset = findoffset(str[2], pc,21);
	i20 = offset[20];
	i10 = offset.substr(1, 9);
	i11 = offset[11];
	i19 = offset.substr(12, 8);
	op = "1101111";
	cout << i20<<i10<<i11<<i19 <<" | " << rd << " | " << op << endl;
}

void bType(string input,int pc) 
{
	string imm, rs2, rs1, fun3,op, str[4],i12,i10,i4,i11;
	int p;
	p = input.find(" ", 0);
	str[0] = input.substr(0, p);
	input = input.substr(p + 1, input.length());
	for (int i = 1; i < 4; i++) {
		p = input.find(",", 0);
		str[i] = input.substr(0, p);
		input = input.substr(p + 1, input.length());
	}
	if (str[0] == "beq")
		fun3 = "000";
	else if (str[0] == "bne") 
		fun3 = "001";
	else if (str[0] == "blt")
		fun3 = "100";
	else if (str[0] == "bge")
		fun3 = "101";
	else if (str[0] == "bltu")
		fun3 = "110";
	else if (str[0] == "bgeu")
		fun3 = "111";
	op = "1100011";
	rs2 = toBin(str[2], 5);
	rs1 = toBin(str[1], 5);
	imm = findoffset(str[3], pc,13);
	i12 = imm[0];
	i10 = imm.substr(2, 5);
	i11 = imm[1];
	i4 = imm.substr(8, 4);
	cout << i12 << i10 << " | " << rs2 << " | " << rs1 << " | " <<fun3 << " | " << i4 << i11 << " | "<< op << endl;
}

int main()
{
	string input,temp;
	int p,pc;
	getline(cin, input);
	int cou = 0;
	bool push = true;
	while (input[0] != cin.eof()) {
		push = true;
		p = input.find("//", 0); //解決註解
		if (p != input.npos) {
			input = input.substr(0, p);
			if (p == 0) {
				cou--;
				push = false;
			}
		}
		p = input.find(':', 0); //處理label
		if (p != input.npos) {
			label.push_back(input.substr(0, p));
			lbnum.push_back(cou);
			if (p + 1 < input.length()) {//若label與inst未分行
				input = input.substr(p + 1, input.length());
				if (input[0] == ' ')
					input = input.substr(1, input.length());
			}
			else {
				push = false;
				cou--;
			}
		}
		if (push)
			inputall.push_back(input);
		getline(cin, input);
		cou++;
	}
	for (int i = 0; i < inputall.size(); ++i) {
		if (inputall[i].find("ui", 0) != inputall[i].npos) {
			uType(inputall[i],i);
		}
		else if (inputall[i][0] == 'l' || inputall[i].find("i", 0) != inputall[i].npos || inputall[i].find("jalr", 0) != inputall[i].npos) {
			iType(inputall[i],i);
		}
		else if (inputall[i][0] == 's' && inputall[i].find(" ", 0) == 2) {
			sType(inputall[i],i);
		}
		else if (inputall[i][0] == 'b') {
			bType(inputall[i],i);
		}
		else if (inputall[i].find("jal", 0) != inputall[i].npos) {
			ujType(inputall[i],i);
		}
		else {
			rType(inputall[i],i);
		}
	}
}