#This is the install script for fcalc under gpl3

#This script is perposefull not directly exicuitable,
#it is ment only to be used with the make file of fcalc

if [ ! -d $1 ]; then
    echo "Making dir $1"
    mkdir $1
fi

if [ ! -d $2 ]; then
    echo "Making dir $2"
    mkdir $2
fi

for file in "$@"
do
    if [ $file != $1 ]; then
        if [ $file != $2 ]; then
            if [ $file == "LICENSE" ]; then
                echo "copying: $file to $2/"
                cp $file $2/
            else
                echo "copying: $file to $1/"
                cp $file $1/
            fi
        fi
    fi
done
