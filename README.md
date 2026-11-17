# Proyecto 2
# Sistema de Planilla Hospitalaria

Proyecto de Programación #2 · Programación I · Universidad Nacional 
Cristopher Montero Jiménez · 
Este proyecto consiste en un programa desarrollado en C++ para administrar la planilla de un hospital. Permite registrar empleados, organizar departamentos y puestos, y generar comprobantes de pago.
El programa también realiza los cálculos de salarios, bonificaciones y deducciones. Además, guarda la información en archivos de texto para que los datos no se pierdan al cerrar el programa.

#Integrante
Dylan Madrigal Muñoz | 605050266
## Cómo ejecutar el programa
Con ZinjaI
1. Descargar o clonar el repositorio.
2. Abrir el proyecto desde la carpeta ProyectoPlanilla.
3. Verificar que exista la carpeta data con los archivos necesarios.
4. Compilar y ejecutar

## Guía de uso
Al iniciar el programa, se muestra un menú principal con las siguientes opciones:
Empleados
Departamentos y puestos
Planilla y comprobantes
Salir

# Empleados
Permite registrar, consultar, modificar y eliminar empleados. Se pueden agregar médicos, enfermeros y administrativos 

#Departamento y puestos
permite registrar y administrar los diferentes departamentos del hospital y los puestos que pertenecen a cada uno.

#Planilla y comprobantes
Permite generar, consultar y eliminar comprobantes de pago. El programa calcula automáticamente el salario bruto, las deducciones y el salario neto.

# El calculo de salarios
Para calcular los pagos se toma en cuenta el salario base, las horas extra y las bonificaciones correspondientes a cada tipo de empleado.
También se aplican las deducciones de ley de Costa Rica:
- SEM: 5,50 %.
- IVM: 4,33 %.
- Banco Popular: 1 %.
- Impuesto sobre el salario según el monto recibido.

# los archivos de datos
La información del programa se guarda en tres archivos de texto ubicados en la carpeta `data`:

empleados.txt: información de los empleados.
departamentos.txt: información de los departamentos y puestos.
planilla.txt: comprobantes de pago.
