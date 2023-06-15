#!/bin/bash

stage_worlds_path="/home/ofirhelerman/Downloads/Stage-4.3.0/worlds"

function run_stage() {
  answer=""
  echo "------------- run-stage script -------------"
  echo ""
  echo "The script will run with the following path:"
  echo " - stage_worlds_path: $stage_worlds_path"
  echo "Do you wish to continue? (y/n)"
  read -r answer
  if [[ "$answer" != "y" ]]; then
    echo "Exiting script"
    exit 1
  fi

  cd "$stage_worlds_path" || {
    echo "Invalid path: $stage_worlds_path"
    exit 1
  }

  echo "Running 'player rooms.cfg' in $stage_worlds_path"
  player rooms.cfg
}

function change_path() {
  echo "The current stage_worlds_path is set to: $stage_worlds_path"
  echo "Please enter an alternative path:"
  read -r new_path

  if [[ -d "$new_path" ]]; then
    stage_worlds_path="$new_path"
    echo "stage_worlds_path has been updated to: $stage_worlds_path"
  else
    echo "Invalid path: $new_path"
  fi
}

function main () {
  echo "Welcome to the script!"
  while true; do
    echo ""
    echo "Please select an option:"
    echo "1. Run stage"
    echo "2. Change path"
    echo "3. Exit"
    echo ""
    echo "Enter your choice (command number): "
    read -r option
    echo ""
    case $option in
      1)
        run_stage
        break
        ;;
      2)
        change_path
        ;;
      3)
        echo "Exiting script"
        exit 0
        ;;
      *)
        echo "Unrecognized option. Please try again."
        ;;
    esac
  done
}

main

