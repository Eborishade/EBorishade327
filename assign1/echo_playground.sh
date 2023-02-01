echo Hello
echo $0
echo You entered $1
if [[ -z ${1} ]]; then 
    echo "You didn't enter an argument"

fi

echo path: ${PATH}
echo current program ${0}
echo
echo

echo creating var
new_var=this-is-it
echo $new_var

new_dir=/usr/bin
echo this $new_dir is a directory 
echo
echo running help...
help | grep ec

echo
echo
echo

#parameter expansion
echo this is $new_dir/test a directory expansion
#command substitution
echo "1 Machine hardware name is $(uname -m)"

hardware_name=$(uname -m)
echo "2 Machine hardware name is $hardware_name"

echo 3 machine hardware name is $hardware_name

echo "The hostname is $(uname -a)"
echo "The hostname cut is $(uname -a | cut -d " " -f 2)"

echo "\tKernal Release:\t%s\n" "$(uname -r)"
printf "\tKernal Release:\t%s\n" "$(uname -r)"
printf "\tKernal Release:\t%s\t%s\n" "$(uname -r) $(uname -m)"


num=3
#for $num in $num do $(find ..); done