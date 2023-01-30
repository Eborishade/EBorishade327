#!/usr/bin/env bash

# assigning the output of the date command
# to a variable
gen_date=$(TZ="America/Chicago" date +"%D @ %r")

echo "System info for ${HOSTNAME}"
printf "\tKernel Release:\t%s\n" $(uname -r)
printf "\tBash Version:\t%s\n" "${BASH_VERSION}"
printf "\tFree Storage:\t%s\n" $(df -h / | sed -n 2p | awk '{print $4}')
printf "\tFree Memory:\t%s\n" $(free -h | grep "^Mem:" | awk '{print $4}')
printf "\tFiles in pwd:\t%s\n" $(ls | wc -l)

# Because the gen_date variable contains a string containing
# spaces it needs to be wrapped in quotes. Remove the quotes
# to see what happens.
printf "\tGenerated on:\t%s\n" "${gen_date}"