# Proyectos en Vivado

## Desempaquetar proyecto [^1] desde Tool Command Language (`tcl`)

1. Ejecutar el archivo `.bat` el cual referencia al archivo `.tcl`
2. Ir a la subcarpeta creada, y abrir el archivo `.xpr` creado

**Nota**: Toda subcarpeta desde esta posición raíz, junto a sus archivos, será ignorada a la hora de ejecutar comandos de captura de repositorios en git (como `git commit`). Cualquier archivo que necesite para guardar y subir al repositorio deberá guardarlo directamente acá o en carpetas anteriores. Para más detalle, abra [.gitignore](.gitignore).

## Reempaquetar proyecto en `tcl`

1. Ir a "File -> Project -> Write Tcl..."
2. Seleccionar "Copy resources to new project" y "Recreate block designs using Tcl"
3. Presionar OK 

## Crear archivo de diseño de hardware para Vitis

0. (Si no ha sido creado) Buscar el *block design* (`bd`), click derecho y seleccionar "Create HDL wrapper" con las opciones por defecto.
1. Crear *bitstream*.
2. Buscar el ícono de *block design* (`bd`), click derecho y seleccionar "Generate output products" con las opciones por defecto
3. Ir a "File -> Export -> Export Hardware", seleccionar "Include bitstream" y crear archivo `.xsa` [^1].

[^1]: **Nota**: Toda subcarpeta desde esta posición raíz, junto a sus archivos, será ignorada a la hora de ejecutar comandos de captura de repositorios en git (como `git commit`). Cualquier archivo que necesite para guardar y subir al repositorio deberá guardarlo directamente acá o en carpetas anteriores. Para más detalle, abra [.gitignore](.gitignore).