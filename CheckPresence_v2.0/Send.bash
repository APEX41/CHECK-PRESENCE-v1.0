#!/bin/bash

echo " -------------------------------------------------"
echo "| -Veuillez entrer l'email de l'expéditeur :      |"
echo " -------------------------------------------------"
read -p "-> " exp
echo " -------------------------------------------------"
echo "| -Veuillez entrer l'email du destinataire :      |"
echo " -------------------------------------------------"
read -p "-> " dest
echo "-----------------------------------------------------"
read -p " Veuillez saisir l'objet du mail :  " obj
echo "-----------------------------------------------------"
echo "Veuillez saisir le corps de l'email : "
read -p "-> " corps

# Lecture sécurisée du mot de passe
echo "Veuillez entrer le mot de passe pour $exp (il ne s'affichera pas à l'écran) : "
read -s mdp

# Utilisation de sendemail pour envoyer l'email
sendemail -f $exp -t $dest -u "$obj" -m "$corps" -a ./check.csv -s smtp.gmail.com:587 -xu $exp -xp "$mdp" -o tls=yes -v

