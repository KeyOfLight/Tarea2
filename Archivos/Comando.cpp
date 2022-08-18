#include "Comando.h"

void Comando::identificacionCMD(Parametros p){
    if(p.Comando=="crear"){ // Se identifica el tipo de comando
        if(p.Tamano != " " && p.Dimensional != " "){ // Se validan los parametros para el comando
            crearArchivo(p.Tamano,p.Dimensional);
        }else{
            cout << "Error creando Disco: Parametros obligatorios no definidos." << endl;
        }
    }else if(p.Comando=="escribir"){ // Se identifica el tipo de comando
        if(p.Id != " " && p.Nombre != " " && p.Telefono != " " && p.Direccion != " " && p.X != " "){ // Se validan los parametros para el comando
            escribir(p.Id,p.Nombre,p.Telefono,p.Direccion,p.X);
        }else{
            cout << "Error escribiendo en Disco: Parametros obligatorios no definidos." << endl;
        }
    }else if(p.Comando=="vertodo"){ // Se identifica el tipo de comando
        vertodo();
    }else if(p.Comando=="verx"){ // Se identifica el tipo de comando
        if(p.X != " "){ 
            verX(p.X);
        }else{
            cout << "Error visualizando x registro: Parametros obligatorios no definidos." << endl;
        }
    }else if(p.Comando=="eliminarx"){ // Se identifica el tipo de comando
        if(p.X != " "){ // Se validan los parametros para el comando
            eliminarX(p.X);
        }else{
            cout << "Error elimando x registro: Parametros obligatorios no definidos." << endl;
        }
    }else if(p.Comando=="execut"){ // Se identifica el tipo de comando
        if(p.Direccion != " "){ // Se validan los parametros para el comando ------------------------TERMINAR EL COMANDO
            mkdiscCreation(p.Direccion);
        }else{
            cout << "Error elimando x registro: Parametros obligatorios no definidos." << endl;
        }
    }               
}

void Comando::mkdiscCreation(string dir){
    FILE *archivo_binario;
    Ejemplo ejm;
    int cont = 0;
    archivo_binario = fopen("Ejemplo3.dsk", "rb+");
    while (!feof(archivo_binario)){
        // Movimiento de puntero y lectura de Struct en archivo binario 
        fseek(archivo_binario,cont*sizeof(Ejemplo), SEEK_SET);
        fread(&ejm, sizeof(ejm), 1, archivo_binario);
        mostrar_struct(ejm);
        cont++;
    }
    cont = 0;
    fclose(archivo_binario);
}




void Comando::crearArchivo(string tam, string dim){
    // Calculo Tamaño del Archivo
    int size_file = 0, tamano = atoi(tam.c_str());
    char dimen = dim.at(0);
    if (dimen == 'k' || dimen == 'K')
    {
        size_file = tamano;
    }
    else if (dimen == 'm' || dimen == 'M')
    {
        size_file = tamano * 1024;
    }
    else if (dimen == 'g' || dimen == 'G')
    {
        size_file = tamano * 1024 * 1024;
    }

    // Preparacion Bloque
    char bloque[1024];
    for (int i = 0; i < 1024; i++)
    {
        bloque[i] = '\0';
    }

    // Escritura de Bloque en Archivo
    int limite = 0;
    FILE *archivo_binario;
    archivo_binario = fopen("Ejemplo3.dsk", "w");
    while (limite != size_file)
    {
        fwrite(&bloque, 1024, 1, archivo_binario);
        limite++;
    }
    fclose(archivo_binario);
}

void Comando::escribir(string id, string nombre, string tel, string dir, string x){
    FILE *archivo_binario;
    Ejemplo ejm;
    string nm = "", direc = "";
    int registros = atoi(x.c_str());

    archivo_binario = fopen("Ejemplo3.dsk", "rb+");
    for (int i = 0; i < registros; i++){
        // Seteo de parametros en Struct
        ejm.id = i + atoi(id.c_str());
        nm = nombre;
        nm += " " + to_string(ejm.id);
        strcpy(ejm.nombre, nm.c_str());
        ejm.telefono = (rand() + i) + atoi(tel.c_str());
        direc = dir;
        direc += " " + to_string(ejm.id);
        strcpy(ejm.direccion, direc.c_str());
        // Movimiento de puntero y escritura de Struct en archivo binario 
        fseek(archivo_binario, i * sizeof(Ejemplo), SEEK_SET);
        fwrite(&ejm, sizeof(ejm), 1, archivo_binario);
        nm = "";
        direc = "";
    }
    fclose(archivo_binario);
}

void Comando::vertodo(){
    FILE *archivo_binario;
    Ejemplo ejm;
    int cont = 0;
    archivo_binario = fopen("Ejemplo3.dsk", "rb+");
    while (!feof(archivo_binario)){
        // Movimiento de puntero y lectura de Struct en archivo binario 
        fseek(archivo_binario,cont*sizeof(Ejemplo), SEEK_SET);
        fread(&ejm, sizeof(ejm), 1, archivo_binario);
        mostrar_struct(ejm);
        cont++;
    }
    cont = 0;
    fclose(archivo_binario);
}

void Comando::verX(string x){
    FILE *archivo_binario;
    Ejemplo ejm;
    int xreg = atoi(x.c_str()) - 1;
    archivo_binario = fopen("Ejemplo3.dsk", "rb+");
    // Movimiento de puntero y lectura de Struct en archivo binario 
    fseek(archivo_binario, xreg * sizeof(Ejemplo), SEEK_SET);
    fread(&ejm, sizeof(ejm), 1, archivo_binario);
    mostrar_struct(ejm);
    fclose(archivo_binario);
}

void Comando::eliminarX(string x){
    FILE *archivo_binario;
    Ejemplo ejm;
    ejm.id = 0;
    strcpy(ejm.nombre, " ");
    ejm.telefono = 0;
    strcpy(ejm.direccion, " ");
    int xreg = atoi(x.c_str()) - 1;
    archivo_binario = fopen("Ejemplo3.dsk", "rb+");
    // Movimiento de puntero y escritura de Struct en archivo binario
    fseek(archivo_binario, xreg * sizeof(Ejemplo), SEEK_SET);
    fwrite(&ejm, sizeof(ejm), 1, archivo_binario);
    mostrar_struct(ejm);
    fclose(archivo_binario);
}

void Comando::mostrar_struct(Ejemplo ejm){
    if(ejm.id > 0 && ejm.nombre != "" && ejm.telefono > 0 && ejm.direccion != ""){
        cout << "ID: ";
        cout << ejm.id;
        cout << ", Nombre: ";
        cout << ejm.nombre;
        cout << ", Telefono: ";
        cout << ejm.telefono;
        cout << ", Direccion: ";
        cout << ejm.direccion << endl;
    }
}