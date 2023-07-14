# README

## Install build tools

```sh
sudo apt install cmake clang build-essential gdb libxml2-dev libssl-dev
```

## Very simple profiling

```sh
ts=$(date +%s%N) ; cmake-build-debug-wsl/ticketswap ; tt=$((($(date +%s%N) - $ts)/1000000)) ; echo "Time taken: $tt milliseconds"
```

