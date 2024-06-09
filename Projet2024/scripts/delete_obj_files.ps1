
# SCRIPT POWERSHELL POUR WINDOWS

# Supprime les fichiers .obj qui sont generes par le programme c++
# (evite de supprimer les fichiers a la main avant chaque execution)

# ATTENTION : prendre en compte que le script est execute depuis le fichier main.cpp 
# Les chemins sont donc relatifs au fichier main.cpp

# Bruteforce
# $directory = "Tests\generated\BruteForce"
# Get-ChildItem $directory -Filter *.obj | Remove-Item -Force

# Recuit simule
#$directory = "Tests\generated\RecuitSimule"
#Get-ChildItem $directory -Filter *.obj | Remove-Item -Force

# Genetique
$directory = "Tests\generated\GeneticAlgo"
Get-ChildItem $directory -Filter *.obj | Remove-Item -Force
