#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
vector<char> letras = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
void comprobar_completa(string& texto, string& clave) {
    int c = clave.length();
    int t = texto.length();
    string result="";
    for (int i = 0, j = 0; i < t; i++) {
        if (texto[i] != ' ') {
            result += clave[j % c];
            j++;
        } else {
            result += ' ';
        }
    }
    clave=result;
}

int posicion(char x) {
    for (int i = 0; i < letras.size(); i++) {
        if (letras[i] == x) {
            return i;
        }
    }
    return -1;
}

string codificar(string& txt, string& clave){
    string result = "";
    for (int i = 0; i < txt.length(); i++) {
        int n = posicion(tolower(txt[i]));
        if (n != -1) {
            n = (n + posicion(tolower(clave[i]))) % 26;
            if (isupper(txt[i])) {
                result += toupper(letras[n]);
            } else if (islower(txt[i])) {
                result += tolower(letras[n]);
            }
        } else {
            result += txt[i];
        }
    }
    return result;
}
string decodificar(string& txt, string& clave){
    string result = "";
    for (int i = 0; i < txt.length(); i++) {
        int n = posicion(tolower(txt[i]));
        if (n != -1) {
            n = (n - posicion(tolower(clave[i])) + 26) % 26; 
            if (isupper(txt[i])) {
                result += toupper(letras[n]);
            } else if (islower(txt[i])) {
                result += tolower(letras[n]);
            }
        } else {
            result += txt[i];
        }
    }
    return result;
}

string leerArchivo(const string &filepath) {
    ifstream entr(filepath);
    string frase, linea;
    while (getline(entr, linea)) {
        frase += linea;
    }
    entr.close();
    return frase;
}

void imprimirMatriz(const vector<vector<char>>& matriz, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

string generarMatrizCifrar(vector<vector<char>>& matriz, int f, int c, string& txt,string& clave) {
    string result="";
    string claveordenada=clave;
    sort(claveordenada.begin(),claveordenada.end());
    int index=0;
    matriz=vector<vector<char>>(f,vector<char>(c,'$'));

    for(int i=0; i<f; i++){
        for(int j=0; j<c; j++){
            if(index==txt.length()){
                break; 
            }
            else{
                matriz[i][j]=txt[index];
                index++;
            }
        }
    }
    imprimirMatriz(matriz,f,c);
    vector<vector<char>> matriz2(f, vector<char>(c, '$'));
    for (int j = 0; j < c; j++) {
        int originalRow = clave.find(claveordenada[j]);
        for (int i = 0; i < f; i++) {
            matriz2[i][j] = matriz[i][originalRow];
        }
    }
    for(int j=0; j<c; j++){
        for(int i=0; i<f; i++){
            result+=matriz2[i][j];
        }
    }
    cout << "Matriz2:" << endl;
    imprimirMatriz(matriz2, f, c);
    return result;
}

string descifrar(vector<vector<char>>& matriz, int f, int c,string cifrado, string clave) {
    string resultado = "";
    string claveOrdenada = clave;
    sort(claveOrdenada.begin(), claveOrdenada.end());
    matriz=vector<vector<char>>(f,vector<char>(c,'$'));
    vector<vector<char>> matrizCifrado(f, vector<char>(c, '$'));
    int index=0;
    for(int j=0; j<c; j++){
        for(int i=0; i<f; i++){
            matriz[i][j]=cifrado[index];
            index++;
        }
    }
    for(int j=0; j<c; j++){
        int OriginalRow=clave.find(claveOrdenada[j]);
        for(int i=0; i<f; i++){
            matrizCifrado[i][OriginalRow]=matriz[i][j];
        }
    }
    imprimirMatriz(matrizCifrado,f,c);
    for(int i=0; i<f; i++){
        for(int j=0; j<c; j++){
            if(matrizCifrado[i][j]!='$'){
            resultado+=matrizCifrado[i][j];
            }
        }
    }
    return resultado;
    
}
string comprobar_clave2(string clave, int c){
    string result="";
    for(int i=0; i<c; i++){
        result+=clave[i%clave.length()];
    }
    return result;
}

string encriptar(const string &txt, int k) {
    string result = "";
    for (int i = 0; i < txt.length(); i++) {
        int n = posicion(tolower(txt[i]));
        if (n != -1) {
            n = (n + k) % 26;
            if (isupper(txt[i])) {
                result += toupper(letras[n]);
            } else if (islower(txt[i])) {
                result += tolower(letras[n]);
            }
        } else {
            result += txt[i];
        }
    }
    return result;
}
int main(){
    string texto,clave;
    string filepathEntrada = "C:\\Users\\User\\Desktop\\Cesar\\entrada_vinegere.txt";
    texto=leerArchivo(filepathEntrada);
    cout<<"El texto es: "<<texto<<endl;
    cout<<"Ingrese la clave"<<endl;
    getline(cin,clave);
    int k=clave.length();
    string new_clave=encriptar(clave,k);
    cout<<"Nueva clave para el cifrado vinegre:" <<new_clave<<endl;
    comprobar_completa(texto,new_clave);
    string msjcodi=codificar(texto,new_clave);
    cout<<new_clave<<endl;
    cout<<"Texto codificado: "<<msjcodi<<endl;
    int c=k;
    int f;
    if (msjcodi.length() % c == 0) {
        f = msjcodi.length() / c;
    } else {
        f = msjcodi.length() / c + 1;
    }
    vector<vector<char>> matriz_cifrado;
    string clave2=comprobar_clave2(new_clave,c);
    string codificado = generarMatrizCifrar(matriz_cifrado, f, c, msjcodi, clave2);
    cout << "Mensaje codificado: " << codificado << endl;
    string descifrado = descifrar(matriz_cifrado, f, c, codificado, clave2);
    cout << "Mensaje descifrado: " << descifrado << endl;
    string decodificacion_final=decodificar(descifrado,new_clave);
    cout<<decodificacion_final<<endl;
    return 0;
}
