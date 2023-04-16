
#!/bin/sh

# AUTHOR CREDIT DOES TO: https://github.com/catkin/catkin_tools/issues/551 user:https://github.com/ndepal

cd `catkin locate --workspace $(pwd)`

concatenated="build/compile_commands.json"

echo "[" > $concatenated

first=1
for d in build/*
do
    f="$d/compile_commands.json"

    if test -f "$f"; then
        if [ $first -eq 0 ]; then
            echo "," >> $concatenated
        fi

        cat $f | sed '1d;$d' >> $concatenated
    fi

    first=0
done

echo "]" >> $concatenated