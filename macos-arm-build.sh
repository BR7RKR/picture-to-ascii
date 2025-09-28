# To make script runnable write "chmod +x ./macos-arm-build.sh"

echo "[START BUILD]"

echo "> Installing dependencies"
brew install gcc libjpeg-turbo

echo "> Go to src"
cd src

echo "> Run make release"
make release

echo "> Test run with the --help flag"
./pictoascii --help

echo "> Pack console app"
tar czf pictoascii-macos-arm64.tar.gz pictoascii

echo "> Cleanup"
make clean

echo "[FINISH BUILD]"