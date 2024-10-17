@echo off

REM Affiche le répertoire d'exécution du script (C:\allegro\project\)
echo %~dp0

REM Compilation avec Allegro
REM Chemin vers les fichiers d'en-têtes dans C:\allegro\include\allegro5 et les bibliothèques dans C:\allegro\lib
gcc %~dp0src/*.c -I"C:\allegro\include" -L"C:\allegro\lib" -lmingw32 -lallegro_monolith -o %~dp0exe/programme.exe

REM Vérifie si l'exécutable a été correctement généré avant de l'exécuter
if exist %~dp0exe/programme.exe (
    REM Exécution du programme compilé
    %~dp0exe/programme.exe
) else (
    echo Erreur lors de la compilation !
)

pause
