
# Repositorio de IPs `ip_Repo` para Vivado

## Cómo crear periférico AXI4:

1. Crear un nuevo proyecto de Vivado y seleccionar la placa xc7z010clg400-1.
2. Haga clic en "tools" en la barra superior y seleccione "Create and Package New IP".
3. Seleccione "Create New AXI4 Peripheral" y haga clic en "Next".
4. Asigne un nombre a su periférico, una descripción y la ubicación donde guardara el módulo IP.
5. Seleccione la interfaz AXI4 adecuada (en la mayoría de los casos se utiliza AXI4-Lite, ya que es más fácil de implementar) y seleccione el número de registros a utilizar en el periférico. Lo demás se mantiene por defecto y haga clic en “Finish”.
6. Para ver la IP recién creada haga clic en “IP Catalog” en la barra izquierda y seleccione en la barra derecha User Repository -> AXI Peripheral -> IP creada.
7. Después de empaquetado el IP, ir a `<nombre de la IP>/drivers/<nombre del driver>/src` y reemplazar el archivo `Makefile` de esa ruta por la ubicada en esta carpeta ([`Makefile`](Makefile))

## Incluir repositorio en proyecto de Vivado

1. Abrir proyecto en Vivado
2. Ir a "Tools -> Settings -> Project Settings -> IP -> Repository" e incluir esta carpeta, o las IPs deseadas.
