#include <iostream>
#include <array>
#include <cmath>

using namespace std;

// prototype functions
    char implikasi(char, char);
    char biimplikasi(char, char);
    char dan(char, char);
    char atau(char, char);
    char ekslusif(char, char);
    char negation(char);
    char logicswitch(char, char, char);
    void display(string[], int);
    string notasi(string, string, string);
    void calculate(string[],string, string, string, string, char, int);
    void makeCol(string[], string, string, int);
    void negationCol(string[], string, string, int);


//main functions
int main() {

    cout << "konfigurasi tabel" << endl;
    cout << "masukkan jumlah baris statemen :";
    int rows;
    cin >> rows;

    string table[rows+1];

    while (true)
    {
        cout << endl << "MENU TABEL" << endl;
        cout << "A. buat kolom" << endl;
        cout << "B. hitung operasi boolean" << endl;
        cout << "C. negasi pernyataan" << endl;
        cout << "D. exit" << endl;
        char opsi;
        cout << "<- ";
        cin >> opsi;
        string p, statP, q, statQ;
        if(opsi == 'd' || opsi == 'D') break;
        switch (opsi) {

            case 'a': case 'A':
                cout << "\n-> NEW COLLUMN" << endl;
                cout << "masukkan nama variabel : ";
                cin.get();getline(cin, p);
                cout << "masukkan urutan statemen (contoh: tftf) : ";
                cin >> statP;
                makeCol(table, p, statP, rows);
                break;
            
            case 'b': case 'B':
                cout << "\n-> BOOLEAN ALGEBRA" << endl;
                cout << "masukkan nama variabel operand 1 : ";
                cin.get();getline(cin, p);
                cout << "masukkan nama variabel operand 2 : ";
                getline(cin, q);
                cout << "pilih operasi boolean" << endl;
                cout << "a. implikasi" << endl;
                cout << "b. biimplikasi" << endl;
                cout << "c. dan / and" << endl;
                cout << "d. atau / or" << endl;
                cout << "e. or eksklusif / xor" << endl;
                char operasi;
                cout << "<- ";
                cin >> operasi;
                cout << "masukkan statemen untuk " << p << " (contoh: tftf) : ";
                cin >> statP;
                cout << "masukkan statemen untuk " << q << " (contoh: tftf) : ";
                cin >> statQ;
                calculate(table, p, statP, q, statQ, operasi, rows);
                break;

            case 'c': case 'C':
                cout << "\n-> NEGATION OF STATEMENT" << endl;
                cout << "masukkan nama variabel : ";
                cin.get();getline(cin, p);
                cout << "masukkan urutan statemen (contoh: tftf) : ";
                cin >> statP;
                negationCol(table, p, statP, rows);
                break;

            default:
                cout << "\n !!! error: input opsi tidak valid\n";
                break;
        }
    }



return 0;
}





// UI functions
void display(string table[], int rows) {
    cout << "\nTABLE :";
    for(int i = 0; i <= rows; i++) {
        if(i == 1) cout << endl;
        cout << table[i] << endl;
    }
}

string notasi(char fungsi, string a, string b) {
    if(a.length() > 2) a = '(' + a + ')';
    if(b.length() > 2) b = '(' + b + ')';
    switch (fungsi)
    {
    case 'a': case 'A': return a + "->" + b;
    case 'b': case 'B': return a + "<->" + b;
    case 'c': case 'C': return a + "^" + b;
    case 'd': case 'D': return a + "v" + b;
    case 'e': case 'E': return a + "O" + b;
    }
}

void makeCol(
    string table[],
    string p,
    string statP,
    int rows) {

        // error checking
        if(statP.length() != rows) {
            cout << "\n !!! error: panjang statemen tidak sesuai\n"; return;}
        for(char statement : statP) {
            if(statement != 't' && statement != 'f') {
                cout << "\n !!! error: format statemen tidak valid\n"; return;}
        }

        // code
        table[0] += '\t' + p;

        float varLength = p.length() / 8.0;
        for(int i = 1; i <= rows; i++) {
            table[i] += '\t';
            table[i] += statP[i-1] - 32;
            for(int j = 1; j < ceil(varLength); j++)
            table[i] += '\t';
        }

        display(table, rows);

    }

void negationCol(
    string table[],
    string p,
    string statP,
    int rows) {

        // error checking
        if(statP.length() != rows) {
            cout << "\n !!! error: panjang statemen tidak sesuai\n"; return;}
        for(char statement : statP) {
            if(statement != 't' && statement != 'f') {
                cout << "\n !!! error: format statemen tidak valid\n"; return;}
        }
        // code
        if(p.length() > 1) p = "(" + p + ")";
        table[0] += "\t~" + p;

        for(int i = 1; i <= rows; i++) {
            table[i] += '\t';
            table[i] += negation(statP[i-1]);
        }

        display(table, rows);

    }

void calculate(
    string table[],
    string p, string statP,
    string q, string statQ,
    char fungsi, int rows) {

        // error checking
        if(statP.length() != rows || statQ.length() != rows) {
            cout << "\n !!! error: panjang statemen tidak sesuai\n"; return;}
        for(int i = 0; i < statP.length(); i++) {
            if((statP[i] != 't' && statP[i] != 'f')
            || (statQ[i] != 't' && statQ[i] != 'f')) {
                cout << "\n !!! error: format statemen tidak valid\n"; return;}
        }
        // code
        table[0] += '\t' + notasi(fungsi, p, q);
        float statLength = notasi(fungsi, p, q).length() / 8.0;

        for(int i = 1; i <= rows; i++) {
            table[i] += '\t';
            table[i] += logicswitch(fungsi, statP[i-1], statQ[i-1]);
            for(int j = 1; j < ceil(statLength); j++)
            table[i] += '\t';
        }

        display(table, rows);

    }

// logic functions
char implikasi(char a, char b) {
    if(a == 't' && b == 'f') return 'F';
    return 'T';
}

char biimplikasi(char a, char b) {
    if(a == b) return 'T';
    return 'F';
}

char dan(char a, char b) {
    if(a == 't' && b == 't') return 'T';
    return 'F';
}

char atau(char a, char b) {
    if(a == 'f' && b == 'f') return 'F';
    return 'T';
}

char ekslusif(char a, char b) {
    if(a == b) return 'F';
    return 'T';
}

char negation(char a) {
    return (a == 't') ? 'F' : 'T';
}

char logicswitch(char fungsi, char a, char b) {
    switch (fungsi)
    {
    case 'a': case 'A': return implikasi(a, b);
    case 'b': case 'B': return biimplikasi(a, b);
    case 'c': case 'C': return dan(a, b);
    case 'd': case 'D': return atau(a, b);
    case 'e': case 'E': return ekslusif(a, b);
    }
}