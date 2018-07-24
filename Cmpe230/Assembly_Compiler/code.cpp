#include<bits/stdc++.h>

using namespace std;
// raw input
vector<string> inp;
// temporary string to store each line to process
string cur_row;
// to store postfix version of lines
vector<string> postfix_inp;
// temporary string to store postfix version of each line
string cur_postfix;
// to map each variable to a unique number
map<string,int> vars;
// to store extra variables to be used in multiplication
vector<string> mul_vars;
// to store extra variables to be used in power operation
vector<string> pow_vars;
// to check whether an error has been detected before in a line
vector<bool> error;
vector<int> line_no;

// to determine if there is a syntax error because of unbalanced paranthesis
int paranthesis;
// to determine if there is an error in a line
int line_error;
// to determine if there is an error in general
int error_flag;

// current index in the line we are processing
int cnt;
// count to make loop labels distinct
int loop_cnt;
// count to make skip labels distinct
int skip_cnt;
// count to make pow labels distinct
int pow_cnt;
// to count number of variables mapped
int var_cnt;

string var_name(string s) {
    stringstream ss;
    ss << vars[s];
    string str = ss.str();
    return "var" + str;
}

// function to read the file
void read() {

    string str;

    int i=0;

    while(getline(cin,str)) {
        i++;
        if(str.size()) {
            inp.push_back(str);
            line_no.push_back(i);
        }
    }

    error.resize(inp.size(), false);
}

// function to delete empty characters
// and to check some errors
void edit() {

    for(int i=0; i<inp.size(); i++) {

        // checking left-hand side of an assignment operation
        if(inp[i].find('=')!=-1) {

            if(inp[i].find('+')!=-1 && inp[i].find('+')<inp[i].find('=')) {
                error[i] = true;
                error_flag = 1;
            }

            if(inp[i].find('*')!=-1 && inp[i].find('*')<inp[i].find('=')) {
                error[i] = true;
                error_flag = 1;
            }

            if(inp[i].find('(')!=-1 && inp[i].find('(')<inp[i].find('=')) {
                error[i] = true;
                error_flag = 1;
            }

            if(inp[i].find(')')!=-1 && inp[i].find(')')<inp[i].find('=')) {
                error[i] = true;
                error_flag = 1;
            }

            int index = 0;

            while(index < inp[i].size() && inp[i][index]==' ')
                index++;

            while(index < inp[i].size() && inp[i][index]!=' ')
                index++;

            if(index < inp[i].find('=')) {
                while(index < inp[i].size() && inp[i][index]==' ')
                    index++;

                if(inp[i][index] != '=') {
                    error[i] = true;
                    error_flag = 1;
                }
            }
        }

        paranthesis=0;
        string temp = "";

        for(int j=0; j<inp[i].size(); j++) {
            if(inp[i][j] != ' ')
                temp += inp[i][j];

            if(inp[i][j] == '(')
                paranthesis++;
            else if(inp[i][j] == ')')
                paranthesis--;

            if(paranthesis<0) {
                error[i] = true;
                error_flag=1;
            }
        }

        if(paranthesis != 0) {
            error[i] = true;
            error_flag = 1;
        }

        // if a line ends with an operator
        if(temp.substr(temp.size()-1,1)=="+" || temp.substr(temp.size()-1,1)=="*" || temp.substr(temp.size()-1,1)=="=" ){
            error[i] = true;
            error_flag=1;
        }

        // less than two parameters for an operator
        if(temp.find("++")!=-1 || temp.find("+*")!=-1 || temp.find("*+")!=-1 || temp.find("**")!=-1 ||
           temp.find("(+")!=-1 || temp.find("(*")!=-1 || temp.find("+)")!=-1 || temp.find("*)")!=-1 || temp.find("()")!=-1) {
            error[i] = true;
            error_flag = 1;
        }

        inp[i] = temp;
    }

}

void factor();
void term();
void expr();
void moreterms();
void morefactors();

void factor() {

    // if an expression starts with a paranthesis
    if(cur_row.size() > cnt && cur_row[cnt] == '(') {
        cnt++;
        expr();

        // error handling for unmatched paranthesis
        if(cur_row.size() <= cnt || cur_row[cnt]!=')') {
            line_error=1;
        }
        cnt++;
    }

    // if it is a number
    else if(cur_row.size() > cnt && isdigit(cur_row[cnt])) {

        cur_postfix += " ";
        while(cur_row.size() > cnt && (isdigit(cur_row[cnt]) ||
                (cur_row[cnt] >= 'a' && cur_row[cnt] <= 'f') ||
                (cur_row[cnt] >= 'A' && cur_row[cnt] <= 'F'))) {
            cur_postfix += cur_row[cnt++];
        }

        // if a number ends with an unknown character
        if(cur_row.size() > cnt && cur_row[cnt]!= '+' && cur_row[cnt]!= '*' &&
                cur_row[cnt]!= ',' && cur_row[cnt]!= ')') {
            line_error = 1 ;
        }
    }

    // if it is a power operation
    else if(!cur_row.substr(cnt,4).compare("pow(")) {

        cnt += 4;
        expr();

        // if there is no comma between expressions in power operation
        if(cur_row.size() <= cnt || cur_row[cnt]!=',') {
            line_error=1;
        }
        cnt++;
        expr();

        // if power operation does not end with a closing paranthesis
        if(cur_row.size() <= cnt || cur_row[cnt]!=')') {
            line_error=1;
        }
        cnt++;
        cur_postfix += " ^";
    }

    // if it is a variable
    else {

        cur_postfix += " ";

        string new_var = "";

        while(cnt < cur_row.size() && cur_row[cnt] != '+' && cur_row[cnt] != '*' && cur_row[cnt] != ',' && cur_row[cnt]!=')') {
            new_var += cur_row[cnt];
            cur_postfix += cur_row[cnt++];
        }

        if(!vars[new_var]) {
            vars[new_var]=++var_cnt;
        }
    }
}

void morefactors() {

    if(cur_row.size() > cnt && cur_row[cnt] == '*') {
        cnt++;
        factor();
        cur_postfix += " *";
        morefactors();
    }
}

void moreterms() {

    if(cur_row.size() > cnt && cur_row[cnt] == '+') {
        cnt++;
        term();
        cur_postfix += " +";
        moreterms();
    }

}

void term() {
    factor();
    morefactors();
}

void expr() {
    term();
    moreterms();
}
// to convert postfix version
void to_postfix() {

    for(int i=0; i<inp.size(); i++) {

        if(error[i]) {
            cout << "Line " << line_no[i]<< ": Syntax Error" << endl;
            return;
        }

        line_error=0;
        cur_postfix = "";
        cur_row = inp[i];

        cnt = 0;

        // if there is an equal sign
        if(inp[i].find("=") != -1)
        {
            cnt = inp[i].find("=")+1;

            if(!vars[inp[i].substr(0,cnt-1)])
                vars[inp[i].substr(0,cnt-1)]=++var_cnt;
        }

        expr();

        cur_postfix += " ";
        postfix_inp.push_back(cur_postfix);

        // if there is an error in line
        if(line_error) {
            cout << "Line " << line_no[i] << ": Syntax Error" << endl;
            error_flag=1;
            return;
        }
    }
}

// multiplication process
void multiply() {

    cout << "\npop " << mul_vars[0] << endl;
    cout << "pop " << mul_vars[1] << endl;
    cout << "pop " << mul_vars[2] << endl;
    cout << "pop " << mul_vars[3] << endl;

    cout << "mov ax," << mul_vars[1] << endl;
    cout << "mul " << mul_vars[3] << endl;
    cout << "push ax" << endl;

    cout << "mov bx,dx" << endl;
    cout << "mov ax," << mul_vars[1] << endl;
    cout << "mul " << mul_vars[2] << endl;
    cout << "add bx,ax" << endl;

    cout << "mov ax," << mul_vars[0] << endl;
    cout << "mul " << mul_vars[3] << endl;
    cout << "add bx,ax" << endl;

    cout << "push bx" << endl;
}

void to_assembly() {

    cout << "jmp start\n" << endl;

    // variables to be used in pow process
    for(int i=0; i<vars.size()+3; i++) {

        stringstream ss;
        ss << i;

        if(vars.find("pow_var"+ss.str())==vars.end()) {

            pow_vars.push_back("pow_var"+ss.str()+"left");
            pow_vars.push_back("pow_var"+ss.str()+"right");

            cout << "pow_var" << i << "left dw 0" << endl;
            cout << "pow_var" << i << "right dw 0" << endl;

            if(pow_vars.size() == 6)
                break;
        }
    }

    // variables to be used in multiplication process
    for(int i=0; i<vars.size()+2; i++) {

        stringstream ss;
        ss << i;

        if(vars.find("mul_var"+ss.str())==vars.end()) {

            mul_vars.push_back("mul_var"+ss.str()+"left");
            mul_vars.push_back("mul_var"+ss.str()+"right");

            cout << "mul_var" << i << "left dw 0" << endl;
            cout << "mul_var" << i << "right dw 0" << endl;

            if(mul_vars.size() == 4)
                break;
        }
    }

    // declaring variables and setting them to be zero
    for(map<string,int>::iterator it=vars.begin(); it!=vars.end(); it++) {

        cout << var_name(it->first) << "left dw 0" << endl;
        cout << var_name(it->first) << "right dw 0" << endl;
    }

    cout << "\nstart:\n" << endl;

    // to process each postfix line
    for(int i=0; i<postfix_inp.size(); i++) {

        if(inp[i].find("=") != -1) {
            string temp = inp[i].substr(0,inp[i].find("="));
            cout << "\npush offset " << var_name(temp) << "right" << endl;
            cout << "push offset " << var_name(temp) << "left" << endl;
        }

        int ind = 1;
        while(ind < postfix_inp[i].size()) {

            cout << endl;

            int next = postfix_inp[i].find(" ",ind);
            string temp = postfix_inp[i].substr(ind, next-ind);

            if(temp[0] == '+') {
                puts("");
                puts("pop ax");
                puts("pop bx");
                puts("pop cx");
                puts("pop dx");
                puts("add bx,dx");
                cout << "jnc skip" << ++skip_cnt << endl;
                puts("add ax,1");
                cout << "skip" << skip_cnt << ":" << endl;
                puts("add ax,cx");
                puts("push bx");
                puts("push ax");
            }

            else if(temp[0] == '*') {
                multiply();
            }

            else if(temp[0] == '^') {
                cout << "mov " << pow_vars[4] << ",0" << endl;
                cout << "mov " << pow_vars[5] << ",1" << endl;

                cout << "pop " << pow_vars[0] << endl;
                cout << "pop " << pow_vars[1] << endl;
                cout << "pop " << pow_vars[2] << endl;
                cout << "pop " << pow_vars[3] << endl;

                cout << "pow_loop" << ++pow_cnt << ":" << endl;

                cout << "mov bx," << pow_vars[1] << endl;
                cout << "and bx,1" << endl;
                cout << "cmp bl,0" << endl;
                cout << "jz pow_skip" << pow_cnt << endl;

                cout << "push " << pow_vars[5] << endl;
                cout << "push " << pow_vars[4] << endl;
                cout << "push " << pow_vars[3] << endl;
                cout << "push " << pow_vars[2] << endl;

                multiply();

                cout << "pop " << pow_vars[4] << endl;
                cout << "pop " << pow_vars[5] << endl;

                cout << "pow_skip" << pow_cnt << ":" << endl;

                cout << "shr " << pow_vars[1] << ",1" << endl;

                cout << "mov bx," << pow_vars[0] << endl;
                cout << "and bx,1" << endl;
                cout << "cmp bl,0" << endl;
                cout << "jz pow2_skip" << pow_cnt << endl;

                cout << "add " << pow_vars[1] << ",8000h" << endl;

                cout << "pow2_skip" << pow_cnt << ":" << endl;

                cout << "shr " << pow_vars[0] << ",1" << endl;

                cout << "push " << pow_vars[3] << endl;
                cout << "push " << pow_vars[2] << endl;
                cout << "push " << pow_vars[3] << endl;
                cout << "push " << pow_vars[2] << endl;

                multiply();

                cout << "pop " << pow_vars[2] << endl;
                cout << "pop " << pow_vars[3] << endl;

                cout << "mov bx," << pow_vars[0] << endl;
                cout << "add bx," << pow_vars[1] << endl;
                cout << "cmp bx,0" << endl;
                cout << "jz endloop" << pow_cnt << endl;

                cout << "jmp pow_loop" << pow_cnt << endl;
                cout << "endloop" << pow_cnt << ":" << endl;

                cout << "push " << pow_vars[5] << endl;
                cout << "push " << pow_vars[4] << endl;
            }

            else {
                // if temp is a variable
                if(!isdigit(temp[0])) {
                    cout << "push " << var_name(temp) << "right" << endl;
                    cout << "push " << var_name(temp) << "left" << endl;
                }
                    // if temp is a number
                else {
                    // number has 4 or less hex digits
                    if(temp.size()<=4) {
                        cout << "push 0" << temp << "h" << endl;
                        cout << "push 0" << endl;
                    }
                    // number has more than 4 hex digits
                    else {
                        cout << "push 0" << temp.substr(temp.size()-4, 4) << "h" << endl;
                        cout << "push 0" << temp.substr(0, temp.size()-4) << "h" << endl;
                    }
                }
            }

            ind = next+1;
        }

        if(inp[i].find("=") != -1) {

            puts("\npop cx");
            puts("pop dx");
            puts("pop bx");
            puts("mov [bx],cx");
            puts("pop bx");
            puts("mov [bx],dx");
        }

        // to print the line if there is no equal sign
        else {
            for(int j=0; j<=1; j++) {
                puts("pop ax");
                puts("mov bx,ax");
                puts("mov cx,4h");
                puts("mov ah,2h");
                cout << "loop" << ++loop_cnt << ":\n";
                puts("mov dx,0fh");
                puts("rol bx,4h");
                puts("and dx,bx");
                puts("cmp dl,0ah");
                cout << "jae hexdigit" << loop_cnt << endl;
                puts("add dl,'0'");
                cout << "jmp output" << loop_cnt << endl;
                cout << "hexdigit" << loop_cnt << ":\n";
                puts("add dl,'A'");

                puts("sub dl,0ah");
                cout << "output" << loop_cnt << ":\n";
                puts("int 21h");
                puts("dec cx");
                cout << "jnz loop" << loop_cnt << endl;
            }
            puts("\npush 10d");
            puts("pop dx");
            puts("mov ah,02h");
            puts("int 21h");
        }
    }

    cout << "\nint 20h" << endl;
}

int main(int argc, char* argv[]) {

    freopen(argv[1],"r",stdin);
    string output = string(argv[1]).substr(0, string(argv[1]).find('.'));
    freopen((output+".asm").c_str(),"w",stdout);
    read();
    edit();
    to_postfix();

    if(!error_flag)
        to_assembly();
}
