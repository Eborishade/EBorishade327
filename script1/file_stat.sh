#Emmanuel Borishade
#Description: Bash shell script that lists all the files in a given directory
# along with their file sizes and last modification date.
#
#

#Test whether directory entered in $1
if [[ -z ${1} ]]; then 
    echo "You didn't enter an argument"
    
    #Ask for a directory
    read -p "Enter a directory : " dir

    #If does not exist, exit
    if [[ -z ${1} ]]; then 
        exit
    fi

    _new_dir=dir

else 
_new_dir=$1

fi


echo You entered _new_dir
_sub_dirs=$(find $_new_dir)

#Use Stat to find stats:
#stat %y prints time of last data mod %Y = time in seconds %s = size 
#stat --format=%s::%y [directory]

printf "Filename\t\t\t\tSize\tLast Modified\n==============================\t\t======\t===============\n" >> output.txt
#Looks like:
#Filename                                                Size    Last Modfified
#==============================                          ======  ===============

for _directory in $_sub_dirs;
 do 
    _size=$(stat --format=%s $_directory)
    _modded=$(stat --format=%y $_directory)

    #printf "$_directory $_size $_modded\n"
    printf "%-39s %6s %36s \n" "$_directory" "$_size" "$_modded" >> output.txt;

done

