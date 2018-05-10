# sturdy-happiness

## Options du makefile
    all     Compile le jeu
    play    Lance le jeu dans l'émulateur fceux
    clean   Efface tous les fichiers issus de la compilation

## Première utilisation
Ce dépôt ne se suffit pas à lui-même :

Il faut ajouter un dossier _./lib/_ contenant les fichiers :
- _nes.lib_ (dans _ftp://ftp.musoftware.de/pub/uz/cc65/cc65-nes-2.13.3-1.zip_)
- _c64.lib_ (dans _ftp://ftp.musoftware.de/pub/uz/cc65/cc65-c64-2.13.3-1.zip_)

Il faut ajouter un dossier _./tools/_ contenant :
- un répertoire _./cc65/_ contenant le compilateur obtenu comme suit :
    - Créer un répertoire _./cc65/_ dans le répertoire _./tools/_
    - Dézipper _ftp://ftp.musoftware.de/pub/uz/cc65/cc65-win32-2.13.3-1.zip_
    - Placer les fichiers obtenus dans le répertoire _./cc65/_
- un répertoire _./make/_ contenant le programme make obtenu comme suit (pour Windows) :
    - Créer un répertoire _./make/_ dans le répertoire tools/
    - Dézipper _http://gnuwin32.sourceforge.net/downlinks/make-bin-zip.php_
    - Placer les fichiers obtenus dans le répertoire _./make/_
    - Dézipper _http://gnuwin32.sourceforge.net/downlinks/make-dep-zip.php_
    - Placer les fichiers obtenus dans le répertoire _./make/_ en validant la fusion des dossiers

Les répertoires _lib_ et _tools_ peuvent également être des liens symboliques.

Tout ceci est assez sale. Je l'arrangerai plus tard.

### Fichiers externes à récupérer
#### Tous OS
    ftp://ftp.musoftware.de/pub/uz/cc65/cc65-nes-2.13.3-1.zip
    ftp://ftp.musoftware.de/pub/uz/cc65/cc65-c64-2.13.3-1.zip
    ftp://ftp.musoftware.de/pub/uz/cc65/cc65-win32-2.13.3-1.zip

Les versions 2.7 et 3.4 de python sont compatibles pour fceux\_symbols.py.

#### Windows
    http://gnuwin32.sourceforge.net/downlinks/make-bin-zip.php
    http://gnuwin32.sourceforge.net/downlinks/make-dep-zip.php

#### Linux
Les fichiers _lib/c64.lib_ et _lib/nes.lib_ sont à utiliser tels quels.

Pour les fichiers _tools/cc65/bin/*_ (_ca65.exe_, _cc65.exe_, _ld65.exe_), il faut lancer ceux de _cc65-win32-2.13.3-1.zip_ avec _wine_.

Exemple : fichier _tools/cc65/bin/ca65_ (permissions +x)

    #! /bin/sh
    wine $(PATH_TO_CC65)/cc65-win32/bin/ca65.exe $*

Utiliser fceux pour Linux (de préférence, compiler les sources, la version packagée semble un peu vieille).

FCEUX pour windows fonctionne mal pour ce jeu... dommage, c'est la seule version avec outils de debug.

### Arborescence minimale de compilation
    .
    ├── animations
    ├── compile
    │   ├── asm
    │   │   └── animations
    │   └── obj
    │       └── animations
    ├── debug
    ├── fceux_symbols.py
    ├── graphics
    ├── include
    ├── lib
    │   ├── c64.lib
    │   └── nes.lib
    ├── link.ld
    ├── makefile
    ├── src
    └── tools
        ├── cc65
        │   └── bin
        │       ├── ca65
        │       ├── cc65
        │       └── ld65
        ├── fceux
        │   └── fceux
        └── python
            └── python


## Émulateurs NES à tester
    Fceux
    Mesen

## Documentation
    https://wiki.nesdev.com/
    http://jdc.koitsu.org/lj/Programmingthe65816_ProgManual.pdf
    https://www.cc65.org/doc/cc65.html

# EOF
