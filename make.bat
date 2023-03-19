mkdir -p build
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o build\raptor.o sprites\raptor.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o build\MchBullet.o sprites\MchBullet.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o build\BravoW1GBC.o maps\BravoW1GBC.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o build\RaptorMapTilesGBC.o maps\RaptorMapTilesGBC.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o build\main.o src\main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wm-yn"Raptor" -Wm-yc -o main.gbc build\main.o build\raptor.o build\MchBullet.o build\BravoW1GBC.o build\RaptorMapTilesGBC.o
pause