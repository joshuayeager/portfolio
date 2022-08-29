#!/usr/bin/env bash
# Directory to work in
DIR="/media/TV/"

# Renames each file in the current directory using the naming structure Exx
rename()
{
    local counter=1 # Set starting count
    local season="S01" # Set season default

    local current="${PWD##*/}" # Get current directory

    local parent="${PWD%/*}" # Get parent directory
    parent="${parent##*/}"

    local stop="${DIR%/*}" # Get top directory
    stop="${stop##*/}"

    if [[ "$current" == "S"* && "$parent" != "$stop" ]] # Checks if in season folder
    then
    season="$current"
  fi

  for i in *
  do
    if [[ "$i" == *.mkv ]] # Ignores non-mkv files
    then

      if [[ $counter -lt 10 ]] # Filters E0x vs Exx
      then
        mv "$i" "${season}E0${counter}.mkv"
      else
        mv "$i" "${season}E${counter}.mkv"
      fi

    counter=$((counter + 1)) # Iterates $counter
    fi
  done

  if [[ "$parent" != "$stop" ]] # Moves files into parent folder
  then
    mv *.mkv ..
    cd .. || die "cd .. FAILED!"
    rm -rf "$current"
  fi
}

# Main
cd $DIR || die "cd \$DIR FAILED!"

for j in * # Loop through series folders
do
  folders="F" # Whether or not current directory has folders
  cd "${DIR}${j}" || die "cd \${DIR}\${j} FAILED!"# cd into series folder
  echo "Renaming ${DIR}${j}..."
  for k in * # Check series folder for season folders
  do
    if [[ -d "${DIR}${j}/${k}" ]]
    then
      echo "Season folder detected: ${DIR}${j}/${k}"
      echo "Renaming and moving season into series folder ${DIR}${j}"
      folders="T"
      cd "$DIR${j}/${k}" || die "cd \${DIR}\${j}/\${k} FAILED!"
      rename
    fi
  done

  if [[ $folders == "F" ]] # If there are no season folders
  then
    rename
  fi
done
echo "Renaming complete. Enjoy watching!"
