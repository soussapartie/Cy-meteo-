#!/bin/bash

#Déclaration des variables qui vont servir à vérifier les options entrées
start=`date +%s`        #On recupere l'heure du debut de l'execution du programme                        
f="0"                   #Variable permettant de savoir si l'option -f a été utilisé
t="0"                   #Variable permettant de savoir si l'option -t a été utilisé
p="0"                   #Variable permettant de savoir si l'option -p a été utilisé
h="0"                   #Variable permettant de savoir si l'option -h a été utilisé
m="0"                   #Variable permettant de savoir si l'option -m a été utilisé
w="0"                   #Variable permettant de savoir si l'option -w a été utilisé
lieu="0"                #Variable permettant de savoir si une option géograpghique a été utilisé
tri="0"                 #Variable permettant de savoir si de tri a été utilisé
date_debut="0"          #Variable permettant de savoir si l'option -d a été utilisé, si oui elle servira à contenir la date de début
#date_fin="0"            #Variable permettant de contenir la date de fin  p-e inutile 

verif_fichier() {       #Fonction qui vérifie que le fichier entré en paramètre existe, est lisible et exécutable.
  local file=$1
  if [ -e "$file" ]; then
    if [ ! -x "$file" ]; then
      echo "Error: $file is not executable."
      exit 12
    fi
    if [ ! -r "$file" ]; then
      echo "Error: $file is not readable."
      exit 13
    fi
  else
    echo "Error: $file does not exist."
    exit 11
  fi
}

verif_dates () {    #Fonction qui vérifie si les dates sont au bon format et si elles ne sont pas incohérentes (trop ancienne/dans le futur)
  if [[ $1 =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]] && [[ $2 =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]]; then
    now=$(date +%Y-%m-%d)
    limit_date="2000-01-01"
    if [[ "$1" > "$now" ]]; then
        echo "Error: Date 1 is in the future"
        exit 15
    elif [[ "$2" < "$limit_date" ]]; then
        echo "Error: Date 2 is too old"
        exit 16
    elif [[ "$2" > "$1" ]]; then
        return 0
    else
        echo "Error: The minimal date is more recent than or equal to the maximal date"
        exit 17
    fi
  else
    echo "Invalid dates format, please use YYYY-MM-DD"
    exit 14
  fi
}

if [[ ( $# < 1 ) ]];            #S'il n'y a pas d'argument on affiche un message d'erreur et on sort du programme
then
    echo "Error: Please enter arguments"
    exit 1
else
    while [[ $# -gt 0 ]]; do                #Parcours tous les arguments : si un argument est entré on enregistre sa présence, s'il est entré 2 fois on affiche un message d'erreur et sort du programme
        var="$1" # Stocker l'argument actuel
        case $var in
            "--help")
                echo "Bla bla bla faire liste d'aide" # ICI ECRIRE LE MANUEL D'UTILISATION L'AIDE
                exit 2
            ;;
            "-f")
                if [[ ( $f == "0" ) ]];
                then
                    f=$2    # variable $f contient nom du fichier csv contenant les données 
                    shift
                else
                    echo "Error: Argument passed several times in parameter"  # afficher erreur si l'argument est passé plusieurs fois en paramètre
                    exit 3
                fi
            ;;
            "-t") 
                echo "Error: Please add a mode (for example : -t2)"     # affiche erreur et sort du programme s'il n'y a pas de mode pour -t
                exit 4
            ;;
            "-p") 
                echo "Error: Please add a mode (for example : -p2)"     # affiche erreur et sort du programme s'il n'y a pas de mode pour -p
                exit 4
            ;;
            "-t1") 
                if [[ ( $t == "0" ) ]];
                then
                    t="1"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-t2") 
                if [[ ( $t == "0" ) ]];
                then
                    t="2"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-t3") 
                if [[ ( $t == "0" ) ]];
                then
                    t="3"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-p1") 
                if [[ ( $p == "0" ) ]];
                then
                    p="1"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-p2") 
                if [[ ( $p == "0" ) ]];
                then
                    p="2"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-p3") 
                if [[ ( $p == "0" ) ]];
                then
                    p="3"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-h") 
                if [[ ( $h == "0" ) ]];
                then
                    h="1"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-m") 
                if [[ ( $m == "0" ) ]];
                then
                    m="1"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-w") 
                if [[ ( $w == "0" ) ]];
                then
                    w="1"
                else
                    echo "Error: Argument passed several times in parameter"
                    exit 3
                fi
            ;;
            "-F") 
                if [[ ( $lieu == "0" ) ]];
                then
                    lieu="F"
                else
                    echo "Error: A location has already been selected"
                    exit 5
                fi
            ;;
            "-G") 
                if [[ ( $lieu == "0" ) ]];
                then
                    lieu="G"
                else
                    echo "Error: A location has already been selected"
                    exit 5
                fi
            ;;
            "-S") 
                if [[ ( $lieu == "0" ) ]];
                then
                    lieu="S"
                else
                    echo "Error: A location has already been selected"
                    exit 5
                fi
            ;;
            "-A") 
                if [[ ( $lieu == "0" ) ]];
                then
                    lieu="A"
                else
                    echo "Error: A location has already been selected"
                    exit 5
                fi
            ;;
            "-O") 
                if [[ ( $lieu == "0" ) ]];
                then
                    lieu="O"
                else
                    echo "Error: A location has already been selected"
                    exit 5
                fi
            ;;
            "-Q")  
                if [[ ( $lieu == "0" ) ]];
                then
                    lieu="Q"
                else
                    echo "Error: A location has already been selected"
                    exit 5
                fi
            ;;
            "-d") 
                if [[ ( $date_debut == "0" ) ]];
                then
                    date_debut=$2
                    shift
                    date_fin=$2
                    shift
                else
                    echo "Error: A date range has already been selected"
                    exit 6
                fi
            ;;
            "--tab") 
                if [[ ( $tri == "0" ) ]];
                then
                    tri="tab"
                else
                    echo "Error: A sorting mode is already selected"
                    exit 7
                fi
            ;;
            "--abr") 
                if [[ ( $tri == "0" ) ]];
                then
                    tri="abr"
                else
                    echo "Error: A sorting mode is already selected"
                    exit 7
                fi
            ;;
            "--avl") 
                if [[ ( $tri == "0" ) ]];
                then
                    tri="avl"
                else
                    echo "Error: A sorting mode is already selected"
                    exit 7
                fi
            ;;
            *)
                echo "Error: invalid argument"
                exit 8
            ;;
            esac 
        shift
    done

    if [[ ( $f == "0" ) ]];     # Verifie si -f est passé en paramètre si oui on continue sinon on stop le programme et affiche un message d'erreur
    then
        echo "Error: No file entered as parameter"
        exit 9
    else
        verif_fichier "$f"
    fi

    if [[ ( $t == "0" ) && ( $p == "0" ) && ( $w == "0" ) && ( $m == "0" ) && ( $h == "0" ) ]]; # Verifie si il y a au moins un -w/m/h/t/p passé en paramètre, si oui on continue sinon on stop le programme et affiche un message d'erreur
    then
        echo "Error: Please enter at least one argument for the data type (-t | -p | -w | -m | -h)"
        exit 10
    fi

    case $lieu in #On vérifie quelle restriction géographique a été choisie
            "F")
                awk -F ';' '$1 >= 7005 && $1 <= 7790 {print $0}' $f > lieu.csv  #On récupère les informations situé en France métropolitaine + Corse dans un nouveau fichier lieu.csv
            ;;
            "G")
                awk -F ';' '$1 >= 81401 && $1 <= 81415 {print $0}' $f > lieu.csv    #On récupère les informations situé en Guyane dans un nouveau fichier lieu.csv
            ;;
            "S")
                awk -F ';' '$1 == 71805 {print $0}' $f > lieu.csv   #On récupère les informations situé à ST PIERRE dans un nouveau fichier lieu.csv
            ;;
            "A")
                awk -F ';' '$1 >= 78890 && $1 <= 78925 {print $0}' $f > lieu.csv    #On récupère les informations situé au Antilles dans un nouveau fichier lieu.csv
            ;;
            "O")
                awk -F ';' '$1 >= 61968 && $1 <= 67005 {print $0}' $f > lieu.csv    #On récupère les informations situé dans l'Océan Indien dans un nouveau fichier lieu.csv
            ;;
            "Q")
                awk -F ';' '$1 == 89642 {print $0}' $f > lieu.csv   #On récupère les informations situé en Antarctique dans un nouveau fichier lieu.csv
            ;;
            *)
                cp $f lieu.csv  #S'il n'y a aucune restriction géographique on copie toutes les informations dans un nouveau fichier lieu.csv
            ;;
        esac 

    if [[ ( $date_debut != "0" ) ]]; #On vérifie si restriction temporelle a été choisie
    then 
        verif_dates "$date_debut" "$date_fin"   #S'il y en a une on appelle la fonction verif_dates pour vérifier que la saisie de l'utilisateur est bonne
        if [ $? -eq 0 ]; then
            awk -F ";" -v date_debut="$date_debut" -v date_fin="$date_fin" '($2 >= date_debut) && ($2 <= date_fin) {print $0}' lieu.csv > date.csv  #Lorsque la saisie est valide on applique la restriction au fichier lieu.csv puis on la transfert d'en un fichier date.csv
            rm lieu.csv     #le fichier lieu.csv n'est plus d'aucune utilité donc on le supprime
        fi
    else # sinon on renomme lieu.csv en date.csv
        mv lieu.csv date.csv
    fi

    if [[ ( $t == "1" ) ]];     #Si l'option -t1 est entrée on l'applique
    then
        awk -F\; '{
            arr[$1]+=$11
            if(!min[$1] || $11<min[$1]) {
                min[$1]=$11
            }
            if(!max[$1] || $11>max[$1]) {
                max[$1]=$11
            }
            count[$1]++
        } END {
            for(i in arr) {
                avg=arr[i]/count[i]
                printf("%s;%f;%f;%f\n",i,min[i],max[i],avg) >> "temp.csv"
            }
        }' date.csv
    elif [[ ( $t == "2" ) ]]; #Sinon si l'option -t2 est entrée on l'applique 
    then
        awk -F\; '{a[$2]+=$11;b[$2]++;c[$2]=$1} END {
            n=asorti(a, d);
            for (i=1;i<=n;i++) 
                print c[d[i]] ";" d[i] ";" a[d[i]]/b[d[i]];
        }' date.csv > temp.csv
    elif [[ ( $t == "3" ) ]];   #Sinon si l'option -t3 est entrée on l'applique 
    then
        sort -t\; -k1,1n -k2,2n date.csv | cut -d";" -f1,2,11 > temp.csv

    fi

    if [[ ( $p == "1" ) ]]; #Si l'option -p1 est entrée on l'applique 
    then
        awk -F\; '{
            arr[$1]+=$7
            if(!min[$1] || $7<min[$1]) {
                min[$1]=$7
            }
            if(!max[$1] || $7>max[$1]) {
                max[$1]=$7
            }
            count[$1]++
        } END {
            for(i in arr) {
                avg=arr[i]/count[i]
                printf("%s;%f;%f;%f\n",i,min[i],max[i],avg) >> "press.csv"
            }
        }' date.csv

    elif [[ ( $p == "2" ) ]];   #Sinon si l'option -p2 est entrée on l'applique 
    then
        awk -F\; '{a[$2]+=$7;b[$2]++;c[$2]=$1} END {
            n=asorti(a, d);
            for (i=1;i<=n;i++) 
                print c[d[i]] ";" d[i] ";" a[d[i]]/b[d[i]];
        }' date.csv > press.csv
    elif [[ ( $p == "3" ) ]];   #Sinon si l'option -p3 est entrée on l'applique 
    then
        sort -t\; -k1,1n -k2,2n date.csv | cut -d";" -f1,2,7 > press.csv
    fi

    if [[ ( $h == "1" ) ]];     #Si l'option -h est entrée on l'applique 
    then
        sort -t ";" -k14rn date.csv | cut -d";" -f1,14 > altitude.csv
    fi

    if [[ ( $m == "1" ) ]];     #Si l'option -m est entrée on l'applique 
    then
        cut -d';' -f1,6 date.csv | sort -k1,1 -k6,6nr | awk 'BEGIN{FS=";"} {if ($1!=p) {print $0; p=$1}}' > result.csv
        sort -t ";" -k2rn result.csv > humidite.csv
        rm result.csv
    fi

    if [[ ( $w == "1" ) ]];     #Si l'option -w est entrée on l'applique 
    then
        awk -F\; '{a[$1]+=$11;b[$1]+=$7;c[$1]++} END {for (i in a) print i ";" a[i]/c[i] ";" b[i]/c[i]}' date.csv | sort -t \; -k 1,1 > tmp.csv
        sort -t ";" -k1n tmp.csv > vent.csv
        rm tmp.csv
    fi
    rm date.csv
fi

end=`date +%s`  #On recupere l'heure à la fin de l'execution du programme
runtime=$((end-start)) #On soustrait l'heure de début à l'heure de fin et on obtient le temps d'execution du programme
echo "The execution time of the script was $runtime seconds"
exit 0