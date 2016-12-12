# sturdy-happiness

Ce dépot ne se suffit pas à lui même :
pour l'instant c'est assez sale.

Il faut ajouter un dossier ./lib/ contenant les fichiers
- nes.lib (dans ftp://ftp.musoftware.de/pub/uz/cc65/cc65-nes-2.13.3-1.zip)
- c64.lib (dans ftp://ftp.musoftware.de/pub/uz/cc65/cc65-c64-2.13.3-1.zip)

Il faut ajouter un dossier ./tools/ contenant :
- un repertoire ./cc65/ contenant le compilateur obtenu comme suit
	- Créer un repertoire ./cc65/ dans le répertoire ./tools/
	- Dézipper ftp://ftp.musoftware.de/pub/uz/cc65/cc65-win32-2.13.3-1.zip
	- Placer les fichiers obtenus dans le repertoire ./cc65/
- un repertoire ./make/ contenant le programme make obtenu comme suit
	- Créer un repertoire ./make/ dans le répertoire tools/
	- Dézipper http://gnuwin32.sourceforge.net/downlinks/make-bin-zip.php
	- Placer les fichiers obtenus dans le repertoire ./make/
	- Dézipper http://gnuwin32.sourceforge.net/downlinks/make-dep-zip.php
	- Placer les fichiers obtenus dans le repertoire ./make/ en validant la fusion des dossiers

- Il faut créer un dossier ./compile/ vide.

Tout ceci est assez sale. Je l'arrangerai plus tard.