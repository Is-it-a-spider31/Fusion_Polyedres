
# SCRIPT POWERSHELL POUR WINDOWS

# Supprime les fichiers .obj qui sont generes par le projet cpp
# (evite de supprimer les fichiers a la main avant chaque execution)
$directory = "MergeTest\generated"  # Chemin du repertoire
Get-ChildItem $directory -Filter *.obj | Remove-Item -Force

$directory = "GeneticAlgorithm\generated"  # Chemin du repertoire
Get-ChildItem $directory -Filter *.obj | Remove-Item -Force
