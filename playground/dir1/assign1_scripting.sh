#!/usr/bin/env bash
echo Hello
echo ${0}
echo You entered $1
if [[ -z ${1} ]]; then
    echo "You didn't suppy an argument"
fi
echo ${PATH}
echo ${HOME}
my_dir=/usr/bin
# parameter expansion ${var_name}
echo "this is ${my_dir}/test a directory"

# command substitution
echo "Machine hardware name is $(uname -m)"
hardware_name=$(uname -m)
echo "Machine hardware name is $hardware_name"

echo "The hostname is $(uname -a | cut -d " " -f 2)"

printf "\tKernel Release:\t%s\t%s\n" $(uname -r) `uname -m`
