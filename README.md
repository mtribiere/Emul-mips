# Emul-mips
Le projet d'émulateur MIPS de CS351

/!\ IMPORTANT : Les instructions contenant des labels, ainsi que les chargements dans la mémoire principale n'ont, par manque de temps, pas pu être testées pleinement dans le mode de convertion. Elles ne fourniront de ce fait qu'une simulation de leur comportement dans une execution.

# Instructions supportées : 
```
ADD
ADDI
SUB
AND
OR
XOR
BEQ
BNE
LW
SW
```

# Compilation et utilisation
```
$> make clean && make
```

## Mode 
```
$> Mode d'execution classique : ./emul-mips <fichier d'entrée> <fichier de sortie>
$> Mode d'execution pas à pas : ./emul-mips <fichier d'entrée> <fichier de sortie> --pas
$> Mode interactif : ./emul-mips

```
