
# A faire avant le debut de la session pratique

## Mémo Important
**Avant la première session**, vérifiez impérativement les points suivants de ce document.

**Avertissement :**  
Ces installations peuvent prendre **beaucoup de temps**. **Ne les faites pas à la dernière minute** !  
Nous ne reviendrons pas en détail dessus durant la session pratique, mais des séances de permanences (heures de questions) sont prévues pour vous aider si nécessaire.

---

# 1. Configurer votre environnement

## 1.a. Windows (via WSL)

### Installer WSL :

Voir [wiki](https://wiki.student.info.ucl.ac.be/Logiciels/WSL).

### Ouvrir un terminal :

- Recherchez “Ubuntu” dans votre menu Démarrer ou utilisez l’application “Windows Terminal” (préinstallée sur Windows 11, ou téléchargeable depuis le Store).
- Sélectionnez votre distribution “Ubuntu” dans l’onglet ou le menu déroulant.

### Installer les paquets nécessaires :

**Mémo pour le terminal :**  
- Toutes les commandes mentionnées ci-dessous sont à taper (ou coller) directement dans votre terminal.  
- Pour coller dans la plupart des terminaux Linux/WSL, utilisez la combinaison **Ctrl+Shift+V** (au lieu de Ctrl+V).

```sh
sudo apt update
sudo apt install -y clang make libcunit1-dev git
```
#### Explications :

- `clang` : compilateur C.
- `make` : permet d’utiliser les Makefiles pour automatiser la compilation.
- `libcunit1-dev` : bibliothèque pour écrire des tests unitaires en C.

## 1.b Linux (distribution native)

### Ouvrir un terminal :

- Généralement déjà installé : recherchez “Terminal” dans votre environnement de bureau (GNOME, KDE, etc.) ou utilisez les raccourcis (par exemple, Ctrl+Alt+T sur Ubuntu).

### Installer les paquets nécessaires :

#### Sur Ubuntu/Debian ou dérivées :

```sh
sudo apt update
sudo apt install -y clang make libcunit1-dev git
```

## 1.c macOS

### Ouvrir un terminal :

- Ouvrez l’application “Terminal” (depuis “Launchpad” ou “Finder > Applications > Utilitaires”).

### Installer les outils de compilation :

Voir site [officiel](https://apps.apple.com/us/app/xcode/id497799835?mt=12).

### Installer Homebrew (si vous ne l’avez pas déjà) :

```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

- Suivez les instructions indiquées dans le terminal.

### Installer clang, make et CUnit via brew :

```sh
brew install llvm make cunit git
```

- Sur macOS, brew installera généralement LLVM (qui contient clang).

- Vous devrez peut-être configurer la variable d’environnement PATH pour pointer sur la bonne version de clang (Homebrew l’explique souvent en fin d’installation).

# 2. Test rapide de votre installation

Pour vérifier que tout est correctement configuré, vous pouvez compiler un “Hello World” minimal depuis n’importe quel dossier de travail :

### Créer un fichier test_hello.c

```sh
nano test_hello.c
```

Note: `nano` est un éditeur de texte en ligne de commande. Vous pouvez le remplacer par `vim`, `emacs` ou tout autre éditeur de texte de votre choix. Pour quitter `nano`, utilisez `Ctrl+X`, puis répondez `Y` pour sauvegarder les modifications.

### Copiez-y le code suivant :

```c
#include <stdio.h>

int main(void) {
    printf("Installation réussie!\n");
    return 0;
}
```

### Compilez :

```sh
clang test_hello.c -o test_hello
```

### Exécutez :

```sh
./test_hello
```

Vous devriez voir `Installation réussie!` s’afficher.

# 3. Cloner le dépôt des exercices

Si cela fonctionne, vous pouvez passer à la suite en (toute) confiance et [cloner](https://forge.uclouvain.be/lepl15031/students/practical-sessions/2024-2025/-/blob/main/README.md) le dépôt des exercices.

```sh
git clone https://forge.uclouvain.be/lepl15031/students/practical-sessions/2024-2025.git
```

