
# Repositorio de IPs `ip_Repo` para Vivado

## Cómo crear periférico AXI4:

1. Desde Vivado, ir a "Tools -> Create and Package new IP"
2. 
3. 
4. Después de empaquetado el IP, ir a `<nombre de la IP>/drivers/<nombre del driver>/src` y reemplazar el archivo `Makefile` de esa ruta por la ubicada en esta carpeta ([`Makefile`](Makefile))

## Incluir repositorio en proyecto de Vivado

1. Abrir proyecto en Vivado
2. Ir a "Tools -> Settings -> Project Settings -> IP -> Repository" e incluir esta carpeta, o las IPs deseadas.