#!/bin/bash

set -e -x


VENV_PATH=./work/venv
MODULE=dbtraining

function init_venv() {
  if [ -d "${VENV_PATH}" ]; then
    echo "venv directory already exists... skipping creation..."
  else
    python -m venv "${VENV_PATH}"
    module_paths=$(find src -maxdepth 1 -type d -exec realpath {} \;)
    path_string=$(echo -e "${module_paths}" | tr "\n" ":")
    (
      echo ""
      echo "### Added by init_venv.sh"
      echo "export PYTHONPATH=${path_string}\$PYTHONPATH"
      echo ""
    ) >> "${VENV_PATH}/bin/activate"
    python -m pip install --upgrade pip
  fi
  export PYTHONPATH="${path_string}$PYTHONPATH"
  find src -iname requirements.txt | while read req
  do
    python -m pip install -r "${req}"
  done
}


function run_cmd() {
  CMD="${1}"
  cli_cmd="cli/${CMD}.py"
  shift
  source "${VENV_PATH}/bin/activate" || (echo "Can't find venv: ${VENV_PATH}"; exit 1)
  (
    cd "./src/${MODULE}" &&
    python "${cli_cmd}" $@
  ) || (echo "Can't find cli command: ${cli_cmd}"; exit 1)
}


if [ -z "${@}" ]; then
  init_venv
else
  MODULE=students
  run_cmd $@
fi
