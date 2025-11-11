[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/169Klt-T)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=21584412&assignment_repo_type=AssignmentRepo)
# 📒 Proyecto: Agenda de Contactos en C

## 🧠 Descripción general

Este proyecto consiste en implementar una **agenda de contactos** en lenguaje C, capaz de:
- Agregar contactos con nombre, apellido, día de nacimiento, mes de nacimiento, teléfono y tipo de teléfono.  
- Buscar contactos existentes.  
- Guardar y leer los contactos desde un archivo de texto.  
- Imprimir los contactos en pantalla.  
- Ordenar los contactos alfabéticamente por nombre tanto ascendente como descendente(método Burbuja).

El repositorio está configurado para **autocalificarse automáticamente** en GitHub Classroom usando **GitHub Actions**.  
Cada vez que hagas un `git push`, se compilará el programa, se ejecutarán las pruebas y verás si tu implementación pasa todos los casos.

---

## 🎯 Objetivo educativo

- Aplicar estructuras (`struct`) y arreglos de estructuras en C.  
- Usar funciones y modularización en un programa real.  
- Practicar el manejo de archivos (`fopen`, `fprintf`, `fscanf`).  

---

## ⚙️ Cómo compilar y ejecutar

### 🔹 En tu computadora (Linux, macOS o Windows con MinGW)

1. Abre una terminal en la carpeta del proyecto.  
2. Compila todo el código fuente y los tests:

   ```bash
   gcc src/*.c tests/*.c -o test_agenda
