# Proyecto2
# Sistema de Planilla Hospitalaria

Proyecto de Programación #2 · Programacion I · Universidad Nacional · Cristopher Montero Jimenez · 11 - 11 - 2026

Aplicación de consola en C++ para administrar la planilla de un hospital: empleados (médicos, enfermeros y administrativos), departamentos con sus puestos y comprobantes de pago con salario bruto, deducciones de ley y salario neto. Los datos se guardan en archivos de texto y se cargan automáticamente al iniciar.

## Integrantes

Dylan Madrigal Muñoz |  605050266

Trabajo individual.

## Requisitos

- Compilador de C++
- IDE 

## Cómo compilar y ejecutar

### Con ZinjaI
1. Clonar o descargar el repositorio.
2. En ZinjaI, abrir el proyecto de la carpeta `ProyectoPlanilla`.
3. Verificar que exista la carpeta `data` dentro de `ProyectoPlanilla`, con los archivos `empleados.txt`, `departamentos.txt` y `planilla.txt` (pueden estar vacíos).
4. Compilar y ejecutar con **F9**.

## Guía de uso

Al iniciar, el programa carga automáticamente los tres archivos de `data/`. Después de cada cambio (registrar, actualizar o eliminar) guarda los datos en el archivo correspondiente, así que no hay que guardar manualmente.

### Menú principal

| 1 | Empleados |
| 2 | Departamentos y puestos |
| 3 | Planilla y comprobantes |
| 4 | Salir |

### Empleados
Registrar (médico, enfermero o administrativo), listar, buscar por cédula, actualizar y eliminar.
- La **cédula** debe tener entre 9 y 12 dígitos, sin guiones ni espacios, y no puede repetirse.
- Médico: especialidad y cantidad de guardias. Enfermero: turno y horas nocturnas.
- No se puede eliminar un empleado que ya tiene comprobantes de pago.

### Departamentos y puestos
Registrar, listar (con sus puestos), actualizar y eliminar departamentos; registrar, actualizar y eliminar puestos de un departamento.
- Los códigos no pueden repetirse (departamentos entre sí, y puestos dentro de su departamento).
- Al eliminar un departamento se eliminan también sus puestos.
- No se puede eliminar un departamento que ya tiene comprobantes de pago.

### Planilla y comprobantes
Generar un comprobante indicando código, fecha, cédula del empleado y código del departamento; luego se puede listar, buscar y eliminar.
- La fecha se escribe en formato `AAAA-MM-DD` (ejemplo: `2026-11-08`) y se valida, incluyendo años bisiestos.
- El programa calcula el salario bruto, las deducciones y el salario neto automáticamente.

## Cálculo de la planilla

```
Salario bruto = salario base + pago de horas extra + bonificación del tipo de empleado
Salario neto  = salario bruto − deducciones
Deducciones   = cargas sociales (10,83 %) + impuesto sobre el salario
```

| Pago por hora extra | 1,5 veces el valor de la hora ordinaria |
| Bonificación del médico | ₡20 000 por guardia |
| Bonificación del enfermero | ₡1 500 por hora nocturna |
| Bonificación del administrativo | Ninguna |
| Seguro de Enfermedad y Maternidad (SEM) | 5,50 % |
| Invalidez, Vejez y Muerte (IVM) | 4,33 % |
| Banco Popular | 1,00 % |
| Impuesto sobre el salario | Por tramos mensuales: hasta ₡918 000 exento; de ₡918 000 a ₡1 347 000, 10 %; hasta ₡2 364 000, 15 %; hasta ₡4 727 000, 20 %; más de ₡4 727 000, 25 % |

Supuestos y simplificaciones: los montos de guardia y hora nocturna son valores definidos para este proyecto; el impuesto se calcula sobre el salario bruto.

## Archivos de datos

Los archivos de la carpeta `data/` guardan un dato por línea:

- `empleados.txt`: tipo (`MEDICO`, `ENFERMERO` o `ADMINISTRATIVO`), cédula, nombre, salario base, horas extra y, según el tipo, especialidad y guardias, o turno y horas nocturnas.
- `departamentos.txt`: código, nombre, cantidad de puestos y, por cada puesto, código, nombre y salario.
- `planilla.txt`: código, fecha, salario bruto, deducciones, salario neto, cédula del empleado y código del departamento.

Si se editan a mano, deben respetar este orden; de lo contrario el programa puede no cargarlos.

## Diseño

![Diagrama UML]

### Clases principales
- Empleado (abstracta) con `Medico`, `Enfermero` y `Administrativo`: herencia y polimorfismo mediante `calcularBonificacion()`.
- Departamento y Puesto: composición (un departamento contiene sus puestos y los puestos no existen sin él).
- ComprobantePago: agregación (apunta a un `Empleado` y a un `Departamento` sin ser su dueño).
- Listas dinámicas manuales (`ListaEmpleados`, `ListaPuestos`, `ListaDepartamentos`, `ListaComprobantes`) con sus nodos: listas enlazadas simples, sin usar contenedores de la biblioteca estándar.
- CalculadoraPlanilla: todos los cálculos de salario y deducciones.
- PersistenciaArchivos: lectura y escritura de los archivos de texto.
- Validaciones: cédula, textos, montos y fechas.
- GestorEmpleados, GestorDepartamentos, GestorPlanilla: reglas de negocio de cada área; asociación con las listas, la persistencia y las validaciones.

Las clases de entidades y los gestores no usan `cin` ni `cout`. toda la interacción con el usuario está en `main.cpp`.

### Principios SOLID aplicados
- Responsabilidad única (SRP):cada clase tiene un solo trabajo (calcular, validar, guardar, gestionar).
- Abierto/cerrado (OCP): agregar un nuevo tipo de empleado no requiere modificar `CalculadoraPlanilla`, solo crear una nueva clase hija.
- Sustitución de Liskov (LSP): cualquier hija de `Empleado` puede usarse donde se espera un `Empleado`.

### Manejo de memoria
Cada lista es dueña de sus elementos y los libera en su destructor. `ComprobantePago` no borra al empleado ni al departamento que apunta. 
