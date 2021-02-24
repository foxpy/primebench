#!/bin/bash

if [ "$#" -ne 3 ]; then
  echo "Usage: $0 MEGABYTES NUMJOBS NUMTASKS" 1>&2
  exit 1
fi

numprimes="$(($1 * 1000 * 1000))"
numjobs="$2"
numtasks="$3"

mkdir -p tmp
cd tmp || exit
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j "$numjobs"
echo "Single thread speed:"
/usr/bin/time ./primes -q "--N=$numprimes"
echo "Multi thread speed:"
threaded_run() {
  numtasks="$1"
  numjobs="$2"
  numprimes="$3"
  for ((i=0; i<numtasks; i++)); do
    echo "$i"
  done | xargs -n 1 -P "$numjobs" ./primes -q "--N=$numprimes"
}
export -f threaded_run
/usr/bin/time bash -c "threaded_run $numtasks $numjobs $numprimes" --
cd .. || exit
rm -r tmp
