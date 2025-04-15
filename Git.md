# Git

## Commandes Git Essentielles

Voici quelques commandes Git essentielles. Pour plus de [ressources](https://www.jesuisundev.com/comprendre-git-en-7-minutes/), reportez-vous au site Git ou à la documentation de votre plate-forme de travail.

### Initialiser un dépôt

```sh
git init
```

Crée un dépôt Git local dans le dossier courant.

### Cloner un dépôt existant

```sh
git clone <URL-du-dépôt>
```

Copie un dépôt distant sur votre machine.

### Vérifier l’état des fichiers

```sh
git status
```

Affiche les changements, les nouveaux fichiers, etc.

### Suivre et enregistrer des modifications

```sh
git add <nom_fichier>  # ou git add .
git commit -m "Message de commit"
```

`git add .` ajoute tous les fichiers modifiés, puis `git commit -m` enregistre ces modifications localement.

### Pousser les changements vers un dépôt distant

```sh
git push
```

Envoie vos commits vers le serveur distant (ex. GitHub, GitLab).

### Récupérer les mises à jour depuis le dépôt distant

```sh
git pull
```

Récupère et fusionne les modifications du serveur vers votre copie locale.

## Petit Exercices en Ligne

Pour pratiquer vos compétences Git, nous vous recommandons de faire ces exercices interactifs en ligne : [Learn Git Branching](https://learngitbranching.js.org/).
